#include <archverse_core\structures\player.h>
#include <archverse_core\structures\diplomatic_message.h>
#include <archverse_core\structures\news.h>
#include <archverse_core\structures\relationship.h>
#include <archverse_core\structures\game_event.h>
#include <archverse_core\structures\prerequisite.h>

#include <archverse_core\containers\tech_list.h>
#include <archverse_core\containers\action_list.h>

#include <archverse_core\containers\diplomatic_message_table.h>
#include <archverse_core\containers\territory_table.h>
#include <archverse_core\containers\news_table.h>
#include <archverse_core\containers\game_event_table.h>
#include <archverse_core\containers\relationship_table.h>

#include <archverse_core\archverse_core_state.h>

#include <string>
#include <cstdint>
#include <exception>
#include <stddef.h>
#include <tuple>

using archverse_core::archverse_core_state;
using archverse_core::containers::territory_table;
using archverse_core::containers::diplomatic_message_table;
using archverse_core::containers::relationship_table;
using archverse_core::containers::tech_list;
using archverse_core::containers::tech_table;
using archverse_core::containers::news_table;
using archverse_core::containers::game_event_table;
using archverse_core::containers::action_table;
using archverse_core::containers::game_event_table;

using archverse_core::structures::player;
using archverse_core::structures::territory;
using archverse_core::structures::game_event;
using archverse_core::structures::relationship;
using archverse_core::structures::diplomatic_message;
using archverse_core::structures::news;
using archverse_core::structures::player_base_t;
using archverse_core::structures::prerequisite;

using archverse_core::structures::territory_sequence_t;
using archverse_core::structures::diplomatic_message_sequence_t;
using archverse_core::structures::relationship_sequence_t;
using archverse_core::structures::news_sequence_t;
using archverse_core::structures::game_event_sequence_t;

using std::uint32_t;
using std::uint8_t;
using std::string;
using std::runtime_error;
using std::vector;

using boost::tuple;

territory_sequence_t
	player::owned_territories(archverse_core::containers::territory_table* territoryTable, bool locked)
{
	return territoryTable->by_owner(id(), locked);
}

std::tuple<diplomatic_message_sequence_t, diplomatic_message_sequence_t> 
	player::messages(archverse_core::containers::diplomatic_message_table* messageTable, bool locked)
{
	return messageTable->by_owner(id(), locked);
}

std::tuple<relationship_sequence_t, relationship_sequence_t>
	player::relations(archverse_core::containers::relationship_table* relationshipTable, bool locked)
{
	return relationshipTable->by_owner(id(), locked);
}

news_sequence_t
	player::current_news(archverse_core::containers::news_table* newsTable, bool locked)
{
	return newsTable->by_owner(id(), locked);
}

game_event_sequence_t
	player::events(archverse_core::containers::game_event_table* gameEventTable, bool locked)
{
	return gameEventTable->by_owner(id(), locked);
}

