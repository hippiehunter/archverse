#ifndef ARCHVERSE_CORE_GAME_RACE
#define ARCHVERSE_CORE_GAME_RACE

#include <archverse_core\structures\control_model.h>

#include<cstdint>
#include<vector>
#include<string>

namespace archverse_core
{
	namespace structures
	{
		class tech;
		
		class race
		{
		public:
			enum social_type
			{
				SOCIETY_TOTALISM,
				SOCIETY_CLASSISM,
				SOCIETY_PERSONALISM
			};
		private:
			std::uint32_t _id;
			social_type _socialType;
			control_model _controlModel;
			std::string _name;
			std::string _description;
			std::vector<std::uint32_t> _abilities;
			std::vector<std::uint32_t> _startingTechs;
		public:
			typedef std::uint32_t index_t;

			const std::string& name() const {return _name;}
			void add_starting_tech(const tech& techId);
			static const std::string& social_type_string(social_type socialType);
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_RACE