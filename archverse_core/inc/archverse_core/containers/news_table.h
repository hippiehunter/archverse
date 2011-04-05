#ifndef ARCHVERSE_CORE_CONTAINERS_NEWS_TABLE
#define ARCHVERSE_CORE_CONTAINERS_NEWS_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\database_core.h>
#include <archverse_core\data_access\common_sequence_types.h>
#include <archverse_core\structures\news.h>

#include <string>
#include <cstdint>
#include <functional>

namespace archverse_core		
{
	class archverse_core_state;
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::news> news_table_base_t;

		class news_table : public news_table_base_t
		{	
		private:
			archverse_core::data_access::database_core<std::uint32_t, archverse_core::structures::news> _ownerDB;
		public:
			news_table(environment_t* environment, archverse_core_state* archverseCoreState) : 
			  news_table_base_t("news", environment, archverseCoreState), 
			  _ownerDB("news_owner_index", environment, news_table_base_t::_dbBackend, &archverse_core::structures::news::owner_mapper) { }


			  archverse_core::structures::news_sequence_t by_owner(std::uint32_t ownerID, bool lock = false);
		};
	}
	
}

#endif