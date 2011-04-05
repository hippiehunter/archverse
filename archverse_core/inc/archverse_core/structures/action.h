#ifndef ARCHVERSE_CORE_GAME_ACTION
#define ARCHVERSE_CORE_GAME_ACTION

#include <cstdint>
#include <string>

namespace archverse_core
{
	namespace structures
	{
		class player;
		
		struct action
		{
		public:
			typedef std::uint32_t index_t;

			enum action_type
			{
				AT_ENTERED_ALLIANCE,
				AT_ENTERED_WAR,
				AT_ENTERED_PEACE_TREATY,
				AT_BROKE_ALLIANCE,
				AT_BROKE_PEACE_TREATY,
				AT_LOST_LARGE_BATTLE,
				AT_WON_LARGE_BATTLE,
				AT_HAS_EXPEDITION,
				AT_WAITING = 1 << 15
			};
		private:
			action_type _actionType;
			std::uint32_t _data;
			std::uint32_t _turn;
		public:
			bool interact(archverse_core::structures::player& player, int input);
			std::string action_string() const;

		};
	}
}
#endif //ARCHVERSE_CORE_GAME_ACTION