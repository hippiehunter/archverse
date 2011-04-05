#include <archverse_core\containers\admission_request_table.h>

#include <cstdint>
#include <string>
#include <tuple>

using archverse_core::containers::admission_request_table;
using archverse_core::structures::admission_request;
using archverse_core::structures::admission_request_sequence_t;

using std::tuple;
using std::string;
using std::uint32_t;



void admission_request_table::create_new_admission_request(uint32_t councilId, uint32_t playerId, 
	const string& message, admission_request& destination)
{
	create_new_entity([&](admission_request& target)
	{
		target.unchecked_council_id(councilId);
		target.unchecked_player_id(playerId);
		target.unchecked_message(message);
		destination = target;
	});
}

admission_request_sequence_t
	admission_request_table::by_council(uint32_t ownerID, bool lock)
{
	return admission_request_sequence_t(ownerID, &_councilIdDb, lock);
}