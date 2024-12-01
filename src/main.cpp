#include "wx/log.h"
#include "wx/aboutdlg.h"
#include "wx/event.h"
#include "wx/frame.h"
#include "wx/fontdata.h"
#include "wx/gdicmn.h"
#include "wx/fontdata.h"
#include "wx/fontdlg.h"
#include "wx/sizer.h"
#include "wx/string.h"
#include "wx/toolbar.h"
#include "wx/toplevel.h"
#include "wx/utils.h"

#include "main.hpp"
#include "ui/cDrawPane.hpp"
#include "ui/cPanel_Main.hpp"
#include "util/RandGen.hpp"
#include "ui/cMapPane.hpp"

#include <string>


const int ID_FILE_QUIT = wxID_EXIT;
const int ID_OI_MENU_OI = 1101;
const int ID_OI_MENU_MMKAY = 1102;
const int ID_HELP_ABOUT = wxID_ABOUT;
const int ID_BTN1 = 1001;
const int ID_BTN2 = 1002;
const int ID_BTN3 = 1003;

// Custom events
wxDECLARE_EVENT(FONT_CHANGE_EVENT, wxCommandEvent);
wxDEFINE_EVENT(FONT_CHANGE_EVENT, wxCommandEvent);

// Event table -- Link event IDs to functions
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_MENU(wxID_EXIT, cMain::OnFileQ)
    EVT_MENU(wxID_ABOUT, cMain::OnAbout)
    EVT_MENU(ID_OI_MENU_OI, cMain::SayHi)
    EVT_TOOL(ID_BTN1, cMain::TransformStatusBar)
    EVT_TOOL(ID_BTN2, cMain::popSB)
    EVT_TOOL(ID_BTN3, cMain::OnChooseFont)

wxEND_EVENT_TABLE()

// cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Raekan", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE) {
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Raekan", wxPoint(300,300), wxSize(800, 600), wxDEFAULT_FRAME_STYLE) {
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

  // Book
  m_book = new wxNotebook(this, -1);

  // Main tabs
  cPanel_Main* m_panelMain = new cPanel_Main(m_book      );
  cDrawPane*   m_drawPane  = new cDrawPane(  m_book, this);
  cMapPane*    m_mapPane   = new cMapPane(   m_book, this);

  // Add tabs to notebook
  m_book->AddPage(m_panelMain, "Main", true);
  m_book->AddPage(m_drawPane, "Drawing", false);
  m_book->AddPage(m_mapPane, "Map", false);

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
  m_tool2 = m_mainToolbar->AddTool(ID_BTN2, _("Ay"), m_toolIcon2, m_toolIcon2, wxITEM_NORMAL,
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
  Bind(FONT_CHANGE_EVENT, &cDrawPane::OnParentFontChanged, m_drawPane);

}

cMain::~cMain() {}

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

void cMain::TransformStatusBar(wxCommandEvent& WXUNUSED(event)) {
  int seed = m_RandGen->getInt(4242, 9999);
  wxString str = std::to_string(seed);
  m_mainStatusbar->PushStatusText(str, 1);
}

void cMain::popSB(wxCommandEvent& WXUNUSED(event)) {
  wxString str = m_mainStatusbar->GetStatusText(1);
  if (str.IsEmpty()) {
    wxLogStatus(this, "No more status msg on stack");
    m_mainStatusbar->PushStatusText("Wow.", 1);
  } else {
    m_mainStatusbar->PopStatusText(1);
  }
}

void cMain::SayHi(wxCommandEvent& WXUNUSED(event)) {
  wxLogStatus("Hey ho, Silver");
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
    wxLogStatus("Selected Font: %s, Color: #%02X%02X%02X",
                font.GetFaceName(),
                color.Red(), color.Green(), color.Blue());

    wxCommandEvent fontChangedEvent(FONT_CHANGE_EVENT);
    ProcessEvent(fontChangedEvent);
  }
}

wxFont cMain::getSelectedFont() {
  return m_selectedFont.IsOk() ? m_selectedFont :
    wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true);
}
