#ifndef ARCHVERSE_CORE_GAME_EVENT
#define ARCHVERSE_CORE_GAME_EVENT

#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\data_access\secondary_index_mapper.h>

#include <boost\assign.hpp>

#include<vector>
#include<functional>
#include<string>
#include<cstdint>

namespace archverse_core
{
	namespace containers
	{
		class prerequisite_list;
	}
	namespace structures
	{
		class council;
		class player;
		struct control_model;

		class game_event : archverse_core::data_access::reflective_record<game_event>
		{
		public:
			typedef std::uint32_t index_t;

		private:
			std::uint32_t _id;
			std::uint32_t _owner;
			std::string _name;
			std::string _description;
			std::vector<uint32_t> _prerequisites;
		public:
			static int owner_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey) 
			{ 
				return archverse_core::data_access::secondary_index_mapper<game_event, uint32_t, &game_event::_owner>(sdbp, pkey, pdata, skey);
			}

			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&game_event::_id, "Id")
					(&game_event::_owner, "Owner")
					(&game_event::_name, "Name")
					(&game_event::_description, "Description")
					(&game_event::_prerequisites, "Prerequisites");
			}

			game_event() { }
			game_event(std::uint32_t id) { _id = id; }

			std::uint32_t id() const {return _id;}
			void prerequisites(std::function<void (archverse_core::containers::prerequisite_list&)>& destination);
			const std::string& name() const {return _name;}
			bool (*OnUpdateTurn)(council& council, player& player, control_model& controlModel);
		};
	}
}
#endif //ARCHVERSE_CORE_GAME_EVENT