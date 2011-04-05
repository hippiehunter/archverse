#include <archverse_core\structures\region.h>
#include <archverse_core\containers\territory_table.h>

#include <functional>
#include <cstdint>

using std::uint32_t;
using std::function;

using archverse_core::structures::region;
using archverse_core::structures::territory;

using archverse_core::containers::territory_table;

using archverse_core::data_access::database_sequence;


database_sequence<region::index_t, territory> region::territories(archverse_core::containers::territory_table* territoryTable, bool locked) const
{
	return territoryTable->by_region(id(), locked);
}
		