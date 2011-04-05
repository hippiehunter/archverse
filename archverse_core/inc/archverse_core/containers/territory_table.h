#ifndef ARCHVERSE_CORE_CONTAINERS_TERRITORY_TABLE
#define ARCHVERSE_CORE_CONTAINERS_TERRITORY_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\database_core.h>
#include <archverse_core\structures\territory.h>
#include <archverse_core\data_access\common_sequence_types.h>

#include <string>
#include <cstdint>

namespace archverse_core
{
	namespace structures
	{
		class region;
	}
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::territory> territory_table_base_t;

		class territory_table : public territory_table_base_t
		{
		private:
			archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::territory> _ownerDB;
			archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::territory> _regionDB;
		public:
			territory_table(environment_t* environment, archverse_core::archverse_core_state* archverseCoreState) : 
			  territory_table_base_t("territory_table", environment, archverseCoreState), 
			  _ownerDB("territory_owner_index", environment, territory_table_base_t::_dbBackend, &archverse_core::structures::territory::owner_mapper),
			  _regionDB("territory_region_index", environment, territory_table_base_t::_dbBackend, &archverse_core::structures::territory::region_mapper)
			  { }
			  
			void create_new_territory(std::uint32_t luckRoll, std::uint32_t ownerId, const archverse_core::structures::region& containingRegion, archverse_core::structures::territory& destination);
			void create_new_home_territory(std::uint32_t ownerId, std::uint32_t raceId, archverse_core::structures::territory& destination);

			archverse_core::structures::territory_sequence_t by_owner(std::uint32_t ownerId, bool lock = false);
			archverse_core::structures::territory_sequence_t by_region(std::uint32_t regionId, bool lock = false);
		};
	}
}

#endif