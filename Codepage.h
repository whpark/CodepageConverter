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
