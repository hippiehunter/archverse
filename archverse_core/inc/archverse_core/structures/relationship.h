#ifndef ARCHVERSE_CORE_GAME_RELATIONSHIP
#define ARCHVERSE_CORE_GAME_RELATIONSHIP

#include <archverse_core\data_access\reflection_metadata.h>
#include <archverse_core\data_access\secondary_index_mapper.h>

#include <cstdint>
#include <vector>
#include <string>

#include <boost\assign.hpp>

namespace archverse_core
{
	namespace structures
	{
		class relationship : public archverse_core::data_access::reflective_record<relationship>
		{
		public:
			typedef std::uint32_t index_t;
			enum relation_type
			{
				RELATION_NONE = 0,
				RELATION_SUBORDINARY,
				RELATION_ALLY,
				RELATION_TRADE,
				RELATION_TRUCE,
				RELATION_WAR,
				RELATION_TOTAL_WAR,
				RELATION_BOUNTY,
				RELATION_HOSTILE
			};
		private:
			std::uint32_t _id;
			relation_type _relationType;

			std::uint32_t _member1;
			std::uint32_t _member2;
		public:
			static int member1_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey)
			{
				return archverse_core::data_access::secondary_index_mapper<relationship, std::uint32_t, &relationship::_member1>( sdbp, pkey, pdata, skey);
			}

			static int member2_mapper(Db * sdbp, const Dbt * pkey, const Dbt * pdata, Dbt * skey)
			{
				return archverse_core::data_access::secondary_index_mapper<relationship, std::uint32_t, &relationship::_member2>( sdbp, pkey, pdata, skey);
			}

			static std::vector< boost::tuple<reflective_record_variant_type, std::string> > __init_type_fields() throw()
			{
				return boost::assign::tuple_list_of<reflective_record_variant_type, std::string>
					(&relationship::_id, "Id")
					(reinterpret_cast<std::uint32_t relationship::*>(&relationship::_relationType), "RelationType")
					(&relationship::_member1, "Member1")
					(&relationship::_member2, "Member2");
			}

			relationship(uint32_t id) { _id = id; }
			relationship() { }

			std::uint32_t id()  const {return _id;}
			std::uint32_t member1() const {return _member1;}
			std::uint32_t member2() const {return _member2;}
			relation_type member_relation() const {return _relationType;}
			std::string relation_text() const;
			bool has_secondary_index(std::uint32_t index) const { return _member1 == index || _member2 == index; }


			void unchecked_member1_id(std::uint32_t value) { _member1 = value;}
			void unchecked_member2_id(std::uint32_t value) { _member2 = value;}
			void unchecked_member_relation(relation_type value) { _relationType = value;}

		};
	}
}

#endif //ARCHVERSE_CORE_GAME_RELATIONSHIP