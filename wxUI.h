///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

namespace ui
{
	///////////////////////////////////////////////////////////////////////////////
	/// Class IMainWnd
	///////////////////////////////////////////////////////////////////////////////
	class IMainWnd : public wxFrame
	{
		private:

		protected:
			wxStaticText* m_staticText1;

		public:

			IMainWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Desktop"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxTAB_TRAVERSAL );

			~IMainWnd();

	};

} // namespace ui

