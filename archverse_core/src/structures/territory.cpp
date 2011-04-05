#include <archverse_core\structures\territory.h>
#include <archverse_core\structures\prerequisite.h>

#include <boost\algorithm\string.hpp>
#include <boost\iterator.hpp>
#include <boost\range.hpp>
#include <boost\range\algorithm.hpp>

#include <cstdint>
#include <string>
#include <stdexcept>

using archverse_core::structures::territory;
using archverse_core::structures::prerequisite;

using std::uint32_t;
using std::string;
using std::vector;
using std::runtime_error;

using boost::algorithm::join;
using boost::make_iterator_range;



std::string territory::size_string() const
{
	switch(_size)
	{
	case SIZE_TINY:
		return "tiny";
	case SIZE_SMALL:
		return "small";
	case SIZE_MEDIUM:
		return "medium";
	case SIZE_LARGE:
		return "large";
	case SIZE_HUGE:
		return "huge";
	default:
		throw runtime_error("bad territory size");
	}
}


std::string territory::attribute_string(uint32_t attribute)
{
	switch(attribute)
	{
	case PA_LOST_TRABOTULIN_LIBRARY:
		return "Lost Trabotulin Library";
	case PA_COGNITION_AMPLIFIER:
		return "Cognition Amplifier";
	case PA_MILITARY_STRONGHOLD:
		return "Military Stronghold";
	case PA_ANCIENT_RUINS:
		return "Ancient Ruins";
	case PA_ARTIFACT:
		return "Artifact";
	case PA_MASSIVE_ARTIFACT:
		return "Massive Artifact";
	case PA_ASTEROID:
		return "Astroid";
	case PA_MOON:
		return "Moon";
	case PA_RADIATION:
		return "Radiation";
	case PA_SEVERE_RADIATION:
		return "Severe Radiation";
	case PA_HOSTILE_MONSTER:
		return "Hostile Monster";
	case PA_OBSTINATE_MICROBE:
		return "Obstinate Microbe";
	case PA_BEAUTIFUL_LANDSCAPE:
		return "Beautiful Landscape";
	case PA_BLACK_HOLE:
		return "Black Hole";
	case PA_NEBULA:
		return "Nebula";
	case PA_DARK_NEBULA:
		return "Dark Nebula";
	case PA_VOLCANIC_ACTIVITY:
		return "Volcanic Activity";
	case PA_INTENSE_VOLCANIC_ACTIVITY:
		return "Intense Volcanic Activity";
	case PA_OCEAN:
		return "Ocean";
	case PA_IRREGULAR_CLIMATE:
		return "Irregular Climate";
	case PA_MAJOR_SPACE_ROUTE:
		return "Major Space Route";
	case PA_MAJOR_SPACE_CROSSROUTE:
		return "Major Space Cross-Route";
	case PA_FRONTIER_AREA:
		return "Frontier Area";
	case PA_GRAVITY_CONTROLED:
		return "Gravity Controlled";
	case PA_SHIP_YARD:
		return "Ship Yard";
	case PA_MAINTENANCE_CENTER:
		return "Maintenance Center";
	case PA_UNDERGROUND_CAVERNS:
		return "Underground Caverns";
	case PA_RARE_ORE:
		return "Rare Ore";
	case PA_MOON_CLUSTER:
		return "Moon Cluster";
	default:
		throw runtime_error("invalid territory attribute");
	}
}

std::string territory::attributes_string() const
{
	boost::iterator_range<vector<string>::iterator> itr;
	auto combinedAttributes = join(boost::transform(_attributes, itr, &territory::attribute_string), string(","));
}

std::uint32_t territory::value_for_prerequisite(prerequisite::requisite_type type, std::uint32_t argument) const
{
	return 0;
}