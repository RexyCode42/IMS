#pragma once

#include <string>
#include <string_view>
#include <algorithm>
#include <ranges>
#include <unordered_set>

class StringValidator {
protected:
	[[nodiscard]] bool isEmpty(std::string_view str) const;

	[[nodiscard]] bool hasValidLength(
		std::string_view str,
		const std::size_t& minLengthLimit,
		const std::size_t& maxLengthLimit) const;

	[[nodiscard]] bool containsAlphaCharacter(std::string_view str) const;

	[[nodiscard]] bool containsDigit(std::string_view category) const;

	[[nodiscard]] bool containsSpecialCharacter(std::string_view str) const;
};

class NameValidator : public StringValidator {
public:
	[[nodiscard]] bool isValid(std::string_view name) const;

	[[nodiscard]] std::size_t getMinLengthLimit() const;

	[[nodiscard]] std::size_t getMaxLengthLimit() const;

private:
	static constexpr std::size_t minLengthLimit_{ 2 };
	static constexpr std::size_t maxLengthLimit_{ 50 };
};

class CategoryValidator : public StringValidator {
public:
	[[nodiscard]] bool isValid(std::string_view category) const;

	[[nodiscard]] std::size_t getMinLengthLimit() const;

	[[nodiscard]] std::size_t getMaxLengthLimit() const;

private:
	static constexpr std::size_t minLengthLimit_{ 2 };
	static constexpr std::size_t maxLengthLimit_{ 50 };
};

class UnitPriceValidator {
public:
	[[nodiscard]] bool isValid(double unitPrice) const;

	[[nodiscard]] double getMinPriceLimit() const;

	[[nodiscard]] double getMaxPriceLimit() const;

private:
	static constexpr double minUnitPriceLimit_{ 0 };
	static constexpr double maxUnitPriceLimit_{ 500'000 };
};

class StockValidator {
public:
	[[nodiscard]] bool isValid(int stock) const;

	[[nodiscard]] int getMinStockLimit() const;

	[[nodiscard]] int getMaxStockLimit() const;

private:
	static constexpr int minStockLimit_{ 0 };
	static constexpr int maxStockLimit_{ 250'000 };
};
