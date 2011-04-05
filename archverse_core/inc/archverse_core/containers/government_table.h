#ifndef ARCHVERSE_CORE_CONTAINERS_GOVERNMENT_TABLE
#define ARCHVERSE_CORE_CONTAINERS_GOVERNMENT_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\in_memory_database.h>
#include <archverse_core\structures\government.h>

#include <string>
#include <cstdint>
#include <functional>

namespace archverse_core		
{
	class archverse_core_state;
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::government*, 
			archverse_core::data_access::in_memory_database<archverse_core::structures::government*> > government_table_base_t;

		class government_table : public government_table_base_t
		{	
		public:
			government_table(archverse_core_state* archverseCoreState) : 
			  government_table_base_t("government", 0, archverseCoreState) { }

			void availible_governments(const archverse_core::structures::player& player, std::function<bool (const archverse_core::structures::government&)> pred);
		};
	}
	
}

#endif