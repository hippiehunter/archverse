#ifndef ARCHVERSE_CORE_CONTAINERS_RELATIONSHIP_TABLE
#define ARCHVERSE_CORE_CONTAINERS_RELATIONSHIP_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\common_sequence_types.h>
#include <archverse_core\structures\relationship.h>

#include <string>
#include <cstdint>

#include <tuple>

namespace archverse_core
{
	class archverse_core_state;
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::relationship> relationship_table_base_t;

		class relationship_table : public relationship_table_base_t
		{
		private:
			archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::relationship> _member1IdDB;
			archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::relationship> _member2IdDB;
		public:
			relationship_table(const std::string& name, environment_t* environment, archverse_core::archverse_core_state* archverseCoreState) : 
			  relationship_table_base_t(name, environment, archverseCoreState),
			  _member1IdDB(name + "member1_index", environment, _dbBackend, &archverse_core::structures::relationship::member1_mapper),
			  _member2IdDB(name + "member2_index", environment, _dbBackend, &archverse_core::structures::relationship::member2_mapper){ }

			void create_relationship(std::uint32_t member1, std::uint32_t member2, archverse_core::structures::relationship::relation_type relationType, archverse_core::structures::relationship& destination);
			
			std::tuple<archverse_core::structures::relationship_sequence_t, archverse_core::structures::relationship_sequence_t>
				by_owner(std::uint32_t ownerId, bool lock = false);
		};
	}
}

#endif