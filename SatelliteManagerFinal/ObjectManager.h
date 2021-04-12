#include "OrbitObject.h"
#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include <list>
using namespace std;
#ifndef ObjectManager_h
#define ObjectManager_h

class ObjectManager
{
public:
	typedef struct OrbitItem {
		OrbitObject *orbitter;
		int comboBoxId;
	}OrbitItem;

	ObjectManager(CString PlanetString);
	ObjectManager(const ObjectManager&);
	~ObjectManager();

	void PrintPlanet(CPaintDC &dc, CDC &ManagerDC, CBitmap &Mercury, CBitmap &Venus, CBitmap &Earth, CBitmap &Jupiter, CBitmap &Mars, CBitmap &Saturn, CBitmap &Uranus, CBitmap &Neptune, CBitmap &Pluto); // Print Planet to dialog

	void PrintArcs(CDC *pDC);

	void PrintObjects(CPaintDC &dc, CDC &ManagerDC, CBitmap &Astroid, CBitmap &Debris, CBitmap &Satellite, CBitmap &SpaceStation); // Print Objects to dialog

	CPoint PlanetPoint; // Default Picture Location

	CString PlanetString; // This Object Manager Planet

	CComboBox *ComboSelectObject; // Pointer to Combo Selected Object Box

	void SetComboSelect(CComboBox &ComboSelectObjectDlg);

	void AddListToCombo();

	void ClearCombo();

	void CreateObject(double GetAltitude, CString GetType, double GetPlanetMass, double GetPlanetRadius);

	void CreateObject(int ID,double GetAltitude, CString GetType, double GetPlanetMass, double GetPlanetRadius,int ComboBoxId,double location);

	void SelectObject(); // SelectedItem = To Object ID from ComboSelectObject

	void DeleteSelected(); 

	void UndoDelete();

	void NextHour(double Minutes); // Updates all nodes next 1 hour location

	void PrevHour(double Minutes);// Updates all nodes previous 1 hour location

	const OrbitObject& GetSelectedOrbitter() const; // Returns Selected Orbitter

	list<OrbitItem> ItemList; // List of Items
	list<OrbitItem> DeletedList; // List of Deleted Items
	list<OrbitItem>::iterator SelectedItem; // Pointer To Selected Item
private:
	int generatedId; // Most Recent Generated ID
	
	
};

#endif