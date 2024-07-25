// #include "ManagementSystem.h"
#include <iostream>
#include <functional>
#include <vector>
#include <unordered_set>
#include <limits>
#include <expected>
#include "Product.h"
#include "StringUtils.h"
#include "DataAccess/InMemoryStorage.h"
#include "ErrorHandling/ProductValidation/ProductAttributeValidator.h"

// IMS = Inventory Management System
//class IUserInteraction {
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

void clearFlagsAndIgnoreInvalidInput() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string promptForNameAndFormatIt() {
	ProductAttributeValidator productNameValidator{ NameValidator{}  };
	std::string name{};

	do {
		std::cout << "Enter product name: ";
		std::getline(std::cin, name);
	} while (!productNameValidator.isValid(name));

	FormatString::trimEdgesAndBody(name);
	FormatString::toUpperAll(name);

	return name;
}

std::string promptForCategoryAndFormatIt() {
	ProductAttributeValidator productCategoryValidator{ CategoryValidator{} };
	std::string category{};

	do {
		std::cout << "Enter product category: ";
		std::getline(std::cin, category);
	} while (!productCategoryValidator.isValid(category));

	FormatString::trimEdgesAndBody(category);
	FormatString::toUpperAll(category);

	return category;
}

double promptForProductPrice() {
	ProductAttributeValidator productUnitPriceValidator{ UnitPriceValidator{} };
	double unitPrice{};

	do {
		std::cout << "Enter product price: ";
		if (!(std::cin >> unitPrice))
			clearFlagsAndIgnoreInvalidInput();
	} while (!productUnitPriceValidator.isValid(unitPrice));

	return unitPrice;
}

int promptForProductStock() {
	ProductAttributeValidator productStockValidator{ StockValidator{} };
	int stock{};

	do {
		std::cout << "Enter product stock: ";
		if (!(std::cin >> stock))
			clearFlagsAndIgnoreInvalidInput();
	} while (!productStockValidator.isValid(stock));

	return stock;
}

std::tuple<std::string, std::string, std::string, double, int>
getProductAttributes(const std::string& lastProductId) {
	Inventory::IdGenerator idGenerator{};
	const std::string id{ idGenerator.generateId(lastProductId) };
	const std::string name{ promptForNameAndFormatIt() };
	const std::string category{ promptForCategoryAndFormatIt() };
	const double unitPrice{ promptForProductPrice() };
	const int stock{ promptForProductStock() };
	return { id, name, category, unitPrice, stock };
}

Inventory::Product createProduct(
	const std::tuple<std::string, std::string, std::string, double, int>& attributes) {
	const auto [id, name, category, unitPrice, stock] {attributes};
	return Inventory::Product{ id, name, category, unitPrice, stock };
}

void addProduct(Inventory::InMemoryProductStorage& inMemoryProductStorage) {
	const std::string lastProductId{ (!inMemoryProductStorage.getProducts().empty()) ?
		inMemoryProductStorage.getProducts().back().getId() : ""
	};
	const auto attributes{ getProductAttributes(lastProductId) };
	const auto product{ createProduct(attributes) };
	inMemoryProductStorage.add(product);
}

int main() {
    Inventory::InMemoryProductStorage inMemoryProductStorage{};
	addProduct(inMemoryProductStorage);
	std::cout
		<< inMemoryProductStorage.getProducts().back().getId() << " "
		<< inMemoryProductStorage.getProducts().back().getName() << " "
		<< inMemoryProductStorage.getProducts().back().getCategory() << " "
		<< inMemoryProductStorage.getProducts().back().getPrice() << " "
		<< inMemoryProductStorage.getProducts().back().getStock() << " "
		<< inMemoryProductStorage.getProducts().back().calculateInventoryValue();

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


