#pragma once

#include "../Product.h"

namespace Inventory {
    class InMemoryProductStorage {
    public:
        explicit InMemoryProductStorage(const std::vector<Product>& products = {});
        void add(const Product& product);
        void remove(std::string_view productName);
        [[nodiscard]] bool exists(const Product& product) const;
        [[nodiscard]] std::vector<Product> getProducts() const noexcept;

    private:
        std::vector<Product> products_;
    };
}