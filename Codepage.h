#pragma once

#include "gtl/gtl.h"

#include <unicode/ucnv.h>
#include <unicode/ucsdet.h>

namespace gtl {
	using uchar = unsigned char;
	enum class eFILE_TYPE { unknown = -1, ansi, utf8, utf16le, utf16be, utf32le, utf32be };

	//eFILE_TYPE GetFileBOM(std::filesystem::path const& path, std::vector<int>& lines);
	eFILE_TYPE ReadFileBOM(std::filesystem::path const& path);
	std::string DetectCodepage(std::string_view str);
	std::string DetectCodepage(std::filesystem::path const& path);
	bool CheckCodepageFolder(std::filesystem::path const& folder);

	int GetCharSizeFromCodepage(std::string codepage);
}
