#include <archverse_core\structures\council.h>
#include <archverse_core\containers\diplomatic_message_table.h>
#include <archverse_core\containers\relationship_table.h>
#include <archverse_core\containers\player_table.h>
#include <archverse_core\containers\admission_request_table.h>
#include <archverse_core\archverse_core_state.h>

using archverse_core::structures::council;
using archverse_core::structures::player_sequence_t;
using archverse_core::structures::relationship_sequence_t;
using archverse_core::structures::diplomatic_message_sequence_t;
using archverse_core::structures::admission_request_sequence_t;

using archverse_core::containers::diplomatic_message_table;
using archverse_core::containers::relationship_table;
using archverse_core::containers::player_table;
using archverse_core::containers::admission_request_table;


std::tuple<diplomatic_message_sequence_t, diplomatic_message_sequence_t> council::messages(diplomatic_message_table* diplomaticMessageTable, bool locked)
{
	return diplomaticMessageTable->by_owner(id(), locked);
}

std::tuple<relationship_sequence_t, relationship_sequence_t> council::relations(archverse_core::containers::relationship_table* relationshipTable, bool locked)
{
	return relationshipTable->by_owner(id(), locked);
}

player_sequence_t council::players(archverse_core::containers::player_table* playerTable, bool locked)
{
	return playerTable->by_council(id(), locked);
}

admission_request_sequence_t council::admission_requests(archverse_core::containers::admission_request_table* admissionRequestTable, bool locked)
{
	return admissionRequestTable->by_council(id(), locked);
}
			