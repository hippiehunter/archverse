#include <archverse_core\containers\game_event_table.h>


using archverse_core::containers::game_event_table;
using archverse_core::structures::game_event_sequence_t;

game_event_sequence_t game_event_table::by_owner(std::uint32_t ownerID, bool lock)
{
	return game_event_sequence_t(ownerID, &_ownerDB, lock);
}