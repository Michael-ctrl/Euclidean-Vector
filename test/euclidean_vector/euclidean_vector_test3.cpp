#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

/**
Testing utility functions just to make sure they work as intended for basic uses. Some of the
 functions may overlap and use functions from other utilities.
**/
TEST_CASE("basic utilities test") {
	SECTION("Euclidean Normal") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		auto a2 = comp6771::euclidean_vector(3, 1.5);
		a2 *= 2;
		CHECK(comp6771::euclidean_norm(a1) == comp6771::euclidean_norm(a2));

		auto a3 = comp6771::euclidean_vector{3, 4};
		CHECK(comp6771::euclidean_norm(a3) == 5); // check normal with expected value with no floating
		                                          // point errors
	}

	SECTION("Unit Vector") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		auto a2 = comp6771::euclidean_vector(3, 1.5);
		a2 *= 4;
		a2 /= 2;
		CHECK(comp6771::unit(a1) == comp6771::unit(a2)); // comparing two arrays that should be equal
		auto const a3 = comp6771::euclidean_vector(3, 3.0);
		CHECK(comp6771::unit(a1) == comp6771::unit(a3)); // comparing a const and nonconst array

		auto a4 = comp6771::euclidean_vector(3, 3.0 / comp6771::euclidean_norm(a1)); // creating a
		                                                                             // vector using
		                                                                             // expected unit
		                                                                             // vector of a1
		CHECK(comp6771::unit(a1) == a4);
	}

	SECTION("Dot Product") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		auto a2 = comp6771::euclidean_vector(3, 3.0);
		CHECK(comp6771::dot(a1, a2) == 27);
		a1 = {3, 4};
		a2 = {4, -3};
		CHECK(comp6771::dot(a1, a2) == 0);
		CHECK(a1.dimensions() == 2); // check dimensions have correctly been changed
		CHECK(comp6771::euclidean_norm(a1) == 5); // check normal has been calculated after change
	}
}