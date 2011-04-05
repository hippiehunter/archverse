#ifndef ARCHVERSE_CORE_CONTAINERS_MESSAGE_TABLE
#define ARCHVERSE_CORE_CONTAINERS_MESSAGE_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\database_core.h>
#include <archverse_core\data_access\common_sequence_types.h>

#include <archverse_core\structures\diplomatic_message.h>

#include <cstdint>
#include <string>
#include <tuple>

namespace archverse_core
{
	class archverse_core_state;

	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::diplomatic_message> diplomatic_message_table_base_t;

		class diplomatic_message_table : public diplomatic_message_table_base_t
		{	
		private:
			  archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::diplomatic_message> _senderIdDb;
			  archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::diplomatic_message> _receiverIdDb;
		public:
			diplomatic_message_table(const std::string& name, environment_t* environment, archverse_core_state* archverseCoreState) : 
			  diplomatic_message_table_base_t(name, environment, archverseCoreState),
			  _senderIdDb(name + "diplomatic_message_sender_index", environment, diplomatic_message_table_base_t::_dbBackend, &archverse_core::structures::diplomatic_message::sender_mapper),
			  _receiverIdDb(name + "diplomatic_message_reciver_index", environment, diplomatic_message_table_base_t::_dbBackend, &archverse_core::structures::diplomatic_message::receiver_mapper) { }

			void create_new_message(std::uint32_t senderId, std::uint32_t targetId, archverse_core::structures::diplomatic_message::message_type type, 
				const std::string& title, const std::string& body, archverse_core::structures::diplomatic_message& destination);

			std::tuple<archverse_core::structures::diplomatic_message_sequence_t, archverse_core::structures::diplomatic_message_sequence_t>
				by_owner(std::uint32_t ownerID, bool lock = false);
		};
	}
}

#endif