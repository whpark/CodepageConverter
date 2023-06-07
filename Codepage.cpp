#include "pch.h"
#include "Codepage.h"

#include "gtl/gtl.h"

#include "gtl/string/HangeulCodeMap.h"
#include "KSSM.h"

namespace gtl {

	eFILE_TYPE ReadFileBOM(std::filesystem::path const& path) {
		constexpr static std::array<std::pair<std::string_view, eFILE_TYPE>, 5> const codepages{{
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF8), eFILE_TYPE::utf8},
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF32LE), eFILE_TYPE::utf32le},	// UTF32LE must precede UTF16LE
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF16LE), eFILE_TYPE::utf16le},
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF16BE), eFILE_TYPE::utf16be},
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF32BE), eFILE_TYPE::utf32be},
			}};

		eFILE_TYPE type = eFILE_TYPE::unknown;

		std::ifstream f(path, std::ios_base::binary);
		if (!f.seekg(0, std::ios_base::end))
			return type;

		auto file_len = f.tellg();
		if (file_len <= 0)
			return type;
		auto len = std::min<size_t>(16, file_len);
		std::vector<char> buffer(len, 0);
		f.seekg(0, std::ios_base::beg);
		f.read(buffer.data(), buffer.size());

		for (auto const& [sv, codepage] : codepages) {
			if (buffer.size() >= sv.size() and std::memcmp(buffer.data(), sv.data(), sv.size()) == 0) {
				type = codepage;
				break;
			}
		}
		return type;
	}

#if 0
	eFILE_TYPE GetFileBOM(std::filesystem::path const& path, std::vector<int>& lines) {
		constexpr static std::array<std::pair<std::string_view, eFILE_TYPE>, 5> const codepages{{
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF8), eFILE_TYPE::utf8},
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF32LE), eFILE_TYPE::utf32le},	// UTF32LE must precede UTF16LE
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF16LE), eFILE_TYPE::utf16le},
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF16BE), eFILE_TYPE::utf16be},
			{gtl::GetCodepageBOM(gtl::eCODEPAGE::UTF32BE), eFILE_TYPE::utf32be},
			}};

		auto rbuffer = gtl::FileToContainer(path);
		if (!rbuffer)
			return eFILE_TYPE::unknown;
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
			auto sv = std::string_view((char*)buffer.data(), buffer.size());
			int line{};
			for (auto s : std::views::split(sv, '\n')) {
				std::string_view svLine(s.begin(), s.end());
				bool bMSB{};
				if (!gtl::IsUTF8String(svLine, nullptr, &bMSB))
					lines.push_back(line);
				//if (bMSB)
				//	return {eFILE_TYPE::unknown, line};
				line++;
			}
			if (!lines.empty())
				return eFILE_TYPE::unknown;
		}

		std::wstring content;
		if (type == eFILE_TYPE::utf8 or type == eFILE_TYPE::ansi)
			content = gtl::ToString<wchar_t>(std::u8string_view((char8_t*)buffer.data(), buffer.size()));
		else if (type == eFILE_TYPE::utf16le) {
			content.assign(buffer.size()/2 -1, 0);
			memcpy(content.data(), buffer.data() + 2, buffer.size() - 2);
		}

		auto const& map = gtl::charset::KSSM::s_mapUTF16toKSSM;
		int line{};
		for (auto c : content) {
			static_assert(std::is_unsigned_v<wchar_t> and std::is_unsigned_v<char16_t>);
			if (c == '\n')
				line++;
			if (c <= 127)
				continue;
			if (map.find((char16_t)c) == map.end()) {
				if (lines.empty() or lines.back() != line)
					lines.push_back(line);
			}
		}

		return lines.empty() ? type : eFILE_TYPE::unknown;
	}
#endif

	std::string DetectCodepage(std::string_view text) {
		// Detect the codepage of the text using the 'ICU' library
		std::string codepage;
		UErrorCode errorCode = U_ZERO_ERROR;
		UCharsetDetector* detector = ucsdet_open(&errorCode);
		ucsdet_setText(detector, text.data(), text.size(), &errorCode);

		const UCharsetMatch* match = ucsdet_detect(detector, &errorCode);
		const char* charset = ucsdet_getName(match, &errorCode);

		codepage = charset;

		ucsdet_close(detector);

		return codepage;
	}

	std::string DetectCodepage(std::filesystem::path const& path) {
		// Detect the codepage of the text using the 'ICU' library
		std::string codepage;
		auto buffer = gtl::FileToContainer(path);
		if (!buffer)
			return codepage;
		auto const& text = *buffer;
		return DetectCodepage(std::string_view{text.begin(), text.end()});
	}

	bool CheckCodepageFolder(std::filesystem::path const& folder) {
		return true;
	}

	int GetCharSizeFromCodepage(std::string codepage) {
		for (auto& c : codepage)
			c = std::tolower(c);
		if (codepage == "ucs" or codepage == "usc2" or codepage == "ucs-16le" or codepage == "ucs-16be")
			return 2;
		if (codepage == "utf16" or codepage == "ucs16le" or codepage == "ucs16be" or codepage == "utf-16le" or codepage == "utf-16be")
			return 2;
		if (codepage == "unicode" or codepage == "_unicode")
			return 2;

		if (codepage == "usc4" or codepage == "ucs-32le" or codepage == "ucs-32be")
			return 4;
		if (codepage == "utf32" or codepage == "ucs32le" or codepage == "ucs32be" or codepage == "utf-32le" or codepage == "utf-32be")
			return 4;

		return 1;
	}

}
