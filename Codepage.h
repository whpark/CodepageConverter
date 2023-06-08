#pragma once

#include "gtl/gtl.h"

#include <unicode/ucnv.h>
#include <unicode/ucsdet.h>

namespace gtl {

	class xCodepageDetector {
	public:
		using this_t = xCodepageDetector;

	private:
		inline static thread_local std::atomic<int> m_refCount{};
		inline static thread_local UCharsetDetector* m_detector = nullptr;
		UErrorCode m_error = U_ZERO_ERROR;

	public:
		xCodepageDetector() {
			if (m_refCount++ == 0)
				Open();
		}
		xCodepageDetector(const this_t&) = delete;
		xCodepageDetector(this_t&&) = delete;
		xCodepageDetector& operator = (const this_t&) = delete;
		xCodepageDetector& operator = (this_t&&) = delete;

		virtual ~xCodepageDetector() {
			if (--m_refCount == 0)
				Close();
		}

		std::string DetectCodepage(std::string_view text);
		std::pair<std::string, bool> DetectCodepage(std::filesystem::path const& path);	// codepage, bom
		auto GetLastError() const { return m_error; }
		void ResetError() { m_error = U_ZERO_ERROR; }

		auto operator <=>(xCodepageDetector const&) const = default;

		template < typename tchar >
		struct S_FILE_TEXT {
			std::basic_string<tchar> str;
			std::string codepage;
		};
		template <typename tchar>
		std::optional<S_FILE_TEXT<tchar>> ReadFileAs(std::filesystem::path const& path, std::string codepage, std::error_code& ec) {
			ec.clear();
			if (!std::filesystem::is_regular_file(path, ec))
				return {};
			auto size = std::filesystem::file_size(path, ec);
			if (ec)
				return {};
			std::basic_string<tchar> str;

			gtl::xIFArchive ar(path);
			auto bom = ar.ReadCodepageBOM(gtl::eCODEPAGE::DEFAULT);
			switch (bom) {
			case gtl::eCODEPAGE::UTF8:
			case gtl::eCODEPAGE::UTF16LE:
			case gtl::eCODEPAGE::UTF16BE:
			case gtl::eCODEPAGE::UTF32LE:
			case gtl::eCODEPAGE::UTF32BE:
				{
					codepage = std::format("{} BOM", GetCodepageName(bom));
					str.reserve(size/sizeof(tchar)+1);
					while (auto r = ar.ReadLine<tchar>('\n', false)) {
						str += *r;
						str += '\n';
					}
					return S_FILE_TEXT{str, codepage};
				}
				break;

			default:
				{
					std::string s;
					s.resize(size);
					ar.Read<char>(s.data(), s.size());
					if (codepage.empty()) {
						codepage = DetectCodepage(std::string_view{s});
						//m_text_codepage_source->SetValue(codepage);
					}
					// using iconv, convert string to wstring
					gtl::Ticonv<tchar, char> conv(nullptr, codepage.c_str());
					if (auto r = conv.Convert(s)) {
						str = std::move(*r);
						if (codepage.contains("JIS")) {
							using string_t = std::basic_string<tchar>;
							static std::pair<string_t, string_t> const pairs[]{
								{gtl::ToUTFString<tchar>(u8"‾"sv), gtl::ToUTFString<tchar>(u8"~"sv)},
								{gtl::ToUTFString<tchar>(u8"¥"sv), gtl::ToUTFString<tchar>(u8"\\"sv)},
							};
							for (auto& p : pairs) {
								for (auto pos = str.find(p.first); pos != str.npos; pos = str.find(p.first, pos + p.second.size())) {
									str.replace(pos, p.first.size(), p.second);
								}
							}
						}
						return S_FILE_TEXT{str, codepage};
					}
				}
				break;
			}
			return {};
		}


	private:
		void Open();
		void Close();
	};


	using uchar = unsigned char;
	enum class eFILE_TYPE { unknown = -1, ansi, utf8, utf16le, utf16be, utf32le, utf32be };

	//eFILE_TYPE GetFileBOM(std::filesystem::path const& path, std::vector<int>& lines);
	eFILE_TYPE ReadFileBOM(std::filesystem::path const& path);

	//int GetCharSizeFromCodepage(std::string codepage);
}
