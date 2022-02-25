#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>

TEST_CASE("basic constructors test") {
	auto const a1 = comp6771::euclidean_vector(3, 3.0);
	auto a2 = comp6771::euclidean_vector{2.0, 3.0, 4.0};
	auto a3 = -a1;
	CHECK(a1.dimensions() == 3);
	CHECK(a3.dimensions() == 3);
	CHECK(-a2.dimensions() == -3);

	auto const norm = comp6771::euclidean_vector{1.0, 2.0, 3.0};
	CHECK(comp6771::euclidean_norm(norm) == Approx(3.74).epsilon(0.001));
}