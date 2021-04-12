#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include "ObjectManager.h"
#include "OrbitObject.h"
#define Pi 3.1415926

typedef struct OrbitItem {
	OrbitObject *orbitter;
	int comboBoxId;
}OrbitItem;

ObjectManager::ObjectManager(CString PlanetString)
{
	generatedId = 0;
	PlanetPoint.SetPoint(1475,500); // Default Planet Position
	this->PlanetString = PlanetString;
}

ObjectManager::ObjectManager(const ObjectManager& copyFrom)
{
	generatedId = 0;
	PlanetPoint.SetPoint(1500, 500); // Default Planet Position
	this->PlanetString = copyFrom.PlanetString;
	ItemList = copyFrom.ItemList;
}

ObjectManager::~ObjectManager()
{
	if(ItemList.empty()==false)ItemList.clear();
	if(DeletedList.empty()==false)DeletedList.clear();

}

void ObjectManager::SetComboSelect(CComboBox &ComboSelectObjectDlg)
{
	ComboSelectObject = &ComboSelectObjectDlg;
}

void ObjectManager::AddListToCombo() // Adds ItemList back to ComboBox
{
	CString IDString;
	std::list<OrbitItem>::iterator Iterator = ItemList.begin();
	while (Iterator != ItemList.end())
	{
		IDString.Format(_T("%d"), Iterator->orbitter->GetId()); // ID to CString
		Iterator->comboBoxId = ComboSelectObject->AddString(IDString); // Add to ComboBox & Save to Item ComboID	
		++Iterator;
	}
}

void ObjectManager::ClearCombo() // Clears Combo Box
{
	ComboSelectObject->ResetContent();
}

void ObjectManager::CreateObject(double GetAltitude, CString GetType, double GetPlanetMass, double GetPlanetRadius) // Create and Add Object to ObjectList & Menu
{
	OrbitItem Item; //Create Item
	CString CreatedIDString; // ID String
	Item.orbitter = new OrbitObject(++generatedId, GetAltitude, GetType, GetPlanetMass, GetPlanetRadius); // Create OrbitObject
	Item.comboBoxId = generatedId;
	CreatedIDString.Format(_T("%d"), generatedId); // Int to CString
	Item.comboBoxId= ComboSelectObject->AddString(CreatedIDString); // Add to ComboBox & Save to Item ComboID	
	ItemList.push_front(Item); // Add Item to ItemList
}

void ObjectManager::CreateObject(int ID, double GetAltitude, CString GetType, double GetPlanetMass, double GetPlanetRadius, int ComboBoxId,double location)
{
	OrbitItem Item; //Create Item
	CString CreatedIDString; // ID String
	Item.orbitter = new OrbitObject(++ID, GetAltitude, GetType, GetPlanetMass, GetPlanetRadius,ComboBoxId,location); // Create OrbitObject
	Item.comboBoxId = ID;
	CreatedIDString.Format(_T("%d"), generatedId); // Int to CString
	Item.comboBoxId = ComboSelectObject->AddString(CreatedIDString); // Add to ComboBox & Save to Item ComboID	
	ItemList.push_front(Item); // Add Item to ItemList
}


void ObjectManager::SelectObject() // SelectedItem = To Object ID from ComboSelectObject
{
	std::list<OrbitItem>::iterator selectedIterator = ItemList.begin();
	CString SelectedID;
	int SelectedIDint;
	ComboSelectObject->GetLBText(ComboSelectObject->GetCurSel(), SelectedID); // Get ID CString from combo box
	SelectedIDint = _ttoi(SelectedID);
	for (; selectedIterator != ItemList.end(); ++selectedIterator) // Scan List for ID
	{
		if (SelectedIDint == selectedIterator->orbitter->GetId())
		{
			SelectedItem = selectedIterator; // Set Selected Item
		}
	}
}

void ObjectManager::DeleteSelected() // Delete Selected Object
{
	if (ItemList.empty() ==false)
	{
		ComboSelectObject->DeleteString(SelectedItem->comboBoxId); // Delete from Combo Select
		DeletedList.push_front(*SelectedItem); // Transfer to DeletedList
		ItemList.erase(SelectedItem); // Delete Node
	}
}

void ObjectManager::UndoDelete() // Undo
{
	if (DeletedList.size() != 0)
	{
		std::list<OrbitItem>::iterator DeletedItem = DeletedList.begin(); // Pointer To Selected Item
		CString IDString; // ID String
		IDString.Format(_T("%d"), DeletedItem->orbitter->GetId());
		DeletedItem->comboBoxId = ComboSelectObject->AddString(IDString); // Add to ComboBox & Save to Item ComboID

		ItemList.push_front(*DeletedItem); // Transfer from Deleted to ObjectList
		DeletedList.erase(DeletedItem); // Erase from DeletedList
	}

}

void ObjectManager::NextHour(double Minutes) // Updates all nodes next 1 hour location
{
	std::list<OrbitItem>::iterator p = ItemList.begin();
	while (p != ItemList.end())
	{
		p->orbitter->SetLocation(p->orbitter->GetLocation() + (p->orbitter->GetAngularVelocity())*(Minutes / 60.0)); // Update Next Location by Minutes
		++p;
	}
}

