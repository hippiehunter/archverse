#ifndef ARCHVERSE_CORE_STRUCTURES_DIPLOMATIC_MESSAGE
#define ARCHVERSE_CORE_STRUCTURES_DIPLOMATIC_MESSAGE

#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\data_access\secondary_index_mapper.h>

#include <boost\assign.hpp>

#include <vector>
#include <string>
#include <cstdint>

namespace archverse_core
{
	namespace structures
	{
		class diplomatic_message : archverse_core::data_access::reflective_record<diplomatic_message>
		{
		public:
			typedef std::uint32_t index_t;

			enum message_status
			{
				MS_UNREAD,
				MS_READ,
				MS_REPLIED
			};
			enum message_type
			{
				MT_NORMAL,
				MT_DECLARE_WAR,
				MT_DECLARE_TOTAL_WAR,
				MT_DECLARE_HOSTILITIES,
				MT_CANCEL_ALLIANCE,
				MT_CANCEL_TRADE,
				MT_OFFER_TRUCE,
				MT_OFFER_TRADE,
				MT_OFFER_ALLIANCE,
				MT_OFFER_SUBORDINATE,
				MT_REJECT_OFFER
			};
		private:
			std::uint32_t _id;
			std::uint32_t _senderId;
			std::uint32_t _targetId;
			message_status _status;
			message_type _type;
			std::string _title;
			std::string _body;
		public:
			diplomatic_message() { } 
			diplomatic_message(std::uint32_t id) { _id = id; } 

			static int sender_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey) 
			{ 
				return archverse_core::data_access::secondary_index_mapper<diplomatic_message, uint32_t, &diplomatic_message::_senderId>(sdbp, pkey, pdata, skey);
			}
			static int receiver_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey) 
			{ 
				return archverse_core::data_access::secondary_index_mapper<diplomatic_message, uint32_t, &diplomatic_message::_targetId>(sdbp, pkey, pdata, skey);
			}

			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&diplomatic_message::_id, "Id")
					(&diplomatic_message::_senderId, "SenderId")
					(&diplomatic_message::_targetId, "TargetId")
					(reinterpret_cast<std::uint32_t diplomatic_message::* >(&diplomatic_message::_status), "Status")
					(reinterpret_cast<std::uint32_t diplomatic_message::* >(&diplomatic_message::_type), "Type")
					(&diplomatic_message::_title, "Title")
					(&diplomatic_message::_body, "Body");
			}

			
			message_status status() const { return _status; } 
			std::uint32_t id() const { return _id; }
			std::uint32_t sender_id() const { return _senderId; }
			std::uint32_t target_id() const { return _targetId; }
			message_type type() const { return _type; }
			const std::string& body() const { return _body; }
			const std::string& title() const { return _title; }

			void unchecked_status(message_status messageStatus) { _status = messageStatus; }
			void unchecked_sender_id(std::uint32_t senderId) { _senderId = senderId; }
			void unchecked_receiver_id(std::uint32_t targetId) { _targetId = targetId; }
			void unchecked_type(message_type type) { _type = type; }
			void unchecked_body(const std::string& body) { _body = body; }
			void unchecked_title(const std::string& title) { _title = title; }

		};
	}
}


#endif