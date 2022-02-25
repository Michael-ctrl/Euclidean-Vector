// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

namespace comp6771 {
	///////////////
	// Constructors
	///////////////
	euclidean_vector::euclidean_vector() noexcept
	: euclidean_vector(1, 0) {}

	euclidean_vector::euclidean_vector(int dim) noexcept
	: euclidean_vector(dim, 0) {}

	euclidean_vector::euclidean_vector(int dim, double mag) noexcept
	: dims_{static_cast<std::size_t>(dim)} // NOLINTNEXTLINE(modernize-avoid-c-arrays)
	, magnitude_{std::make_unique<double[]>(dims_)} {
		std::fill_n(magnitude_.get(), dims_, mag);
		update_norm();
	}

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator first,
	                                   std::vector<double>::const_iterator last) noexcept
	: euclidean_vector(static_cast<int>(std::distance(first, last))) {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::copy(first, last, magnitude_.get());
		update_norm();
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> list) noexcept
	: dims_{list.size()} // NOLINTNEXTLINE(modernize-avoid-c-arrays)
	, magnitude_{std::make_unique<double[]>(dims_)} {
		std::copy(list.begin(), list.end(), magnitude_.get());
		update_norm();
	}

	// Copy Constructor
	euclidean_vector::euclidean_vector(euclidean_vector const& orig)
	: dims_{orig.dims_} // NOLINTNEXTLINE(modernize-avoid-c-arrays)
	, magnitude_{std::make_unique<double[]>(dims_)} {
		std::copy(orig.magnitude_.get(), orig.magnitude_.get() + orig.dims_, magnitude_.get());
		update_norm();
	}

	// Move Constructor
	euclidean_vector::euclidean_vector(euclidean_vector&& orig) noexcept
	: euclidean_vector(0) {
		std::swap(this->dims_, orig.dims_);
		std::swap(this->magnitude_, orig.magnitude_);
		std::swap(this->norm_, orig.norm_);
	}

	// Destructor
	euclidean_vector::~euclidean_vector() = default;

	///////////////
	// OPERATIONS
	///////////////
	auto euclidean_vector::operator=(euclidean_vector const& vec) noexcept -> euclidean_vector& {
		auto copy = vec;
		std::swap(copy, *this);
		return *this;
	}

	auto euclidean_vector::operator=(euclidean_vector&& vec) noexcept -> euclidean_vector& {
		std::swap(dims_, vec.dims_);
		std::swap(magnitude_, vec.magnitude_);
		std::swap(norm_, vec.norm_);
		vec.dims_ = 0;
		vec.magnitude_ = nullptr;
		vec.norm_ = 0;
		return *this;
	}

	auto euclidean_vector::operator[](int i) noexcept -> double& {
		assert(i >= 0 and i < static_cast<int>(dims_));
		return magnitude_.get()[i];
	}

	auto euclidean_vector::operator[](int i) const noexcept -> double {
		assert(i >= 0 and i < static_cast<int>(dims_));
		return magnitude_.get()[i];
	}

	auto euclidean_vector::operator+() const noexcept -> euclidean_vector {
		auto copy = euclidean_vector(*this);
		return copy;
	}

	auto euclidean_vector::operator-() const noexcept -> euclidean_vector {
		auto copy = *this;
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + copy.dims_,
		               copy.magnitude_.get(),
		               [](double& i) { return i *= -1; });
		auto copied = euclidean_vector(copy);
		return copied;
	}

	auto euclidean_vector::operator+=(euclidean_vector const& vec) -> euclidean_vector& {
		if (this->dimensions() != vec.dimensions()) {
			throw comp6771::euclidean_vector_error(
			   "Dimensions of LHS(" + std::to_string(this->dimensions()) + ") and RHS("
			   + std::to_string(vec.dimensions()) + ") do not match");
		}
		std::transform(vec.magnitude_.get(),
		               vec.magnitude_.get() + vec.dimensions(),
		               this->magnitude_.get(),
		               this->magnitude_.get(),
		               std::plus<>());
		update_norm();
		return *this;
	}

	auto euclidean_vector::operator-=(euclidean_vector const& vec) -> euclidean_vector& {
		if (this->dimensions() != vec.dimensions()) {
			throw comp6771::euclidean_vector_error(
			   "Dimensions of LHS(" + std::to_string(this->dimensions()) + ") and RHS("
			   + std::to_string(vec.dimensions()) + ") do not match");
		}
		std::transform(vec.magnitude_.get(),
		               vec.magnitude_.get() + vec.dimensions(),
		               this->magnitude_.get(),
		               this->magnitude_.get(),
		               std::minus<>());
		update_norm();
		return *this;
	}

	auto euclidean_vector::operator*=(double num) noexcept -> euclidean_vector& {
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimensions(),
		               this->magnitude_.get(),
		               [num](double& x) { return (x * num); });
		update_norm();
		return *this;
	}

	auto euclidean_vector::operator/=(double num) -> euclidean_vector& {
		if (num == 0) {
			throw comp6771::euclidean_vector_error("Invalid vector division by 0");
		}
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimensions(),
		               this->magnitude_.get(),
		               [num](double& x) { return (x / num); });
		update_norm();
		return *this;
	}

	euclidean_vector::operator std::vector<double>() const noexcept {
		auto vec =
		   std::vector<double>(this->magnitude_.get(), this->magnitude_.get() + this->dimensions());
		return vec;
	}

	euclidean_vector::operator std::list<double>() const noexcept {
		auto list =
		   std::list<double>(this->magnitude_.get(), this->magnitude_.get() + this->dimensions());
		return list;
	}

	///////////////
	// Members
	///////////////
	auto euclidean_vector::at(int i) const -> double {
		if (i < 0 or i >= this->dimensions()) {
			throw comp6771::euclidean_vector_error("Index " + std::to_string(i)
			                                       + " is not valid for this euclidean_vector object");
		}
		return this->magnitude_.get()[i];
	}

	auto euclidean_vector::at(int i) -> double& {
		if (i < 0 or i >= this->dimensions()) {
			throw comp6771::euclidean_vector_error("Index " + std::to_string(i)
			                                       + " is not valid for this euclidean_vector object");
		}
		return this->magnitude_.get()[i];
	}

	auto euclidean_vector::dimensions() const noexcept -> int {
		return static_cast<int>(this->dims_);
	}

	///////////////
	// FRIENDS
	///////////////
	auto operator==(euclidean_vector const& vec1, euclidean_vector const& vec2) noexcept -> bool {
		return vec1.dimensions() == vec2.dimensions();
	}

	auto operator!=(euclidean_vector const& vec1, euclidean_vector const& vec2) noexcept -> bool {
		return not(vec1 == vec2);
	}

	auto operator+(euclidean_vector const& vec1, euclidean_vector const& vec2) -> euclidean_vector {
		if (vec1.dimensions() != vec2.dimensions()) {
			throw comp6771::euclidean_vector_error(
			   "Dimensions of LHS(" + std::to_string(vec1.dimensions()) + ") and RHS("
			   + std::to_string(vec2.dimensions()) + ") do not match");
		}
		auto result = euclidean_vector(vec1.dimensions());
		std::transform(vec1.magnitude_.get(),
		               vec1.magnitude_.get() + vec1.dimensions(),
		               vec2.magnitude_.get(),
		               result.magnitude_.get(),
		               std::plus<>());
		result.update_norm();
		return result;
	}

	auto operator-(euclidean_vector const& vec1, euclidean_vector const& vec2) -> euclidean_vector {
		if (vec1.dimensions() != vec2.dimensions()) {
			throw comp6771::euclidean_vector_error(
			   "Dimensions of LHS(" + std::to_string(vec1.dimensions()) + ") and RHS("
			   + std::to_string(vec2.dimensions()) + ") do not match");
		}
		auto result = euclidean_vector(vec1.dimensions());
		std::transform(vec1.magnitude_.get(),
		               vec1.magnitude_.get() + vec1.dimensions(),
		               vec2.magnitude_.get(),
		               result.magnitude_.get(),
		               std::minus<>());
		result.update_norm();
		return result;
	}

	auto operator*(euclidean_vector const& vec, double num) noexcept -> euclidean_vector {
		auto result = euclidean_vector(vec.dimensions());
		std::transform(vec.magnitude_.get(),
		               vec.magnitude_.get() + vec.dimensions(),
		               result.magnitude_.get(),
		               [num](double& x) { return (x * num); });
		result.update_norm();
		return result;
	}

	auto operator*(double num, euclidean_vector const& vec) noexcept -> euclidean_vector {
		auto result = euclidean_vector(vec.dimensions());
		std::transform(vec.magnitude_.get(),
		               vec.magnitude_.get() + vec.dimensions(),
		               result.magnitude_.get(),
		               [num](double& x) { return (x * num); });
		result.update_norm();
		return result;
	}

	auto operator/(euclidean_vector const& vec, double num) -> euclidean_vector {
		if (num == 0) {
			throw comp6771::euclidean_vector_error("Invalid vector division by 0");
		}
		auto result = euclidean_vector(vec.dimensions());
		std::transform(vec.magnitude_.get(),
		               vec.magnitude_.get() + vec.dimensions(),
		               result.magnitude_.get(),
		               [num](double& x) { return (x / num); });
		result.update_norm();
		return result;
	}

	auto operator<<(std::ostream& stream, euclidean_vector const& vec) noexcept -> std::ostream& {
		stream << "[";
		if (vec.dimensions() != 0) {
			std::copy(vec.magnitude_.get(),
			          vec.magnitude_.get() + vec.dimensions() - 1, // copies up to 2nd last value to
			                                                       // avoid an unnecessary space at the
			                                                       // end before the ']'
			          std::ostream_iterator<double>(stream, " "));
			stream << vec.magnitude_.get()[vec.dimensions() - 1];
		}
		stream << "]";
		return stream;
	}

	///////////////
	// Utility
	///////////////

	// Return the euclidean normal
	auto euclidean_norm(euclidean_vector const& v) noexcept -> double {
		return v.norm_;
	}

	// Find the unit vector for a specific euclidean vector
	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw comp6771::euclidean_vector_error("euclidean_vector with no dimensions does not have "
			                                       "a unit vector");
		}
		if (v.norm_ == 0) {
			throw comp6771::euclidean_vector_error("euclidean_vector with zero euclidean normal does "
			                                       "not have a unit vector");
		}
		auto unit_vec = euclidean_vector(v.dimensions());
		std::transform(v.magnitude_.get(),
		               v.magnitude_.get() + v.dimensions(),
		               unit_vec.magnitude_.get(),
		               [v](double& x) { return (x / v.norm_); });
		unit_vec.update_norm();
		return unit_vec;
	}

	// Find the dot product between two vectors
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			throw comp6771::euclidean_vector_error("Dimensions of LHS("
			                                       + std::to_string(x.dimensions()) + ") and RHS("
			                                       + std::to_string(y.dimensions()) + ") do not match");
		}
		auto dot_product = std::inner_product(x.magnitude_.get(),
		                                      x.magnitude_.get() + x.dimensions(),
		                                      y.magnitude_.get(),
		                                      0.0);
		return dot_product;
	}

	///////////////
	// Own Functions
	///////////////

	// Calculates the new normal after an operation has been performed. By caching the normal, it
	// reduces the amount of calculations if there are big euclidean vectors
	void euclidean_vector::update_norm() noexcept {
		auto norm = 0.0;
		if (this->dimensions() != 0) {
			norm = std::inner_product(this->magnitude_.get(),
			                          this->magnitude_.get() + this->dimensions(),
			                          this->magnitude_.get(),
			                          0.0);
		}
		this->norm_ = sqrt(norm);
	}

} // namespace comp6771
