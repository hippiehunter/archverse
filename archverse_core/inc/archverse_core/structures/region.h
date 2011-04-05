#ifndef ARCHVERSE_CORE_GAME_REGION
#define ARCHVERSE_CORE_GAME_REGION

#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\data_access\common_sequence_types.h>
#include <archverse_core\structures\territory.h>

#include <cstdint>
#include <vector>
#include <string>
#include <functional>
#include <boost\assign.hpp>

namespace archverse_core
{
	namespace containers
	{
		class territory_table;
	}
	namespace structures
	{
		class region : public archverse_core::data_access::reflective_record<region>
		{
		public:
			typedef std::uint32_t index_t;
		private:
			std::uint32_t _id;
			std::string _name;
			std::uint32_t _territoryCount;

		public:
			region(std::uint32_t id) { _id = id; }
			region() { }

			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&region::_id, "Id")
					(&region::_name, "Name");
			}

			std::uint32_t id() const {return _id;}
			const std::string& name() const {return _name;}
			territory_sequence_t territories(archverse_core::containers::territory_table* territoryTable, bool locked = false) const;
		
			void unchecked_name(std::string& name) { _name = name; }
		};
	}
}


#endif //ARCHVERSE_CORE_GAME_REGION