#ifndef ARCHVERSE_CORE_ARCHVERSE_CORE_STATE
#define ARCHVERSE_CORE_ARCHVERSE_CORE_STATE

#include <archverse_core\data_access\database_core.h>
#include <archverse_core\data_access\reflection_metadata.h>

#include <cstdint>
#include <functional>
#include <vector>
#include <string>
#include <boost\assign.hpp>

class DbEnv;

namespace archverse_core
{
	namespace structures
	{
		class player;
	}
	namespace containers
	{
		class user_account_table;
		class diplomatic_message_table;
		class relationship_table;
		class region_table;
		class territory_table;
		class player_table;
		class council_table;
		class admission_request_table;
		class race_table;
		class prerequisite_table;
		class tech_table;
		class component_table;
		class ship_design_table;
		class news_table;
		class project_table;
		class game_event_table;
		class fleet_table;
		class action_table;
		class admiral_table;
		class government_table;
		class region_list;
		class council_list;
	}
	class archverse_core_status;

	typedef archverse_core::data_access::reflective_record<archverse_core_status> archverse_core_status_base_t;
	class archverse_core_status : public archverse_core_status_base_t
	{
	public:
		std::uint32_t tick;
		std::uint32_t turn;
		std::uint32_t running;

		archverse_core_status()
		{
			tick = 0;
			turn = 0;
			running = 0;
		}

		static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
		{
			return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
				(&archverse_core_status::tick, "Tick")
				(&archverse_core_status::turn, "Turn")
				(&archverse_core_status::running, "Running");
		}
	};

	class archverse_core_state
	{
	private:
		DbEnv* _dbEnvironment;
		archverse_core::data_access::database_core<std::uint32_t, archverse_core_status>* _statusDb;
	public:
		archverse_core_state();
		~archverse_core_state();

		archverse_core::containers::user_account_table* userAccountTable;
		archverse_core::containers::diplomatic_message_table* playerMessageTable;
		archverse_core::containers::diplomatic_message_table* councilMessageTable;
		archverse_core::containers::relationship_table* playerRelationTable;
		archverse_core::containers::relationship_table* councilRelationTable;
		archverse_core::containers::region_table* regionTable;
		archverse_core::containers::territory_table* territoryTable;
		archverse_core::containers::player_table* playerTable;
		archverse_core::containers::council_table* councilTable;
		archverse_core::containers::admission_request_table* admissionTable;
		archverse_core::containers::race_table* raceTable;
		archverse_core::containers::prerequisite_table* prerequisiteTable;
		archverse_core::containers::tech_table* techTable;
		archverse_core::containers::component_table* componentTable;
		archverse_core::containers::ship_design_table* shipDesignTable;
		archverse_core::containers::news_table* newsTable;
		archverse_core::containers::project_table* projectTable;
		archverse_core::containers::game_event_table* eventTable;
		archverse_core::containers::fleet_table* fleetTable;
		archverse_core::containers::action_table* actionTable;
		archverse_core::containers::admiral_table* admiralTable;
		archverse_core::containers::government_table* governmentTable;

		std::uint32_t tick();

		bool running();
		void running(bool value);
		void add_ticks(std::uint32_t ticks);
	};
}

#endif