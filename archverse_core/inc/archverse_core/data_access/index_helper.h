#ifndef ARCHVERSE_CORE_DATA_ACCESS_INDEX_HELPER_H
#define ARCHVERSE_CORE_DATA_ACCESS_INDEX_HELPER_H

#include <db_cxx.h>

#include <string>
#include <cstdint>

namespace archverse_core
{
	namespace data_access
	{
		class index_helper
		{
		private:
			Dbt _key;
		public:
			//this needs to be extended to support other index types
			index_helper(const std::string& index) : _key(const_cast<char*>(&index[0]), index.size()) { }
			index_helper(const int& index) : _key(const_cast<int*>(&index), sizeof(index)) { }
			index_helper(const std::uint32_t& index) : _key(const_cast<std::uint32_t*>(&index), sizeof(index)) { }
			index_helper(const std::uint64_t& index) : _key(const_cast<std::uint64_t*>(&index), sizeof(index)) { }

			Dbt* Key() const { return const_cast<Dbt*>(&_key); }
		};
	}
}

#endif