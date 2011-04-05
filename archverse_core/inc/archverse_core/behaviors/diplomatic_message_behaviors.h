#ifndef ARCHVERSE_CORE_BEHAVIORS_DIPLOMATIC_MESSAGE
#define ARCHVERSE_CORE_BEHAVIORS_DIPLOMATIC_MESSAGE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\structures\diplomatic_message.h>
#include <archverse_core\structures\relationship.h>

#include <cstdint>
#include <algorithm>

namespace archverse_core
{
	namespace containers
	{
		class diplomatic_message_table;
	}
	namespace behaviors
	{
		namespace diplomatic_message_behaviors
		{
			using std::uint32_t;
			using archverse_core::data_access::basic_entity_table;
			using archverse_core::containers::diplomatic_message_table;
			using archverse_core::structures::diplomatic_message;
			using archverse_core::structures::relationship;


			//creates the resulting relation_type for a given messageType
			//it is assumed that this method is being called on initiation of the relation
			//some relations must be accepted, others are created when the message is sent
			relationship::relation_type relation_for_message_type(diplomatic_message::message_type messageType)
			{
				switch(messageType)
				{
				case diplomatic_message::message_type::MT_DECLARE_WAR:
					return relationship::relation_type::RELATION_WAR;
				case diplomatic_message::message_type::MT_DECLARE_TOTAL_WAR:
					return relationship::relation_type::RELATION_TOTAL_WAR;
				case diplomatic_message::message_type::MT_DECLARE_HOSTILITIES:
					return relationship::relation_type::RELATION_HOSTILE;
				case diplomatic_message::message_type::MT_CANCEL_ALLIANCE:
					return relationship::relation_type::RELATION_NONE;
				case diplomatic_message::message_type::MT_CANCEL_TRADE:
					return relationship::relation_type::RELATION_NONE;
				case diplomatic_message::message_type::MT_OFFER_TRUCE:
					return relationship::relation_type::RELATION_TRUCE;
				case diplomatic_message::message_type::MT_OFFER_TRADE:
					return  relationship::relation_type::RELATION_TRADE;
				case diplomatic_message::message_type::MT_OFFER_ALLIANCE:
					return  relationship::relation_type::RELATION_ALLY;
				case diplomatic_message::message_type::MT_OFFER_SUBORDINATE:
					return  relationship::relation_type::RELATION_SUBORDINARY;
				default:
					return relationship::relation_type::RELATION_NONE;
				}
			}

			//T is intended to be player or council
			//DIPLOMATIC_STATE_SETTER is intended to be a method that takes the target, weather it initiated the relation and the relation itself
			//here we are using the variant that assumes the target is already loaded and locked
			template<typename T, typename DIPLOMATIC_STATE_SETTER>
			void send_message(diplomatic_message_table* table, basic_entity_table<T>* ttable, relationship_table* rTable, diplomatic_message& message)
			{
				ttable.locked_transaction(message._senderId, [](T& sender)
				{
					ttable.locked_transaction(message._targetId, [](T& target)
					{ 
						sender.messages([](diplomatic_message_list& messages) { messages.push_inbox(message.id()); });
						target.messages([](diplomatic_message_list& messages) { messages.push_sent(message.id()); });
						switch(message._type)
						{
						case relationship::relation_type::MT_DECLARE_WAR:
						case relationship::relation_type::MT_DECLARE_TOTAL_WAR:
						case relationship::relation_type::MT_DECLARE_HOSTILITIES:
						case relationship::relation_type::MT_CANCEL_ALLIANCE:
						case relationship::relation_type::MT_CANCEL_TRADE:
							relationship newRelationship;
							relation_type newRelationType = relation_for_message_type(message.type());
							rTable->create_new_relationship(message.sender_id(), message.target_id(), newRelationType, newRelationship);
							DIPLOMATIC_STATE_SETTER(sender, true, newRelationship);
							DIPLOMATIC_STATE_SETTER(target, false, newRelationship);
						}

					});

				});
			}
			//marks the given messageId as Read, additionaly checks to make sure the message is 
			//actualy owned by the given ownerId
			//T is intended to be player or council
			template<typename T>
			void read_message(diplomatic_message_table* table, basic_entity_table<T>* ttable, uint32_t messageId, uint32_t ownerId, diplomatic_message& destination)
			{
				
				const T owner = ttable->get_by_id(ownerId);
				owner.messages([](diplomatic_message_list& messages) 
				{ 
					if(messages.inbox_contains(messageId))
					{
						table->locked_transaction(messageId, [](diplomatic_message& message)
						{
							message.status(diplomatic_message::message_status::MS_READ);
							destination = message;
						});
					}
					else if(messages.send_contains(messageId))
					{
						destination = table->get_by_id(messageId);
					}
					else
					{
						throw runtime_error("target does not own this messageId");
					}
				});
			}

