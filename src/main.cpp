#include "wx/aboutdlg.h"
#include "wx/app.h"
#include "wx/confbase.h"
#include "wx/event.h"
#include "wx/filefn.h"
#include "wx/frame.h"
#include "wx/filename.h"
#include "wx/fontdata.h"
#include "wx/fontdlg.h"
#include "wx/gdicmn.h"
#include "wx/generic/logg.h"
#include "wx/log.h"
#include "wx/settings.h"
#include "wx/sizer.h"
#include "wx/stdpaths.h"
#include "wx/string.h"
#include "wx/toolbar.h"
#include "wx/toplevel.h"
#include "wx/utils.h"
#include "wx/config.h"
#include "wx/fileconf.h"

#include "events.hpp"
#include "main.hpp"
#include "ui/cLandingPane.hpp"
#include "ui/cNotebook.hpp"
#include "util/RandGen.hpp"


// #################################################################
//  ______               _   
// |  ____|             | |  
// | |____   _____ _ __ | |_  ___
// |  __\ \ / / _ \ '_ \| __|/ __|
// | |___\ V /  __/ | | | |_ \__ \
// |______\_/ \___|_| |_|\__||___/
// #################################################################

// Evt IDs
enum {
  // Main menu bar
  ID_FILEMENU_QUIT = wxID_EXIT,
  ID_HELPMENU_ABOUT = wxID_ABOUT,
  ID_OPTIONSMENU_MENU_MMKAY = wxID_HIGHEST,
  ID_OPTIONSMENU_FONT,

  // Toolbar buttons
  ID_TOOLBAR_BTN1,
  ID_TOOLBAR_BTN_SHOW_MAIN,
  ID_TOOLBAR_BTN3,
};

// Evt table
wxBEGIN_EVENT_TABLE(cMain, wxFrame) EVT_MENU(wxID_EXIT, cMain::OnFileQ)

EVT_MENU(wxID_ABOUT, cMain::OnAbout)
EVT_MENU(ID_OPTIONSMENU_FONT, cMain::OnChooseFont)
EVT_TOOL(ID_TOOLBAR_BTN_SHOW_MAIN, cNotebook::OnShowMainPanel)
EVT_TOOL(ID_TOOLBAR_BTN3, cMain::OnChooseFont)

wxEND_EVENT_TABLE()


