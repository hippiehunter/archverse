#ifndef ARCHVERSE_CORE_GAME_CONTROL_MODEL
#define ARCHVERSE_CORE_GAME_CONTROL_MODEL

#include <archverse_core\data_access\reflection_metadata.h>

#include <cstdint>
#include <vector>
#include <string>
#include <boost\assign.hpp>

namespace archverse_core
{
	namespace structures
	{
		struct control_model : archverse_core::data_access::reflective_record<control_model>
		{
		public:
			typedef std::uint32_t index_t;

			enum cm_type
			{
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

			 std::uint32_t _populationGrowth;
			 std::uint32_t _populationDensity;
			 std::uint32_t _lifeTechResearch;
			 std::uint32_t _socialTechResearch;
			 std::uint32_t _infoTechResearch;
			 std::uint32_t _matterEnergyTechResearch;
			 std::uint32_t _racialTechResearch;
			 std::uint32_t _research;
			 std::uint32_t _commandAndControl;
			 std::uint32_t _shipProduction;
			 std::uint32_t _shipStrength;
			 std::uint32_t _morale;
			 std::uint32_t _survival;
			 std::uint32_t _berzerker;
			 std::uint32_t _admiralty;
			 std::uint32_t _mining;
			 std::uint32_t _production;
			 std::uint32_t _efficiency;
			 std::uint32_t _commerce;
			 std::uint32_t _diplomacy; //mitigates jump timers and rule based restrictions

			 control_model& operator+=(control_model& target);

			 static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			 {
				return std::vector< boost::tuple<reflective_record_variant_type, std::string> >();
			 }
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_CONTROLMODEL