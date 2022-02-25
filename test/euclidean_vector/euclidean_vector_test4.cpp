#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <vector>

/**
I've decided to test the euclidean vectors of 0 dimensions to potentially find any unexpected
behaviours since most operations should still be valid for an empty vector.
**/
TEST_CASE("basic 0 dimensions test") {
	SECTION("Friends check of 0 dimension vectors") {
		auto const a1 = comp6771::euclidean_vector(0, 5.0);
		auto const a2 = comp6771::euclidean_vector(0, 5.0);
		auto a3 = a1 + a2;
		CHECK(a3.dimensions() == 0);
		a3 = a1 - a2;
		CHECK(a3.dimensions() == 0);
		a3 = a1 * 2;
		CHECK(a3.dimensions() == 0);
		a3 = a1 / 2;
		CHECK(a3.dimensions() == 0);

		auto oss = std::ostringstream{}; // test print the empty vector
		oss << (a3);
		CHECK(oss.str() == "[]");
	}

	SECTION("Utility/Member check of 0 dimension vectors") {
		auto const a1 = comp6771::euclidean_vector(0, 5.0);
		CHECK(comp6771::euclidean_norm(a1) == 0);
		CHECK_THROWS(comp6771::unit(a1));
		auto const a2 = comp6771::euclidean_vector(0, 5.0);
		CHECK(comp6771::dot(a1, a2) == 0);
	}

	SECTION("Operation check of 0 dimension vectors") {
		auto a1 = comp6771::euclidean_vector(0, 5.0);
		comp6771::euclidean_vector a2;
		a2 = a1;
		CHECK(a2.dimensions() == 0);
		CHECK(comp6771::euclidean_norm(a2) == 0);
		a1 *= 2;
		CHECK(a1.dimensions() == 0);
		CHECK(comp6771::euclidean_norm(a1) == 0);
	}

	SECTION("Typecasting of 0 dimension vectors") {
		auto const a1 = comp6771::euclidean_vector(0, 5.0);
		auto const vec = static_cast<std::vector<double>>(a1);
		CHECK(vec.empty());

		auto list = static_cast<std::list<double>>(a1);
		CHECK(list.empty());
	}
}