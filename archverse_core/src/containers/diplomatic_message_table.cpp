#include <archverse_core\containers\diplomatic_message_table.h>

#include <cstdint>
#include <string>
#include <tuple>

using archverse_core::containers::diplomatic_message_table;
using archverse_core::structures::diplomatic_message;
using archverse_core::structures::diplomatic_message_sequence_t;

using std::tuple;
using std::string;
using std::uint32_t;



void diplomatic_message_table::create_new_message(uint32_t senderId, uint32_t targetId, archverse_core::structures::diplomatic_message::message_type type, 
	const string& title, const string& body, archverse_core::structures::diplomatic_message& destination)
{
	create_new_entity([&](diplomatic_message& target)
	{
		target.unchecked_sender_id(senderId);
		target.unchecked_receiver_id(targetId);
		target.unchecked_type(type);
		target.unchecked_body(body);
		target.unchecked_title(title);
		destination = target;
	});
}

tuple<diplomatic_message_sequence_t, diplomatic_message_sequence_t>
	diplomatic_message_table::by_owner(uint32_t ownerID, bool lock)
{
	return tuple<diplomatic_message_sequence_t, diplomatic_message_sequence_t>
		(diplomatic_message_sequence_t(ownerID, &_senderIdDb, lock), 
		diplomatic_message_sequence_t(ownerID, &_receiverIdDb, lock));
}