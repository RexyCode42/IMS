#include "UserInput.h"

Inventory::Product UserInterface::createProduct(const std::tuple<std::string,
	std::string, std::string, double, int>& attributes) {
	const auto [id, name, category, unitPrice, stock] {attributes};
	return Inventory::Product{ id, name, category, unitPrice, stock };
}

std::tuple<std::string, std::string, std::string, double, int> 
UserInterface::getProductAttributes(const std::string& lastProductId) {
	Inventory::IdGenerator idGenerator{};
	const std::string id{ idGenerator.generateId(lastProductId) };
	const std::string name{ UserInterface::promptForProductName() };
	const std::string category{ UserInterface::promptForProductCategory() };
	const double unitPrice{ UserInterface::promptForProductPrice() };
	const int stock{ UserInterface::promptForProductStock() };
	return { id, name, category, unitPrice, stock };
}

void UserInterface::clearFlagAndIgnoreInvalidInput() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string UserInterface::promptForProductName() {
	std::string name{};

	do {
		std::cout << "Enter product name: ";
		std::getline(std::cin, name);
	} while (false);

	return name;
}

std::string UserInterface::promptForProductCategory() {
	std::string category{};

	do {
		std::cout << "Enter product category: ";
		std::getline(std::cin, category);
	} while (false);

	return category;
}

double UserInterface::promptForProductPrice() {
	double unitPrice{};

	do {
		std::cout << "Enter product price: ";
		std::cin >> unitPrice;
	} while (false);

	return unitPrice;
}

int UserInterface::promptForProductStock() {
	int stock{};

	do {
		std::cout << "Enter product stock: ";
		std::cin >> stock;
	} while (false);

	return stock;
}