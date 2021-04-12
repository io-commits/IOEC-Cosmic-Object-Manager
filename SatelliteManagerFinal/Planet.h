#include "ICosmic.h"
#include "ObjectManager.h"
#include "pch.h"
#include "framework.h"
#include "afxdialogex.h"

#ifndef Planet_h
#define Planet_h

class Planet : public ICosmic
{
public:
	Planet(const CString name,const double radius,const double mass);
	const CString& GetPlanetName() const;
	const double GetMass() const;
	const double GetRadius() const;
	ObjectManager *planetManager;
	~Planet();
private:
	const double radius;
	const double mass;
	const CString name;
};

#endif