uint32_t player::value_for_prerequisite(prerequisite::requisite_type reqType, uint32_t argument) const
{
	switch(reqType)
	{
	case prerequisite::requisite_type::RT_RACE:
		return _race;
	case prerequisite::requisite_type::RT_TECH:
		if(find(_knownTechs.begin(), _knownTechs.end(), argument) != _knownTechs.end())
			return 1;
		else
			return 0;
	case prerequisite::requisite_type::RT_TECH_COUNT:
		return _knownTechs.size();
	case prerequisite::requisite_type::RT_BUILDING_COUNT:
		return 0;
	case prerequisite::requisite_type::RT_POWER:
		return _power;
	case prerequisite::requisite_type::RT_RANK:
		return _rank;
	case prerequisite::requisite_type::RT_REGION:
		return 0;
	case prerequisite::requisite_type::RT_COMMANDER_LEVEL:
		return 0;
	case prerequisite::requisite_type::RT_FLEET:
		return 0;
	case prerequisite::requisite_type::RT_ORE:
		return _currentOre;
	case prerequisite::requisite_type::RT_FOOD:
		return _currentFood;
	case prerequisite::requisite_type::RT_ENERGY:
		return _currentEnergy;
	case prerequisite::requisite_type::RT_MP:
		return _currentMP;
	case prerequisite::requisite_type::RT_KP:
		return _currentKP;
	case prerequisite::requisite_type::RT_PP:
		return _currentPP;
	case prerequisite::requisite_type::RT_HAS_SHIP:
		return 0;
	case prerequisite::requisite_type::RT_SHIP_POOL:
		return 0;
	case prerequisite::requisite_type::RT_POPULATION:
		return 0;
	case prerequisite::requisite_type::RT_GOVERNMENT_MODE:
		return _government;
	case prerequisite::requisite_type::RT_TITLE:
		return 0;
	case prerequisite::requisite_type::RT_COUNCIL_SPEAKER:
		return 0;
	case prerequisite::requisite_type::RT_COUNCIL_WAR:
		return 0;
	case prerequisite::requisite_type::RT_WAR_IN_COUNCIL:
		return 0;
	case prerequisite::requisite_type::RT_VALOR:
		return _valor;

	case prerequisite::requisite_type::CM_POPULATION_GROWTH:
		return _controlModel._populationGrowth;
	case prerequisite::requisite_type::CM_POPULATION_DENSITY:
		return _controlModel._populationDensity;
	case prerequisite::requisite_type::CM_LIFE_TECH_RESEARCH:
		return _controlModel._lifeTechResearch;
	case prerequisite::requisite_type::CM_SOCIAL_TECH_RESEARCH:
		return _controlModel._socialTechResearch;
	case prerequisite::requisite_type::CM_INFO_TECH_RESEARCH:
		return _controlModel._infoTechResearch;
	case prerequisite::requisite_type::CM_MATTER_ENERGY_TECH_RESEARCH:
		return _controlModel._matterEnergyTechResearch;
	case prerequisite::requisite_type::CM_RACIAL_TECH_RESEARCH:
		return _controlModel._racialTechResearch;
	case prerequisite::requisite_type::CM_RESEARCH:
		return _controlModel._research;
	case prerequisite::requisite_type::CM_COMMAND_AND_CONTROL:
		return _controlModel._commandAndControl;
	case prerequisite::requisite_type::CM_SHIP_PRODUCTION:
		return _controlModel._production;
	case prerequisite::requisite_type::CM_SHIP_STRENGTH:
		return _controlModel._shipStrength;
	case prerequisite::requisite_type::CM_MORALE:
		return _controlModel._morale;
	case prerequisite::requisite_type::CM_SURVIVAL:
		return _controlModel._survival;
	case prerequisite::requisite_type::CM_BERZERKER:
		return _controlModel._berzerker;
	case prerequisite::requisite_type::CM_ADMIRALTY:
		return _controlModel._admiralty;
	case prerequisite::requisite_type::CM_MINING:
		return _controlModel._mining;
	case prerequisite::requisite_type::CM_PRODUCTION:
		return _controlModel._production;
	case prerequisite::requisite_type::CM_EFFICIANCY:
		return _controlModel._efficiency;
	case prerequisite::requisite_type::CM_COMMERCE:
		return _controlModel._commerce;
	case prerequisite::requisite_type::CM_DIPLOMACY:
		return _controlModel._diplomacy;
	default:
		throw runtime_error("invalid prerequisite value");
	}
}

int player::name_mapper(	Db *sdbp,          // secondary db handle
		                const Dbt *pkey,   // primary db record's key
		                const Dbt *pdata,  // primary db record's data
		                Dbt *skey) 
{ 
	uint8_t* startOfName = reinterpret_cast<uint8_t*>(pdata->get_data()) + offsetof(player, _name);
	uint32_t nameLength = *reinterpret_cast<uint32_t*>(startOfName);
	startOfName += sizeof(uint32_t);
	if(nameLength > 0)
	{
		skey->set_data(startOfName);
		skey->set_size(nameLength);
		return 0;
	}
	else
		return DB_DONOTINDEX;
}
