#include <archverse_core\containers\relationship_table.h>

#include <cstdint>
#include <functional>

using std::tuple;

using std::uint32_t;
using std::function;

using archverse_core::containers::relationship_table;
using archverse_core::structures::relationship;

using archverse_core::structures::relationship_sequence_t;

void relationship_table::create_relationship(uint32_t member1, uint32_t member2, relationship::relation_type relationType, relationship& destination)
{
	create_new_entity([&](relationship& target)
	{
		target.unchecked_member1_id(member1);
		target.unchecked_member2_id(member2);
		target.unchecked_member_relation(relationType);
		destination = target;
	});
}

tuple<relationship_sequence_t, relationship_sequence_t>
	relationship_table::by_owner(uint32_t ownerId, bool lock)
{
	return tuple<relationship_sequence_t, relationship_sequence_t>
		(relationship_sequence_t(ownerId, &_member1IdDB, lock), 
		relationship_sequence_t(ownerId, &_member2IdDB, lock));
}
