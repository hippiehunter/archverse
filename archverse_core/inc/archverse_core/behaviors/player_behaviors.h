#ifndef ARCHVERSE_CORE_BEHAVIORS_PLAYER
#define ARCHVERSE_CORE_BEHAVIORS_PLAYER

#include <cstdint>

namespace archverse_core
{
	class archverse_core_state;
	namespace structures
	{
		class council;
		struct control_model;
		class player;
		class relationship;
	}
	namespace containers
	{
		class player_list;
		class player_table;
	}
	namespace behaviors
	{
		namespace player_behaviors
		{
			using std::uint32_t;
			using archverse_core::structures::council;
			using archverse_core::structures::control_model;
			using archverse_core::structures::player;
			using archverse_core::archverse_core_state;
			using archverse_core::containers::player_list;

			void enter_truce(player& initiate, player& targetPlayer);
			void enter_alliance(player& initiate, player& targetPlayer);
			void enter_trade(player& initiate, player& targetPlayer);
			void enter_war(player& initiate, player& targetPlayer);
			void declare_war(player& initiate, player& targetPlayer);
			void enter_hostilities(player& initiate, player& targetPlayer);
			void declare_hostilities(player& initiate, player& targetPlayer);
			void clear_relation(player& initiate, player& targetPlayer);

			void diplomatic_state_setter(const uint32_t targetID, bool initiated, relationship& relationship, player_table* playerTable);
			void diplomatic_state_setter(player& target, bool initiated, relationship& relationship);

			void join_council(const uint32_t playerId, const uint32_t& councilId, archverse_core_state* archverseCoreState);
			void cast_council_vote(const uint32_t playerId, const uint32_t targetPlayerId, archverse_core_state* archverseCoreState);

			bool update(const uint32_t playerId, const council& currentCouncil, const control_model& councilControlModel, uint32_t tick, archverse_core_state* archverseCoreState);
			void propegate_territory_update(player& target, uint32_t pp, uint32_t ore, uint32_t food, uint32_t energy, uint32_t kp, uint32_t mp, uint32_t population, uint32_t power);
			
			void expedition_territory(const uint32_t playerId, int luckRoll, archverse_core_state* archverseCoreState);

			void target_security_level(const uint32_t playerId, const uint32_t level, archverse_core_state* archverseCoreState);
			void change_government(const uint32_t playerId, const uint32_t governmentId, archverse_core_state* archverseCoreState);
			void discover_tech(const uint32_t playerId, const uint32_t techId, archverse_core_state* archverseCoreState);
		}
	}
}

#endif