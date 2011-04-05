#ifndef ARCHVERSE_CORE_GAME_TECH
#define ARCHVERSE_CORE_GAME_TECH

#include <archverse_core\structures\control_model.h>

#include <cstdint>
#include <vector>
#include <string>
#include <list>

namespace archverse_core
{
	namespace containers
	{
		class prerequisite_list;
	}
	namespace structures
	{
		class project;
		class prerequisite;
		class component;

		class tech
		{
		private:
			std::uint32_t _id;
			std::uint32_t _kpCost;
			control_model _modifiers;
			std::vector<std::uint32_t> _spyOps;
			std::vector<std::uint32_t> _buildings;
			std::vector<std::uint32_t> _components;
			std::vector<std::uint32_t> _prerequisites;
			std::string _name;
			std::string _description;
			std::string _category;
		public:
			typedef std::uint32_t index_t;
			const std::string& name() const {return _name;}
			std::uint32_t id() const {return _id;}
			std::uint32_t kp_cost() const {return _kpCost;}

			void add_prerequisite(std::uint32_t prerequisite);
			void add_component(std::uint32_t component);
			void add_building(std::uint32_t project);

			tech(std::uint32_t id) : _id(id) {};
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_TECH