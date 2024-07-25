#include "InMemoryStorage.h"

using namespace Inventory;

InMemoryProductStorage::InMemoryProductStorage(const std::vector<Product>& products)
    : products_{ products } {}

void InMemoryProductStorage::add(const Product& product) {
    if (exists(product)) {
        std::cerr << "Product Already Exists: " << product.getName() << '\n';
        return;
    }

    products_.emplace_back(product);
    std::cout << "Successfully added: " << product.getName() << '\n';
}

void InMemoryProductStorage::remove(std::string_view productName) {
    const auto productPos{ std::ranges::find_if(products_, [&productName](const Product& product)
        { return product.getName() == productName; })
    };

    if (productPos == products_.end()) {
        std::cerr << "Product not found: " << productName << '\n';
        return;
    }

    products_.erase(productPos);
    std::cout << "Successfully removed: " << productName << '\n';
}

[[nodiscard]] bool InMemoryProductStorage::exists(const Product& product) const {
    return std::ranges::any_of(products_, [&product](const Product& other) {
        return other.getName() == product.getName();
    });
}

[[nodiscard]] std::vector<Product> InMemoryProductStorage::getProducts() const noexcept {
    return products_;
}