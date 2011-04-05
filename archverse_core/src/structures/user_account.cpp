#include <archverse_core\structures\user_account.h>

#include <db_cxx.h>

#include <stddef.h>
#include <vector>
#include <string>
#include <cstdint>
#include <boost\tuple\tuple.hpp>

using std::vector;
using std::uint32_t;
using std::uint8_t;
using std::string;
using boost::tuple;

using archverse_core::structures::user_account;
using archverse_core::structures::user_account_base_t;

int user_account::name_mapper(	Db *sdbp,          // secondary db handle
		                const Dbt *pkey,   // primary db record's key
		                const Dbt *pdata,  // primary db record's data
		                Dbt *skey) 
{ 
	uint8_t* startOfName = reinterpret_cast<uint8_t*>(pdata->get_data()) + offsetof(user_account, _userName);
	uint32_t nameLength = *reinterpret_cast<uint32_t*>(startOfName);
	startOfName += sizeof(uint32_t);
	if(nameLength > 0)
	{
		skey->set_data(startOfName);
		skey->set_size(nameLength);
		return 0;
	}
	else
		return DB_DONOTINDEX;
}

int user_account::auth_string_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey)
{
	uint8_t* data = reinterpret_cast<uint8_t*>(pdata->get_data()) + offsetof(user_account, _userName);
	uint32_t nameLength = *reinterpret_cast<uint32_t*>(data);
	data += sizeof(uint32_t) + nameLength;
	uint32_t authStringLength = *reinterpret_cast<uint32_t*>(data);
	data += sizeof(uint32_t);
	if(authStringLength > 0)
	{
		skey->set_data(data);
		skey->set_size(authStringLength);
		return 0;
	}
	else
		return DB_DONOTINDEX;
}