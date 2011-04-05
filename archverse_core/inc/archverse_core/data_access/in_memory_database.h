#ifndef ARCHVERSE_CORE_DATA_ACCESS_IN_MEMORY_DATABASE
#define ARCHVERSE_CORE_DATA_ACCESS_IN_MEMORY_DATABASE

#include <vector>
#include <string>
#include <cstdint>

namespace archverse_core
{
	namespace data_access
	{

		using std::vector;
		using std::uint32_t;

		template<typename RSLT>	
		class in_memory_database
		{
		public:
			typedef uint32_t db_environment_t; //this isnt used, just set it to zero
		private:
			const string& _name;
			vector<RSLT> _data;
		public:
			in_memory_database(const string& name, db_environment_t* environment) : _name(name) { }
			~in_memory_database()
			{
				for_each(_data.begin(), _data.end(), [](RSLT& rslt) { delete rslt; });
			}
			bool exists(const uint32_t& index)
			{
				return _data.size() < index;
			}

			int load_element(const uint32_t& index, RSLT& destination)
			{
				destination = _data[index];
			}

			int save_element(const uint32_t& index, const RSLT& source)
			{
				_data[index] = source;
			}
			template<typename ACTUAL_TYPE>
			RSLT new_element()
			{
				_data.push_back(new ACTUAL_TYPE(_data.size()));
				return _data.back();
			}
		};
	}
}

#endif