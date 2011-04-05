#include <archverse_core\archverse_core_state.h>
#include <archverse_core\containers\player_table.h>
#include <archverse_core\containers\territory_table.h>
#include <archverse_core\containers\user_account_table.h>


#include <boost\lexical_cast.hpp>
#include <string>
#include <iostream>

using boost::lexical_cast;
using std::string;

using archverse_core::archverse_core_state;
using archverse_core::containers::player_table;
using archverse_core::containers::territory_table;
using archverse_core::structures::player;
using archverse_core::structures::user_account;

int main()
{
	archverse_core_state state;
	state.add_ticks(5);

	
	string nameie = lexical_cast<string>(7777777);
	bool isUserCreated = state.userAccountTable->create_user(nameie, nameie);
	if(isUserCreated)
	{
		user_account user;
		if(state.userAccountTable->user_account_from_name(nameie, user))
		{
			player newPlayer;
			state.playerTable->create_new_player(user.id(), nameie, 0, newPlayer);
		}
	}
	else
	{
		std::cout<<"failed " <<nameie<<std::endl;
	}
}