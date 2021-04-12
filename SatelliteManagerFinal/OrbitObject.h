#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include "ICosmic.h"

#ifndef OrbitObject_h
#define OrbitObject_h

class OrbitObject : public ICosmic
{
public:
	OrbitObject(int, double, CString, double, double); // ID, Altitude, Type, PlanetMass, PlanetRadius
	OrbitObject(int, double, CString, double, double,int,double); // ID, Altitude, Type, PlanetMass, PlanetRadius, comboBoxId,location

	virtual ~OrbitObject();

	double GetLocation() const; // Return Location
	int GetLocationX(); // Return X Location
	int GetLocationY(); // Return Y Location
	CString GetType() ; // Return Type
	double GetAltitude()const; // Return Altitude
	double GetVelocity()const; // Return Velocity
	double GetAngularVelocity()const; // Return AngularVelocity
	double GetOrbitTime()const; // Return OrbitTime	
	double GetAcceleration()const; // Return Acceleration
	int GetComboBoxID() const;
	/*void SetID(const int);
	void SetComboBoxID(int);*/
	void SetLocation(double); // Set Location
	/*void SetType(CString);
	void SetAltitude(double);
	void SetVelocity(double);
	void SetAngularVelocity(double);
	void SetOrbitTime(double);
	void SetAcceleration(double);*/
	const int GetId() const;
private:
	const int ID; // Object ID
	int ComboBoxID; // ComboBox ID
	double Location; // Object Location
	CString Type; // Object Type
	double Altitude; // Object Altitude
	double Velocity; // Object Velocity
	double AngularVelocity; // Object Angular Velocity
	double OrbitTime; // Object Orbit Time
	double Acceleration; // Object Acceleration
};
#endif
