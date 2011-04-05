#ifndef ARCHVERSE_CORE_SYSTEM_REFLECTION_METADATA_H
#define ARCHVERSE_CORE_SYSTEM_REFLECTION_METADATA_H

#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>

#include <cstdint>
#include <time.h>
#include <boost/variant.hpp>

namespace archverse_core 
{ 
	namespace data_access
	{
		using std::vector;
		using std::string;
		using boost::variant;
		using std::uint32_t;
		using boost::tuple;

		struct null_type {};

		template<typename FIELD_TYPE, typename ENCLOSING_TYPE>
		class reflective_field
		{
		public:
			FIELD_TYPE ENCLOSING_TYPE::*_fieldPointer;
			reflective_field(FIELD_TYPE ENCLOSING_TYPE::*fieldPointer) : _fieldPointer(fieldPointer) { };
		};

		template<typename T = null_type, typename T2 = null_type, typename T3 = null_type, typename T5 = null_type>
		struct reflective_record_variant { };

		template<typename T>
		struct reflective_record_variant<T, null_type, null_type, null_type>
		{
		public:
			typedef variant<reflective_field<uint32_t, typename T>,
				reflective_field<bool, typename T>,
				reflective_field<uint64_t, typename T>,
				reflective_field<char, typename T>,
				reflective_field<time_t, typename T>,
				reflective_field<string, typename T>,
				reflective_field<vector<uint32_t>, typename T>> variant_t;
		};

		template<typename T, typename VARIANT = reflective_record_variant<T> >
		class reflective_record
		{
		public:
			
			typedef typename VARIANT::variant_t reflective_record_variant_type;

			typedef tuple<reflective_record_variant_type, string> reflective_record_variant_pair_type;
		};

		template<typename T, typename T2>
		struct reflective_record_variant<T, T2, null_type, null_type>
		{
		public:
			typedef variant<reflective_field<uint32_t, typename T>,
				reflective_field<bool, typename T>,
				reflective_field<uint64_t, typename T>,
				reflective_field<char, typename T>,
				reflective_field<time_t, typename T>,
				reflective_field<string, typename T>,
				reflective_field<vector<uint32_t>, typename T>,
				reflective_field<typename T2, typename T>> variant_t;
		};

		template<typename T, typename T2, typename T3>
		struct reflective_record_variant<T, T2, T3, null_type>
		{
		public:
			typedef variant<reflective_field<uint32_t, typename T>,
				reflective_field<bool, typename T>,
				reflective_field<uint64_t, typename T>,
				reflective_field<char, typename T>,
				reflective_field<time_t, typename T>,
				reflective_field<string, typename T>,
				reflective_field<vector<uint32_t>, typename T>,
				reflective_field<typename T2, typename T>,
				reflective_field<typename T3, typename T>> variant_t;
		};

	}
}
#endif