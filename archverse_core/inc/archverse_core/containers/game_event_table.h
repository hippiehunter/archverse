#ifndef ARCHVERSE_CORE_CONTAINERS_GAME_EVENT_TABLE
#define ARCHVERSE_CORE_CONTAINERS_GAME_EVENT_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\common_sequence_types.h>
#include <archverse_core\structures\game_event.h>

#include <string>
#include <cstdint>

namespace archverse_core
{
	class archverse_core_state;
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::game_event> game_event_table_base_t;

		class game_event_table : public game_event_table_base_t
		{
		private:
			archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::game_event> _ownerDB;
		public:
			game_event_table(environment_t* environment, archverse_core_state* archverseCoreState) :
				game_event_table_base_t("game_event_table", environment, archverseCoreState),
				_ownerDB("game_event_owner_index", environment, _dbBackend, &archverse_core::structures::game_event::owner_mapper)
				{ }


			archverse_core::structures::game_event_sequence_t by_owner(std::uint32_t ownerID, bool lock = false);
				
		};
	}
}

#endif