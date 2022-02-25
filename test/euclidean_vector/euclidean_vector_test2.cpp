#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>

/**
Using these tests to make sure that all compound operations are functioning correctly for both const
and nonconst euclidean vectors. Also checks for correct exceptions being thrown and the normal to be
updated correctly in these operations.
**/
TEST_CASE("basic compound operations test") {
	SECTION("Compound Addition") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		auto const a2 = comp6771::euclidean_vector(3, 2.0);
		CHECK_NOTHROW(a1 += a2);
		auto const a3 = comp6771::euclidean_vector(4, 2.0);
		CHECK_THROWS(a1 += a3);

		CHECK(a1.dimensions() == 3); // Make sure dimensions haven't changed

		auto a4 = comp6771::euclidean_vector(3, 5.0);
		auto const a5 = comp6771::euclidean_vector(3, 5.0);
		CHECK(a1 == a4); // Check that the added vector equals expected vector.
		CHECK(a1 == a5); // Check that the added vector equals expected (const) vector.

		CHECK(comp6771::euclidean_norm(a1) == comp6771::euclidean_norm(a4)); // Check that the added
		                                                                     // vector normal equals
		                                                                     // expected vector
		                                                                     // normal.
		CHECK(comp6771::euclidean_norm(a1) == comp6771::euclidean_norm(a5)); // Check that the added
		                                                                     // vector normal equals
		                                                                     // expected (const)
		                                                                     // vector normal.
	}
	SECTION("Compound Subtraction") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		auto const a2 = comp6771::euclidean_vector(3, 2.0);
		CHECK_NOTHROW(a1 -= a2);
		auto const a3 = comp6771::euclidean_vector(4, 2.0);
		CHECK_THROWS(a1 -= a3);

		CHECK(a1.dimensions() == 3); // Make sure dimensions haven't changed

		auto a4 = comp6771::euclidean_vector(3, 1.0);
		auto const a5 = comp6771::euclidean_vector(3, 1.0);
		CHECK(a1 == a4); // Check that the added vector equals expected vector.
		CHECK(a1 == a5); // Check that the added vector equals expected (const) vector.

		CHECK(comp6771::euclidean_norm(a1) == comp6771::euclidean_norm(a4)); // Check that the added
		                                                                     // vector normal equals
		                                                                     // expected vector
		                                                                     // normal.
		CHECK(comp6771::euclidean_norm(a1) == comp6771::euclidean_norm(a5)); // Check that the added
		                                                                     // vector normal equals
		                                                                     // expected (const)
		                                                                     // vector normal.
	}
	SECTION("Compound Multiplication") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		a1 *= 3;
		CHECK(a1.dimensions() == 3); // Make sure dimensions haven't changed

		auto a2 = comp6771::euclidean_vector(3, 9.0);
		auto const a3 = comp6771::euclidean_vector(3, 9.0);
		CHECK(a1 == a2); // Check that the added vector equals expected vector.
		CHECK(a1 == a3); // Check that the added vector equals expected (const) vector.

		CHECK(comp6771::euclidean_norm(a1) == comp6771::euclidean_norm(a2)); // Check that the added
		                                                                     // vector normal equals
		                                                                     // expected vector
		                                                                     // normal.
		CHECK(comp6771::euclidean_norm(a1) == comp6771::euclidean_norm(a3)); // Check that the added
		                                                                     // vector normal equals
		                                                                     // expected (const)
		                                                                     // vector normal.
	}
	SECTION("Compound Division") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK_THROWS(a1 /= 0); // Check that exception was thrown for invalid input
		CHECK_NOTHROW(a1 /= 2);
		CHECK(a1.dimensions() == 3); // Make sure dimensions haven't changed

		auto a2 = comp6771::euclidean_vector(3, 1.5);
		auto const a3 = comp6771::euclidean_vector(3, 1.5);
		CHECK(a1 == a2); // Check that the added vector equals expected vector.
		CHECK(a1 == a3); // Check that the added vector equals expected (const) vector.

		CHECK(comp6771::euclidean_norm(a1) == comp6771::euclidean_norm(a2)); // Check that the added
		                                                                     // vector normal equals
		                                                                     // expected vector
		                                                                     // normal.
		CHECK(comp6771::euclidean_norm(a1) == comp6771::euclidean_norm(a3)); // Check that the added
		                                                                     // vector normal equals
		                                                                     // expected (const)
		                                                                     // vector normal.
	}
}