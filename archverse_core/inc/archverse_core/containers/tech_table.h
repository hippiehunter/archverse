#ifndef ARCHVERSE_CORE_CONTAINERS_TECH_TABLE
#define ARCHVERSE_CORE_CONTAINERS_TECH_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\in_memory_database.h>
#include <archverse_core\structures\tech.h>

#include <vector>
#include <cstdint>
#include <string>

namespace archverse_core
{
	class archverse_core_state;

	namespace structures
	{
		struct control_model;
	}

	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::tech*, 
			archverse_core::data_access::in_memory_database<archverse_core::structures::tech*> > tech_table_base_t;

		class tech_table : public tech_table_base_t
		{
		public:
			tech_table(archverse_core_state* archverseCoreState) : 
			  tech_table_base_t("tech_table", 0, archverseCoreState) {}
		
			bool create_new_tech(const std::string& name, const std::string& description, const std::string& category, 
				const std::uint32_t kpCost, const archverse_core::structures::control_model& modifiers);
		};
	}
}

#endif