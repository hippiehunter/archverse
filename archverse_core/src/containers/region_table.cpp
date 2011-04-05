#include <archverse_core\containers\region_table.h>
#include <archverse_core\containers\territory_table.h>

#include <boost\shared_ptr.hpp>
#include <vector>
#include <string>
#include <functional>
#include <boost\lexical_cast.hpp>

using std::vector;
using std::function;
using std::uint32_t;
using std::string;
using boost::shared_ptr;

using boost::lexical_cast;

using archverse_core::containers::region_table;
using archverse_core::containers::territory_table;

using archverse_core::structures::region;
using archverse_core::structures::region_sequence_t;

static const int PLACEMENT_MAX = 1000;

void region_table::random_region_for_placement(region& destination)
{
	vector<shared_ptr<region>> options;
	auto regionSequence = all_regions(false);

	std::copy_if(regionSequence.begin(), regionSequence.end(), back_inserter(options), [&](shared_ptr<region>& option) -> bool
	{
		auto territorySequence = option->territories(_archverseCoreState->territoryTable);
		return territorySequence.size() > PLACEMENT_MAX;
	});

	if(options.size() == 0)
		create_new_region(destination);
	else
	{
		srand(time(NULL));
		destination = *options[rand() % options.size()];
	}

}

void region_table::create_new_region(region& destination)
{
	create_new_entity([&](region& target)
	{
		target.unchecked_name(lexical_cast<string>(target.id()));
	});
}

region_sequence_t region_table::all_regions(bool locked)
{
	return region_sequence_t(&_dbBackend, locked);
}