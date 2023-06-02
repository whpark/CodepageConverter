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
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/filepicker.h>
#include <wx/dirctrl.h>
#include <wx/treelist.h>
#include <wx/listbox.h>
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
			wxButton* m_btnCheck;
			wxButton* m_btnConvert;
			wxStaticText* m_staticText5;
			wxComboBox* m_cmbCodepageSrc;
			wxStaticBitmap* m_bitmap1;
			wxComboBox* m_cmbCodepageDest;
			wxStaticText* m_staticText7;
			wxComboBox* m_cmbFilter;
			wxStaticText* m_staticText8;
			wxStaticText* m_staticText71;
			wxComboBox* m_comboBox41;
			wxStaticText* m_staticText81;
			wxStaticText* m_staticText14;
			wxCheckBox* m_chkBackupOriginalFiles;
			wxCheckBox* m_chkPreserveModifiedTime;
			wxCheckBox* m_chkConvertAll;
			wxDirPickerCtrl* m_browser;
			wxButton* m_btnBrowse;
			wxGenericDirCtrl* m_dir;
			wxTreeListCtrl* m_lst;
			wxListBox* m_list;

			// Virtual event handlers, override them in your derived class
			virtual void OnButtonClick_Check( wxCommandEvent& event ) = 0;
			virtual void OnButtonClick_Convert( wxCommandEvent& event ) = 0;
			virtual void OnButtonClick_Browse( wxCommandEvent& event ) = 0;


		public:

			IMainWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Desktop"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 980,522 ), long style = wxDEFAULT_FRAME_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxTAB_TRAVERSAL );

			~IMainWnd();

	};

} // namespace ui

