
// SatelliteManagerFinalDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SatelliteManagerFinal.h"
#include "SatelliteManagerFinalDlg.h"
#include "afxdialogex.h"
#include "OrbitObject.h"
#include "ObjectManager.h"
#include "ICosmic.h"
#include "Planet.h"
#include <iostream>
#include <list>
#include "Markup.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSatelliteManagerFinalDlg dialog



CSatelliteManagerFinalDlg::CSatelliteManagerFinalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SATELLITEMANAGERFINAL_DIALOG, pParent)
	, OutputLocation(0)
	, OutputType(_T(""))
	, OutputAltitude(0)
	, OutputVelocity(0)
	, OutputAngularVelocity(0)
	, OutputOrbitTime(0)
	, OutputAcceleration(0)
	, InputAltitude(0)
	, InputMinutes(60)
	, SimulationMinutes(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSatelliteManagerFinalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, ComboSelectPlanet);
	DDX_Control(pDX, IDC_COMBO2, ComboSelectType);
	DDX_Control(pDX, IDC_COMBO3, ComboSelectObject);
	DDX_Text(pDX, IDC_EDIT1, InputAltitude);
	DDX_Text(pDX, IDC_EDIT2, OutputLocation);
	DDX_Text(pDX, IDC_EDIT3, OutputType);
	DDX_Text(pDX, IDC_EDIT4, OutputAltitude);
	DDX_Text(pDX, IDC_EDIT5, OutputVelocity);
	DDX_Text(pDX, IDC_EDIT6, OutputAngularVelocity);
	DDX_Text(pDX, IDC_EDIT7, OutputOrbitTime);
	DDX_Text(pDX, IDC_EDIT8, OutputAcceleration);
	DDX_Text(pDX, IDC_EDIT10, InputMinutes);
	DDX_Text(pDX, IDC_EDIT11, SimulationMinutes);
}

