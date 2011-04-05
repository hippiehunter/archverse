#ifndef ARCHVERSE_CORE_GAME_PREREQUISITE
#define ARCHVERSE_CORE_GAME_PREREQUISITE

#include <cstdint>
#include <vector>
#include <string>
#include <functional>

namespace archverse_core
{
	namespace structures
	{
		class player;
		class territory;
		class ship_design;

		//this needs to be code based with composable helpers
		class prerequisite
		{
		public:
			enum requisite_operator
			{
				RO_GREATER = 0,
				RO_LESS,
				RO_EQUAL,
				RO_GREATER_EQUAL,
				RO_LESS_EQUAL,
				RO_NOT
			};

			enum requisite_type
			{
				RT_RACE = 0,
				RT_TERRITORY_COUNT,
				RT_TECH,
				RT_TECH_COUNT,
				RT_BUILDING_COUNT,
				RT_POWER,
				RT_RANK,
				RT_REGION,
				RT_COMMANDER_LEVEL,
				RT_FLEET,
				RT_COUNCIL_SIZE,
				RT_ORE,
				RT_FOOD,
				RT_ENERGY,
				RT_MP,
				RT_KP,
				RT_PP,
				RT_HAS_SHIP,
				RT_SHIP_POOL,
				RT_POPULATION,
				RT_GOVERNMENT_MODE,
				RT_TITLE,
				RT_COUNCIL_SPEAKER,
				RT_COUNCIL_WAR,
				RT_WAR_IN_COUNCIL,
				RT_VALOR,

				CM_POPULATION_GROWTH,
				CM_POPULATION_DENSITY,
				CM_LIFE_TECH_RESEARCH,
				CM_SOCIAL_TECH_RESEARCH,
				CM_INFO_TECH_RESEARCH,
				CM_MATTER_ENERGY_TECH_RESEARCH,
				CM_RACIAL_TECH_RESEARCH,
				CM_RESEARCH,
				CM_COMMAND_AND_CONTROL,
				CM_SHIP_PRODUCTION,
				CM_SHIP_STRENGTH,
				CM_MORALE,
				CM_SURVIVAL,
				CM_BERZERKER,
				CM_ADMIRALTY,
				CM_MINING,
				CM_PRODUCTION,
				CM_EFFICIANCY,
				CM_COMMERCE,
				CM_DIPLOMACY
			};
		private:
			std::uint32_t _id;
			requisite_type _requirement;
			requisite_operator _operator;
			std::uint32_t _amount;

		public:
			typedef std::uint32_t index_t;

			bool evaluate(const player& targetPlayer);
			bool evaluate(const territory& targetTerritory);
			bool evaluate(const ship_design& targetShipDesign);

		};
	}
}

#endif //ARCHVERSE_CORE_GAME_PREREQUISITE