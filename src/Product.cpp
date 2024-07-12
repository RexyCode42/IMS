#include "product.h"

using namespace Inventory;

Product::Product(const std::string& id, const std::string& name,
	const std::string& category, double unitPrice, int stock) :
	id_{ id },
	name_{ name },
	category_{ category },
	unitPrice_{ unitPrice },
	stock_{ stock } {}

void Product::setId(const std::string& id) {
	id_ = id;
}

void Product::setName(const std::string& name) {
	name_ = name;
}

void Product::setCategory(const std::string& category) {
	category_ = category;
}

void Product::setPrice(double unitPrice) {
	unitPrice_ = unitPrice;
}

void Product::setStock(int stock) {
	stock_ = stock;
}

[[nodiscard]] std::string Product::getId() const noexcept {
	return id_;
}

[[nodiscard]] std::string Product::getName() const noexcept {
	return name_;
}

[[nodiscard]] std::string Product::getCategory() const noexcept {
	return category_;
}

[[nodiscard]] double Product::getPrice() const noexcept {
	return unitPrice_;
}

[[nodiscard]] int Product::getStock() const noexcept {
	return stock_;
}

[[nodiscard]] double Product::calculateInventoryValue() const noexcept {
	return unitPrice_ * stock_;
}

[[nodiscard]] std::string IdGenerator::generateId(const std::string& lastProductId) {
	if (const std::string defaultId{ "0000AA" }; lastProductId.empty())
		return defaultId;

	std::string newId{ lastProductId };

	// Explanation on why we use unsigned char with std::isdigit()
	// And other functions from the <cctype> header
	// https://en.cppreference.com/w/cpp/string/byte/isdigit
	const auto isDigit{ [](unsigned char digit) -> unsigned char { return std::isdigit(digit); } };
	const auto posFirstDigit{ std::find_if(std::rbegin(newId), std::rend(newId), isDigit) };

	if (isOutOfUniqueId(posFirstDigit, newId))
		return doubleIdSize(newId); // "9999ZZ" => "00000000AAAA"

	// Find position of first non-'9' digit
	const auto isDigit9{ [](char digit) { return (digit != '9'); } };
	const auto posDigit{ std::find_if(posFirstDigit, std::rend(newId), isDigit9) };

	if (std::size_t idLength{ newId.length() };
		posDigit == std::rend(newId)) {
		while (newId[--idLength] == 'Z');
		newId[idLength]++;
	}
	else {
		(*posDigit)++;
	}

	std::fill(posFirstDigit, posDigit, '0');

	return newId;
}

[[nodiscard]] bool IdGenerator::isOutOfUniqueId(const std::reverse_iterator<std::string::const_iterator> posFirstDigit,
	const std::string& newId) {
	const auto isAlphaZ{ [](unsigned char alpha) -> unsigned char { return (alpha == 'Z'); } };
	const auto isDigit9{ [](unsigned char digit) -> unsigned char { return (digit == '9'); } };

	return std::all_of(std::crbegin(newId), posFirstDigit, isAlphaZ) &&
		std::all_of(posFirstDigit, std::crend(newId), isDigit9);
}

[[nodiscard]] std::string IdGenerator::doubleIdSize(const std::string& newId) {
	const auto isDigit{ [](unsigned char digit) -> unsigned char { return std::isdigit(digit); } };
	const auto numberOfDigits{ std::ranges::count_if(newId, isDigit) };
	const auto numberOfChars{ newId.length() - numberOfDigits };

	std::string largerId;
	largerId.reserve(numberOfDigits * 2 + numberOfChars * 2);
	largerId.append(numberOfDigits * 2, '0');
	largerId.append(numberOfChars * 2, 'A');

	return largerId;
}
