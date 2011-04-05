#ifndef ARCHVERSE_CORE_CONTAINERS_TECH_LIST
#define ARCHVERSE_CORE_CONTAINERS_TECH_LIST

#include <archverse_core\data_access\basic_entity_list.h>
#include <archverse_core\structures\tech.h>
#include <archverse_core\containers\tech_table.h>

#include <vector>
#include <cstdint>
#include <string>

namespace archverse_core
{
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_list<archverse_core::structures::tech, tech_table> tech_list_base_t;
		class tech_list : public tech_list_base_t
		{
		public:
			tech_list(std::vector<std::uint32_t>& techs, tech_table* techTable) : 
			  tech_list_base_t(techs, techTable) {};
		};
	}
}

#endif