// #################################################################
//       __  __       _
//      |  \/  |     (_)
//   ___| \  / | __ _ _ _ __
//  / __| |\/| |/ _` | | '_ \
// | (__| |  | | (_| | | | | |
//  \___|_|  |_|\__,_|_|_| |_|
// #################################################################

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Raekan", wxPoint(300,300), wxSize(800, 600), wxDEFAULT_FRAME_STYLE) {
  m_config = new wxFileConfig("Raekan", "", wxString{}, "", wxCONFIG_USE_LOCAL_FILE);
  wxConfig::Set(m_config); // Use spec'd conf object globally

  // TEMPORARY DEBUG LOGGERY
  wxLogChain* logChain = new wxLogChain(new wxLogStderr);
  wxLogWindow* logWindow = new wxLogWindow(this, "LOGGERY");
  // wxString logPath = wxStandardPaths::Get().GetUserDir(wxStandardPathsBase::Dir_Documents) + "raekan.log";
  // wxFileName::Mkdir(wxStandardPaths::Get().GetUserDir(wxStandardPathsBase::Dir_Documents),
  //                  wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);

  // Write dir paths to config
  wxString uD = wxStandardPaths::Get().GetUserDir(wxStandardPathsBase::Dir_Documents);
  wxString aD;
  wxGetEnv("APPDATA", &aD);
  m_config->Write("/UserDirs/AppDataDir", aD);
  m_config->Write("/UserDirs/DocsDir", uD);

  // DB
  initDB();

  // For seed generation
  m_RandGen = new cRandGen;

  // Set icon from .rc ID
  this->SetIcon(wxICON(APP_ICON));

  // #################################################################
  //  __  __
  // |  \/  |
  // | \  / | ___ _ __  _   _ ___
  // | |\/| |/ _ \ '_ \| | | / __|
  // | |  | |  __/ | | | |_| \__ \
  // |_|  |_|\___|_| |_|\__,_|___/
  // #################################################################

  // Top-level menu
  wxMenu *fileMenu = new wxMenu;
  fileMenu->AppendSeparator();
  fileMenu->AppendSeparator();
  fileMenu->Append(ID_FILEMENU_QUIT, ("Exit\tAlt-X"),
                   ("Quit like a coward"), ("Flee in fear and shame"));

  wxMenu *optionsMenu = new wxMenu;
  optionsMenu->Append(ID_FILEMENU_QUIT, ("&Mmkay"), ("Bai"));

  wxMenu *options_Fonts_Menu = new wxMenu;
  options_Fonts_Menu->Append(ID_OPTIONSMENU_FONT, ("&Primary font"), ("Set primary font"));
  optionsMenu->AppendSubMenu(options_Fonts_Menu, "&Fonts");

  wxMenu *helpMenu = new wxMenu;
  helpMenu->AppendSeparator();
  helpMenu->Append(ID_HELPMENU_ABOUT, ("About...\tF1"),
                   ("a boot"));
  wxMenuBar *menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, _T("&File"));
  menuBar->Append(optionsMenu, _T("&Options"));
  menuBar->Append(helpMenu, _T("&Help"));
  SetMenuBar(menuBar);

  // #################################################################
  //    _____ _        _               _
  //  / ____| |      | |             | |
  // ( (___ | |_ __ _| |_ _   _ ___  | |__   __ _ _ __
  // \____ \| __/ _` | __| | | / __| | '_ \ / _` | '__|
  //  ____) | || (_| | |_| |_| \__ \ | |_) | (_| | |
  // |_____/ \__\__,_|\__|\__,_|___/ |_.__/ \__,_|_|
  // #################################################################

  m_mainStatusbar = new wxStatusBar(this, wxID_ANY);
  const int SB_WIDTHS[3] = {-2,-1,100};
  m_mainStatusbar->SetFieldsCount(3, SB_WIDTHS);
  m_mainStatusbar->PushStatusText("Very status. Such bar.", 0);
  m_mainStatusbar->PushStatusText("Wow.", 1);

  wxDateTime dt = wxDateTime::Now();
  wxString ts = dt.Format("%Y-%m-%d");
  m_mainStatusbar->SetStatusText(ts, 2);

  SetStatusBar(m_mainStatusbar);

// #################################################################
//   _   _       _       _                 _
//  | \ | |     | |     | |               | |
//  |  \| | ___ | |_ ___| |__   ___   ___ | | __
//  | . ` |/ _ \| __/ _ \ '_ \ / _ \ / _ \| |/ /
//  | |\  | (_) | ||  __/ |_) | (_) | (_) |   <
//  |_| \_|\___/ \__\___|_.__/ \___/ \___/|_|\_\
// #################################################################

  m_book = new cNotebook(this, m_config);
  m_book->Bind(FONT_CHANGE_EVENT, &cNotebook::OnParentFontChanged, m_book);
  /* TODO: Why or why not bind here instead of in the child pane's constructor? */
  // m_book->Bind(EVT_ON_SHOW_MAIN, &cLandingPane::OnButtonTwo, m_book);
  wxLogDebug("cMain: Binding FONT_CHANGE_EVENT at: %p", m_book);
  wxLogDebug("cMain: Notebook ID: %d", this->GetId());

  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

  mainSizer->Add(m_book, 1, wxEXPAND | wxALL, 0);
  SetSizer(mainSizer);

