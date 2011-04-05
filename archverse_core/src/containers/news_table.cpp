#include <archverse_core\containers\news_table.h>


using archverse_core::containers::news_table;
using archverse_core::structures::news_sequence_t;

news_sequence_t news_table::by_owner(std::uint32_t ownerID, bool lock)
{
	return news_sequence_t(ownerID, &_ownerDB, lock);
}