BEGIN_MESSAGE_MAP(CSatelliteManagerFinalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CSatelliteManagerFinalDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON8, &CSatelliteManagerFinalDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON7, &CSatelliteManagerFinalDlg::OnBnClickedButton7)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSatelliteManagerFinalDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSatelliteManagerFinalDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CSatelliteManagerFinalDlg::OnCbnSelchangeCombo3)
	ON_EN_CHANGE(IDC_EDIT1, &CSatelliteManagerFinalDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON4, &CSatelliteManagerFinalDlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT10, &CSatelliteManagerFinalDlg::OnEnChangeEdit10)
	ON_BN_CLICKED(IDC_BUTTON5, &CSatelliteManagerFinalDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CSatelliteManagerFinalDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT11, &CSatelliteManagerFinalDlg::OnEnChangeEdit11)
	ON_BN_CLICKED(IDC_BUTTON3, &CSatelliteManagerFinalDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CSatelliteManagerFinalDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CSatelliteManagerFinalDlg message handlers

BOOL CSatelliteManagerFinalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// --------------------------------------------------------------------- Initialization Code
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	/*ComboSelectPlanet.AddString(_T("Mercury"));
	ComboSelectPlanet.AddString(_T("Venus"));*/

	ComboSelectPlanet.AddString(_T("Mercury"));
	ComboSelectPlanet.AddString(_T("Venus"));
	ComboSelectPlanet.AddString(_T("Earth"));
	ComboSelectPlanet.AddString(_T("Mars"));
	ComboSelectPlanet.AddString(_T("Jupiter"));
	ComboSelectPlanet.AddString(_T("Saturn"));
	ComboSelectPlanet.AddString(_T("Uranus"));
	ComboSelectPlanet.AddString(_T("Neptune"));
	ComboSelectPlanet.AddString(_T("Pluto"));

	ComboSelectType.AddString(_T("Satellite"));
	ComboSelectType.AddString(_T("Station"));
	ComboSelectType.AddString(_T("Debris"));
	ComboSelectType.AddString(_T("Astroid"));

	planetsList = new list<Planet>();
	planetsList->push_back(Planet(_T("Mercury"), 2.4397e+6, 3.3011e+23));
	planetsList->push_back(Planet(_T("Venus"), 6.0518e+6, 4.8675e+24));
	planetsList->push_back(Planet(_T("Earth"), 6.37e+6, 5.972e+24));
	planetsList->push_back(Planet(_T("Mars"), 3.389e+6, 6.39e+23));
	planetsList->push_back(Planet(_T("Jupiter"), 6.9911e+7, 1.898e+27));
	planetsList->push_back(Planet(_T("Saturn"), 5.8232e+7, 5.6834e+26));
	planetsList->push_back(Planet(_T("Uranus"), 2.5362e+7, 8.6810e+25));
	planetsList->push_back(Planet(_T("Neptune"), 2.4622e+7, 1.02413e+26));
	planetsList->push_back(Planet(_T("Pluto"), 1.1883e+6, 1.303e+22));

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSatelliteManagerFinalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSatelliteManagerFinalDlg::OnPaint()
{
	CBitmap Earth, Jupiter, Mars, Mercury, Venus, Saturn, Uranus, Neptune, Pluto, Astroid, Debris, Satellite, SpaceStation; //CBitmap to all --------------------------------- Graphics
	// Load the bitmap from the resource
	Earth.LoadBitmap(IDB_BITMAP4);
	Jupiter.LoadBitmap(IDB_BITMAP5);
	Mars.LoadBitmap(IDB_BITMAP6);
	Mercury.LoadBitmap(IDB_BITMAP9);
	Venus.LoadBitmap(IDB_BITMAP14);
	Saturn.LoadBitmap(IDB_BITMAP12);
	Uranus.LoadBitmap(IDB_BITMAP13);
	Neptune.LoadBitmap(IDB_BITMAP10);
	Pluto.LoadBitmap(IDB_BITMAP11);
	Astroid.LoadBitmap(IDB_BITMAP2);
	Debris.LoadBitmap(IDB_BITMAP3);
	Satellite.LoadBitmap(IDB_BITMAP7);
	SpaceStation.LoadBitmap(IDB_BITMAP8);

	CPaintDC dc(this);
	CDC ManagerDC;

	if (ManagerExist)
	{
		CDC *cdc = GetDC();
		OManager->PrintPlanet(dc, ManagerDC, Mercury, Venus, Earth, Jupiter, Mars, Saturn, Uranus, Neptune, Pluto); // Print planet
		OManager->PrintArcs(cdc); // Print Arcs
		OManager->PrintObjects(dc, ManagerDC, Astroid, Debris, Satellite, SpaceStation); // Print Objects
	}

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSatelliteManagerFinalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// --------------------------------------------------------------------- Real Code Start HERE

void CSatelliteManagerFinalDlg::OnBnClickedButton2() // Create New Orbiting Object
{
	if (TypeSelected)
	{
		OManager->CreateObject(InputAltitude, ObjectType, planetIterator->GetMass(), planetIterator->GetRadius());
		UpdateData(FALSE);
		Invalidate();
	}
}

void CSatelliteManagerFinalDlg::OnBnClickedButton8() // Next Hour
{
	if (ManagerExist)
	{
		OManager->NextHour(InputMinutes);
		Refresh();
		Invalidate();
	}
}


void CSatelliteManagerFinalDlg::OnBnClickedButton7() // Previous Hour
{
	if (ManagerExist)
	{
		OManager->PrevHour(InputMinutes);
		Refresh();
		Invalidate();
	}
}

void CSatelliteManagerFinalDlg::Refresh() // Refresh Output Boxes
{
	if (IsSelected)
	{
		OrbitObject cur = OManager->GetSelectedOrbitter();
		OutputLocation = (int)cur.GetLocation(); // Output Location (deg)
		OutputType = cur.GetType(); //Output CString ObjectType
		OutputAltitude = (int)cur.GetAltitude(); // Altitude (km)
		OutputVelocity = (int)cur.GetVelocity(); // Velocity (m/s)
		OutputAngularVelocity = cur.GetAngularVelocity(); // AngVelocity > To degrees > sec to hour
		OutputOrbitTime = cur.GetOrbitTime(); // Orbit Time (Hours)
		OutputAcceleration = cur.GetAcceleration(); // Gravity Force Acceleration
		UpdateData(FALSE);
	}
}

void CSatelliteManagerFinalDlg::OnCbnSelchangeCombo1() // Combo Select Planet
{
	ComboSelectPlanet.GetLBText(ComboSelectPlanet.GetCurSel(), PlanetType); //Get Selected Planet
	UpdateData(FALSE);
	planetIterator = planetsList->begin();
	while (planetIterator->GetPlanetName() != PlanetType) ++planetIterator; //Update PlanetIterator
	OManager = planetIterator->planetManager; // Transfer PlanetIterator to Manager
	OManager->SetComboSelect(ComboSelectObject); // Connect OManager With ComboBox Select Object
	OManager->ClearCombo(); // Delete old object strings
	OManager->AddListToCombo(); // Update to planet's objects strings
	ManagerExist = true;
	Invalidate();
}


void CSatelliteManagerFinalDlg::OnCbnSelchangeCombo2() // Combo Select Type
{
	ComboSelectType.GetLBText(ComboSelectType.GetCurSel(), ObjectType);
	TypeSelected = true;
	UpdateData(FALSE);
}


void CSatelliteManagerFinalDlg::OnCbnSelchangeCombo3() // Combo Select
{
	OManager->SelectObject(); // Manager Object Select
	IsSelected = true;
	UpdateData(FALSE);
	Refresh();
}


void CSatelliteManagerFinalDlg::OnEnChangeEdit1() // Input Height
{
	UpdateData(TRUE);
}


void CSatelliteManagerFinalDlg::OnBnClickedButton4() // Delete
{
	if (IsSelected)
		OManager->DeleteSelected();
	IsSelected = false;
	UpdateData(FALSE);
	Invalidate();
}

void CSatelliteManagerFinalDlg::OnEnChangeEdit10() // Input Minutes
{
	UpdateData(TRUE);
}


void CSatelliteManagerFinalDlg::OnBnClickedButton5() // Undo
{
	if (ManagerExist)
		OManager->UndoDelete(); // Undo Delete in Manager
	UpdateData(FALSE);
	Invalidate();
}

void CSatelliteManagerFinalDlg::OnBnClickedButton1() //Start Simulation Button
{
	Simulate();
}

void CSatelliteManagerFinalDlg::Simulate()
{
	CPoint startRect;
	startRect.x = 1000;
	startRect.y = 100;
	CPoint endRect;
	endRect.x = 2000;
	endRect.y = 1000;
	CRect *refreshed = new CRect(startRect, endRect);
	for (int i = 0; i < SimulationMinutes; i++)
	{
		OManager->NextHour(1.0);
		Refresh();
		RedrawWindow(*refreshed);
		Sleep(20);
	}
}

void CSatelliteManagerFinalDlg::OnEnChangeEdit11() // Simulation Minutes Update
{
	UpdateData(TRUE);
}

void CSatelliteManagerFinalDlg::OnBnClickedButton3() //SAVE
{
	planetIterator = planetsList->begin();
	CMarkup xmlFile;
	for (; planetIterator != planetsList->end(); planetIterator++)
	{
		xmlFile.AddElem(planetIterator->GetPlanetName());
		if (planetIterator->planetManager->ItemList.empty() == false)
		{
			xmlFile.IntoElem();
			orbitterIterator = planetIterator->planetManager->ItemList.begin();
			for (; orbitterIterator != planetIterator->planetManager->ItemList.end(); ++orbitterIterator)
			{
				xmlFile.AddElem(_T("OrbitItem"));
				xmlFile.SetAttrib(_T("MainComboBoxId"), orbitterIterator->comboBoxId);
				xmlFile.SetAttrib(_T("ID"), orbitterIterator->orbitter->GetId());
				xmlFile.SetAttrib(_T("ComboBoxId"), orbitterIterator->orbitter->GetComboBoxID());
				xmlFile.SetAttrib(_T("Location"), orbitterIterator->orbitter->GetLocation());
				xmlFile.SetAttrib(_T("Type"), orbitterIterator->orbitter->GetType());
				xmlFile.SetAttrib(_T("Altitude"), orbitterIterator->orbitter->GetAltitude());
				xmlFile.SetAttrib(_T("Velocity"), orbitterIterator->orbitter->GetVelocity());
				xmlFile.SetAttrib(_T("AngularVelocity"), orbitterIterator->orbitter->GetAngularVelocity());
				xmlFile.SetAttrib(_T("OrbitTime"), orbitterIterator->orbitter->GetOrbitTime());
				xmlFile.SetAttrib(_T("Acceleration"), orbitterIterator->orbitter->GetAcceleration());
			}
		}
		xmlFile.ResetPos();
	}
	xmlFile.Save(_T("configFile.xml"));
}


void CSatelliteManagerFinalDlg::OnBnClickedButton6() //LOAD
{
	CMarkup xmlFile;
	xmlFile.Load(_T("configFile.xml"));
	planetIterator = planetsList->begin();
	for (; planetIterator != planetsList->end(); ++planetIterator)
	{
		xmlFile.FindElem(planetIterator->GetPlanetName());
		if (xmlFile.OutOfElem() == false)
		{
			xmlFile.IntoElem();
			planetIterator->planetManager->SetComboSelect(ComboSelectObject); // Connect OManager With ComboBox Select Object
			while (xmlFile.FindElem(_T("OrbitItem")))
			{
				int ID = _ttoi(xmlFile.GetAttrib(_T("MainComboBoxId")));
				int altitude =_ttoi(xmlFile.GetAttrib(_T("Altitude")));			
				CString type = xmlFile.GetAttrib(_T("Type"));				
				int comboBoxId = _ttoi(xmlFile.GetAttrib(_T("ComboBoxId")));
				double location = _ttoi(xmlFile.GetAttrib(_T("Location")));
				planetIterator->planetManager->CreateObject(ID,altitude, type, planetIterator->GetMass(), planetIterator->GetRadius(),comboBoxId,location);
			}
		}
		xmlFile.ResetPos();
	}
}
