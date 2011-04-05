#ifndef ARCHVERSE_CORE_GAME_USERACCOUNT_H
#define ARCHVERSE_CORE_GAME_USERACCOUNT_H

#include <archverse_core\data_access\reflection_metadata.h>

#include <vector>
#include <string>
#include <cstdint>

#include <boost\assign.hpp>

class Db;
class Dbt;

namespace archverse_core
{
	namespace structures
	{
		class user_account;

		typedef archverse_core::data_access::reflective_record<user_account> user_account_base_t;

		class user_account : public user_account_base_t
		{
		private:
			std::uint32_t _id;
			std::uint32_t _playerId;
			std::size_t _password;
			std::string _userName;
			std::string _lastGeneratedAuthString;
		public:
			typedef std::uint32_t index_t;

			user_account() { };
			user_account(std::uint32_t id) 
			{ 
				_id = id; 
				_playerId = 0;
				_password = 0;
				_userName = "";
				_lastGeneratedAuthString = "";
			};

			std::uint32_t id() const {return _id;}
			std::uint32_t player_id() const {return _playerId;}
			const std::string& user_name() const { return _userName;}
			bool is_password_hash(std::uint32_t password) const { return _password == password; }

			void unchecked_player_id(std::uint32_t id) {_playerId = id;}
			void unchecked_user_name(const std::string& userName) { _userName = userName; }
			void unchecked_password_hash(std::size_t password) { _password = password;}
			void unchecked_auth_string(const std::string& authString) {_lastGeneratedAuthString = authString;}

			static int name_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey);
			static int auth_string_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey);

			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&user_account::_id, "Id")
					(&user_account::_playerId, "PlayerId")
					(&user_account::_password, "Password")
					(&user_account::_userName, "UserName")
					(&user_account::_lastGeneratedAuthString, "LastGeneratedAuthString");
			}
		};
	}
}

#endif //ARCHVERSE_CORE_GAME_USERACCOUNT_H