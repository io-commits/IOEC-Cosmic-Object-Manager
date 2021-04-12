
// SatelliteManagerFinalDlg.h : header file
//

#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include "ObjectManager.h"
#include "OrbitObject.h"
#include "ICosmic.h"
#include "Planet.h"
#include <iostream>
using namespace std;


typedef struct OrbitItem {
	OrbitObject *orbitter;
	int comboBoxId;
}OrbitItem;

// CSatelliteManagerFinalDlg dialog
class CSatelliteManagerFinalDlg : public CDialogEx
{
// Construction
public:
	CSatelliteManagerFinalDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SATELLITEMANAGERFINAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int SimulationMinutes; // Simulation Minutes Var
	double InputMinutes; // Input Minutes
	bool ManagerExist = false; //First Manager Created
	bool IsSelected = false; // Selected Object Flag
	bool TypeSelected = false; // Type Flag
	list<Planet> *planetsList; // List of Planets
	list<Planet>::iterator planetIterator; // Selected Planet
	list<ObjectManager::OrbitItem>::iterator orbitterIterator;//
	ObjectManager *OManager; // Object Manager
	double PlanetMass = 1; // Planet Mass
	double PlanetRadius = 1; // Planet Radius
	CString PlanetType; // For Planet Combo
	CString ObjectType; // For Create Combo
	CString ObjectSelect; // For Select Combo
	CComboBox ComboSelectPlanet; //Combo Value
	CComboBox ComboSelectType; //Combo Value
	CComboBox ComboSelectObject; //Combo Value
	double InputAltitude; // Input Altitude
	double OutputLocation; // For Output Box
	CString OutputType; // For Output Box
	double OutputAltitude; // For Output Box
	double OutputVelocity; // For Output Box
	double OutputAngularVelocity; // For Output Box
	double OutputOrbitTime; // For Output Box
	double OutputAcceleration; // For Output Box
	void Refresh(); // Refresh Outputs
	void Simulate(); // Simulate Button
	afx_msg void OnBnClickedButton2(); // Create New Orbiting Object
	afx_msg void OnBnClickedButton8(); // Next Hour
	afx_msg void OnBnClickedButton7(); // Previous Hour
	afx_msg void OnCbnSelchangeCombo1(); // Combo Select Planet
	afx_msg void OnCbnSelchangeCombo2(); // Combo Select Type
	afx_msg void OnCbnSelchangeCombo3(); // Combo Select Object
	afx_msg void OnEnChangeEdit1(); // Altitude Creation Select
	afx_msg void OnBnClickedButton4(); // Delete Object
	afx_msg void OnEnChangeEdit10(); // Input Minutes
	afx_msg void OnBnClickedButton5(); // Undo
	afx_msg void OnBnClickedButton1(); // Simulation Start
	afx_msg void OnEnChangeEdit11(); // Simulation Minutes Input
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
};
