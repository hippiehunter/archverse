#ifndef ARCHVERSE_CORE_DATA_ACCESS_BASIC_ENTITY_TABLE
#define ARCHVERSE_CORE_DATA_ACCESS_BASIC_ENTITY_TABLE

#include <archverse_core/data_access/database_core.h>
#include <archverse_core/archverse_core_state.h>

#include <type_traits>
#include <boost\noncopyable.hpp>

namespace archverse_core
{
	namespace data_access
	{
		using std::remove_pointer;

		template<class T, class DB_BACKEND = database_core<uint32_t, T> > 
		class basic_entity_table : private boost::noncopyable
		{
		public:
			typedef typename DB_BACKEND::db_environment_t environment_t;
			typedef typename remove_pointer<typename T>::type T_plain_t;
			typedef typename T_plain_t::index_t index_t;
		protected:
			DB_BACKEND _dbBackend;
			archverse_core_state* _archverseCoreState;
		public:
			basic_entity_table(const string& name, environment_t* environment, archverse_core_state* archverseCoreState) : _dbBackend(name, environment), _archverseCoreState(archverseCoreState) { }

			bool get_by_id(index_t id, T& t)
			{
				return _dbBackend.load_element(id, t) == 0;
			}

			const T get_by_id(index_t id)
			{
				T t;
				_dbBackend.load_element(id, t);
				return t;
			}

			template<typename INITIALIZER>
			void create_new_entity(const INITIALIZER& functionObject)
			{
				T t = _dbBackend.new_element<T_plain_t>();
				functionObject(t);
				_dbBackend.save_element(t.id(), t);
			}

			bool remove_by_id(index_t id)
			{
				return _dbBackend.delete_element(id) == 0;
			}

			template<typename F>
			bool locked_transaction(const index_t index, const F& functionObject)
			{
				T destination;
				int rslt = 0;
				if((rslt = _dbBackend.load_element(index, destination)) == 0 || rslt == DB_NOTFOUND)
				{
					if(functionObject(destination))
					{
						return _dbBackend.save_element(index, destination) == 0;
					}
				}
				return false;
			}
			template<typename F>
			void iterate(F& functionObject, bool locked = false)
			{
				_dbBackend.load_sequence(functionObject, locked);
			}
		};
	}
}
#endif