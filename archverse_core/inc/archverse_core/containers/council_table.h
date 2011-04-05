#ifndef ARCHVERSE_CORE_CONTAINERS_COUNCIL_TABLE
#define ARCHVERSE_CORE_CONTAINERS_COUNCIL_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\database_core.h>
#include <archverse_core\data_access\common_sequence_types.h>
#include <archverse_core\structures\council.h>

#include <string>
#include <cstdint>

namespace archverse_core		
{
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::council> council_table_base_t;

		class council_table : public council_table_base_t
		{	
		private:
			archverse_core::data_access::database_core<std::string, archverse_core::structures::council> _nameDB;
		public:
			council_table(environment_t* environment, archverse_core::archverse_core_state* archverseCoreState) : 
			  council_table_base_t("council", environment, archverseCoreState),
				  _nameDB("council_name_index", environment, _dbBackend, &archverse_core::structures::council::name_mapper) { }

			void get_by_name(const std::string& name, archverse_core::structures::council& destination);
			void create_new_council(const std::string& councilName, const std::string& motto, const std::uint32_t creatorId, archverse_core::structures::council& destination);
			
			void unchecked_random_council_assignment(archverse_core::structures::player& target, archverse_core::structures::council& destination);
			void random_council_assignment(const std::uint32_t playerId, archverse_core::structures::council& destination);

			void unverified_join_council(const std::uint32_t playerId, const std::uint32_t councilId);

			archverse_core::structures::council_sequence_t all_councils(bool lock = false);

		};
	}
	
}

#endif