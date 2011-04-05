#ifndef ARCHVERSE_CORE_GAME_SHIP
#define ARCHVERSE_CORE_GAME_SHIP

#include"system\JSON\json_spirit.h"
#include"system\database_core.h"

#include<vector>
#include<string>
#include<cstdint>

namespace archverse_core
{
	namespace game
	{
		using namespace json_spirit;
		using std::uint32_t;
		using std::uint8_t;
		using std::string;
		using std::vector;

		class ShipPool;
		

		class Ship
		{
		private:
			uint32_t _designId;
			float _damagePct; //0-100;
			uint32_t _crew;
			uint32_t _experiance;
		};

		class ShipPool
		{


		};
	}
}

#endif //ARCHVERSE_CORE_GAME_SHIP