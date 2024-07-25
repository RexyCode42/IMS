#pragma once

#include "Validators.h"
#include <concepts>
#include <type_traits>
#include <string>

template <class Validator>
concept StringValidatorType = requires(const Validator & validator, const std::string& s) {
	{ validator.isValid(s) } -> std::same_as<bool>;
};

template <class Validator>
concept DoubleValidatorType = requires(const Validator & validator, double d) {
	{ validator.isValid(d) } -> std::same_as<bool>;
};

template <class Validator>
concept IntValidatorType = requires(const Validator & validator, int i) {
	{ validator.isValid(i) } -> std::same_as<bool>;
};

template<typename T>
struct dependent_false : public std::false_type {};

template<class Validator>
class ProductAttributeValidator {
public:
	explicit ProductAttributeValidator(const Validator& validator) : validator_{ validator } {}

	template<typename T>
	[[nodiscard]] bool isValid(const T& var) const {
		if constexpr (
			std::same_as<T, std::string> && StringValidatorType<Validator> ||
			std::same_as<T, double> && DoubleValidatorType<Validator> ||
			std::same_as<T, int> && IntValidatorType<Validator>) {
			return validator_.isValid(var);
		}
		else {
			// Professional Definition: 
			// Use dependent_false<T>::value for dependent context-specific static assertion.
			// 
			// Clearer Definition: 
			// Use dependent_false<T>::value to delay the error until the actual code path is instantiated.
			// This technique is used to make the error dependent on the template parameter, 
			// providing a more meaningful and context-specific error message.
			static_assert(dependent_false<T>::value,
				"The Validator's isValid() function violates the interface contract. Check for any spelling mistakes or unsupported types. The supported types are: std::string, double, and int.");
		}
	}

private:
	Validator validator_;
};

 