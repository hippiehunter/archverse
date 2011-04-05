#include <archverse_core\archverse_core_state.h>
#include <archverse_core\containers\user_account_table.h>
#include <archverse_core\containers\diplomatic_message_table.h>
#include <archverse_core\containers\relationship_table.h>
#include <archverse_core\containers\region_table.h>
#include <archverse_core\containers\territory_table.h>
#include <archverse_core\containers\player_table.h>
#include <archverse_core\containers\council_table.h>
#include <archverse_core\containers\admission_request_table.h>
#include <archverse_core\containers\race_table.h>
#include <archverse_core\containers\prerequisite_table.h>
#include <archverse_core\containers\tech_table.h>
#include <archverse_core\containers\news_table.h>
#include <archverse_core\containers\project_table.h>
#include <archverse_core\containers\game_event_table.h>
#include <archverse_core\containers\action_table.h>
#include <archverse_core\containers\admiral_table.h>
#include <archverse_core\containers\government_table.h>

#include <boost\python.hpp>

using archverse_core::archverse_core_state;


extern void init_structures();
extern void init_containers();

BOOST_PYTHON_MODULE(archverse_core)
{
	using namespace boost::python;

	object package = scope();
    package.attr("__path__") = "archverse_core";

	bool (archverse_core_state::*get_running)() = &archverse_core_state::running;
	void (archverse_core_state::*set_running)(bool) = &archverse_core_state::running;
	
	
	class_<archverse_core_state>("archverse_core_state")
        .add_property("userAccountTable", make_getter(&archverse_core_state::userAccountTable, return_value_policy<reference_existing_object>()))
		.add_property("playerMessageTable", make_getter(&archverse_core_state::playerMessageTable, return_value_policy<reference_existing_object>()))
		.add_property("councilMessageTable", make_getter(&archverse_core_state::councilMessageTable, return_value_policy<reference_existing_object>()))
		.add_property("playerRelationTable", make_getter(&archverse_core_state::playerRelationTable, return_value_policy<reference_existing_object>()))
		.add_property("councilRelationTable", make_getter(&archverse_core_state::councilRelationTable, return_value_policy<reference_existing_object>()))
		.add_property("regionTable", make_getter(&archverse_core_state::regionTable, return_value_policy<reference_existing_object>()))
		.add_property("territoryTable", make_getter(&archverse_core_state::territoryTable, return_value_policy<reference_existing_object>()))
		.add_property("playerTable", make_getter(&archverse_core_state::playerTable, return_value_policy<reference_existing_object>()))
		.add_property("councilTable", make_getter(&archverse_core_state::councilTable, return_value_policy<reference_existing_object>()))
		.add_property("admissionTable", make_getter(&archverse_core_state::admissionTable, return_value_policy<reference_existing_object>()))
		.add_property("raceTable", make_getter(&archverse_core_state::raceTable, return_value_policy<reference_existing_object>()))
		.add_property("prerequisiteTable", make_getter(&archverse_core_state::prerequisiteTable, return_value_policy<reference_existing_object>()))
		.add_property("techTable", make_getter(&archverse_core_state::techTable, return_value_policy<reference_existing_object>()))
		//.add_property("componentTable", make_getter(&archverse_core_state::componentTable, return_value_policy<reference_existing_object>()))
		//.add_property("shipDesignTable", make_getter(&archverse_core_state::shipDesignTable, return_value_policy<reference_existing_object>()))
		.add_property("newsTable", make_getter(&archverse_core_state::newsTable, return_value_policy<reference_existing_object>()))
		.add_property("projectTable", make_getter(&archverse_core_state::projectTable, return_value_policy<reference_existing_object>()))
		.add_property("eventTable", make_getter(&archverse_core_state::eventTable, return_value_policy<reference_existing_object>()))
		//.add_property("fleetTable", make_getter(&archverse_core_state::fleetTable, return_value_policy<reference_existing_object>()))
		.add_property("actionTable", make_getter(&archverse_core_state::actionTable, return_value_policy<reference_existing_object>()))
		//.add_property("admiralTable", make_getter(&archverse_core_state::admiralTable, return_value_policy<reference_existing_object>()))
		.add_property("governmentTable", make_getter(&archverse_core_state::governmentTable, return_value_policy<reference_existing_object>()))

        .def("tick", &archverse_core_state::tick)
		.def("add_ticks", &archverse_core_state::add_ticks)
    ;

	init_structures();
	init_containers();
}