// #################################################################
//   _______          _ _
//  |__   __|        | | |
//     | | ___   ___ | | |__   __ _ _ __
//     | |/ _ \ / _ \| | '_ \ / _` | '__|
//     | | (_) | (_) | | |_) | (_| | |
//     |_|\___/ \___/|_|_.__/ \__,_|_|
// #################################################################

  static const long TB_STYLES = wxTB_FLAT | wxTB_HORZ_TEXT;
  m_mainToolbar = this->CreateToolBar(TB_STYLES, wxID_ANY);
  m_mainToolbar->SetMargins(1,1);
  wxIcon m_toolIcon(wxICON(TOOL_DOGE));
  wxIcon m_toolIcon2(wxICON(TOOL_DOGE2));
  m_tool1 = m_mainToolbar->AddTool( ID_TOOLBAR_BTN1, _("oi"), m_toolIcon, m_toolIcon, wxITEM_NORMAL,
                                    _("OIIII"),
                                    _("Some sort of description"));
  // m_mainToolbar->InsertSeparator(1);
  m_tool2 = m_mainToolbar->AddTool(ID_TOOLBAR_BTN_SHOW_MAIN, _("Show 'Main'"), m_toolIcon2, m_toolIcon2, wxITEM_NORMAL,
                                    _("Show 'Main' panel"),
                                    _("Just try the damn button"));
  m_mainToolbar->InsertSeparator(2);
  m_tool3 = m_mainToolbar->AddTool(ID_TOOLBAR_BTN3, "Font sel.", m_toolIcon2, m_toolIcon2, wxITEM_NORMAL,
                                   _("Select font"),
                                   _("SELECT FONT"));
  m_mainToolbar->AddStretchableSpace();
  m_mainToolbar->AddCheckTool(ID_TOOLBAR_BTN3, _("Toggle"), m_toolIcon, m_toolIcon2,
                              _("Toggle a thing"),
                              _("Toggle the thing, I said"));
  m_mainToolbar->Realize();


}

cMain::~cMain() {
  delete m_config;
}

void cMain::OnFileQ(wxCommandEvent& WXUNUSED(event)) {
  Close(true);
}

void cMain::OnAbout(wxCommandEvent& WXUNUSED(event)) {
  wxAboutDialogInfo info;
  info.SetName(("Raekan"));
  info.SetCopyright(("(C) 2024"));
  info.SetDescription("Eine kleine applicazione");
  info.AddDeveloper(("thallheim <thall@thallheim.com>"));
  info.SetWebSite("https://thallheim.com");

  wxAboutBox(info);
}

void cMain::OnChooseFont(wxCommandEvent& event) {
  wxFontData fontData;
  fontData.EnableEffects(true);
  // fontData.SetInitialFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  fontData.SetInitialFont(m_config->Read("/Fonts/MainAppFont"));
  wxFontDialog fontDialog(this, fontData);

  if (fontDialog.ShowModal() == wxID_OK) {
    fontData = fontDialog.GetFontData(); // TODO: Do I ever need the constituent data?
    m_selectedFont_data = fontData;
    wxFont font = fontDialog.GetFontData().GetChosenFont();
    m_selectedFont = font;
    wxColour color = fontData.GetColour();

    wxLogStatus("Font selected: %s, Colour: #%02X%02X%02X",
                font.GetFaceName(),
                color.Red(), color.Green(), color.Blue());

    wxCommandEvent fontEvt(FONT_CHANGE_EVENT);
    fontEvt.SetEventObject(this);
    fontEvt.SetClientData(new wxFontData(fontData));
    wxPostEvent(m_book, fontEvt);

    // TODO: (Mayhaps) Move to destructor?
    m_config->Write("/Fonts/MainAppFont", m_selectedFont);
    wxLogDebug("Wrote new font to config");
  }
}

wxFont cMain::getSelectedFont() {
  return m_selectedFont.IsOk() ? m_selectedFont :
    wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true);
}

bool cMain::initDB() {
  try {
    wxString aD = m_config->Read("/UserDirs/AppDataDir");
    wxString dbPath = aD + "/raekan_test.db3";
    SQLite::Database db(dbPath, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

    return true;

} catch (std::exception& e) {
    wxLogError("ERROR: Init/open db failed: \n -- %s", e.what());
  }
  return false;
}
