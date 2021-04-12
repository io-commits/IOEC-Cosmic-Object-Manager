#include "ObjectManager.h"
#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"
#include "Planet.h"
#include "ICosmic.h"


Planet::Planet(const CString cPlanetName, const double cRadius, const double cMass) : name(cPlanetName),radius(cRadius),mass(cMass)
{
	planetManager = new ObjectManager(cPlanetName);
}

Planet::~Planet() {  }

const CString & Planet::GetPlanetName() const { return this->name; }

const double Planet::GetMass() const { return this->mass; }

const double Planet::GetRadius() const { return this->radius; }
