#ifndef ARCHVERSE_CORE_DATA_ACCESS_DBCORE_H
#define ARCHVERSE_CORE_DATA_ACCESS_DBCORE_H

#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\data_access\binary_serialization.h>
#include <archverse_core\data_access\index_helper.h>

#include <db_cxx.h>
#include <boost\array.hpp>
#include <boost\variant.hpp>
#include <boost\noncopyable.hpp>

#include <vector>
#include <string>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <functional>
#include <exception>


namespace archverse_core 
{ 
	namespace data_access
	{
		using std::vector;
		using std::uint8_t;
		using std::uint32_t;
		using std::string;
		using boost::variant;
		using boost::array;

		template<typename INDEX, typename RSLT>
		class database_core : boost::noncopyable
		{
		public:
			typedef DbEnv db_environment_t;
			Db _dbConnection;
			Db* _sequenceDb;
		private:
			static const int MAX_REC_SIZE = 4096;
			DbSequence* _dbSequence;
			uint64_t _sequenceStartPoint;
			Dbt* _sequenceStartPointKey;
		public:
			


			database_core(const string& name, db_environment_t* environment) : _dbConnection(environment, 0)
			{
				_dbConnection.set_error_stream(&std::cout);
				u_int32_t oFlags = DB_CREATE;
				// Open the database
				_dbConnection.open(NULL,                // Transaction pointer 
					name.c_str(),          // Database file name 
					NULL,                // Optional logical database name
					DB_BTREE,            // Database access method
					oFlags,              // Open flags
					0);                  // File mode (using defaults)

				_sequenceDb = new Db(environment, 0);

				_sequenceDb->open(NULL,                // Transaction pointer 
					(name + "seq").c_str(),          // Database file name 
					NULL,                // Optional logical database name
					DB_BTREE,            // Database access method
					oFlags,              // Open flags
					0);                  // File mode (using defaults)

				_dbSequence = new DbSequence(_sequenceDb, 0);
				_sequenceStartPoint = std::numeric_limits<uint64_t>::max();
				_sequenceStartPointKey = new Dbt(reinterpret_cast<char*>(&_sequenceStartPoint), sizeof(uint64_t));
				_dbSequence->open(NULL, _sequenceStartPointKey, DB_CREATE);
			}

			template<typename PRIMARYDB>
			database_core(const string& name, db_environment_t* environment, PRIMARYDB& primary, int (*keyMapper)(Db *, const Dbt *, const Dbt *, Dbt *), bool immutableKeys = false) : _dbConnection(environment, 0)
			{
				_dbSequence = NULL;
				_sequenceDb = NULL;
				_dbConnection.set_flags(DB_DUPSORT);
				_dbConnection.set_error_stream(&std::cout);
				u_int32_t oFlags = DB_CREATE;
				// Open the database
				_dbConnection.open(NULL,                // Transaction pointer 
					name.c_str(),          // Database file name 
					NULL,                // Optional logical database name
					DB_BTREE,            // Database access method
					oFlags,              // Open flags
					0);                  // File mode (using defaults)

				primary._dbConnection.associate(NULL,          // Txn id
                      &_dbConnection,     // Associated secondary database
                      keyMapper,  //key mapper
                      immutableKeys ? DB_IMMUTABLE_KEY : 0);            // Flags 
			}

			~database_core()
			{
				if(_dbSequence != NULL)
				{
					delete _sequenceStartPointKey;
					delete _dbSequence;
					delete _sequenceDb;
				}
				_dbConnection.close(0);
			}

			bool exists(const index_helper& index)
			{
				return _dbConnection.exists(0,index.Key(), 0) ==  0;
			}

			int load_element(const index_helper& index, RSLT& destination)
			{
				array<unsigned char, MAX_REC_SIZE> buffer;
				Dbt data;
				memset(&data, 0, sizeof(Dbt));
				data.set_flags(DB_DBT_USERMEM);
				data.set_ulen(MAX_REC_SIZE);
				data.set_data(&buffer);
				int ret = 0;

				ret = _dbConnection.get(0, index.Key(), &data, 0);
				if(ret == 0 && data.get_data() != NULL)
					binary_deserializer<typedef RSLT, unsigned char*>::deserialize(destination, &buffer[0], data.get_size());
				
				return ret;
			}

			int save_element(const index_helper& index, const RSLT& source)
			{
				array<unsigned char, MAX_REC_SIZE> buffer;
				int recordSize = binary_serializer<typedef RSLT, unsigned char*>::serialize(source, &buffer[0], MAX_REC_SIZE);
				Dbt data(&buffer[0], recordSize);
				data.set_flags(DB_DBT_USERMEM);
				return _dbConnection.put(0, index.Key(), &data, 0);
			}

			template<typename ACTUAL_TYPE>
			RSLT new_element()
			{
				if(_dbSequence != NULL)
				{
					db_seq_t seq;
					_dbSequence->get(NULL, 1, &seq, 0);
					return ACTUAL_TYPE((INDEX)seq);
				}
				else
					throw std::exception("secondary databases dont support creating new elements");
			}

			std::uint32_t sequence_size(const index_helper& startingPoint)
			{
				Dbc *cursor;
				Dbt data;
				auto key = startingPoint.Key();
				memset(&data, 0, sizeof(Dbt));
				_dbConnection.cursor(NULL, &cursor, 0);
				db_recno_t recno = 0;
				
				if(cursor->get(key, &data, DB_SET) > DB_NOTFOUND)
					cursor->count(&recno, 0);


				cursor->close();
				return recno;
			}

			std::uint32_t sequence_size()
			{
				DB_HASH_STAT hashStat;
				_dbConnection.stat(NULL, (void*)&hashStat, DB_FAST_STAT);
				return hashStat.hash_ndata;
			}
		};

	}
}

#endif