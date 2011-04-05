#include <archverse_core\containers\council_table.h>
#include <archverse_core\structures\council.h>
#include <archverse_core\containers\player_table.h>
#include <archverse_core\archverse_core_state.h>
#include <archverse_core\structures\player.h>

#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include <boost\shared_ptr.hpp>
#include <boost\lexical_cast.hpp>

#include <stdlib.h>
#include <time.h>

using std::uint32_t;
using std::function;
using std::string;
using std::vector;
using boost::shared_ptr;

using boost::lexical_cast;

using archverse_core::containers::council_table;
using archverse_core::containers::player_table;

using archverse_core::structures::council;
using archverse_core::structures::player;

using archverse_core::structures::council_sequence_t;

void council_table::get_by_name(const string& name, council& destination)
{
	_nameDB.load_element(name, destination);
}

//empty council name auto generates a council name
void council_table::create_new_council(const string& councilName, const string& motto, const uint32_t creatorId, council& destination)
{
	create_new_entity([&](council& target)
	{
		if(councilName.size() != 0)
			target.unchecked_name(councilName);
		else
			target.unchecked_name("Council#" + lexical_cast<string>(target.id()));
		target.unchecked_motto(motto);
		target.unchecked_speaker(creatorId);

		unverified_join_council(creatorId, target.id());

		destination = target;
	});
}

void council_table::unchecked_random_council_assignment(archverse_core::structures::player& target, archverse_core::structures::council& destination)
{
	vector<shared_ptr<council>> options;
	auto councilSequence = all_councils(false);

	std::copy_if(councilSequence.begin(), councilSequence.end(), back_inserter(options), [&](shared_ptr<council>& option) -> bool
	{
		return option->accepting_new_players();
	});

	if(options.size() == 0)
		create_new_council("", "", target.id(), destination);
	else
	{
		srand(time(NULL));
		auto targetCouncil = options[rand() % options.size()];
		target.unchecked_council_id(targetCouncil->id());
		destination = *targetCouncil;
	}
}

void council_table::random_council_assignment(const uint32_t playerId, council& destination)
{
	_archverseCoreState->playerTable->locked_transaction(playerId, [&](player& target) -> bool
	{
		unchecked_random_council_assignment(target, destination);
		return true;
	});
}

void council_table::unverified_join_council(const uint32_t playerId, const uint32_t councilId)
{
	_archverseCoreState->playerTable->locked_transaction(playerId, [&](player& target) -> bool
	{
		target.unchecked_council_id(councilId);
		return true;
	});
}

council_sequence_t
	council_table::all_councils(bool lock)
{
	return council_sequence_t(&_dbBackend, lock);
}
