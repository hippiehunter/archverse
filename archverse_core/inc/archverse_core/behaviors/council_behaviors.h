#ifndef ARCHVERSE_CORE_BEHAVIORS_COUNCIL
#define ARCHVERSE_CORE_BEHAVIORS_COUNCIL

#include <cstdint>
#include <string>

namespace archverse_core
{
	class archverse_core_state;
	namespace behaviors
	{
		namespace council_behaviors
		{
			using std::uint32_t;
			using std::string;
			using archverse_core::archverse_core_state;
			
			void admission_request(uint32_t councilId, uint32_t playerId, const string& messageBody, archverse_core_state* archverseCoreState);
			void remove_player(uint32_t councilId, const uint32_t& playerId, archverse_core_state* archverseCoreState);

			void update(const uint32_t councilId, control_model& councilControlModel, const uint32_t turn);
		}
	}
}
#endif