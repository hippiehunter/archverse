#ifndef ARCHVERSE_CORE_GAME_ABILITY
#define ARCHVERSE_CORE_GAME_ABILITY

#include <string>
#include <cstdint>

namespace archverse_core
{
	namespace structures
	{
		class ability
		{
		public:
			typedef std::uint32_t index_t;

			enum ability_type {
				ABILITY_NO_BREATH,
				ABILITY_TERRAFORM_GRAVITY,
				ABILITY_NO_SPY,
				ABILITY_UNDEAD,
				ABILITY_PSI,
				ABILITY_ENHANCED_PSI,
				ABILITY_DUKE,
				ABILITY_MARQUIS,
				ABILITY_EARL,
				ABILITY_VISCOUNT,
				ABILITY_BARON,
				ABILITY_ROGUE_DUKE,
				ABILITY_ROGUE_MARQUIS,
				ABILITY_ROGUE_EARL,
				ABILITY_ROGUE_VISCOUNT,
				ABILITY_ROGUE_BARON,
				ABILITY_GENETIC_ENGINEERING_SPECIALIST,
				ABILITY_FRAGILE_MIND_STRUCTURE,
				ABILITY_GREAT_SPAWNING_POOL,
				ABILITY_FAST_MANEUVER,
				ABILITY_STEALTH,
				ABILITY_SCAVENGER,
				ABILITY_INFORMATION_NETWORK_SPECIALIST,
				ABILITY_EFFICIENT_INVESTMENT,
				ABILITY_DOWNLOADABLE_COMMANDER_EXPERIENCE,
				ABILITY_ASTEROID_MANAGEMENT,
				ABILITY_DIPLOMAT,
				ABILITY_TRAINED_MIND,
				ABILITY_PACIFIST,
				ABILITY_FANATIC_FLEET,
				ABILITY_HIGH_MORALE,
				ABILITY_STEALTH_PIRATE,
				ABILITY_TACTICAL_MASTERY,
				ABILITY_FANATICAL_RECRUITING,
				ABILITY_MILITARISTIC_DOMINANCE,
				ABILITY_ADVANCED_BATTLE_PROCESSING,
				ABILITY_HIVE_SHIP_YARD,
				ABILITY_ENHANCED_SHIELDING
			};
			static std::string ability_type_string(ability_type abilityType);
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_ABILITY