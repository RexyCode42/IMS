#include "ErrorHandling.h"

enum class ErrorUtils::ErrorCode : int {
	ERROR_FILE_NOT_FOUND,
	ERROR_INVALID_NAME,
	ERROR_INVALID_CATEGORY, 
	ERROR_INVALID_PRICE,
	ERROR_INVALID_QUANTITY
};

[[nodiscard]] std::string ErrorUtils::errorToMessage(const ErrorCode& error) {
	using ErrorUtils::ErrorCode;
	switch (error) {
	case ErrorCode::ERROR_FILE_NOT_FOUND:
		return "Error: File Not Found";
	case ErrorCode::ERROR_INVALID_NAME:
		return "Error: Violated Name Requirements";
	case ErrorCode::ERROR_INVALID_CATEGORY:
		return "Error: Violated Category Requirements";
	case ErrorCode::ERROR_INVALID_PRICE:
		return "Error: Violated Price Requirements";
	case ErrorCode::ERROR_INVALID_QUANTITY:
		return "Error: Violated Quanity Requirements";
	default:
		return "Error: Unknown";
	}
}

[[nodiscard]] std::expected<bool, ErrorUtils::ErrorCode>
ErrorUtils::isFilePathValid(const std::string& filePath) {
	return (std::filesystem::exists(filePath)) ? 
		std::expected<bool, ErrorCode>(true) : 
		std::unexpected(ErrorCode::ERROR_FILE_NOT_FOUND);
}
