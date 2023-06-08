///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-284-gf026a8e1)
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

	m_btnAnalyze = new wxButton( this, wxID_ANY, _("Analyze"), wxDefaultPosition, wxSize( 140,-1 ), 0 );

	m_btnAnalyze->SetDefault();
	m_btnAnalyze->SetFont( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer8->Add( m_btnAnalyze, 0, wxALL|wxEXPAND, 5 );

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
	m_cmbCodepageSrc->Enable( false );

	bSizer3->Add( m_cmbCodepageSrc, 0, wxALL, 5 );

	m_bitmap1 = new wxStaticBitmap( sbSizerOption->GetStaticBox(), wxID_ANY, wxArtProvider::GetBitmap( wxART_GO_FORWARD, wxART_FRAME_ICON ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_bitmap1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_cmbCodepageDest = new wxComboBox( sbSizerOption->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_cmbCodepageDest->Append( _("65001 - UTF8") );
	m_cmbCodepageDest->Append( _("1200 - Unicode Little-Endian (for Windows)") );
	m_cmbCodepageDest->SetSelection( 0 );
	bSizer3->Add( m_cmbCodepageDest, 0, wxALL, 5 );

	m_chkWriteBOM = new wxCheckBox( sbSizerOption->GetStaticBox(), wxID_ANY, _("Write BOM"), wxDefaultPosition, wxDefaultSize, 0 );
	m_chkWriteBOM->SetValue(true);
	bSizer3->Add( m_chkWriteBOM, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	fgSizer2->Add( bSizer3, 1, wxEXPAND, 5 );

	m_staticText7 = new wxStaticText( sbSizerOption->GetStaticBox(), wxID_ANY, _("Filter (include):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer2->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_cmbFilter = new wxComboBox( sbSizerOption->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0, NULL, 0 );
	m_cmbFilter->Append( _("*.cpp;*.cxx;*.h;*.hpp;*.hxx") );
	m_cmbFilter->Append( _("*.txt") );
	m_cmbFilter->Append( _("*.*") );
	m_cmbFilter->SetSelection( 0 );
	m_cmbFilter->SetMinSize( wxSize( 400,-1 ) );

	bSizer4->Add( m_cmbFilter, 1, wxALL|wxEXPAND, 5 );

	m_staticText8 = new wxStaticText( sbSizerOption->GetStaticBox(), wxID_ANY, _("( for Batch Job )"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer4->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	fgSizer2->Add( bSizer4, 1, wxEXPAND, 5 );

	m_staticText71 = new wxStaticText( sbSizerOption->GetStaticBox(), wxID_ANY, _("Filter (exclude):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	fgSizer2->Add( m_staticText71, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_cmbFilterExclude = new wxComboBox( sbSizerOption->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0, NULL, 0 );
	m_cmbFilterExclude->Append( _("resource.h;.git/;.vs/;.vscode/;x64/;Debug/;Release/") );
	m_cmbFilterExclude->SetSelection( 0 );
	bSizer5->Add( m_cmbFilterExclude, 1, wxALL|wxEXPAND, 5 );

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

	m_chkConvertAll = new wxCheckBox( sbSizerOption->GetStaticBox(), wxID_ANY, _("Convert ALL (if no selection) !"), wxDefaultPosition, wxDefaultSize, 0 );
	m_chkConvertAll->SetValue(true);
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

	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );

	m_btnOpenFileWith1 = new wxButton( this, wxID_ANY, _("notepad++"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_btnOpenFileWith1, 0, wxALL|wxEXPAND, 5 );

	m_btnOpenFileWith2 = new wxButton( this, wxID_ANY, _("vscode"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_btnOpenFileWith2, 0, wxALL|wxEXPAND, 5 );

	m_btnOpenFileWith3 = new wxButton( this, wxID_ANY, _("shell"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_btnOpenFileWith3, 0, wxALL, 5 );


	bSizer131->Add( bSizer15, 0, wxEXPAND, 5 );

	m_lst = new wxTreeListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 500,-1 ), wxTL_MULTIPLE );
	m_lst->AppendColumn( _("filename"), 370, wxALIGN_LEFT, wxCOL_RESIZABLE );
	m_lst->AppendColumn( _("encoding"), 100, wxALIGN_CENTER, wxCOL_RESIZABLE );
	m_lst->AppendColumn( _("size"), 80, wxALIGN_RIGHT, wxCOL_RESIZABLE );
	m_lst->AppendColumn( _("comments"), wxCOL_WIDTH_DEFAULT, wxALIGN_LEFT, wxCOL_RESIZABLE );

	bSizer131->Add( m_lst, 1, wxALL|wxEXPAND, 5 );


	bSizerFolder->Add( bSizer131, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText72 = new wxStaticText( this, wxID_ANY, _("Encoding :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText72->Wrap( -1 );
	bSizer111->Add( m_staticText72, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );

	m_text_codepage_source = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer111->Add( m_text_codepage_source, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_cmbEncodingSource = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_cmbEncodingSource->Append( _("detect") );
	m_cmbEncodingSource->Append( _("utf-8") );
	m_cmbEncodingSource->Append( _("utf-16") );
	m_cmbEncodingSource->Append( _("utf-32") );
	m_cmbEncodingSource->Append( _("EUC-KR") );
	m_cmbEncodingSource->Append( _("Shift_JIS") );
	m_cmbEncodingSource->SetSelection( 0 );
	bSizer111->Add( m_cmbEncodingSource, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );

	m_btnConvertSelectedFile = new wxButton( this, wxID_ANY, _("Convert"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer111->Add( m_btnConvertSelectedFile, 0, wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer10->Add( bSizer111, 0, wxEXPAND, 5 );

	m_code = new wxStyledTextCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString );
	m_code->SetUseTabs( true );
	m_code->SetTabWidth( 4 );
	m_code->SetIndent( 4 );
	m_code->SetTabIndents( true );
	m_code->SetBackSpaceUnIndents( true );
	m_code->SetViewEOL( false );
	m_code->SetViewWhiteSpace( false );
	m_code->SetMarginWidth( 2, 0 );
	m_code->SetIndentationGuides( true );
	m_code->SetReadOnly( false );
	m_code->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
	m_code->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
	m_code->SetMarginWidth( 1, 16);
	m_code->SetMarginSensitive( 1, true );
	m_code->SetProperty( wxT("fold"), wxT("1") );
	m_code->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	m_code->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_code->SetMarginWidth( 0, m_code->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	{
		wxFont font = wxFont( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Cascadia Code") );
		m_code->StyleSetFont( wxSTC_STYLE_DEFAULT, font );
	}
	m_code->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_code->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_code->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_code->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_code->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_code->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_code->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_code->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_code->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_code->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_code->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_code->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_code->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_code->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_code->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_code->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_code->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	m_code->SetFont( wxFont( 10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Cascadia Code") ) );

	bSizer10->Add( m_code, 1, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );


	bSizerFolder->Add( bSizer10, 1, wxEXPAND, 5 );


	bSizerTOP->Add( bSizerFolder, 1, wxEXPAND, 5 );


	this->SetSizer( bSizerTOP );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_btnAnalyze->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Analyze ), NULL, this );
	m_btnConvert->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Convert ), NULL, this );
	m_browser->Connect( wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler( IMainWnd::OnDirChanged_Browser ), NULL, this );
	m_btnBrowse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Browse ), NULL, this );
	m_btnOpenFileWith1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_OpenWith1 ), NULL, this );
	m_btnOpenFileWith2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_OpenWith2 ), NULL, this );
	m_btnOpenFileWith3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_OpenWith3 ), NULL, this );
	m_lst->Connect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( IMainWnd::OnTreelistSelectionChanged_Lst ), NULL, this );
	m_cmbEncodingSource->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( IMainWnd::OnCombobox_EncodingSource ), NULL, this );
	m_btnConvertSelectedFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_ConvertSelectedFile ), NULL, this );
}

IMainWnd::~IMainWnd()
{
	// Disconnect Events
	m_btnAnalyze->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Analyze ), NULL, this );
	m_btnConvert->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Convert ), NULL, this );
	m_browser->Disconnect( wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler( IMainWnd::OnDirChanged_Browser ), NULL, this );
	m_btnBrowse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_Browse ), NULL, this );
	m_btnOpenFileWith1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_OpenWith1 ), NULL, this );
	m_btnOpenFileWith2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_OpenWith2 ), NULL, this );
	m_btnOpenFileWith3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_OpenWith3 ), NULL, this );
	m_lst->Disconnect( wxEVT_TREELIST_SELECTION_CHANGED, wxTreeListEventHandler( IMainWnd::OnTreelistSelectionChanged_Lst ), NULL, this );
	m_cmbEncodingSource->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( IMainWnd::OnCombobox_EncodingSource ), NULL, this );
	m_btnConvertSelectedFile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( IMainWnd::OnButtonClick_ConvertSelectedFile ), NULL, this );

}
