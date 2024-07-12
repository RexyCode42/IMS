#pragma once

#include <string>
#include <algorithm>
#include <cctype>
#include <ranges>
#include <iterator>

namespace FormatString {
	void toUpperAll(std::string& str);

	// https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
	void trimLeft(std::string& str);

	void trimRight(std::string& str);

	void trimBody(std::string& str);

	void trimEdgesAndBody(std::string& str);
}