			//returns all of the diplomatic_messages marked as unread and owned by the target
			//T is intended to be player or council
			template<typename T>
			void new_messages(diplomatic_message_table* table, basic_entity_table<T>* ttable, uint32_t ownerId, vector<diplomatic_message>& messages)
			{
				diplomatic_message tmpMessage;
				T t = ttable->get_by_id(ownerId);
				t.messages([](diplomatic_message_list& messages) 
				{
					messages.iterate_inbox([](uint32_t messageId)
					{
						T t = table->get_by_id(messageId);
						if(t.status() == diplomatic_message::message_status::MS_UNREAD)
						{
							messages.push_back(t);
						}
					});
				});
			}

			//returns all the diplomatic_messages currently in the target outbox
			//T is intended to be player or council
			template<typename T>
			void sent_messages(diplomatic_message_table* table, basic_entity_table<T>* ttable, uint32_t ownerId, vector<diplomatic_message>& messages)
			{
				diplomatic_message tmpMessage;
				T t = ttable->get_by_id(ownerId);
				t.messages([](diplomatic_message_list& messages) 
				{
					messages.iterate_sent([](uint32_t messageId)
					{
						messages.push_back(table->get_by_id(messageId));
					});
				});
			}

			//returns all the diplomatic_messages currently in the target inbox
			//T is intended to be player or council
			template<typename T>
			void recived_messages(diplomatic_message_table* table, basic_entity_table<T>* ttable, uint32_t ownerId, vector<diplomatic_message>& messages)
			{
				diplomatic_message tmpMessage;
				T t = ttable->get_by_id(ownerId);
				t.messages([](diplomatic_message_list& messages) 
				{
					messages.iterate_inbox([](uint32_t messageId)
					{
						messages.push_back(table->get_by_id(messageId));
					});
				});
			}

			//some diplomatic messages leave outstanding offers to be accepted by the target, this is where those are finished
			//actions should be generated as well to leave record of what happens here
			//T is intended to be player or council
			template<typename T>
			void accept_offer(diplomatic_message_table* table, basic_entity_table<T>* ttable, uint32_t ownerId, uint32_t messageId, relationship_table& relationTable)
			{
				T t = ttable->get_by_id(ownerId);
				t.messages([](diplomatic_message_list& messages) 
				{
					if(messages.inbox_contains(messageId))
					{
						diplomatic_message message = table.get_by_id(messageId);
						if(message.type() != relationship::relation_type::MT_NORMAL)
						{
							relationship newRelationship;
							relation_type newRelationType = relation_for_message_type(message.type());
							rTable->create_new_relationship(message.sender_id(), message.target_id(), newRelationType, newRelationship);
							DIPLOMATIC_STATE_SETTER(sender, true, newRelationship);
							DIPLOMATIC_STATE_SETTER(target, false, newRelationship);
						}
						else
						{
							throw runtime_error("there is no offer to accept");
						}
					}
					else
					{
						throw runtime_error("target does not own this messageId");
					}

				}
			}
		}
	}
}

#endif