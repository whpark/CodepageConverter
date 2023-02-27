///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include "wxUI.h"

///////////////////////////////////////////////////////////////////////////
using namespace ui;

IMainWnd::IMainWnd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizerTOP;
	bSizerTOP = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	m_btnCheck = new wxButton( this, wxID_ANY, _("Check"), wxDefaultPosition, wxSize( 140,-1 ), 0 );

	m_btnCheck->SetDefault();
	m_btnCheck->SetFont( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer8->Add( m_btnCheck, 0, wxALL|wxEXPAND, 5 );

	m_btnConvert = new wxButton( this, wxID_ANY, _("Convert"), wxDefaultPosition, wxSize( 140,-1 ), 0 );
	m_btnConvert->SetFont( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer8->Add( m_btnConvert, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizerOption;
	sbSizerOption = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("option") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText5 = new wxStaticText( sbSizerOption->GetStaticBox(), wxID_ANY, _("Codepage :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer2->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_cmbCodepageSrc = new wxComboBox( sbSizerOption->GetStaticBox(), wxID_ANY, _("0 - auto"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_cmbCodepageSrc->Append( _("0 - auto") );
	m_cmbCodepageSrc->Append( _("65000 - UTF8") );
	m_cmbCodepageSrc->Append( _("949 - Korean") );
	m_cmbCodepageSrc->Append( _("1250 - Latin 2") );
	m_cmbCodepageSrc->Append( _("1251 - Cyrillic") );
	m_cmbCodepageSrc->Append( _("1252 - Western") );
	m_cmbCodepageSrc->Append( _("1253 - Greek") );
	m_cmbCodepageSrc->Append( _("950 - (Chinese)BIG5") );
	m_cmbCodepageSrc->Append( _("1370 - (Chinese)BIG5") );
	m_cmbCodepageSrc->Append( _("932 - (Japanese)Shift JIS") );
	m_cmbCodepageSrc->Append( _("943 - (Japanese)Shift JIS") );
	m_cmbCodepageSrc->SetSelection( 0 );
	bSizer3->Add( m_cmbCodepageSrc, 0, wxALL, 5 );

	m_bitmap1 = new wxStaticBitmap( sbSizerOption->GetStaticBox(), wxID_ANY, wxArtProvider::GetBitmap( wxART_GO_FORWARD, wxART_FRAME_ICON ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_bitmap1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_cmbCodepageDest = new wxComboBox( sbSizerOption->GetStaticBox(), wxID_ANY, _("65001 - UTF8 with BOM"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_cmbCodepageDest->Append( _("65001 - UTF8 with BOM") );
	m_cmbCodepageDest->Append( _("65000 - UTF8") );
	m_cmbCodepageDest->Append( _("1200 - Unicode Little-Endian (for Windows)") );
	m_cmbCodepageDest->Append( _("1201 - Unicode Big-Endian") );
	m_cmbCodepageDest->SetSelection( 0 );
	bSizer3->Add( m_cmbCodepageDest, 0, wxALL, 5 );


	fgSizer2->Add( bSizer3, 1, wxEXPAND, 5 );

	m_staticText7 = new wxStaticText( sbSizerOption->GetStaticBox(), wxID_ANY, _("File Filter :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer2->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_cmbFilter = new wxComboBox( sbSizerOption->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0, NULL, 0 );
	m_cmbFilter->Append( _("*.cpp;*.cxx;*.h;*.hpp;*.hxx") );
	m_cmbFilter->Append( _("*.txt") );
	m_cmbFilter->Append( _("*.*") );
	m_cmbFilter->Append( wxEmptyString );
	m_cmbFilter->SetSelection( 0 );
	m_cmbFilter->SetMinSize( wxSize( 400,-1 ) );

	bSizer4->Add( m_cmbFilter, 1, wxALL|wxEXPAND, 5 );

	m_staticText8 = new wxStaticText( sbSizerOption->GetStaticBox(), wxID_ANY, _("( for Batch Job )"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer4->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	fgSizer2->Add( bSizer4, 1, wxEXPAND, 5 );

	m_staticText71 = new wxStaticText( sbSizerOption->GetStaticBox(), wxID_ANY, _("Exclude Files :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	fgSizer2->Add( m_staticText71, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_comboBox41 = new wxComboBox( sbSizerOption->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0, NULL, 0 );
	m_comboBox41->Append( _("resource.h") );
	m_comboBox41->SetSelection( 0 );
	bSizer5->Add( m_comboBox41, 1, wxALL|wxEXPAND, 5 );

	m_staticText81 = new wxStaticText( sbSizerOption->GetStaticBox(), wxID_ANY, _("( for Batch Job )"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	bSizer5->Add( m_staticText81, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	fgSizer2->Add( bSizer5, 1, wxEXPAND, 5 );

	m_staticText14 = new wxStaticText( sbSizerOption->GetStaticBox(), wxID_ANY, _("options :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer2->Add( m_staticText14, 0, wxALL, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );

	m_chkBackupOriginalFiles = new wxCheckBox( sbSizerOption->GetStaticBox(), wxID_ANY, _("Backup"), wxDefaultPosition, wxDefaultSize, 0 );
	m_chkBackupOriginalFiles->SetValue(true);
	bSizer11->Add( m_chkBackupOriginalFiles, 0, wxALL, 5 );

	m_chkPreserveModifiedTime = new wxCheckBox( sbSizerOption->GetStaticBox(), wxID_ANY, _("Preserve FileTime"), wxDefaultPosition, wxDefaultSize, 0 );
	m_chkPreserveModifiedTime->SetValue(true);
	bSizer11->Add( m_chkPreserveModifiedTime, 0, wxALL, 5 );

	m_chkConvertAll = new wxCheckBox( sbSizerOption->GetStaticBox(), wxID_ANY, _("Convert ALL !"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_chkConvertAll, 0, wxALL, 5 );


	fgSizer2->Add( bSizer11, 1, wxEXPAND, 5 );


	sbSizerOption->Add( fgSizer2, 1, wxEXPAND, 5 );


	bSizer8->Add( sbSizerOption, 1, wxEXPAND, 5 );


	bSizerTOP->Add( bSizer8, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizerFolder;
	bSizerFolder = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	m_browser = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_SMALL|wxDIRP_USE_TEXTCTRL );
	m_browser->SetMinSize( wxSize( 300,-1 ) );

	bSizer13->Add( m_browser, 0, wxTOP|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	m_btnBrowse = new wxButton( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 30,-1 ), 0 );

	m_btnBrowse->SetDefault();

	m_btnBrowse->SetBitmap( wxArtProvider::GetBitmap( wxART_FOLDER_OPEN, wxART_BUTTON ) );
	bSizer13->Add( m_btnBrowse, 0, wxALIGN_CENTER_VERTICAL|wxTOP, 5 );


	bSizer12->Add( bSizer13, 0, wxEXPAND, 5 );

	m_dir = new wxGenericDirCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxSUNKEN_BORDER, wxEmptyString, 0 );

	m_dir->ShowHidden( false );
	bSizer12->Add( m_dir, 1, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );


	bSizerFolder->Add( bSizer12, 0, wxEXPAND, 5 );

	m_lst = new wxTreeListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_3STATE|wxTL_CHECKBOX|wxTL_MULTIPLE );

	bSizerFolder->Add( m_lst, 0, wxEXPAND | wxALL, 5 );

	m_list = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizerFolder->Add( m_list, 1, wxALL|wxEXPAND, 5 );


	bSizerTOP->Add( bSizerFolder, 1, wxEXPAND, 5 );


	this->SetSizer( bSizerTOP );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_btnCheck->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Check ), NULL, this );
	m_btnConvert->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Convert ), NULL, this );
	m_btnBrowse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Browse ), NULL, this );
}

IMainWnd::~IMainWnd()
{
	// Disconnect Events
	m_btnCheck->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Check ), NULL, this );
	m_btnConvert->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Convert ), NULL, this );
	m_btnBrowse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Browse ), NULL, this );

}
