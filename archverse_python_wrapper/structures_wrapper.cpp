#include <archverse_core\structures\region.h>
#include <archverse_core\structures\player.h>
#include <archverse_core\structures\prerequisite.h>
#include <archverse_core\structures\relationship.h>
#include <archverse_core\structures\game_event.h>
#include <archverse_core\structures\news.h>
#include <archverse_core\structures\admission_request.h>
#include <archverse_core\structures\council.h>
#include <archverse_core\structures\user_account.h>
#include <archverse_core\structures\territory.h>
#include <archverse_core\structures\region.h>
#include <archverse_core\structures\diplomatic_message.h>
#include <archverse_core\data_access\common_sequence_types.h>

#include <boost\python.hpp>

#include <boost\shared_ptr.hpp>

using boost::shared_ptr;

using archverse_core::structures::player;
using archverse_core::structures::user_account;
using archverse_core::structures::territory;
using archverse_core::structures::council;
using archverse_core::structures::region;
using archverse_core::structures::diplomatic_message;
using archverse_core::structures::relationship;
using archverse_core::structures::news;
using archverse_core::structures::admission_request;
using archverse_core::structures::game_event;
using archverse_core::structures::prerequisite;

using archverse_core::structures::player_sequence_t;
using archverse_core::structures::territory_sequence_t;
using archverse_core::structures::council_sequence_t;
using archverse_core::structures::region_sequence_t;
using archverse_core::structures::diplomatic_message_sequence_t;
using archverse_core::structures::game_event_sequence_t;
using archverse_core::structures::news_sequence_t;
using archverse_core::structures::relationship_sequence_t;
using archverse_core::structures::admission_request_sequence_t;

