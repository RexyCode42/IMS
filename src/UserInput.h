#include "ErrorHandling.h"
#include "Product.h"

#pragma once

namespace UserInterface {
	[[nodiscard]] Inventory::Product createProduct(const std::tuple<std::string,
		std::string, std::string, double, int>& attributes);

	[[nodiscard]] std::tuple<std::string, std::string, std::string, double, int> 
		getProductAttributes(const std::string& lastProductId);

	void clearFlagAndIgnoreInvalidInput();

	[[nodiscard]] std::string promptForProductName();

	[[nodiscard]] std::string promptForProductCategory();

	[[nodiscard]] double promptForProductPrice();

	[[nodiscard]] int promptForProductStock();
}