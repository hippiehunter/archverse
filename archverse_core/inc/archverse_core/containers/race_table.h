#ifndef ARCHVERSE_CORE_CONTAINERS_RACE_TABLE
#define ARCHVERSE_CORE_CONTAINERS_RACE_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\in_memory_database.h>
#include <archverse_core\structures\race.h>

#include <vector>
#include <cstdint>
#include <string>

namespace archverse_core
{
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::race*, 
			archverse_core::data_access::in_memory_database<archverse_core::structures::race*> > race_table_base_t;

		class race_table : public race_table_base_t
		{
		public:
			race_table(archverse_core_state* archverseCoreState) : 
			  race_table_base_t("race_table", 0, archverseCoreState) {}
		};
	}
}

#endif