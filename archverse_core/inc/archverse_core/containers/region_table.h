#ifndef ARCHVERSE_CORE_CONTAINERS_REGION_TABLE
#define ARCHVERSE_CORE_CONTAINERS_REGION_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\common_sequence_types.h>
#include <archverse_core\structures\region.h>

#include <string>
#include <cstdint>
#include <functional>

namespace archverse_core
{
	class archverse_core_state;
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::region> region_table_base_t;

		class region_table : public region_table_base_t
		{
		private:
			static const std::uint32_t STARTING_REGIONS = 10;

			void create_new_region(archverse_core::structures::region& destination);

		public:
			region_table(environment_t* environment, archverse_core_state* archverseCoreState) :
			region_table_base_t("region_table", environment, archverseCoreState) { }

			void random_region_for_placement(archverse_core::structures::region& destination);
			
			archverse_core::structures::region_sequence_t all_regions(bool locked = false);
		};
	}
}

#endif