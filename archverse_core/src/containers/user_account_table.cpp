#include <archverse_core\containers\user_account_table.h>

#include <boost\functional\hash.hpp>
#include <boost\lexical_cast.hpp>
#include <string>

using boost::hash;
using std::string;
using boost::lexical_cast;

using archverse_core::containers::user_account_table;
using archverse_core::structures::user_account;

bool user_account_table::user_account_from_auth_string(const string& authString, user_account& destination)
{
	return _authStringDB.load_element(authString, destination) == 0;
}

bool user_account_table::user_account_from_name(const string& accountName, user_account& destination)
{
	return _nameDB.load_element(accountName, destination) == 0;
}

string user_account_table::login(const string& username, const string& password, user_account& destination)
{
	user_account account;
	hash<string> stringHash;

	//try to load the account, if it returns 0(exists) then check if we have the right password
	if(_nameDB.load_element(username, account) == 0 &&
		account.is_password_hash(stringHash(password)))
	{
		auto authStringPart = lexical_cast<string>(stringHash(password)) + lexical_cast<string>(rand()) + username;
		std::random_shuffle(authStringPart.begin(), authStringPart.end());

		locked_transaction(account.id(), [&](user_account& lockedAccount) -> bool
		{
			lockedAccount.unchecked_auth_string(authStringPart);
			destination = lockedAccount;
			return true;
		});

		return authStringPart;
	}
	return string();
}

bool user_account_table::create_user(const string& userName, const string& password)
{
	if(_nameDB.exists(userName))
		return false;

	create_new_entity([&](user_account& target)
	{
		hash<string> stringHash;
		target.unchecked_user_name(userName);
		target.unchecked_password_hash(stringHash(password));
	});

	return true;
}