#ifndef ARCHVERSE_CORE_CONTAINERS_PREREQUISITE_LIST
#define ARCHVERSE_CORE_CONTAINERS_PREREQUISITE_LIST

#include <archverse_core\data_access\basic_entity_list.h>
#include <archverse_core\containers\prerequisite_table.h>
#include <archverse_core\structures\prerequisite.h>

#include <vector>
#include <cstdint>

namespace archverse_core
{
	namespace structures
	{
		class player;
		class territory;
	}
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_list<archverse_core::structures::prerequisite> prerequisite_list_base_t;

		class prerequisite_list : public prerequisite_list_base_t
		{
		public:
			prerequisite_list(std::vector<std::uint32_t>& prerequisites, prerequisite_table* prerequisiteTable) : 
			  prerequisite_list_base_t(prerequisites, prerequisiteTable) {};

			bool evaluate(const archverse_core::structures::player& player) const;
			bool evaluate(const archverse_core::structures::territory& territory) const;
		};
	}
}

#endif