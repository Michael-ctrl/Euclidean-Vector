#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <cmath>
#include <list>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// Constructors
		euclidean_vector() noexcept; // Default Constructor

		explicit euclidean_vector(int dim) noexcept; // Single Argument Constructor

		euclidean_vector(int dim, double mag) noexcept; // Constructor

		euclidean_vector(std::vector<double>::const_iterator first,
		                 std::vector<double>::const_iterator last) noexcept; // Constructor

		euclidean_vector(std::initializer_list<double>) noexcept; // Constructor

		euclidean_vector(euclidean_vector const&); // Copy Constructor

		euclidean_vector(euclidean_vector&&) noexcept; // Move Constructor

		// Destructor
		~euclidean_vector();

		// Operations
		auto operator=(euclidean_vector const& vec) noexcept -> euclidean_vector&; // Copy Assignment

		auto operator=(euclidean_vector&& vec) noexcept -> euclidean_vector&; // Move Assignment

		auto operator[](int i) noexcept -> double&; // Subscript

		auto operator[](int i) const noexcept -> double; // Subscript

		auto operator+() const noexcept -> euclidean_vector; // Unary Plus

		auto operator-() const noexcept -> euclidean_vector; // Negation

		auto operator+=(euclidean_vector const& vec) -> euclidean_vector&; // Compound Addition

		auto operator-=(euclidean_vector const& vec) -> euclidean_vector&; // Compound Subtraction

		auto operator*=(double num) noexcept -> euclidean_vector&; // Compound Multiplication

		auto operator/=(double num) -> euclidean_vector&; // Compound Division

		explicit operator std::vector<double>() const noexcept; // Vector Type Conversion

		explicit operator std::list<double>() const noexcept; // List Type Conversion

		// Member
		[[nodiscard]] auto at(int i) const -> double; // Magnitude value at certain vector position

		auto at(int i) -> double&; // Magnitude value reference at certain vector position

		[[nodiscard]] auto dimensions() const noexcept -> int; // Vector dimensions

		// Friends
		friend auto operator==(euclidean_vector const&, euclidean_vector const&) noexcept -> bool;

		friend auto operator!=(euclidean_vector const&, euclidean_vector const&) noexcept -> bool;

		friend auto operator+(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;

		friend auto operator-(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;

		friend auto operator*(euclidean_vector const&, double) noexcept -> euclidean_vector;

		friend auto operator*(double, euclidean_vector const&) noexcept -> euclidean_vector;

		friend auto operator/(euclidean_vector const&, double) -> euclidean_vector;

		friend auto operator<<(std::ostream&, euclidean_vector const&) noexcept -> std::ostream&;

		// Utility Friends
		friend auto euclidean_norm(euclidean_vector const& v) noexcept -> double;

		friend auto unit(euclidean_vector const& v) -> euclidean_vector;

		friend auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;

		// Own functions
		void update_norm() noexcept;

	private:
		std::size_t dims_; // Dimensions of the euclidean array
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;

		double norm_; // Euclidean Normal
	};

	// Utility Declaration

	auto euclidean_norm(euclidean_vector const& v) noexcept -> double;

	auto unit(euclidean_vector const& v) -> euclidean_vector;

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
