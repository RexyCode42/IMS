#include "Validators.h"

[[nodiscard]] bool StringValidator::isEmpty(std::string_view str) const {
	return str.empty();
}

[[nodiscard]] bool StringValidator::hasValidLength(
	std::string_view str,
	const std::size_t& minLengthLimit,
	const std::size_t& maxLengthLimit) const {
	return str.length() >= minLengthLimit && str.length() <= maxLengthLimit;
}

[[nodiscard]] bool StringValidator::containsAlphaCharacter(std::string_view str) const {
	const auto isAlpha{ [](unsigned char ch) -> unsigned char { return std::isalpha(ch); } };
	return std::ranges::any_of(str, isAlpha);
}

[[nodiscard]] bool StringValidator::containsDigit(std::string_view category) const {
	const auto isDigit{ [](unsigned char ch) -> unsigned char { return std::isdigit(ch); } };
	return std::ranges::any_of(category, isDigit);
}

[[nodiscard]] bool StringValidator::containsSpecialCharacter(std::string_view str) const {
	const std::unordered_set<char> illegalCharacters{
		'!', '\"', '#', '$', '%', '&',
		'\'', '(', ')', '*', '+', ',',
		'/', '<', '=', '>', '?', '@',
		'[', '\\', ']', '^', '`', '{',
		'|', '}', '~'
	};

	const auto isSpecialCharacter{ [&illegalCharacters](char ch) { return illegalCharacters.contains(ch); } };

	return std::ranges::any_of(str, isSpecialCharacter);
}

[[nodiscard]] bool NameValidator::isValid(std::string_view name) const
{
	return
		!StringValidator::isEmpty(name) &&
		StringValidator::hasValidLength(name, minLengthLimit_, maxLengthLimit_) &&
		StringValidator::containsAlphaCharacter(name) &&
		!StringValidator::containsSpecialCharacter(name);
}

[[nodiscard]] std::size_t NameValidator::getMinLengthLimit() const {
	return minLengthLimit_;
}

[[nodiscard]] std::size_t NameValidator::getMaxLengthLimit() const {
	return maxLengthLimit_;
}

[[nodiscard]] bool CategoryValidator::isValid(std::string_view category) const
{
	return
		!StringValidator::isEmpty(category) &&
		StringValidator::hasValidLength(category, minLengthLimit_, maxLengthLimit_) &&
		!StringValidator::containsDigit(category) &&
		StringValidator::containsAlphaCharacter(category) &&
		!StringValidator::containsSpecialCharacter(category);
}

[[nodiscard]] std::size_t CategoryValidator::getMinLengthLimit() const {
	return minLengthLimit_;
}

[[nodiscard]] std::size_t CategoryValidator::getMaxLengthLimit() const {
	return maxLengthLimit_;
}

[[nodiscard]] bool UnitPriceValidator::isValid(double unitPrice) const {
	return (unitPrice > minUnitPriceLimit_ && unitPrice <= maxUnitPriceLimit_);
}

[[nodiscard]] double UnitPriceValidator::getMinPriceLimit() const {
	return minUnitPriceLimit_;
}

[[nodiscard]] double UnitPriceValidator::getMaxPriceLimit() const {
	return maxUnitPriceLimit_;
}

[[nodiscard]] bool StockValidator::isValid(int stock) const {
	return (stock >= minStockLimit_ && stock <= maxStockLimit_);
}

[[nodiscard]] int StockValidator::getMinStockLimit() const {
	return minStockLimit_;
}

[[nodiscard]] int StockValidator::getMaxStockLimit() const {
	return maxStockLimit_;
}