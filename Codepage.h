#pragma once

#include "gtl/gtl.h"

namespace gtl {
	using uchar = unsigned char;
	enum class eFILE_TYPE { unknown = -1, ansi, utf8, utf16le, utf16be, utf32le, utf32be };

	eFILE_TYPE CheckCodepage(std::filesystem::path const& path, std::vector<int>& lines);
	bool CheckCodepageFolder(std::filesystem::path const& folder);

}
