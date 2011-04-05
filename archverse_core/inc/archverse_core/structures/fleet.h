#ifndef ARCHVERSE_CORE_GAME_FLEET
#define ARCHVERSE_CORE_GAME_FLEET

#include "system\ReflectionMetadata.h"
#include "game\Ship.h"

#include <vector>
#include <string>
#include <tuple>
#include <cstdint>
#include <boost\assign.hpp>

namespace archverse_core
{
	namespace game
	{
		using namespace archverse_core::System;
		using std::uint32_t;
		using boost::assign::tuple_list_of;
		using std::string;
		using std::vector;

		class Fleet : public ReflectiveRecord<Fleet>
		{
		public:
			enum FleetMissionType
			{
				FM_IDLE,
				FM_TRAIN,
				FM_EXPEDITION,
				FM_STATION,
				FM_BLOCKADE,
				FM_RAID,
				FM_PATROL
			};
		private:
			uint32_t _id;
			uint32_t _admiral;
			uint32_t _owner;
			uint32_t _attackFormation;
			uint32_t _defenseFormation;
			uint32_t _attackOrders;
			uint32_t _defenseOrders;
			FleetMissionType _currentMission;
			uint32_t _missionStartTurn;
			uint32_t _missionData;
			string _name;
			vector<Ship> _ships;
		public:
			static vector<ReflectiveRecordVariantPairType> __init_type_fields() throw()
			{
				return tuple_list_of<ReflectiveRecordVariantType, string>
					(&Fleet::_id, "Id")
					(&Fleet::_admiral, "Admiral")
					(&Fleet::_owner, "Owner") 
					(&Fleet::_attackFormation, "AttackFormation")
					(&Fleet::_defenseFormation, "DefenseFormation") 
					(&Fleet::_attackOrders, "AttackOrders") 
					(&Fleet::_defenseOrders, "DefenseOrders")
					//(&Fleet::_currentMission, "CurrentMission") 
					(&Fleet::_missionStartTurn, "MissionStartTurn")
					(&Fleet::_missionData, "MissionData")
					(&Fleet::_name, "Name");
					//(&Fleet::_ships, "Ships");
			}
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_FLEET