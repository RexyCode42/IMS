#include "StringUtils.h"

void FormatString::toUpperAll(std::string& str) {
	const auto toUpper{ [](unsigned char ch) -> unsigned char { return std::toupper(ch); } };
	std::ranges::transform(str, std::begin(str), toUpper);
}

void FormatString::trimLeft(std::string& str) {
	if (str.empty())
		return;

	const auto isSpace{ [](unsigned char ch) -> unsigned char { return std::isspace(ch); } };
	str.erase(std::begin(str), std::ranges::find_if_not(str, isSpace));
}

void FormatString::trimRight(std::string& str) {
	if (str.empty())
		return;

	const auto isSpace{ [](unsigned char ch) -> unsigned char { return std::isspace(ch); } };
	const auto reversedStr{ str | std::views::reverse };
	str.erase(std::ranges::find_if_not(reversedStr, isSpace).base(), std::end(str));
}

void FormatString::trimBody(std::string& str) {
	if (str.empty())
		return;

	const auto isConsecutiveWhiteSpace{
		[](unsigned char ch1, unsigned char ch2) -> unsigned char
		{ return std::isspace(ch1) && std::isspace(ch2); }
	};

	const auto newStrEnd{ std::unique(std::begin(str), std::end(str), isConsecutiveWhiteSpace) };

	str.erase(newStrEnd, std::end(str));
}

void FormatString::trimEdgesAndBody(std::string& str) {
	if (str.empty())
		return;

	trimLeft(str);

	trimRight(str);

	trimBody(str);
}