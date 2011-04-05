#include <archverse_core\archverse_core_state.h>

#include <archverse_core\structures\player.h>
#include <archverse_core\structures\territory.h>
#include <archverse_core\structures\region.h>

#include <archverse_core\containers\territory_table.h>
#include <archverse_core\containers\player_table.h>
#include <archverse_core\containers\region_table.h>

#include <archverse_core\data_access\common_sequence_types.h>

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

#include <boost\lexical_cast.hpp>

using std::uint32_t;
using std::string;
using std::vector;
using std::function;

using boost::lexical_cast;

using archverse_core::archverse_core_state;

using archverse_core::structures::territory;
using archverse_core::structures::player;
using archverse_core::structures::region;

using archverse_core::containers::territory_table;
using archverse_core::containers::player_table;

using archverse_core::structures::territory_sequence_t;

void territory_table::create_new_territory(uint32_t luckRoll, uint32_t ownerId, const region& containingRegion, territory& destination)
{
	create_new_entity([&](territory& target)
	{
		auto territorySequence = containingRegion.territories(this);

		target.unchecked_name(containingRegion.name() + "-" + lexical_cast<string>(territorySequence.size()));
		target.unchecked_owner_id(ownerId);

		destination = target;
	});
}

void territory_table::create_new_home_territory(uint32_t ownerId, uint32_t raceId, territory& destination)
{
	region homeRegion;
	_archverseCoreState->regionTable->random_region_for_placement(homeRegion);
	create_new_territory(50, ownerId, homeRegion, destination);
	//do racial terraforming and initial building / population counts
}

territory_sequence_t territory_table::by_owner(uint32_t ownerId, bool lock)
{
	return territory_sequence_t(ownerId, &_ownerDB, lock);
}

territory_sequence_t territory_table::by_region(uint32_t regionId, bool lock)
{
	return territory_sequence_t(regionId, &_regionDB, lock);
}