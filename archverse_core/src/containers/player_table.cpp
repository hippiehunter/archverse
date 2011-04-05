#include <archverse_core\containers\player_table.h>
#include <archverse_core\containers\territory_table.h>
#include <archverse_core\containers\council_table.h>
#include <archverse_core\containers\race_table.h>
#include <archverse_core\containers\user_account_table.h>

#include <archverse_core\structures\player.h>
#include <archverse_core\structures\territory.h>
#include <archverse_core\structures\council.h>

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

using std::uint32_t;
using std::string;
using std::vector;
using std::function;

using archverse_core::structures::player;
using archverse_core::structures::council;
using archverse_core::structures::user_account;
using archverse_core::structures::territory;
using archverse_core::structures::player_sequence_t;

using archverse_core::containers::territory_table;
using archverse_core::containers::council_table;
using archverse_core::containers::player_table;
using archverse_core::containers::race_table;


void player_table::get_by_account(const string& accountName, player& destination)
{
	user_account account;
	_archverseCoreState->userAccountTable->user_account_from_name(accountName, account);
	_accountIdDB.load_element(account.player_id(), destination);
}

void player_table::get_by_name(const string& name, player& destination)
{
	_nameDB.load_element(name, destination);
}

void player_table::get_by_auth_string(const string& authString, player& destination)
{
	user_account account;
	_archverseCoreState->userAccountTable->user_account_from_auth_string(authString, account);
	_accountIdDB.load_element(account.player_id(), destination);
}

void player_table::create_new_player(const uint32_t userAccountId, const string& playerName, const uint32_t raceId, player& destination)
{
	create_new_entity([&](player& target)
	{
		target.unchecked_account_id(userAccountId);
		target.unchecked_name(playerName);
		target.unchecked_race(raceId);

		_archverseCoreState->userAccountTable->locked_transaction(userAccountId, [&](user_account account) -> bool
		{
			account.unchecked_player_id(target.id());
			return true;
		});

		territory homeTerritory;
		_archverseCoreState->territoryTable->create_new_home_territory(target.id(), raceId, homeTerritory);

		council targetCouncil;
		_archverseCoreState->councilTable->unchecked_random_council_assignment(target, targetCouncil);

		destination = target;
	});


}

player_sequence_t
	player_table::by_council(uint32_t ownerID, bool lock)
{
	return player_sequence_t(ownerID, &_councilIdDB, lock);
}


player_sequence_t
	player_table::all_players(bool lock)
{
	return player_sequence_t(&_dbBackend, lock);
}