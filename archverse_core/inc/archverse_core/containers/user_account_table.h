#ifndef ARCHVERSE_CORE_CONTAINERS_USER_ACCOUNT_TABLE
#define ARCHVERSE_CORE_CONTAINERS_USER_ACCOUNT_TABLE

#include <archverse_core\data_access\basic_entity_table.h>
#include <archverse_core\data_access\database_core.h>
#include <archverse_core\structures\user_account.h>

#include <string>
#include <cstdint>

namespace archverse_core		
{
	namespace containers
	{
		typedef archverse_core::data_access::basic_entity_table<archverse_core::structures::user_account> user_account_table_base_t;

		class user_account_table : public user_account_table_base_t
		{
		private:
			archverse_core::data_access::database_core<std::string, archverse_core::structures::user_account> _nameDB;
			archverse_core::data_access::database_core<std::string, archverse_core::structures::user_account> _authStringDB;
		public:
			user_account_table(environment_t* environment, archverse_core_state* archverseCoreState) : 
			  	user_account_table_base_t("user_account", environment, archverseCoreState), 
				_nameDB("account_name_index", environment, user_account_table_base_t::_dbBackend, &archverse_core::structures::user_account::name_mapper),
				_authStringDB("account_auth_string_index", environment, user_account_table_base_t::_dbBackend, &archverse_core::structures::user_account::auth_string_mapper)
			  { }

			bool user_account_from_auth_string(const std::string& authString, archverse_core::structures::user_account& destination);
			bool user_account_from_name(const std::string& accountName, archverse_core::structures::user_account& destination);
			std::string login(const std::string& username, const std::string& password, archverse_core::structures::user_account& destination);
			bool create_user(const std::string& userName, const std::string& password);
		};
	}
	
}

#endif