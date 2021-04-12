#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include "ICosmic.h"
#include "OrbitObject.h"
#include <iostream>
#include <cmath>
#define G 6.67e-11 // Gravitation Constant
#define Pi 3.14159265358979

using namespace std;

OrbitObject::OrbitObject(int cID, double cAltitude, CString cObjectType, double cPlanetMass, double cPlanetRadius) :ID(cID)
{
	ComboBoxID = 0;
	Location = 0; // (deg)
	Type = cObjectType; // Object Type
	Altitude = cAltitude; // Altitude (km)
	Velocity = sqrt((G * cPlanetMass) / (cPlanetRadius + (Altitude * 1000))); // Velocity (m/s)
	AngularVelocity = (Velocity / (cPlanetRadius + (Altitude * 1000)))*(57.2957795)*(3600); // AngVelocity > To degrees > sec to hour
	OrbitTime = 360 / AngularVelocity; // Orbit Time (Hours)
	Acceleration = (G*cPlanetMass) / ((cPlanetRadius + Altitude)*(cPlanetRadius + (Altitude * 1000))); // Gravity Force Acceleration (m/s^2)

}

OrbitObject::OrbitObject(int cID, double cAltitude, CString cObjectType, double cPlanetMass, double cPlanetRadius,int cComboBoxId,double cLocation) :ID(cID)
{
	ComboBoxID = cComboBoxId;
	Location = cLocation; // (deg)
	Type = cObjectType; // Object Type
	Altitude = cAltitude; // Altitude (km)
	Velocity = sqrt((G * cPlanetMass) / (cPlanetRadius + (Altitude * 1000))); // Velocity (m/s)
	AngularVelocity = (Velocity / (cPlanetRadius + (Altitude * 1000)))*(57.2957795)*(3600); // AngVelocity > To degrees > sec to hour
	OrbitTime = 360 / AngularVelocity; // Orbit Time (Hours)
	Acceleration = (G*cPlanetMass) / ((cPlanetRadius + Altitude)*(cPlanetRadius + (Altitude * 1000))); // Gravity Force Acceleration (m/s^2)
}

OrbitObject::~OrbitObject() {}

double OrbitObject::GetLocation() const { return this->Location; }

int OrbitObject::GetLocationX()
{
	int X;
	X = (sin((this->Location+0.5)*Pi/180)*(sqrt(this->Altitude>30000?30000: this->Altitude) +140));
	return X;
}

int OrbitObject::GetLocationY()
{
	int Y;
	Y =(cos((this->Location+0.1)*Pi / 180)*(sqrt(this->Altitude > 30000 ? 30000 : this->Altitude) + 140)*(-1));
	return Y;
}

CString OrbitObject::GetType()  { return this->Type; }

double OrbitObject::GetAltitude() const { return this->Altitude; }

double OrbitObject::GetVelocity() const { return this->Velocity; }

double OrbitObject::GetAngularVelocity()const { return this->AngularVelocity; }

double OrbitObject::GetOrbitTime()const { return this->OrbitTime; }

double OrbitObject::GetAcceleration() const { return this->Acceleration; }

const int OrbitObject::GetId() const { return this->ID; }

void OrbitObject::SetLocation(double GetLocation) 
{
	this->Location = (int)GetLocation % 360; // Whole Part
	this->Location += GetLocation - (int)GetLocation; // After Dot
	if (this->Location < 0) // abs
		this->Location += 360;
}

int OrbitObject::GetComboBoxID() const { return ComboBoxID; }