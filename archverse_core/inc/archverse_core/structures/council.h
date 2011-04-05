#ifndef ARCHVERSE_CORE_GAME_COUNCIL
#define ARCHVERSE_CORE_GAME_COUNCIL

#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\data_access\common_sequence_types.h>

#include <boost\assign.hpp>

#include <cstdint>
#include <vector>
#include <string>
#include <tuple>

class Db;
class Dbt;

namespace archverse_core
{
	class archverse_core_state;

	namespace containers
	{
		class admission_request_table;
		class relationship_table;
		class diplomatic_message_table;
		class player_table;
	}
	namespace structures
	{
		class player;
		class admission_request;
		class relationship;
		struct control_model;

		class council : public archverse_core::data_access::reflective_record<council>
		{
		public:
			typedef std::uint32_t index_t;
			static int name_mapper(Db *, const Dbt *, const Dbt *, Dbt *) { return 0; }
		private:
			std::uint32_t _id;
			std::uint32_t _speakerId;
			std::uint32_t _production;
			std::uint32_t _power;
			bool _acceptingNewPlayers;

			std::string _name;
			std::string _motto;
			static const std::uint32_t MAX_COUNCIL_SIZE = 20;
		public:
			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&council::_id, "Id")
					(&council::_speakerId, "SpeakerId")
					(&council::_production, "Production")
					(&council::_power, "Power") 
					(&council::_acceptingNewPlayers, "AcceptingNewPlayers")
					(&council::_motto, "Motto");
			}
			
			//simple utility constructor
			council(std::uint32_t id) { _id = id; }
			council() { }
			
			std::tuple<diplomatic_message_sequence_t, diplomatic_message_sequence_t> messages(archverse_core::containers::diplomatic_message_table* diplomaticMessageTable, bool locked = false);
			std::tuple<relationship_sequence_t, relationship_sequence_t> relations(archverse_core::containers::relationship_table* relationshipTable, bool locked = false);
			player_sequence_t players(archverse_core::containers::player_table* playerTable, bool locked = false);
			admission_request_sequence_t admission_requests(archverse_core::containers::admission_request_table* admissionRequestTable, bool locked = false);

			std::uint32_t id() { return _id; }
			const std::string& name() const { return _name; }
			std::uint32_t speaker_id() {return _speakerId; }
			bool accepting_new_players() const {return _acceptingNewPlayers; }
			
			void unchecked_motto(const std::string& motto) { _motto = motto; }
			void unchecked_name(const std::string& name) { _name = name; }
			void unchecked_speaker(std::uint32_t speakerId) { _speakerId = speakerId; }
			
			
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_COUNCIL