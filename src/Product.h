#pragma once

#include "ErrorHandling.h"

namespace Inventory {
	class Product {
	public:
		Product() = delete; // Make sure that the object is always initialized

		Product(const std::string& id, const std::string& name, 
			const std::string& category, double unitPrice, int stock);

		void setId(const std::string& id);
		void setName(const std::string& name);
		void setCategory(const std::string& category);
		void setPrice(double unitPrice);
		void setStock(int stock);

		[[nodiscard]] std::string getId() const noexcept;
		[[nodiscard]] std::string getName() const noexcept;
		[[nodiscard]] std::string getCategory() const noexcept;
		[[nodiscard]] double getPrice() const noexcept;
		[[nodiscard]] int getStock() const noexcept;
		[[nodiscard]] double calculateInventoryValue() const noexcept;

	private:
		std::string id_{};
		std::string name_{};
		std::string category_{};
		double unitPrice_{};
		int stock_{};
	};

	// Product ID Characteristics: 4 digits ('0', '1', ..., '9') and 2 char ('A', 'B', ..., 'Z')
	// Unique ID combinations: 10'000 (digits) * 52 (alpha char) = 520'000
	// If there are no unique ID combinations left, 
	// Double the size of the ID and start over ("9999ZZ" -> "00000000AAAA")
	class IdGenerator {
	public:		
		[[nodiscard]] std::string generateId(const std::string& lastProductId);

	private:
		[[nodiscard]] bool isOutOfUniqueId(const std::reverse_iterator<std::string::const_iterator> posFirstDigit,
			const std::string& newId);

		[[nodiscard]] std::string doubleIdSize(const std::string& newId);
	};
}

