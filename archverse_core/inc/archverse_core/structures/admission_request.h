#ifndef ARCHVERSE_CORE_GAME_ADMISSIONREQUEST
#define ARCHVERSE_CORE_GAME_ADMISSIONREQUEST

#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\data_access\secondary_index_mapper.h>

#include <boost\assign.hpp>

#include<vector>
#include<string>
#include<cstdint>

class Db;
class Dbt;

namespace archverse_core
{
	namespace structures
	{
		class admission_request : public archverse_core::data_access::reflective_record<admission_request>
		{
		private:
			std::uint32_t _id;
			std::uint32_t _playerId;
			std::uint32_t _councilId;
			std::string _message;
		public:
			static int council_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey) 
			{ 
				return archverse_core::data_access::secondary_index_mapper<admission_request, uint32_t, &admission_request::_councilId>(sdbp, pkey, pdata, skey);
			}

			typedef std::uint32_t index_t;

			admission_request(std::uint32_t id) { _id = id; }
			admission_request() { }

			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&admission_request::_id, "Id")
					(&admission_request::_playerId, "PlayerId")
					(&admission_request::_councilId, "CouncilId")
					(&admission_request::_message, "Message");
			}
			std::uint32_t id() {return _id;}
			std::uint32_t player_id() {return _playerId;}
			std::uint32_t council_id() {return _councilId;}
			const std::string& message() {return _message; }

			void unchecked_council_id(std::uint32_t councilId) { _councilId = councilId; }
			void unchecked_player_id(std::uint32_t playerId) { _playerId = playerId; }
			void unchecked_message(const std::string& message) { _message = message; }

		};
	}
}
#endif