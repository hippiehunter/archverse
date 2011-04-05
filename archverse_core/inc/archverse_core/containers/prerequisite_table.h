#ifndef ARCHVERSE_CORE_CONTAINERS_PREREQUISITE_TABLE
#define ARCHVERSE_CORE_CONTAINERS_PREREQUISITE_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\in_memory_database.h>
#include <archverse_core\structures\prerequisite.h>

#include <string>
#include <cstdint>

namespace archverse_core		
{
	class archverse_core_state;
	namespace structures
	{
		class tech;
	}
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::prerequisite*, 
			archverse_core::data_access::in_memory_database<archverse_core::structures::prerequisite*> > prerequisite_table_base_t;

		class prerequisite_table : public prerequisite_table_base_t
		{	
		public:
			prerequisite_table(archverse_core_state* archverseCoreState) : 
			  prerequisite_table_base_t("prerequisite", 0, archverseCoreState) { }

			std::uint32_t tech_requisite(archverse_core::structures::tech& requirement);
		};
	}
	
}

#endif