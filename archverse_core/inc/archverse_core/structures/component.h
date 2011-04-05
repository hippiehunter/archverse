#ifndef ARCHVERSE_CORE_GAME_COMPONENT
#define ARCHVERSE_CORE_GAME_COMPONENT

#include "system\JSON\json_spirit.h"
#include "system\database_core.h"

#include<cstdint>
#include<vector>
#include<string>
#include<list>

namespace archverse_core
{
	namespace structures
	{
		using std::uint32_t;
		using std::vector;
		using std::string;
		using std::list;
		
		class Component
		{
		protected:
			uint32_t _id;
			string _name;
			string _description;
			vector<uint32_t> _prerequisites;
			vector<uint32_t> _designPrerequisites;
			uint32_t _cost;
			uint32_t _power;
			vector<uint32_t> _staticFleetEffect;
			vector<uint32_t> _dynamicFleetEffect;
		public:
			Component(const string& name, const string& description,
				const vector<uint32_t>& prerequisites, const vector<uint32_t>& designPrerequisites,
				uint32_t cost, uint32_t power, const vector<uint32_t>& staticFleetEffect, 
				const vector<uint32_t>& dynamicFleetEffect) : _name(name), _description(description), _prerequisites(prerequisites),
				_designPrerequisites(designPrerequisites), _cost(cost), _power(power), _staticFleetEffect(staticFleetEffect),
				_dynamicFleetEffect(dynamicFleetEffect) {}
		};

		class Weapon : public Component
		{
		public:
			enum WeaponType
			{
				WT_BEAM,
				WT_MISSILE,
				WT_PROJECTILE
			};
		private:
			WeaponType _weaponType;	//weapon type
			uint32_t _attackingRate;	//attacking rate
			uint32_t _damageRoll;	//roll
			uint32_t _damageDice;	//dice, damage=[roll]D[dice]
			uint32_t _space;			//space
			uint32_t _coolingTime;	//cooling time
			uint32_t _range;			//range
			uint32_t _angleOfFire;	//angle of fire, from hardpoint
			uint32_t _speed;			//speed, move distance per turn
			
		public:
			Weapon(const string& name, const string& description,
				const vector<uint32_t>& prerequisites, const vector<uint32_t>& designPrerequisites,
				uint32_t cost, uint32_t power, const vector<uint32_t>& staticFleetEffect, 
				const vector<uint32_t>& dynamicFleetEffect, WeaponType weaponType, uint32_t attackingRate, uint32_t damageRoll,
				uint32_t damageDice, uint32_t space, uint32_t coolingTime, uint32_t range, uint32_t angleOfFire, uint32_t speed) :
				Component(name, description, prerequisites, designPrerequisites, cost, power, staticFleetEffect,
					dynamicFleetEffect), _weaponType(weaponType), _attackingRate(attackingRate), _damageRoll(damageRoll),
					_damageDice(damageDice), _space(space), _coolingTime(coolingTime), _range(range), _angleOfFire(angleOfFire),
					_speed(speed) {}

			static string WeaponTypeString(WeaponType weaponType);
		};

		class Engine : public Component
		{
		private:
			uint32_t _battleSpeed;
			uint32_t _battleMobility;
			uint32_t _engineRecharge;
		public:
			Engine(const string& name, const string& description,
				const vector<uint32_t>& prerequisites, const vector<uint32_t>& designPrerequisites,
				uint32_t cost, uint32_t power, const vector<uint32_t>& staticFleetEffect, 
				const vector<uint32_t>& dynamicFleetEffect, uint32_t battleSpeed, uint32_t battleMobility,
				uint32_t engineRecharge) :
				Component(name, description, prerequisites, designPrerequisites, cost, power, staticFleetEffect,
					dynamicFleetEffect), _battleSpeed(battleSpeed), _battleMobility(battleMobility), _engineRecharge(engineRecharge) {}
		};

