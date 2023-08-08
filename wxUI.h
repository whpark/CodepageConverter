///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-284-gf026a8e1)
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
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/filepicker.h>
#include <wx/dirctrl.h>
#include <wx/treelist.h>
#include <wx/textctrl.h>
#include <wx/stc/stc.h>
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
			wxButton* m_btnAnalyze;
			wxButton* m_btnConvert;
			wxStaticText* m_staticText5;
			wxComboBox* m_cmbCodepageSrc;
			wxStaticBitmap* m_bitmap1;
			wxComboBox* m_cmbCodepageDest;
			wxCheckBox* m_chkWriteBOM;
			wxStaticText* m_staticText7;
			wxComboBox* m_cmbFilter;
			wxStaticText* m_staticText8;
			wxStaticText* m_staticText71;
			wxComboBox* m_cmbFilterExclude;
			wxStaticText* m_staticText81;
			wxStaticText* m_staticText14;
			wxCheckBox* m_chkBackupOriginalFiles;
			wxCheckBox* m_chkPreserveModifiedTime;
			wxCheckBox* m_chkConvertAll;
			wxDirPickerCtrl* m_browser;
			wxButton* m_btnBrowse;
			wxGenericDirCtrl* m_dir;
			wxButton* m_btnOpenFileWith1;
			wxButton* m_btnOpenFileWith2;
			wxButton* m_btnOpenFileWith3;
			wxTreeListCtrl* m_lst;
			wxStaticText* m_staticText72;
			wxTextCtrl* m_text_codepage_source;
			wxComboBox* m_cmbEncodingSource;
			wxButton* m_btnConvertSelectedFile;
			wxStyledTextCtrl* m_code;

			// Virtual event handlers, override them in your derived class
			virtual void OnButtonClick_Analyze( wxCommandEvent& event ) = 0;
			virtual void OnButtonClick_Convert( wxCommandEvent& event ) = 0;
			virtual void OnDirChanged_Browser( wxFileDirPickerEvent& event ) = 0;
			virtual void OnButtonClick_Browse( wxCommandEvent& event ) = 0;
			virtual void OnButtonClick_OpenWith1( wxCommandEvent& event ) = 0;
			virtual void OnButtonClick_OpenWith2( wxCommandEvent& event ) = 0;
			virtual void OnButtonClick_OpenWith3( wxCommandEvent& event ) = 0;
			virtual void OnTreelistSelectionChanged_Lst( wxTreeListEvent& event ) = 0;
			virtual void OnCombobox_EncodingSource( wxCommandEvent& event ) = 0;
			virtual void OnButtonClick_ConvertSelectedFile( wxCommandEvent& event ) = 0;


		public:

			IMainWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Codepage Converter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1330,689 ), long style = wxDEFAULT_FRAME_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxTAB_TRAVERSAL );

			~IMainWnd();

	};

} // namespace ui

