#pragma once

#include <string>
#include <string_view>
#include <algorithm>
#include <ranges>
#include <unordered_set>

// Ensure that a validator has an isValid function
// which takes a parameter of type T and returns a bool indicating the validity of the input.
template<class Validator, typename T>
concept ValidatorConcept = requires(const Validator & validator, const T& t) {
	{ validator.isValid(t) } -> std::same_as<bool>;
};

class StringValidator {
protected:
	[[nodiscard]] bool hasValidLength(
		std::string_view str,
		const std::size_t& minLength,
		const std::size_t& maxLength) const;

	[[nodiscard]] bool containsLetter(std::string_view str) const;

	[[nodiscard]] bool containsDigit(std::string_view category) const;

	[[nodiscard]] bool containsSpecialCharacter(std::string_view str) const;
};

class NameValidator : public StringValidator {
public:
	[[nodiscard]] bool isValid(std::string_view name) const;

	[[nodiscard]] std::size_t getMinLength() const noexcept;

	[[nodiscard]] std::size_t getMaxLength() const noexcept;

private:
	static constexpr std::size_t minLength_{ 2 };
	static constexpr std::size_t maxLength_{ 50 };
};

class CategoryValidator : public StringValidator {
public:
	[[nodiscard]] bool isValid(std::string_view category) const;

	[[nodiscard]] std::size_t getMinLength() const noexcept;

	[[nodiscard]] std::size_t getMaxLength() const noexcept;

private:
	static constexpr std::size_t minLength_{ 2 };
	static constexpr std::size_t maxLength_{ 50 };
};

class UnitPriceValidator {
public:
	[[nodiscard]] bool isValid(double unitPrice) const;

	[[nodiscard]] double getMinPrice() const noexcept;

	[[nodiscard]] double getMaxPrice() const noexcept;

private:
	static constexpr double minUnitPrice_{ 0 };
	static constexpr double maxUnitPrice_{ 500'000 };
};

class StockValidator {
public:
	[[nodiscard]] bool isValid(int stock) const;

	[[nodiscard]] int getMinStock() const noexcept;

	[[nodiscard]] int getMaxStock() const noexcept;

private:
	static constexpr int minStock_{ 0 };
	static constexpr int maxStock_{ 250'000 };
};
