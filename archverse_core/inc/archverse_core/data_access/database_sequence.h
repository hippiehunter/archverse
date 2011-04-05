#ifndef ARCHVERSE_CORE_DATA_ACCESS_DATABASE_SEQUENCE_H
#define ARCHVERSE_CORE_DATA_ACCESS_DATABASE_SEQUENCE_H

#include <archverse_core\data_access\database_core.h>
#include <archverse_core\data_access\database_iterator.h>

namespace archverse_core
{
	namespace data_access
	{
		template<typename INDEX, typename RSLT>
		class database_sequence
		{
		private:
			bool _locked;
			INDEX _index;
			bool _indexed;
			database_core<typename INDEX, typename RSLT>* _dbCore;
		public:
			typedef boost::forward_traversal_tag category;
			typedef database_iterator<typename INDEX, typename RSLT> type;

			database_sequence(const INDEX& index, database_core<typename INDEX, typename RSLT>* dbCore, bool locked) : _index(index), _dbCore(dbCore), _locked(locked), _indexed(true) { }
			database_sequence(database_core<typename INDEX, typename RSLT>* dbCore, bool locked) : _dbCore(dbCore), _locked(locked), _indexed(false) { }

			database_iterator<typename INDEX, typename RSLT> begin()
			{
				Dbc *cursor;
				_dbCore->_dbConnection.cursor(NULL, &cursor, 0);
				if(_indexed)
					return database_iterator<typename INDEX, typename RSLT>(_index, 
						std::bind( std::mem_fn(&database_core<typename INDEX, typename RSLT>::save_element), _dbCore,std::placeholders::_1, std::placeholders::_2), 
						cursor, _locked);
				else
					return database_iterator<typename INDEX, typename RSLT>( 
						std::bind( std::mem_fn(&database_core<typename INDEX, typename RSLT>::save_element), _dbCore,std::placeholders::_1, std::placeholders::_2), 
						cursor, _locked);
			}

			database_iterator<typename INDEX, typename RSLT> end()
			{
				return database_iterator<typename INDEX, typename RSLT>();
			}

			size_t size()
			{
				return _dbCore->sequence_size(_index);
			}
		};
	}
}

#endif