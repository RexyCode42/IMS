#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <functional>
#include <vector>
#include <expected>
#include <string>

// This program uses std::expected<...> for the following advantages:
// 
// It offers better and clearer error handling than std::optional (i.e., more informative error codes).
// It offers numerous advantages over the conventional exception handling method,
// (i.e., no major memory allocations, no stack unwinding, no std::terminate, etc...) 
// 
// Potential disadvantages:
// 
// It is a newer language feature (as of 5/28/2024), hence, this could mean 
// less available literature, fewer examples, 
// and potentially less community support or expertise available.

namespace ErrorUtils {
	enum class ErrorCode : int;

	[[nodiscard]] std::string errorToMessage(const ErrorCode& error);

	[[nodiscard]] std::expected<bool, ErrorCode> isFilePathValid(const std::string& filePath);
}
