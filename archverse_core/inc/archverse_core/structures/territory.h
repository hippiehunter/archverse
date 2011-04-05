#ifndef ARCHVERSE_CORE_GAME_TERRITORY
#define ARCHVERSE_CORE_GAME_TERRITORY

#include <archverse_core\structures\control_model.h>
#include <archverse_core\structures\prerequisite.h>
#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\data_access\secondary_index_mapper.h>

#include <cstdint>
#include <vector>
#include <boost\assign.hpp>

namespace archverse_core
{
	namespace containers
	{
		class territory_table;
		class territory_list;
	}
	namespace structures
	{
		class player;
		class council;
		class project_list;


		struct territory_build_ratio : public archverse_core::data_access::reflective_record<territory_build_ratio>
		{
		public:
			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&territory_build_ratio::_factory, "Factory")
					(&territory_build_ratio::_researchLab, "ResearchLab")
					(&territory_build_ratio::_millitaryBase, "MillitaryBase")
					(&territory_build_ratio::_mine, "Mine")
					(&territory_build_ratio::_farm, "Farm")
					(&territory_build_ratio::_refinery, "Refinery")
					(&territory_build_ratio::_factoryLeftover, "FactoryLeftover")
					(&territory_build_ratio::_researchLabLeftover, "ResearchLabLeftover")
					(&territory_build_ratio::_millitaryBaseLeftover, "MillitaryBaseLeftover")
					(&territory_build_ratio::_mineLeftover, "MineLeftover")
					(&territory_build_ratio::_farmLeftover, "FarmLeftover")
					(&territory_build_ratio::_refineryLeftover, "RefineryLeftover");
			}
			char factory() const { return _factory; }
			void factory(char val) { _factory = val; }
			char research_lab() const { return _researchLab; }
			void research_lab(char val) { _researchLab = val; }
			char millitary_base() const { return _millitaryBase; }
			void millitary_base(char val) { _millitaryBase = val; }
			char mine() const { return _mine; }
			void mine(char val) { _mine = val; }
			char farm() const { return _farm; }
			void farm(char val) { _farm = val; }
			char refinery() const { return _refinery; }
			void refinery(char val) { _refinery = val; }
			char factory_leftover() const { return _factoryLeftover; }
			void factory_leftover(char val) { _factoryLeftover = val; }

			char farm_leftover() const { return _farmLeftover; }
			void farm_leftover(char val) { _farmLeftover = val; }
			char refinery_leftover() const { return _refineryLeftover; }
			void refinery_leftover(char val) { _refineryLeftover = val; }

			char research_lab_leftover() const { return _researchLabLeftover; }
			void research_lab_leftover(char val) { _researchLabLeftover = val; }
			char millitary_base_leftover() const { return _millitaryBaseLeftover; }
			void millitary_base_leftover(char val) { _millitaryBaseLeftover = val; }
			char mine_leftover() const { return _mineLeftover; }
			void mine_leftover(char val) { _mineLeftover = val; }
			territory_build_ratio()
			{
				_factory = 0;	
				_researchLab = 0;	
				_millitaryBase = 0;	
				_mine = 0;
				_farm = 0;
				_refinery = 0;

				_factoryLeftover = 0;
				_researchLabLeftover = 0;
				_millitaryBaseLeftover = 0;
				_mineLeftover = 0;
				_farmLeftover = 0;
				_refineryLeftover = 0;
			}

		private:
			char _factory;	
			char _researchLab;	
			char _millitaryBase;	
			char _mine;
			char _farm;
			char _refinery;

