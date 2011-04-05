#ifndef ARCHVERSE_CORE_CONTAINERS_PLAYER_TABLE
#define ARCHVERSE_CORE_CONTAINERS_PLAYER_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\database_core.h>
#include <archverse_core\data_access\common_sequence_types.h>
#include <archverse_core\structures\player.h>

#include <string>
#include <cstdint>

namespace archverse_core		
{
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::player> player_table_base_t;

		class player_table : public player_table_base_t
		{	
		private:
			archverse_core::data_access::database_core<std::string, archverse_core::structures::player> _nameDB;
			archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::player> _councilIdDB;
			archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::player> _accountIdDB;
		public:
			player_table(environment_t* environment, archverse_core_state* archverseCoreState) : 
			  player_table_base_t("player", environment, archverseCoreState), 
				  _nameDB("player_name_index", environment, player_table_base_t::_dbBackend, &archverse_core::structures::player::name_mapper, true),
				  _councilIdDB("player_council_index", environment, player_table_base_t::_dbBackend, &archverse_core::structures::player::council_mapper),
				  _accountIdDB("player_account_index", environment, player_table_base_t::_dbBackend, &archverse_core::structures::player::account_mapper)
			  { }

			
			void get_by_account(const std::string& accountName, archverse_core::structures::player& destination);
			void get_by_name(const std::string& name, archverse_core::structures::player& destination);
			void get_by_auth_string(const std::string& authString, archverse_core::structures::player& destination);
			void create_new_player(const std::uint32_t userAccountId, const std::string& playerName,
				const std::uint32_t raceId, archverse_core::structures::player& destination);

			archverse_core::structures::player_sequence_t all_players(bool lock = false);
			archverse_core::structures::player_sequence_t by_council(std::uint32_t ownerId, bool lock = false);
		};
	}
	
}

#endif