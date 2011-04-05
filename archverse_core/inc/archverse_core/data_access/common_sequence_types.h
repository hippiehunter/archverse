#ifndef ARCHVERSE_CORE_DATA_ACCESS_DATABASE_COMMON_SEQUENCE_H
#define ARCHVERSE_CORE_DATA_ACCESS_DATABASE_COMMON_SEQUENCE_H


#include <archverse_core\data_access\database_sequence.h>

namespace archverse_core
{
	namespace structures
	{
		class player;
		class council;
		class diplomatic_message;
		class game_event;
		class news;
		class territory;
		class region;
		class relationship;
		class admission_request;


		typedef archverse_core::data_access::database_sequence<std::uint32_t, player> player_sequence_t;
		typedef archverse_core::data_access::database_sequence<std::uint32_t, council> council_sequence_t;
		typedef archverse_core::data_access::database_sequence<std::uint32_t, diplomatic_message> diplomatic_message_sequence_t;
		typedef archverse_core::data_access::database_sequence<std::uint32_t, game_event> game_event_sequence_t;
		typedef archverse_core::data_access::database_sequence<std::uint32_t, news> news_sequence_t;
		typedef archverse_core::data_access::database_sequence<std::uint64_t, news> news_id_sequence_t;
		typedef archverse_core::data_access::database_sequence<std::uint32_t, territory> territory_sequence_t;
		typedef archverse_core::data_access::database_sequence<std::uint32_t, region> region_sequence_t;
		typedef archverse_core::data_access::database_sequence<std::uint32_t, relationship> relationship_sequence_t;
		typedef archverse_core::data_access::database_sequence<std::uint32_t, admission_request> admission_request_sequence_t;
	}
}


#endif