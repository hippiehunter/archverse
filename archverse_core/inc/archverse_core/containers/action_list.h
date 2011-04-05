#ifndef ARCHVERSE_CORE_CONTAINERS_ACTION_LIST
#define ARCHVERSE_CORE_CONTAINERS_ACTION_LIST

#include <archverse_core\structures\action.h>

#include <vector>
#include <cstdint>

namespace archverse_core
{
	namespace structures
	{
		class player;
	}
	namespace containers
	{
		using std::vector;
		using std::uint32_t;
		using std::uint8_t;

		using archverse_core::structures::action;
		using archverse_core::structures::player;

		class action_list
		{
		private:
			uint32_t _id;
			vector<action> _actions;

			void push_action(const action& action);

		public:
			typedef uint32_t index_t;

			void recycle_actions();
			bool has_action(action::action_type actionType);
			void create_new_action(action::action_type actionType, uint32_t turn, uint32_t data);
			void entity_by_type(action::action_type actionType, vector<action>& actions);
			void interact(action::action_type actionType, int input, player& player);
		};
	}
}

#endif