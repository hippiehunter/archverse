#include <archverse_core\archverse_core_state.h>
#include <archverse_core\data_access\database_core.h>
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

#include <cstdint>
#include <vector>
#include <string>
#include <boost\tuple\tuple.hpp>

using namespace archverse_core::containers;
using archverse_core::archverse_core_state;
using archverse_core::archverse_core_status;
using archverse_core::archverse_core_status_base_t;

using archverse_core::structures::player;
using archverse_core::structures::council;
using archverse_core::structures::region;

using archverse_core::data_access::database_core;
using archverse_core::data_access::database_sequence;


using std::uint32_t;
using std::vector;
using std::string;
using boost::tuple;

archverse_core_state::~archverse_core_state()
{
	delete _statusDb;
	delete userAccountTable;
	delete playerMessageTable;
	delete councilMessageTable;
	delete playerRelationTable;
	delete councilRelationTable;
	delete regionTable;
	delete territoryTable;
	delete playerTable;
	delete councilTable;
	delete admissionTable;
	delete raceTable;
	delete prerequisiteTable;
	delete techTable;
	delete newsTable;
	delete projectTable;
	delete eventTable;
	delete actionTable;
	//delete admiralTable;
	delete governmentTable;
	_dbEnvironment->close(0);
}

archverse_core_state::archverse_core_state()
{
	_dbEnvironment = new DbEnv(0);
	_dbEnvironment->open("data", DB_CREATE |  DB_INIT_MPOOL, 0);
	_statusDb = new database_core<std::uint32_t, archverse_core_status>("archverse_core_status", _dbEnvironment);
	userAccountTable = new archverse_core::containers::user_account_table(_dbEnvironment, this);
	playerMessageTable = new archverse_core::containers::diplomatic_message_table("player_message_table", _dbEnvironment, this);
	councilMessageTable = new archverse_core::containers::diplomatic_message_table("council_message_table", _dbEnvironment, this);
	playerRelationTable = new archverse_core::containers::relationship_table("player_relation_table", _dbEnvironment, this);
	councilRelationTable = new archverse_core::containers::relationship_table("council_relation_table", _dbEnvironment, this);
	regionTable = new archverse_core::containers::region_table(_dbEnvironment, this);
	territoryTable = new archverse_core::containers::territory_table(_dbEnvironment, this);
	playerTable = new archverse_core::containers::player_table(_dbEnvironment, this);
	councilTable = new archverse_core::containers::council_table(_dbEnvironment, this);
	admissionTable = new archverse_core::containers::admission_request_table(_dbEnvironment, this);
	raceTable = new archverse_core::containers::race_table(this);
	prerequisiteTable = new archverse_core::containers::prerequisite_table(this);
	techTable = new archverse_core::containers::tech_table(this);
	newsTable = new archverse_core::containers::news_table(_dbEnvironment, this);
	projectTable = new archverse_core::containers::project_table(this);
	eventTable = new archverse_core::containers::game_event_table(_dbEnvironment, this);
	actionTable = new archverse_core::containers::action_table(_dbEnvironment, this);
	//admiralTable = new admiral_table(_dbEnvironment, this);
	governmentTable = new archverse_core::containers::government_table(this);
}

uint32_t archverse_core_state::tick()
{
	archverse_core_status status;
	_statusDb->load_element(0, status);
	return status.tick;
}

bool archverse_core_state::running()
{
	archverse_core_status status;
	_statusDb->load_element(0, status);
	return status.running == 1;
}

void archverse_core_state::running(bool value)
{
	archverse_core_status status;
	_statusDb->load_element(0, status);

	status.running = value;

	_statusDb->save_element(0, status);
}

void archverse_core_state::add_ticks(uint32_t ticks)
{
	archverse_core_status status;
	_statusDb->load_element(0, status);

	status.tick += ticks;

	_statusDb->save_element(0, status);
}
