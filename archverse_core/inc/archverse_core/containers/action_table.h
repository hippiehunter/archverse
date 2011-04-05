#ifndef ARCHVERSE_CORE_CONTAINERS_ACTION_TABLE
#define ARCHVERSE_CORE_CONTAINERS_ACTION_TABLE

#include <vector>
#include <cstdint>

#include <archverse_core\containers\action_list.h>
#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\database_core.h>

namespace archverse_core
{
	namespace containers
	{
		using archverse_core::data_access::basic_entity_table;
		using archverse_core::containers::action_list;

		using std::uint32_t;

		class action_table : public basic_entity_table<action_list>
		{
		public:
			action_table(environment_t* environment, archverse_core_state* archverseCoreState) : 
			  basic_entity_table<action_list>("action_table", environment, archverseCoreState) { } 
		};
		
	}
}
#endif