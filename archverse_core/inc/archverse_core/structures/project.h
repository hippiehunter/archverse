#ifndef ARCHVERSE_CORE_GAME_PROJECT
#define ARCHVERSE_CORE_GAME_PROJECT


#include<vector>
#include<list>
#include<string>
#include<cstdint>

namespace archverse_core
{
	namespace containers
	{
		class prerequisite_list;
	}
	namespace structures
	{
		struct control_model;
		class territory;
		class council;

		class project
		{
		private:
			std::uint32_t _id;
			std::uint32_t _rpCost;
			std::uint32_t _ppCost;
			std::string _name;
			std::string _description;
			std::vector<std::uint32_t> _prerequisites;
		public:
			typedef std::uint32_t index_t;

			std::uint32_t id() const {return _id;}
			void prerequisites();
			const std::string& name() const {return _name;}
			std::function<void (council&, player&, territory&, control_model&)> onUpdateTurn;
		};
	}
}
#endif //ARCHVERSE_CORE_GAME_PROJECT