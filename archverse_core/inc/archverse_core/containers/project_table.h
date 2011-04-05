#ifndef ARCHVERSE_CORE_CONTAINERS_PROJECT_TABLE
#define ARCHVERSE_CORE_CONTAINERS_PROJECT_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\in_memory_database.h>
#include <archverse_core\structures\project.h>

#include <vector>
#include <cstdint>
#include <string>

namespace archverse_core
{
	class archverse_core_state;
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::project*, 
			archverse_core::data_access::in_memory_database<archverse_core::structures::project*> > project_table_base_t;

		class project_table : public project_table_base_t
		{
		public:
			project_table(archverse_core_state* archverseCoreState) : 
			  project_table_base_t("project_table", 0, archverseCoreState) {}

			archverse_core::structures::project* create_new_project(std::uint32_t rpCost, std::uint32_t ppCost, const std::string& name, const std::string& description, const std::vector<std::uint32_t>& prerequisites);
		};
	}
}

#endif