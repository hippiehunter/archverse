#ifndef ARCHVERSE_CORE_GAME_SHIPHULL
#define ARCHVERSE_CORE_GAME_SHIPHULL

#include<vector>
#include<string>
#include<cstdint>

namespace archverse_core
{
	namespace game
	{
		using std::uint32_t;
		using std::uint8_t;
		using std::string;
		using std::vector;

		class ShipDesign;
		class ShipHullTable;
		class ShipHullList;

		struct WeaponSlot
		{
			enum WeaponSlotType
			{
				FIXED,
				TURRET
			};
		public:
			float _direction;
			WeaponSlotType _type;
			uint32_t _maxSize;
			static string WeaponTypeString(WeaponSlotType slotType);
		};
		class ShipHull
		{
			friend class ShipHullTable;
			friend class ShipHullList;
			friend class ShipHullPresentation_JSON;
		private:
			uint32_t _id;
			uint32_t _size; //in tonnes
			uint32_t _baseHp;
			uint32_t _baseShield;
			uint32_t _baseCost;
			string _name;
			string _description;
			vector<WeaponSlot> _weaponSlots;
			vector<uint32_t> _prerequisites;
		public:
			uint32_t Id() const {return _id;}
			const string& Name() const {return _name;}
			
		};

		class ShipHullTable
		{
		public:
			const ShipHull& ShipHullFromId(uint32_t id);
			bool ValidateShipDesignForHull(ShipDesign& shipDesign);
		};

		class ShipHullList
		{
		private:
			vector<uint32_t>& _shipHulls;
		public:
			ShipHullList(vector<uint32_t>& shipHulls) : _shipHulls(shipHulls) {}
		};

		class ShipHullPresentation_JSON
		{
		public:
			static void ShipHullOverview(ShipHull& hull, Object& destination);
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_SHIPHULL