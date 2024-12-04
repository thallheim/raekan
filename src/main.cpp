#include "wx/aboutdlg.h"
#include "wx/event.h"
#include "wx/filefn.h"
#include "wx/frame.h"
#include "wx/filename.h"
#include "wx/fontdata.h"
#include "wx/fontdlg.h"
#include "wx/gdicmn.h"
#include "wx/generic/logg.h"
#include "wx/log.h"
#include "wx/sizer.h"
#include "wx/stdpaths.h"
#include "wx/string.h"
#include "wx/toolbar.h"
#include "wx/toplevel.h"
#include "wx/utils.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "wx/msw/regconf.h"

#include "main.hpp"
#include "events.hpp"
#include "ui/cNotebook.hpp"
#include "util/RandGen.hpp"

const int ID_FILE_QUIT = wxID_EXIT;
const int ID_OI_MENU_OI = 1101;
const int ID_OI_MENU_MMKAY = 1102;
const int ID_HELP_ABOUT = wxID_ABOUT;
const int ID_BTN1 = 1001;
const int ID_MSGTEST = 1002;
const int ID_BTN3 = 1003;

// Event table -- Link event IDs to functions
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_MENU(wxID_EXIT, cMain::OnFileQ)
    EVT_MENU(wxID_ABOUT, cMain::OnAbout)
    EVT_TOOL(ID_BTN3, cMain::OnChooseFont)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Raekan", wxPoint(300,300), wxSize(800, 600), wxDEFAULT_FRAME_STYLE) {

  // m_config = new wxConfig("Raekan");
  // wxString font_fromConfig;
  // if ( m_config->Read("DrawFont", &font_fromConfig) ) {
  //   wxLogDebug("Config: Using DrawFont from config");
  //   m_selectedFont = font_fromConfig;
  // }
  m_RandGen = new cRandGen;
  
  // Set icon from .rc ID
  this->SetIcon(wxICON(APP_ICON));
  // Top-level menu
  wxMenu *fileMenu = new wxMenu;
  wxMenu *oiMenu = new wxMenu;
  wxMenu *helpMenu = new wxMenu;
  fileMenu->AppendSeparator();
  fileMenu->Append(ID_FILE_QUIT, ("Exit\tAlt-X"),
                   ("Quit like a coward"), ("Flee in fear and shame"));
  oiMenu->Append(ID_OI_MENU_OI, ("&Oi"), ("Oi oi"));
  fileMenu->AppendSeparator();
  oiMenu->Append(ID_FILE_QUIT, ("&Mmkay"), ("Bai"));
  helpMenu->AppendSeparator();
  helpMenu->Append(ID_HELP_ABOUT, ("About...\tF1"),
                   ("a boot"));
  wxMenuBar *menuBar = new wxMenuBar();
  menuBar->Append(fileMenu, _T("&File"));
  menuBar->Append(oiMenu, _T("&Oi"));
  menuBar->Append(helpMenu, _T("&Help"));
  SetMenuBar(menuBar);

  // Status bar
  m_mainStatusbar = new wxStatusBar(this, wxID_ANY);
  const int SB_WIDTHS[3] = {-2,-1,100};
  m_mainStatusbar->SetFieldsCount(3, SB_WIDTHS);
  // m_mainStatusbar->SetStatusText("Very status. Such bar.", 0);
  m_mainStatusbar->PushStatusText("Very status. Such bar.", 0);
  // m_mainStatusbar->SetStatusText("Wow.", 1);
  m_mainStatusbar->PushStatusText("Wow.", 1);

  wxDateTime dt = wxDateTime::Now();
  wxString ts = dt.Format("%Y-%m-%d");
  m_mainStatusbar->SetStatusText(ts, 2);

  SetStatusBar(m_mainStatusbar);

  // Book (tabs)
  m_book = new cNotebook(this);

  wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

  mainSizer->Add(m_book, 1, wxEXPAND | wxALL, 0);
  SetSizer(mainSizer);

  // Toolbar
  static const long TB_SYLES = wxTB_FLAT | wxTB_DOCKABLE | wxTB_HORZ_TEXT;
  m_mainToolbar = this->CreateToolBar(TB_SYLES, -1);
  m_mainToolbar->SetMargins(1,1);
  wxIcon m_toolIcon(wxICON(TOOL_DOGE));
  wxIcon m_toolIcon2(wxICON(TOOL_DOGE2));
  m_tool1 = m_mainToolbar->AddTool( ID_BTN1, _("oi"), m_toolIcon, m_toolIcon, wxITEM_NORMAL,
                                    _("OIIII"),
                                    _("Some sort of description"));
  // m_mainToolbar->InsertSeparator(1);
  m_tool2 = m_mainToolbar->AddTool(ID_MSGTEST, _("Ay"), m_toolIcon2, m_toolIcon2, wxITEM_NORMAL,
                                    _("Wööööw"),
                                    _("Longer string here, yes"));
  m_mainToolbar->InsertSeparator(2);
  m_tool3 = m_mainToolbar->AddTool(ID_BTN3, "Font sel.", m_toolIcon2, m_toolIcon2, wxITEM_NORMAL,
                                   _("Select font"),
                                   _("SELECT FONT"));
  m_mainToolbar->AddStretchableSpace();
  m_mainToolbar->AddCheckTool(ID_BTN3, _("Toggle"), m_toolIcon, m_toolIcon2,
                              _("Toggle a thing"),
                              _("Toggle the thing, I said"));
  m_mainToolbar->Realize();

  // TEMPORARY DEBUG LOGGERY
  wxLogChain* logChain = new wxLogChain(new wxLogStderr);
  wxLogWindow* logWindow = new wxLogWindow(this, "LOGGERY");
  wxString logPath = wxStandardPaths::Get().GetUserDir(wxStandardPathsBase::Dir_Documents) + "raekan.log";
  wxFileName::Mkdir(wxStandardPaths::Get().GetUserDir(wxStandardPathsBase::Dir_Documents),
                    wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);

  wxLogStatus("cNotebook's parent: %s", m_book->GetParent()->GetName());

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
  fontData.SetInitialFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
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

    // m_config->Write("DrawFont", font.GetFaceName());
    wxCommandEvent fontEvt(FONT_CHANGE_EVENT);
    fontEvt.SetEventObject(this);
    fontEvt.SetClientData(new wxFontData(fontData));
    wxPostEvent(m_book, fontEvt);

  }
}

wxFont cMain::getSelectedFont() {
  return m_selectedFont.IsOk() ? m_selectedFont :
    wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true);
}
