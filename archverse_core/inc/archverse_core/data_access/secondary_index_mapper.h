#ifndef ARCHVERSE_CORE_DATA_ACCESS_SECONDARY_INDEX_MAPPER
#define ARCHVERSE_CORE_DATA_ACCESS_SECONDARY_INDEX_MAPPER

#include<db_cxx.h>

namespace archverse_core
{
	namespace data_access
	{
		//this method is only safe if the target field is directly mappable off the stored data
		//in practice this translates to only PODs can exist in the layout before the field
		template<typename T, typename FIELD_TYPE, FIELD_TYPE T::* FIELD>
		static int secondary_index_mapper(	Db *sdbp,          // secondary db handle
		                const Dbt *pkey,   // primary db record's key
		                const Dbt *pdata,  // primary db record's data
		                Dbt *skey) 
		{ 
		    skey->set_data(&(reinterpret_cast<T*>(pdata->get_data())->*FIELD));
		    skey->set_size(sizeof(FIELD_TYPE));
			skey->set_flags(DB_DBT_USERMEM);
			return 0; 
		}
	}
}

#endif