void init_structures()
{
	using namespace boost::python;
    // map the Util namespace to a sub-module
    // make "from mypackage.Util import <whatever>" work
    object utilModule(handle<>(borrowed(PyImport_AddModule("archverse_core.structures"))));
    // make "from mypackage import Util" work
    scope().attr("structures") = utilModule;
    // set the current scope to the new sub-module
    scope util_scope = utilModule;
    // export stuff in the Util namespace

	class_<player_sequence_t>("player_sequence", no_init)
		.def("__iter__", range(&player_sequence_t::begin, &player_sequence_t::end))
		.def("__len__", &player_sequence_t::size)
		;

	class_<council_sequence_t>("council_sequence", no_init)
		.def("__iter__", range(&council_sequence_t::begin, &council_sequence_t::end))
		.def("__len__", &council_sequence_t::size)
		;

	class_<territory_sequence_t>("territory_sequence", no_init)
		.def("__iter__", range(&territory_sequence_t::begin, &territory_sequence_t::end))
		.def("__len__", &territory_sequence_t::size)
		;

	class_<region_sequence_t>("region_sequence", no_init)
		.def("__iter__", range(&region_sequence_t::begin, &region_sequence_t::end))
		.def("__len__", &region_sequence_t::size)
		;

	class_<diplomatic_message_sequence_t>("diplomatic_message_sequence", no_init)
		.def("__iter__", range(&diplomatic_message_sequence_t::begin, &diplomatic_message_sequence_t::end))
		.def("__len__", &diplomatic_message_sequence_t::size)
		;

	class_<game_event_sequence_t>("game_event_sequence", no_init)
		.def("__iter__", range(&game_event_sequence_t::begin, &game_event_sequence_t::end))
		.def("__len__", &game_event_sequence_t::size)
		;

	class_<news_sequence_t>("news_sequence", no_init)
		.def("__iter__", range(&news_sequence_t::begin, &news_sequence_t::end))
		.def("__len__", &news_sequence_t::size)
		;

	class_<relationship_sequence_t>("relationship_sequence", no_init)
		.def("__iter__", range(&relationship_sequence_t::begin, &relationship_sequence_t::end))
		.def("__len__", &relationship_sequence_t::size)
		;

	class_<admission_request_sequence_t>("admission_request_sequence", no_init)
		.def("__iter__", range(&admission_request_sequence_t::begin, &admission_request_sequence_t::end))
		.def("__len__", &admission_request_sequence_t::size)
		;
	

	class_<user_account, shared_ptr<user_account> >("user_account")
		.add_property("id", &user_account::id)
		.add_property("player_id", &user_account::player_id)
		.add_property("user_name", make_function(&user_account::user_name, return_value_policy<copy_const_reference>()))
		.def("is_password_hash", &user_account::is_password_hash)
		;


	class_<player, shared_ptr<player>>("player")
		.add_property("id", &player::id)
		.add_property("council_id", &player::council_id)
		.add_property("owner_id", &player::owner_id)
		.add_property("name", make_function(&player::name, return_value_policy<copy_const_reference>()))
		.add_property("turn", &player::turn)
		.add_property("council_vote", &player::council_vote)
		.add_property("tech_goal", &player::tech_goal)
		.def("owned_territories", &player::owned_territories)
		.def("current_news", &player::current_news)
		.def("events", &player::events)
		.def("relations", &player::relations)
		.def("value_for_prerequisite", &player::value_for_prerequisite)
		;

	class_<council, shared_ptr<council>>("council")
		.add_property("id", &council::id)
		.add_property("name", make_function(&council::name, return_value_policy<copy_const_reference>()))
		.add_property("speaker_id", &council::speaker_id)
		.add_property("accepting_new_players", &council::accepting_new_players)
		.def("players", &council::players)
		.def("messages", &council::messages)
		.def("relations", &council::relations)
		.def("admission_requests", &council::admission_requests)
		;

	class_<territory, shared_ptr<territory>>("territory")
		.add_property("name", make_function(&territory::name, return_value_policy<copy_const_reference>()))
		.add_property("size_string", &territory::size_string)
		.add_property("attributes_string", &territory::attributes_string)
		.add_property("owner_id", &territory::owner_id)
		.add_property("id", &territory::id)
		.add_property("region_id", &territory::region_id)
		.def("value_for_prerequisite", &territory::value_for_prerequisite)
		.def("max_population_for_size", &territory::max_population_for_size)
		.staticmethod("max_population_for_size")
		;

	class_<region, shared_ptr<region>>("region")
		.add_property("id", &region::id)
		.add_property("name", make_function(&region::name, return_value_policy<copy_const_reference>()))
		.def("territories", &region::territories)
		;

	class_<news, shared_ptr<news>>("news")
		.add_property("id", &news::id)
		.add_property("turn", &news::turn)
		.add_property("owner_id", &news::owner_id)
		.add_property("title", make_function(&news::title, return_value_policy<copy_const_reference>()))
		.add_property("body", make_function(&news::body, return_value_policy<copy_const_reference>()))
		;

	bool (prerequisite::*evaluatePlayer)(const player&) = &prerequisite::evaluate;
	bool (prerequisite::*evaluateTerritory)(const territory&) = &prerequisite::evaluate;

	class_<prerequisite, shared_ptr<prerequisite>>("prerequisite")
		.def("evaluate", evaluatePlayer)
		.def("evaluate", evaluateTerritory)
		;

	class_<diplomatic_message, shared_ptr<diplomatic_message>>("diplomatic_message")
		.add_property("status", &diplomatic_message::status)
		.add_property("id", &diplomatic_message::id)
		.add_property("sender_id", &diplomatic_message::sender_id)
		.add_property("target_id", &diplomatic_message::target_id)
		.add_property("message_type", &diplomatic_message::type)
		.add_property("message_body", make_function(&diplomatic_message::body, return_value_policy<copy_const_reference>()))
		.add_property("message_title", make_function(&diplomatic_message::title, return_value_policy<copy_const_reference>()))
		;

	enum_<diplomatic_message::message_status>("message_status")
		.value("Unread", diplomatic_message::MS_UNREAD)
		.value("Read", diplomatic_message::MS_READ)
		.value("Replied", diplomatic_message::MS_REPLIED)
		;

	enum_<diplomatic_message::message_type>("message_type")
		.value("Normal", diplomatic_message::MT_NORMAL)
		.value("DeclareWar", diplomatic_message::MT_DECLARE_WAR)
		.value("DeclareHostilities", diplomatic_message::MT_DECLARE_HOSTILITIES)
		.value("DeclareTotalWar", diplomatic_message::MT_DECLARE_TOTAL_WAR)
		.value("CancelAlliance", diplomatic_message::MT_CANCEL_ALLIANCE)
		.value("CancelTrade", diplomatic_message::MT_CANCEL_TRADE)
		.value("OfferTruce", diplomatic_message::MT_OFFER_TRUCE)
		.value("OfferTrade", diplomatic_message::MT_OFFER_TRADE)
		.value("OfferAlliance", diplomatic_message::MT_OFFER_ALLIANCE)
		.value("OfferSubordinate", diplomatic_message::MT_OFFER_SUBORDINATE)
		.value("RejectOffer", diplomatic_message::MT_REJECT_OFFER)
		;
}