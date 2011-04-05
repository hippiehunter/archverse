#ifndef ARCHVERSE_CORE_GAME_ADMIRAL
#define ARCHVERSE_CORE_GAME_ADMIRAL

#include <archverse_core\data_access\reflection_metadata.h>

#include <boost\assign.hpp>

#include <vector>
#include <string>
#include <cstdint>

class Db;
class Dbt;

namespace archverse_core
{
	namespace structures
	{
		class admiral : public archverse_core::data_access::reflective_record<admiral>
		{
			std::uint32_t _id;
			std::uint32_t _owner;
			std::uint32_t _race;
			std::uint32_t _level;
			std::uint32_t _experiance;
			std::string _name;
			std::vector<std::uint32_t> _attributes;
		public:
			typedef std::uint32_t index_t;

			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&admiral::_id, "Id")
					(&admiral::_owner, "Owner")
					(&admiral::_race, "Race")
					(&admiral::_level, "Level") 
					(&admiral::_experiance, "Experiance")
					(&admiral::_name, "Name")
					(&admiral::_attributes, "Attributes");
			}
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_ADMIRAL