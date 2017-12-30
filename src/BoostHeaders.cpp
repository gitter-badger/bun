#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/preprocessor.hpp>
#include <boost/proto/proto.hpp>
#include "blib/utils/MD5.hpp"
#include <soci/soci.h>
#include <string>
#include <soci/sqlite3/soci-sqlite3.h>
#include <boost/preprocessor.hpp>
#include <third_party/fmt/format.hpp>
#include "blib/bun/DbLogger.hpp"
#include "blib/bun/bun.hpp"

using namespace soci;
using namespace std;

namespace backery {
	struct Bun {
		std::string bun_name;
		float sugar_quantity;
		float flour_quantity;
		float milk_quantity;
		float yeast_quantity;
		float butter_quantity;
		int bun_length;
	};
}

SPECIALIZE_BUN_HELPER((backery::Bun, bun_name, sugar_quantity, flour_quantity));

int main() {
	try {
		session sql(sqlite3, "objects.db");
		connection_parameters c;
		int count = 0;
		sql << "select * from sqlite_master";
	}
	catch (exception const & e) {
		cerr << "Error: " << e.what() << "\n";
	}

	const auto t = BOOST_PP_TUPLE_ELEM(5, (1, 2, 3, 4, 5, 6));
	blib::bun::connect("objects.db");
	blib::bun::createSchema<backery::Bun>();
	blib::bun::PRef<backery::Bun> bun = new backery::Bun;
	bun->bun_length = 10;
	bun->bun_name = "test";
	const std::string bun_json = bun.toJson();
	blib::bun::l().info("bun json: {}", bun_json);
	bun.save();
	std::cout << "Tuple Out: " << t << std::endl;


	return 1;
}
