#ifndef ARCHVERSE_CORE_GAME_SHIPDESIGN
#define ARCHVERSE_CORE_GAME_SHIPDESIGN

#include"system\reflection_metadata.h"

#include<vector>
#include<string>
#include<cstdint>
#include<boost\assign.hpp>

namespace archverse_core
{
	namespace game
	{
		using std::string;
		using std::vector;
		using boost::assign::tuple_list_of;
		using std::uint32_t;
		using boost::tuple;
		using namespace archverse_core::system;

		class ship_design : public reflective_record<ship_design>
		{
		private:
			uint32_t _id;
			uint32_t _owner;
			uint32_t _hull;
			uint32_t _shield;
			uint32_t _computer;
			uint32_t _armor;
			uint32_t _currentPool;
			uint32_t _cost;
			string _name;
			vector<uint32_t> _weapons;
			vector<uint32_t> _devices;
		public:
			uint32_t Id() const {return _id;}
			uint32_t Owner() const {return _owner;}
			const string& Name() const {return _name;}
			uint32_t Cost() const {return _cost;}
			
			static vector<reflective_record_variant_pair_type> __init_type_fields() throw()
			{
				return tuple_list_of<reflective_record_variant_type, const string&>
					(&ship_design::_id, "Id")
					(&ship_design::_owner, "Owner")
					(&ship_design::_hull, "Hull")
					(&ship_design::_shield, "Shield") 
					(&ship_design::_computer, "Computer")
					(&ship_design::_armor, "Armor")
					(&ship_design::_currentPool, "CurrentPool")
					(&ship_design::_cost, "Cost")
					(&ship_design::_name, "Name")
					(&ship_design::_weapons, "Weapons")
					(&ship_design::_devices, "Devices");
			}
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_SHIPDESIGN