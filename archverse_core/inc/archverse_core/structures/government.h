#ifndef ARCHVERSE_CORE_GAME_GOVERNMENT
#define ARCHVERSE_CORE_GAME_GOVERNMENT

#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\structures\control_model.h>

#include <boost\assign.hpp>

#include <cstdint>
#include <vector>
#include <string>
#include <functional>

namespace archverse_core
{
	namespace containers
	{
		class prerequisite_list;
		class prerequisite_table;
	}
	namespace structures
	{
		class government : public archverse_core::data_access::reflective_record<government, archverse_core::data_access::reflective_record_variant<government, control_model> >
		{
		public:
			typedef std::uint32_t index_t;
		private:
			std::uint32_t _id;
			control_model _modifiers;
			std::vector<std::uint32_t> _spyOps;
			std::vector<std::uint32_t> _buildings;
			std::vector<std::uint32_t> _components;
			std::vector<std::uint32_t> _prerequisites;
			std::string _name;
			std::string _description;
			std::string _category;
		public:
			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&government::_id, "Id")
					(&government::_modifiers, "Modifiers")
					(&government::_spyOps, "SpyOps")
					(&government::_buildings, "Buildings")
					(&government::_components, "Components")
					(&government::_prerequisites, "Prerequisites")
					(&government::_name, "Name")
					(&government::_description, "Description")
					(&government::_category, "Category");
			}
			void prerequisites(std::function<void (archverse_core::containers::prerequisite_list&)>& destination, archverse_core::containers::prerequisite_table* prerequisiteTable);
		};
	}
}

#endif //ARCHVERSE_CORE_GOVERNMENT