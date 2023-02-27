module;

#include "gtl/gtl.h"

#include "gtl/string/HangeulCodeMap.h"

export module Codepage;

import gtl_string_convert_codepage_utf16_to_kssm;

export namespace Codepage {
	using uchar = unsigned char;
	enum class eFILE_TYPE { unknown = -1, ansi, utf8, utf16le, utf16be, utf32le, utf32be };

	std::pair<eFILE_TYPE, int> CheckCodepage(std::filesystem::path const& path) {
		constexpr static std::array<std::pair<std::string_view, eFILE_TYPE>, 5> const codepages{{
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF8), eFILE_TYPE::utf8},
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF32LE), eFILE_TYPE::utf32le},	// UTF32LE must precede UTF16LE
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF16LE), eFILE_TYPE::utf16le},
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF16BE), eFILE_TYPE::utf16be},
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF32BE), eFILE_TYPE::utf32be},
			}};

		auto rbuffer = gtl::FileToBuffer<uchar>(path);
		if (!rbuffer)
			return {eFILE_TYPE::unknown, 0};
		std::span buffer = *rbuffer;

		eFILE_TYPE type = eFILE_TYPE::ansi;
		for (auto const& [sv, codepage] : codepages) {
			if (buffer.size() >= sv.size() and std::memcmp(buffer.data(), sv.data(), sv.size()) == 0) {
				type = codepage;
				buffer = buffer.subspan(sv.size());
				break;
			}
		}

		if (type == eFILE_TYPE::utf8 or type == eFILE_TYPE::ansi) {
			bool bMSB{};
			if (!gtl::IsUTF8String(std::string_view((char*)buffer.data(), buffer.size()), nullptr, &bMSB))
				return {eFILE_TYPE::unknown, 0};
			if (!bMSB)
				return {eFILE_TYPE::ansi, 0};
		}

		std::wstring content;
		if (type == eFILE_TYPE::utf8 or type == eFILE_TYPE::ansi)
			content = gtl::ToString<wchar_t>(std::u8string_view((char8_t*)buffer.data(), buffer.size()));
		else if (type == eFILE_TYPE::utf16le) {
			content.assign(buffer.size()/2 -1, 0);
			memcpy(content.data(), buffer.data() + 2, buffer.size() - 2);
		}

		auto const& map = gtl::charset::KSSM::mapUTF16toKSSM_g;
		int line{};
		for (auto c : content) {
			static_assert(std::is_unsigned_v<wchar_t> and std::is_unsigned_v<char16_t>);
			if (c == '\n')
				line++;
			if (c <= 127)
				continue;
			if (map.find((char16_t)c) == map.end())
				return {eFILE_TYPE::unknown, line};
		}

		return {type, 0};
	}

	bool CheckCodepageFolder(std::filesystem::path const& folder) {
		return true;
	}

}