		class Shield : public Component
		{
		private:
			uint32_t _strength;	//amount of shield hp
			uint32_t _solidity; //amount of mitigated damage
			uint32_t _rechargeRate;
		public:
			Shield(const string& name, const string& description,
				const vector<uint32_t>& prerequisites, const vector<uint32_t>& designPrerequisites,
				uint32_t cost, uint32_t power, const vector<uint32_t>& staticFleetEffect, 
				const vector<uint32_t>& dynamicFleetEffect, uint32_t strength, uint32_t solidity, uint32_t rechargeRate) :
				Component(name, description, prerequisites, designPrerequisites, cost, power, staticFleetEffect,
					dynamicFleetEffect), _strength(strength), _solidity(solidity), _rechargeRate(rechargeRate) {}
		
		};

		class Device : public Component
		{
		public:
			Device(const string& name, const string& description,
				const vector<uint32_t>& prerequisites, const vector<uint32_t>& designPrerequisites,
				uint32_t cost, uint32_t power, const vector<uint32_t>& staticFleetEffect, 
				const vector<uint32_t>& dynamicFleetEffect) :
				Component(name, description, prerequisites, designPrerequisites, cost, power, staticFleetEffect,
					dynamicFleetEffect) {}
		};

		class Computer : public Component
		{
		private:
			uint32_t _attackRate;
			uint32_t _defenseRate;
			uint32_t _maxTargets;
		public:
			Computer(const string& name, const string& description,
				const vector<uint32_t>& prerequisites, const vector<uint32_t>& designPrerequisites,
				uint32_t cost, uint32_t power, const vector<uint32_t>& staticFleetEffect, 
				const vector<uint32_t>& dynamicFleetEffect, uint32_t attackRate, uint32_t defenseRate, uint32_t maxTargets) :
				Component(name, description, prerequisites, designPrerequisites, cost, power, staticFleetEffect,
					dynamicFleetEffect), _attackRate(attackRate), _defenseRate(defenseRate), _maxTargets(maxTargets) {}
		};
		
		class Armor : public Component
		{
		public:
			enum ArmorType
			{
				AT_NORM,
				AT_BIO,
				AT_REACTIVE
			};
		private:
			ArmorType _armorType;
			uint32_t _defenseRate;
			double _hpMultiplier;
		public:

			Armor(const string& name, const string& description,
				const vector<uint32_t>& prerequisites, const vector<uint32_t>& designPrerequisites,
				uint32_t cost, uint32_t power, const vector<uint32_t>& staticFleetEffect, 
				const vector<uint32_t>& dynamicFleetEffect, ArmorType armorType, uint32_t defenseRate, uint32_t hpMultiplier) :
				Component(name, description, prerequisites, designPrerequisites, cost, power, staticFleetEffect,
					dynamicFleetEffect), _defenseRate(defenseRate), _armorType(armorType), _hpMultiplier(hpMultiplier) {}
			
			static string ArmorTypeString(ArmorType armorType);
		};

		class ComponentTable
		{
		private:
			list<Weapon> _weapons;
			list<Device> _devices;
			list<Computer> _computers;
			list<Armor> _armors;
			list<Engine> _engines;

			vector<Component*> _components;
		public:
			uint32_t AddWeapon(Weapon& weapon);
			uint32_t AddDevice(Device& device);
			uint32_t AddComputer(Computer& computer);
			uint32_t AddArmor(Armor& armor);
			uint32_t AddEngine(Engine& engine);

			Component* ComponentFromId(uint32_t componentId);
		};

		class ComponentPresentation_JSON
		{
		private:
			static void WeaponOverview(Weapon* component, Object& destination);
			static void ShieldOverview(Shield* component, Object& destination);
			static void ArmorOverview(Armor* component, Object& destination);
			static void ComputerOverview(Computer* component, Object& destination);
			static void EngineOverview(Engine* component, Object& destination);
			static void DeviceOverview(Device* component, Object& destination);
			static void ComponentOverviewImpl(Component* component, Object& destination);
		public:
			static void ComponentOverview(Component* component, Object& destination);
		};
	}
}


#endif //ARCHVERSE_CORE_GAME_COMPONENT