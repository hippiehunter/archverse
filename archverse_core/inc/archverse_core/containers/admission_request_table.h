#ifndef ARCHVERSE_CORE_CONTAINERS_ADMISSION_REQUEST_TABLE
#define ARCHVERSE_CORE_CONTAINERS_ADMISSION_REQUEST_TABLE

#include <vector>
#include <cstdint>

#include <archverse_core\structures\admission_request.h>
#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\database_core.h>
#include <archverse_core\data_access\common_sequence_types.h>

namespace archverse_core
{
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::admission_request> admission_request_table_base_t;

		class admission_request_table : public admission_request_table_base_t
		{
		private:
			archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::admission_request> _councilIdDb;
		public:
			admission_request_table(environment_t* environment, archverse_core_state* archverseCoreState) : 
			  admission_request_table_base_t("admission_request_table", environment, archverseCoreState),
			  _councilIdDb("admission_request_council_index", environment, admission_request_table_base_t::_dbBackend, &archverse_core::structures::admission_request::council_mapper)
			  { } 
			

			void create_new_admission_request(std::uint32_t councilId, std::uint32_t playerId, const std::string& message, archverse_core::structures::admission_request& destination);
		
			archverse_core::structures::admission_request_sequence_t by_council(std::uint32_t councilId, bool locked = false);
		};
		
	}
}
#endif