void ObjectManager::PrevHour(double Minutes)// Updates all nodes previous 1 hour location
{
	std::list<OrbitItem>::iterator p = ItemList.begin();
	while (p != ItemList.end())
	{
		p->orbitter->SetLocation(p->orbitter->GetLocation() - (p->orbitter->GetAngularVelocity())*(Minutes / 60.0)); // Update Prev Location by Minutes
		++p;
	}
}

const OrbitObject& ObjectManager::GetSelectedOrbitter() const // Returns Selected Orbitter
{
	return *SelectedItem->orbitter ;
}

void ObjectManager::PrintPlanet(CPaintDC &dc, CDC &ManagerDC, CBitmap &Mercury, CBitmap &Venus, CBitmap &Earth, CBitmap &Jupiter, CBitmap &Mars, CBitmap &Saturn, CBitmap &Uranus, CBitmap &Neptune, CBitmap &Pluto)
{
	ManagerDC.CreateCompatibleDC(&dc); // Create a memory device compatible with the above CPaintDC variable

	if (PlanetString == "Mercury")
		ManagerDC.SelectObject(&Mercury);
	else if (PlanetString == "Venus")
		ManagerDC.SelectObject(&Venus);
	else if (PlanetString == "Earth")
		ManagerDC.SelectObject(&Earth);
	else if (PlanetString == "Jupiter")
		ManagerDC.SelectObject(&Jupiter);
	else if (PlanetString == "Mars")
		ManagerDC.SelectObject(&Mars);
	else if (PlanetString == "Saturn")
		ManagerDC.SelectObject(&Saturn);
	else if (PlanetString == "Uranus")
		ManagerDC.SelectObject(&Uranus);
	else if (PlanetString == "Neptune")
		ManagerDC.SelectObject(&Neptune);
	else if (PlanetString == "Pluto")
		ManagerDC.SelectObject(&Pluto);

	dc.BitBlt(PlanetPoint.x-128, PlanetPoint.y-128, 256, 256, &ManagerDC, 0, 0, SRCCOPY); // Copy the bits from the memory DC into the current dc
}

void ObjectManager::PrintArcs(CDC* pDC)
{
	if (ItemList.empty() == false)
	{
		std::list<OrbitItem>::iterator p = ItemList.begin();
		pDC->SetArcDirection(AD_CLOCKWISE); // Set Direction

		CPen PenRed;
		PenRed.CreatePen(PS_SOLID | PS_COSMETIC, 2, RGB(255, 0, 0));
		CPen PenGray;
		PenGray.CreatePen(PS_SOLID | PS_COSMETIC, 2, RGB(150, 150, 150));
		CPen PenBlue;
		PenBlue.CreatePen(PS_SOLID | PS_COSMETIC, 2, RGB(0, 0, 255));
		CPen PenGreen;
		PenGreen.CreatePen(PS_SOLID | PS_COSMETIC, 2, RGB(0, 255, 0));
		
		while (p != ItemList.end()) // Scan Item List
		{
			// Select Brush
			if (p->orbitter->GetType() == "Astroid")
				pDC->SelectObject(&PenRed);
			else if (p->orbitter->GetType() == "Debris")
				pDC->SelectObject(&PenGray);
			else if (p->orbitter->GetType() == "Satellite")
				pDC->SelectObject(&PenBlue);
			else if (p->orbitter->GetType() == "Station")
				pDC->SelectObject(&PenGreen);

			// Print Arc
			double radius = 140 + sqrt(p->orbitter->GetAltitude() > 30000 ? 30000 : p->orbitter->GetAltitude()); // Altitude Function
			pDC->Arc(PlanetPoint.x - radius, PlanetPoint.y - radius, PlanetPoint.x + radius, PlanetPoint.y + radius, PlanetPoint.x, PlanetPoint.y-radius, PlanetPoint.x+ p->orbitter->GetLocationX(), PlanetPoint.y+ p->orbitter->GetLocationY()); // Draw Arch

			++p; // Next Item
		}
	}
}

void ObjectManager::PrintObjects(CPaintDC &dc, CDC &ManagerDC, CBitmap &Astroid, CBitmap &Debris, CBitmap &Satellite, CBitmap &SpaceStation) // Scan ItemList and print Objects
{
	if (ItemList.empty() == false)
	{
		std::list<OrbitItem>::iterator p = ItemList.begin();

		while (p != ItemList.end()) // Scan Item List
		{
			// Set Bitmap
			if (p->orbitter->GetType() == "Astroid")
				ManagerDC.SelectObject(&Astroid);
			else if (p->orbitter->GetType() == "Debris")
				ManagerDC.SelectObject(&Debris);
			else if (p->orbitter->GetType() == "Satellite")
				ManagerDC.SelectObject(&Satellite);
			else if (p->orbitter->GetType() == "Station")
				ManagerDC.SelectObject(&SpaceStation);

			// Print Bitmap
			dc.BitBlt(PlanetPoint.x - 16 + p->orbitter->GetLocationX(), PlanetPoint.y - 16 + p->orbitter->GetLocationY(), 128, 128, &ManagerDC, 0, 0, SRCCOPY); // X
			++p; // Next Item
		}
	}
}