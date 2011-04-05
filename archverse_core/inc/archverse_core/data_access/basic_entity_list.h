#ifndef ARCHVERSE_CORE_DATA_ACCESS_BASIC_ENTITY_LIST
#define ARCHVERSE_CORE_DATA_ACCESS_BASIC_ENTITY_LIST

#include <archverse_core\data_access\basic_entity_table.h>

#include <algorithm>
#include <vector>
#include <type_traits>

namespace archverse_core
{
	namespace data_access
	{
		using std::for_each;
		using std::vector;
		using std::find;
		using std::remove_pointer;


		template<class T, class ENTITY_TABLE = basic_entity_table<T>>
		class basic_entity_list
		{
		public:
			typedef typename remove_pointer<typename T>::type T_plain_t;
			typedef typename T_plain_t::index_t index_t;
		protected:
			const vector<index_t>& _entities;
			ENTITY_TABLE* _entityTable;
		public:
			basic_entity_list(const vector<index_t>& entities, ENTITY_TABLE* entityTable) : 
				_entities(entities), _entityTable(entityTable) 
			{ 
			}

			database_sequence<index_t, typename T> sequence()
			{
				return database_sequence(_index, _entityTable->_dbConnection);
			}

			bool contains(index_t id)
			{
				T t = _entityTable->get_by_id(id);
				return t.has_secondary_index(_index);
			}
		};

		

		
	}
}

#endif