#include <archverse_core\containers\council_table.h>
#include <archverse_core\containers\player_table.h>
#include <archverse_core\containers\news_table.h>
#include <archverse_core\containers\diplomatic_message_table.h>
#include <archverse_core\containers\region_table.h>
#include <archverse_core\containers\relationship_table.h>
#include <archverse_core\containers\territory_table.h>
#include <archverse_core\containers\user_account_table.h>

#include <boost\noncopyable.hpp>
#include <boost\python.hpp>

using archverse_core::containers::council_table;
using archverse_core::containers::player_table;
using archverse_core::containers::news_table;
using archverse_core::containers::diplomatic_message_table;
using archverse_core::containers::region_table;
using archverse_core::containers::relationship_table;
using archverse_core::containers::territory_table;
using archverse_core::containers::user_account_table;


void init_containers()
{
	using namespace boost::python;
    // map the Util namespace to a sub-module
    // make "from mypackage.Util import <whatever>" work
    object utilModule(handle<>(borrowed(PyImport_AddModule("archverse_core.containers"))));
    // make "from mypackage import Util" work
    scope().attr("containers") = utilModule;
    // set the current scope to the new sub-module
    scope util_scope = utilModule;
    // export stuff in the Util namespace

	class_<territory_table, boost::noncopyable>("territory_table", no_init)
		.def("create_new_territory", &territory_table::create_new_territory)
		.def("create_new_home_territory", &territory_table::create_new_home_territory)
		.def("by_owner", &territory_table::by_owner)
		.def("by_region", &territory_table::by_region)
		;

	class_<council_table, boost::noncopyable>("council_table", no_init)
		.def("get_by_name", &council_table::get_by_name)
		.def("create_new_council", &council_table::create_new_council)
		.def("random_council_assignment", &council_table::random_council_assignment)
		.def("all_councils", &council_table::all_councils)
		;

	class_<player_table, boost::noncopyable>("player_table", no_init)
		.def("get_by_account", &player_table::get_by_account)
		.def("get_by_name", &player_table::get_by_name)
		.def("create_new_player", &player_table::create_new_player)
		.def("all_players", &player_table::all_players)
		.def("by_council", &player_table::by_council)
		;

	class_<user_account_table, boost::noncopyable>("user_account_table", no_init)
		.def("user_account_from_auth_string", &user_account_table::user_account_from_auth_string)
		.def("user_account_from_name", &user_account_table::user_account_from_name)
		.def("login", &user_account_table::login)
		.def("create_user", &user_account_table::create_user)
		;

	class_<news_table, boost::noncopyable>("news_table", no_init)
		;

	class_<diplomatic_message_table, boost::noncopyable>("diplomatic_message_table", no_init)
		;

	class_<region_table, boost::noncopyable>("region_table", no_init)
		;

	class_<relationship_table, boost::noncopyable>("relationship_table", no_init)
		;

	

}