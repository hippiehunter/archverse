#ifndef ARCHVERSE_CORE_GAME_NEWS
#define ARCHVERSE_CORE_GAME_NEWS

#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\data_access\secondary_index_mapper.h>

#include <cstdint>
#include <vector>
#include <string>

#include <boost\assign.hpp>

namespace archverse_core
{
	namespace structures
	{
		class news : public archverse_core::data_access::reflective_record<news>
		{
		private:
			std::uint64_t _id;
			std::uint32_t _turn;
			std::uint32_t _ownerId;
			std::string _title;
			std::string _body;
		public:
			typedef std::uint64_t index_t;

			static int owner_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey) 
			{ 
				return archverse_core::data_access::secondary_index_mapper<news, std::uint32_t, &news::_ownerId>(sdbp, pkey, pdata, skey);
			}

			news(std::uint32_t id) { _id = id; }
			news() { }

			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&news::_id, "Id")
					(&news::_turn, "Turn")
					(&news::_ownerId, "OwnerId")
					(&news::_title, "Title")
					(&news::_body, "Body");
			}

			std::uint64_t id() const { return _id; }
			std::uint32_t turn() const { return _turn; };
			std::uint32_t owner_id() const { return _ownerId; };
			const std::string& title() const { return _title; };
			const std::string& body() const { return _body; };

		};
	}
}

#endif //ARCHVERSE_CORE_GAME_NEWS