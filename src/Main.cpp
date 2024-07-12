// #include "ManagementSystem.h"
#include <iostream>
#include <functional>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <ranges>
#include <limits>
#include <expected>
#include "StringUtils.h"

// IMS = Inventory Management System
//class IIMSUserInteraction {
//public:
//	virtual void showMessage(const std::string& message) const = 0;
//
//	virtual ~IIMSUserInteraction() = default;
//};
//
//class ConsoleUserInteraction : IIMSUserInteraction {
//public:
//	void showMessage(const std::string& message) const override {
//		std::cout << message << std::endl;
//	}
//};

enum class ErrorCode {
	ERROR_PRODUCT_ALREADY_EXISTS,
	ERROR_EMPTY_INVENTORY,
	ERROR_PRODUCT_DOES_NOT_EXIST
};

//[[nodiscard]] std::string errorToMessage(const ErrorCode& error) {
//	switch (error) {
//	case ErrorCode::ERROR_PRODUCT_ALREADY_EXISTS:
//		return "Error: Product Already Exists";
//	case ErrorCode::ERROR_EMPTY_INVENTORY:
//		return "Error: Cannot Remove Products From Empty Inventory";
//	default:
//		return "Error: Unknown";
//	}
//}

class SearchProductAttributes {
public:
	std::expected<Product, ErrorCode> searchName(
		const std::vector<Product>& products, 
		const std::string_view name) const {
		const auto cmpProductName{ [name](const Product& product) { return product.name == name; } };
		const auto productExists{ std::ranges::find_if(products, cmpProductName) };
		return (productExists != std::end(products)) ? 
			std::expected<Product, ErrorCode>(*productExists) :
			std::unexpected(ErrorCode::ERROR_PRODUCT_DOES_NOT_EXIST);
	}
};

struct Product {
	std::string name;
	double price;
};

class IProductStorage {
public:
	virtual ~IProductStorage() = default;
	virtual void add(const Product& product) = 0;
	virtual void remove() = 0;
	[[nodiscard]] virtual bool exists(const Product& product) const = 0;
};

class InMemoryStorage : IProductStorage {
public:
	void add(const Product& product) override;
	
	void remove() override;

	[[nodiscard]] bool exists(const Product& product) const override;

private:
	std::vector<Product> products;
};

void InMemoryStorage::add(const Product& product)
{
	if (exists(product)) {
		std::cerr << "Product Already Exists" << std::endl;
		return;
	}

	products.emplace_back(product);
	std::cout << "Successfully added: " << product.name << std::endl;
}

void InMemoryStorage::remove()
{
	// Implement Later...
}

[[nodiscard]] bool InMemoryStorage::exists(const Product& product) const {
	const auto cmpProductName{ [&product](const Product& other) { return (other.name == product.name); } };
	const auto productExists{ std::ranges::find_if(products, cmpProductName) };

	return productExists != std::end(products);
}

void formatProduct(Product& product) {
	FormatString::trimEdgesAndBody(product.name);
	FormatString::toUpperAll(product.name);
}

int main() {	
	InMemoryStorage inMemory{};
	Product product{ "carrot", 0.85 };
	formatProduct(product);
	inMemory.add(product);
	product.name = "leek";
	product.price = 0.85;
	formatProduct(product);
	inMemory.add(product);

	product.name = "carrot";
	product.price = 0.85;
	formatProduct(product);
	inMemory.add(product);
	product.name = "orange";
	product.price = 0.85;
	formatProduct(product);
	inMemory.add(product);

	//void AddProduct() {
	//	auto newProduct{ createProduct() };
	//	formatProduct(newProduct);
	//	addToInMemory(newProduct);
	//}

	/*std::cout << "Name requirements:" << std::endl;
	std::cout << "- Special characters allowed: :;-_." << std::endl;
	std::cout << "- Must contain at least one letter" << std::endl;
	std::cout << "- Must be greater than or equal to " << 2 << " characters" << std::endl;
	std::cout << "- Must be lesser than or equal to " << 50 << " characters" << std::endl;
	std::cout << std::endl;*/
}


