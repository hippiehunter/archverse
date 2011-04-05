#ifndef ARCHVERSE_CORE_GAME_PLAYER
#define ARCHVERSE_CORE_GAME_PLAYER

#include <archverse_core\structures\control_model.h>
#include <archverse_core\structures\prerequisite.h>
#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\data_access\secondary_index_mapper.h>
#include <archverse_core\data_access\common_sequence_types.h>

#include <vector>
#include <string>
#include <cstdint>
#include <time.h>
#include <functional>
#include <tuple>

#include <boost\assign.hpp>

class Db;
class Dbt;

namespace archverse_core
{
	class archverse_core_state;
	namespace containers
	{
		class tech_list;
		class action_list;
		class territory_table;
		class news_table;
		class game_event_table;
		class relationship_table;
		class action_table;
		class tech_table;
		class diplomatic_message_table;
	}
	namespace structures
	{
		class news;
		class game_event;
		class diplomatic_message;
		class territory;
		class council;
		class relationship;
		class player;

		typedef archverse_core::data_access::reflective_record<player, 
						archverse_core::data_access::reflective_record_variant<player, control_model> > player_base_t;

		class player : public player_base_t
		{
		public:
			typedef std::uint32_t index_t;
			static int name_mapper(Db *, const Dbt *, const Dbt *, Dbt *);
			static int council_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey) 
			{ 
				return archverse_core::data_access::secondary_index_mapper<player, uint32_t, &player::_council>(sdbp, pkey, pdata, skey);
			}
			static int account_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey) 
			{ 
				return archverse_core::data_access::secondary_index_mapper<player, uint32_t, &player::_userAccount>(sdbp, pkey, pdata, skey);
			}
		private:
			
			std::uint32_t _id;
			std::uint32_t _userAccount;
			std::uint32_t _valor;
			std::uint32_t _turn;
			std::uint32_t _tickPosition;
			std::uint32_t _currentMP; //Military Points
			std::uint32_t _currentKP; //Knowledge Points
			std::uint32_t _currentPP; //Production Points
			std::uint32_t _currentOre;
			std::uint32_t _currentFood;
			std::uint32_t _currentEnergy;
			std::uint32_t _lastTurnMP;
			std::uint32_t _lastTurnKP;
			std::uint32_t _lastTurnPP;
			std::uint32_t _lastTurnOre;
			std::uint32_t _lastTurnFood;
			std::uint32_t _lastTurnEnergy;
			std::uint32_t _council;
			std::uint32_t _government;
			std::uint32_t _race;
			std::uint32_t _techGoal;
			std::uint32_t _rank;
			std::uint32_t _councilVote;
			std::uint32_t _power;
			std::uint32_t _votePower;
			std::uint32_t _population;
			std::uint32_t _actionsId;
			std::uint32_t _targetSecurityLevel;
			std::uint32_t _currentSecurityLevel;
			bool _blockaded;
			time_t _blockTime;
			std::string _name;
			control_model _controlModel;
			
			
			std::vector<std::uint32_t> _abilities;
			std::vector<std::uint32_t> _knownTechs;
			std::vector<std::uint32_t> _events;
		public:
			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&player::_id, "Id")
					(&player::_userAccount, "UserAccountId")
					(&player::_valor, "Valor")
					(&player::_turn, "Turn")
					(&player::_tickPosition, "TickPosition")
					(&player::_currentMP, "CurrentMP")
					(&player::_currentKP, "CurrentKP")
					(&player::_currentPP, "CurrentPP")
					(&player::_currentOre, "CurrentOre")
					(&player::_currentFood, "CurrentFood")
					(&player::_currentEnergy, "CurrentEnergy")
					(&player::_lastTurnMP, "LastTurnMP")
					(&player::_lastTurnKP, "LastTurnKP")
					(&player::_lastTurnPP, "LastTurnPP")
					(&player::_lastTurnOre, "LastTurnOre")
					(&player::_council, "CouncilId")
					(&player::_government, "GovernmentId")
					(&player::_race, "RaceId")
					(&player::_techGoal, "TechGoalId")
					(&player::_rank, "Rank")
					(&player::_councilVote, "CouncilVote")
					(&player::_power, "Power")
					(&player::_votePower, "VotePower")
					(&player::_population, "Population")
					(&player::_actionsId, "ActionListId")
					(&player::_targetSecurityLevel, "TargetSecurityLevel")
					(&player::_currentSecurityLevel, "CurrentSecurityLevel")
					(&player::_blockaded, "Blockaded")
					(&player::_blockTime, "BlockTime")
					(&player::_name, "Name")
					(&player::_controlModel, "ControlModel")
					(&player::_abilities, "Abilities")
					(&player::_knownTechs, "KnownTechs")
					(&player::_events, "Events");

			}
			//simple utility constructor
			player(std::uint32_t id) 
			{ 
				_id = id;
				_userAccount = 0;
				_valor = 0;
				_turn = 0;
				_tickPosition = 0;
				_currentMP = 0;
				_currentKP = 0;
				_currentPP = 0;
				_currentOre = 0;
				_currentFood = 0;
				_currentEnergy = 0;
				_lastTurnMP = 0;
				_lastTurnKP = 0;
				_lastTurnPP = 0;
				_lastTurnOre = 0;
				_lastTurnFood = 0;
				_lastTurnEnergy = 0;
				_council = 0;
				_government = 0;
				_race = 0;
				_techGoal = 0;
				_rank = 0;
				_councilVote = 0;
				_power = 0;
				_votePower = 0;
				_population = 0;
				_actionsId = 0;
				_targetSecurityLevel = 0;
				_currentSecurityLevel = 0;
				_blockaded = false;
				_blockTime = 0;
				_name = "";
			}
			player() { }

			territory_sequence_t owned_territories(archverse_core::containers::territory_table* territoryTable, bool locked = false);
			std::tuple<diplomatic_message_sequence_t, diplomatic_message_sequence_t> messages(archverse_core::containers::diplomatic_message_table* messageTable, bool locked = false);
			
			std::tuple<relationship_sequence_t, relationship_sequence_t>
				relations(archverse_core::containers::relationship_table* relationshipTable, bool locked = false);
			//void known_techs(archverse_core::containers::tech_table* techTable);
			news_sequence_t current_news(archverse_core::containers::news_table* newsTable, bool locked = false);
			game_event_sequence_t events(archverse_core::containers::game_event_table* gameEventTable, bool locked = false);
			//void actions(archverse_core::containers::action_table* actionTable);

			std::uint32_t id() const { return _id; }
			std::uint32_t council_id() const { return _council; }
			std::uint32_t owner_id() const { return _council; }
			const std::string& name() const { return _name; }
			std::uint32_t turn() const {return _turn;}
			std::uint32_t council_vote() const { return _councilVote; }
			std::uint32_t tech_goal() const { return _techGoal; }

			void unchecked_council_id(std::uint32_t councilId) { _council = councilId; }
			void unchecked_name(const std::string& name) { _name = name; }
			void unchecked_account_id(std::uint32_t accountId) { _userAccount = accountId; }
			void unchecked_race(std::uint32_t raceId) { _race = raceId; }

			std::uint32_t value_for_prerequisite(prerequisite::requisite_type reqType, std::uint32_t argument) const;
			const archverse_core::structures::control_model& current_control_model() const {return _controlModel;}
			
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_PLAYER