			char _factoryLeftover;
			char _researchLabLeftover;
			char _millitaryBaseLeftover;
			char _mineLeftover;
			char _farmLeftover;
			char _refineryLeftover;
		};

		class territory : public archverse_core::data_access::reflective_record<territory, 
			archverse_core::data_access::reflective_record_variant<territory, territory_build_ratio, control_model> >
		{
		public:
			typedef std::uint32_t index_t;
			static int owner_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey) 
			{ 
				return archverse_core::data_access::secondary_index_mapper<territory, uint32_t, &territory::_ownerId>(sdbp, pkey, pdata, skey);
			}
			
			static int region_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey) 
			{ 
				return archverse_core::data_access::secondary_index_mapper<territory, uint32_t, &territory::_regionId>(sdbp, pkey, pdata, skey);
			}
		public:
			enum territory_attribute
			{
				PA_LOST_TRABOTULIN_LIBRARY = 0,
				PA_COGNITION_AMPLIFIER,
				PA_MILITARY_STRONGHOLD,
				PA_ANCIENT_RUINS,
				PA_ARTIFACT,
				PA_MASSIVE_ARTIFACT,
				PA_ASTEROID,
				PA_MOON,
				PA_RADIATION,
				PA_SEVERE_RADIATION,
				PA_HOSTILE_MONSTER,
				PA_OBSTINATE_MICROBE,
				PA_BEAUTIFUL_LANDSCAPE,
				PA_BLACK_HOLE,
				PA_NEBULA,
				PA_DARK_NEBULA,
				PA_VOLCANIC_ACTIVITY,
				PA_INTENSE_VOLCANIC_ACTIVITY,
				PA_OCEAN,
				PA_IRREGULAR_CLIMATE,
				PA_MAJOR_SPACE_ROUTE,
				PA_MAJOR_SPACE_CROSSROUTE,
				PA_FRONTIER_AREA,
				PA_GRAVITY_CONTROLED,
				PA_SHIP_YARD,
				PA_MAINTENANCE_CENTER,
				PA_UNDERGROUND_CAVERNS,
				PA_RARE_ORE,
				PA_MOON_CLUSTER,
			};
			enum territory_size
			{
				SIZE_TINY = 0,
				SIZE_SMALL,
				SIZE_MEDIUM,
				SIZE_LARGE,
				SIZE_HUGE,
			};

			static const std::uint32_t STARTING_MILLITARY_BASES = 10;
			static const std::uint32_t STARTING_LABS = 10;
			static const std::uint32_t STARTING_MINES = 10;
			static const std::uint32_t STARTING_FACTORIES = 10;
			static const std::uint32_t STARTING_REFINERIES = 10;
			static const std::uint32_t STARTING_FARMS = 10;
			static const std::uint32_t BASE_WORKFORCE_FOR_BUILDING = 100;
			static const std::uint32_t BUILDING_CONSTRUCTION_COST = 100;

		private:
			std::uint32_t _id;
			std::uint32_t _ownerId;
			std::uint32_t _regionId;
			std::uint32_t _population;
			std::uint32_t _factories;
			std::uint32_t _mines;
			std::uint32_t _millitaryBases;
			std::uint32_t _researchLabs;
			std::uint32_t _farms;
			std::uint32_t _refineries;
			std::uint32_t _power;
			std::uint32_t _targetProjectId;
			std::uint32_t _projectCompletion; // 0 - 100 pct
			territory_build_ratio _buildRatio;
			control_model _controlModel;
			territory_size _size;
			std::string _name;
			std::vector<std::uint32_t> _attributes;
			std::vector<std::uint32_t> _projects;

			static std::string attribute_string(std::uint32_t attribute);
		public:

			territory(std::uint32_t id) 
			{ 
				_id = id; 
				_ownerId = 0;
				_regionId = 0;
				_population = 0;
				_factories = 0;
				_mines = 0;
				_millitaryBases = 0;
				_researchLabs = 0;
				_farms = 0;
				_refineries = 0;
				_power = 0;
				_targetProjectId = 0;
				_projectCompletion = 0;
				_size = static_cast<territory_size>(0);
				_name = "";
			}
			territory() { }

			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&territory::_id, "Id")
					(&territory::_ownerId, "OwnerId")
					(&territory::_regionId, "RegionId")
					(&territory::_population, "Population")
					(&territory::_factories, "Factories")
					(&territory::_mines, "Mines")
					(&territory::_millitaryBases, "MillitaryBases")
					(&territory::_researchLabs, "ResearchLabs")
					(&territory::_farms, "Farms")
					(&territory::_refineries, "Refineries")
					(&territory::_power, "Power")
					(&territory::_targetProjectId, "TargetProjectId")
					(&territory::_projectCompletion, "ProjectCompletion")
					(&territory::_buildRatio, "BuildRatio")
					(&territory::_controlModel, "ControlModel")
					(reinterpret_cast<std::uint32_t territory::* >(&territory::_size), "Size")
					(&territory::_name, "Name")
					(&territory::_attributes, "Attributes")
					(&territory::_projects, "Projects");
			}


			const std::string& name() const { return _name; }
			std::string size_string() const;
			std::string attributes_string() const;
			std::uint32_t owner_id() const { return _ownerId; }
			std::uint32_t id() const { return _id; }
			std::uint32_t region_id() const { return _regionId; }
			
			std::uint32_t value_for_prerequisite(prerequisite::requisite_type type, std::uint32_t argument) const;

			void unchecked_name(const std::string& name) { _name = name; }
			void unchecked_target_project_id(const std::uint32_t& projectId);
			void unchecked_owner_id(const std::uint32_t& id) { _ownerId = id; }
			void unchecked_update_build_ratio(char factories, char mines, char millitaryBases, char labs);
			void unchecked_update(council& ownerCouncil, player& owner, std::uint32_t turn);

			static std::uint32_t max_population_for_size(territory_size territorySize);
		};
	}
}


#endif //ARCHVERSE_CORE_GAME_TERRITORY