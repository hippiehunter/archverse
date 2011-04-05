#ifndef ARCHVERSE_CORE_DATA_ACCESS_BINARY_SERIALIZER_H
#define ARCHVERSE_CORE_DATA_ACCESS_BINARY_SERIALIZER_H

#include <archverse_core/data_access/reflection_metadata.h>

#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <stdexcept>

#include <cstdint>
#include <boost/variant.hpp>

namespace archverse_core 
{ 
	namespace data_access
	{
		using std::vector;
		using std::uint8_t;
		using std::uint32_t;
		using std::string;
		using boost::variant;
		using std::for_each;

		/***************************************************************************/
		/****************** Serialization partial specializations ****************/
		/***************************************************************************/

		template<typename T, typename BUFFERITR, typename R>
		struct binary_serializer_util 
		{ 
			static size_t serialize(const T& t, BUFFERITR destination, reflective_field<typename R, typename T> val)
			{
				return binary_serializer<typename R, typename BUFFERITR>::serialize(t.*(val._fieldPointer), destination, 0);
			}
		};


		template<typename T, typename BUFFERITR>
		struct binary_serializer_util<T, BUFFERITR, uint32_t> 
		{ 
			static size_t serialize(const T& t, BUFFERITR destination, reflective_field<uint32_t, typename T> val)
			{
				*reinterpret_cast<uint32_t*>(destination) = t.*(val._fieldPointer);
				return sizeof(uint32_t);
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_serializer_util<T, BUFFERITR, time_t> 
		{ 
			static size_t serialize(const T& t, BUFFERITR destination, reflective_field<time_t, typename T> val)
			{
				*reinterpret_cast<time_t*>(destination) = t.*(val._fieldPointer);
				return sizeof(time_t);
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_serializer_util<T, BUFFERITR, char> 
		{ 
			static size_t serialize(const T& t, BUFFERITR destination, reflective_field<char, typename T> val)
			{
				*reinterpret_cast<char*>(destination) = t.*(val._fieldPointer);
				return sizeof(char);
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_serializer_util<T, BUFFERITR, uint64_t> 
		{ 
			static size_t serialize(const T& t, BUFFERITR destination, reflective_field<uint64_t, typename T> val)
			{
				*reinterpret_cast<uint64_t*>(destination) = t.*(val._fieldPointer);
				return sizeof(uint64_t);
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_serializer_util<T, BUFFERITR, string> 
		{ 
			static size_t serialize(const T& t, BUFFERITR destination, reflective_field<string, typename T> val)
			{
				const string& strVal = t.*(val._fieldPointer);
				*reinterpret_cast<size_t*>(destination) = strVal.size();
				size_t offset = sizeof(size_t);
				if(strVal.size() > 0)
				{
					copy(strVal.begin(), strVal.end(), destination + offset);
					offset += strVal.size() * sizeof(char);
				}
				return offset;
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_serializer_util<T, BUFFERITR, vector<uint32_t>> 
		{ 
			static size_t serialize(const T& t, BUFFERITR destination, reflective_field<vector<uint32_t>, typename T> val)
			{
				const vector<uint32_t>& vecVal = t.*(val._fieldPointer);
				*reinterpret_cast<size_t*>(destination) = vecVal.size();
				size_t offset = sizeof(size_t);
				if(vecVal.size() > 0)
				{
					copy(vecVal.begin(), vecVal.end(), destination + offset);
					offset += vecVal.size() * sizeof(uint32_t);
				}
				return offset;
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_serializer_util<T, BUFFERITR, bool> 
		{ 
			static size_t serialize(const T& t, BUFFERITR destination, reflective_field<bool, typename T> val)
			{
				*reinterpret_cast<bool*>(destination) = t.*(val._fieldPointer);
				return sizeof(bool);
			}
		};


		/***************************************************************************/
		/****************** Deserialization partial specializations ****************/
		/***************************************************************************/

		template<typename T, typename BUFFERITR, typename R>
		struct binary_deserializer_util 
		{ 
			static size_t deserialize(T& t, BUFFERITR source, reflective_field<typename R, typename T> val)
			{
				return binary_deserializer<typename R, typename BUFFERITR>::deserialize(t.*(val._fieldPointer), source, 0);
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_deserializer_util<T, BUFFERITR, uint32_t> 
		{
			static size_t deserialize(T& t, BUFFERITR source, reflective_field<uint32_t, typename T> val)
			{
				t.*(val._fieldPointer) = *(reinterpret_cast<uint32_t*>(source));
				return sizeof(uint32_t);
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_deserializer_util<T, BUFFERITR, time_t> 
		{
			static size_t deserialize(T& t, BUFFERITR source, reflective_field<time_t, typename T> val)
			{
				t.*(val._fieldPointer) = *(reinterpret_cast<time_t*>(source));
				return sizeof(time_t);
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_deserializer_util<T, BUFFERITR, char> 
		{
			static size_t deserialize(T& t, BUFFERITR source, reflective_field<char, typename T> val)
			{
				t.*(val._fieldPointer) = *(reinterpret_cast<char*>(source));
				return sizeof(char);
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_deserializer_util<T, BUFFERITR, uint64_t> 
		{
			static size_t deserialize(T& t, BUFFERITR source, reflective_field<uint64_t, typename T> val)
			{
				t.*(val._fieldPointer) = *(reinterpret_cast<uint64_t*>(source));
				return sizeof(uint64_t);
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_deserializer_util<T, BUFFERITR, string> 
		{
			static size_t deserialize(T& t, BUFFERITR source, reflective_field<string, typename T> val)
			{
				size_t size = *(reinterpret_cast<size_t*>(source));
				size_t offset = sizeof(size_t);
				if(size > 0)
				{
					auto str = t.*(val._fieldPointer);
					str.clear();
					str.resize(size, 'f');
					memcpy(&str[0], source + offset, size);
					offset += size;
				}
				return offset;
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_deserializer_util<T, BUFFERITR, vector<uint32_t>> 
		{
			static size_t deserialize(T& t, BUFFERITR source, reflective_field<vector<uint32_t>, typename T> val)
			{
				size_t size = *(reinterpret_cast<size_t*>(source));
				size_t offset = sizeof(size_t);
				if(size > 0)
				{
					auto vec = t.*(val._fieldPointer);
					vec.clear();
					vec.resize(size / sizeof(uint32_t), 0);
					memcpy(&vec[0], source + offset, size);
					offset += size;
				}
				return offset;
			}
		};

		template<typename T, typename BUFFERITR>
		struct binary_deserializer_util<T, BUFFERITR, bool> 
		{
			static size_t deserialize(T& t, BUFFERITR source, reflective_field<bool, typename T> val)
			{
				t.*val._fieldPointer = *(reinterpret_cast<bool*>(source));
				return sizeof(bool);
			}
		};

		template<typename T, typename BUFFERITR>
		class binary_deserializer : 
			public boost::static_visitor<>
		{
		private:
			T& _t;
			BUFFERITR _origin;
			BUFFERITR& _source;
			size_t _sourceOffset;
			size_t _sourceLen;
		public:
			binary_deserializer(T& t, BUFFERITR& source, size_t sourceLen) : _t(t), _source(source), _sourceOffset(0), _sourceLen(sourceLen), _origin(source) { }

			template<typename R>
			void operator()(reflective_field<typename R, typename T> val)
			{
				_sourceOffset += binary_deserializer_util<typename T, typename BUFFERITR, typename R>::deserialize(_t, _origin + _sourceOffset, val);
				if(_sourceLen != 0 && _sourceOffset > _sourceLen)
					throw std::runtime_error("source offset exceeded source length while deserializing");
				else
					_source = _origin + _sourceOffset;
			}

			size_t source_offset() { return _sourceOffset; }

			static size_t deserialize(T& t, BUFFERITR source, size_t sourceLen)
			{
				static auto reflectiveFields = typename T::__init_type_fields();
				BUFFERITR start = source;
				binary_deserializer deserializer(t, source, sourceLen);
				auto visitor = boost::apply_visitor(deserializer);
				for_each(reflectiveFields.begin(),
					reflectiveFields.end(), 
					[&](decltype(reflectiveFields[0])& field)
				{
					visitor(field.get<0>());
				});
				return deserializer.source_offset();
			}
		};

		template<typename T, typename BUFFERITR>
		class binary_serializer : 
			public boost::static_visitor<>
		{
		private:
			const T& _t;
			BUFFERITR _origin;
			BUFFERITR& _destination;
			size_t _destinationOffset;
			size_t _destinationLen;
		public:
			binary_serializer(const T& t, BUFFERITR& destination, size_t destinationLen) : _t(t), _destination(destination), _destinationLen(destinationLen), _destinationOffset(0), _origin(destination) { }

			template<typename R>
			void operator()(reflective_field<typename R, typename T> val)
			{
				_destinationOffset += binary_serializer_util<typename T, typename BUFFERITR, typename R>::serialize(_t, _origin + _destinationOffset, val);
				if(_destinationLen != 0 && _destinationOffset > _destinationLen)
					throw std::runtime_error("destination offset exceeded destination length while serializing object");
				else
					_destination = _origin + _destinationOffset;
			}

			size_t destination_offset() { return _destinationOffset; }

			static size_t serialize(const T& t, BUFFERITR destination, size_t destinationLen)
			{
				static auto reflectiveFields = typename T::__init_type_fields();
				BUFFERITR start = destination;
				binary_serializer serializer(t, destination, destinationLen);
				auto visitor = boost::apply_visitor(serializer);
				for_each(reflectiveFields.begin(),
					reflectiveFields.end(), 
					[&](decltype(reflectiveFields[0])& field)
				{
					visitor(field.get<0>());
				});
				return serializer.destination_offset();
			}
		};
	}
}
#endif