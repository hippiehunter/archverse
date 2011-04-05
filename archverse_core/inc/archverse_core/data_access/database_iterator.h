#ifndef ARCHVERSE_CORE_DATA_ACCESS_DATABASE_ITERATOR_H
#define ARCHVERSE_CORE_DATA_ACCESS_DATABASE_ITERATOR_H

#include <archverse_core\data_access\index_helper.h>

#include <boost\iterator\iterator_facade.hpp>

#include <boost\shared_ptr.hpp>
#include <string>
#include <array>
#include <cstdint>
#include <limits>

#include <db_cxx.h>


namespace archverse_core
{
	namespace data_access
	{
		template<typename INDEX>
		struct database_iterator_key_buffer
		{
		private:
			INDEX _buf;
		public:
			void* buffer;
			size_t size;

			database_iterator_key_buffer() : buffer(nullptr), size(0) { }

			database_iterator_key_buffer(const database_iterator_key_buffer<typename INDEX>& buf)
			{
				_buf = buf._buf;
				buffer = reinterpret_cast<void*>(&_buf);
				size = sizeof(typename INDEX);
			}

			database_iterator_key_buffer(INDEX indx)
			{
				_buf = indx;
				buffer = reinterpret_cast<void*>(&_buf);
				size = sizeof(typename INDEX);
			}

		};

		template<>
		struct database_iterator_key_buffer<std::string>
		{
		private:
			std::string _buf;
		public:
			void* buffer;
			size_t size;

			database_iterator_key_buffer() : buffer(nullptr), size(0) { }

			database_iterator_key_buffer(const database_iterator_key_buffer<std::string>& buf)
			{
				_buf = buf._buf;
				buffer = reinterpret_cast<void*>(&_buf[0]);
				size = _buf.size();
			}

			database_iterator_key_buffer(const std::string& indx)
			{
				_buf = indx;
				buffer = reinterpret_cast<void*>(&_buf[0]);
				size = _buf.size();
			}

			
		};

		template<typename INDEX, typename RSLT>
		class database_iterator : public boost::iterator_facade<
			database_iterator<INDEX, RSLT>, boost::shared_ptr<RSLT>, boost::forward_traversal_tag, boost::shared_ptr<RSLT>>
		{
		private:
			static const size_t MAX_REC_SIZE = 4096;

			boost::shared_ptr<RSLT> _itemPtr;
			bool _valid;
			bool _locked;

			std::uint32_t _dbReadFlags;

			Dbc* _dbCursor;
			std::function<int (const index_helper& index, const typename RSLT& source)> _save_element;
			database_iterator_key_buffer<INDEX> _dbKeyBuffer;
			Dbt _key;
		public:
			friend class boost::iterator_core_access;

			database_iterator(const database_iterator<typename INDEX, typename RSLT>& itr)
			{
				_valid = itr._valid;
				if(_valid)
				{
					_locked = itr._locked;
					itr._dbCursor->dup(&_dbCursor, DB_POSITION);
					_dbReadFlags = itr._dbReadFlags;
					_itemPtr = itr._itemPtr;
					_save_element = itr._save_element;
					_dbKeyBuffer = itr._dbKeyBuffer;
				
					_key.set_data(_dbKeyBuffer.buffer);
					_key.set_size(_dbKeyBuffer.size);
				}
				else
					_dbCursor = nullptr;
			}

			database_iterator() { _valid = false;  _dbCursor = nullptr;}
			database_iterator(const INDEX& index, std::function<int (const index_helper& index, const typename RSLT& source)> save_element, Dbc* dbCursor, bool locked = false) : _dbKeyBuffer(index)
			{
				_dbCursor = dbCursor;
				_save_element = save_element;
				_locked = locked;
				
				_key.set_data(_dbKeyBuffer.buffer);
				_key.set_size(_dbKeyBuffer.size);

				//initial increment needs to position to the first in the sequence
				_dbReadFlags = DB_SET;
				increment();

				//subseqent increments need to look for the next duplicate key
				_dbReadFlags = DB_NEXT_DUP;
			}

			database_iterator(std::function<int (const index_helper& index, const typename RSLT& source)> save_element, Dbc* dbCursor, bool locked = false)
			{
				_dbCursor = dbCursor;
				_save_element = save_element;
				_locked = locked;
				_dbReadFlags = DB_NEXT;

				increment();
			}

			~database_iterator()
			{
				if(_dbCursor != nullptr)
					_dbCursor->close();
			}

			void increment()
			{
				std::array<unsigned char, MAX_REC_SIZE> dbDataBuffer;

				Dbt data;
				data.set_flags(DB_DBT_USERMEM);
				data.set_ulen(MAX_REC_SIZE);
				data.set_data(reinterpret_cast<void*>(&dbDataBuffer));

				if(_locked && _itemPtr)
					_save_element(_itemPtr->id(), *_itemPtr);

				_itemPtr.reset(new RSLT());

				int ret = _dbCursor->get(&_key, &data, _dbReadFlags);
				if( ret == 0)
				{
					binary_deserializer<typedef RSLT, unsigned char*>::deserialize(*_itemPtr, &dbDataBuffer[0], data.get_size());
					_valid = true;
				}
				else
					_valid = false;
			}

			bool equal(database_iterator const& other) const
			{
				return this->_valid == other._valid;
			}

			boost::shared_ptr<RSLT> dereference() const
			{ 
				if(!_itemPtr) throw std::exception("attempting to dereference null iterator");
				return _itemPtr;
			}
		};
	}
}

#endif