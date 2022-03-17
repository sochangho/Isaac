#include "framework.h"
#include "CTestObject.h"

CTestObject::CTestObject()
{
}

CTestObject::~CTestObject()
{
}

CTestObject* CTestObject::Clone()
{
    return new CTestObject(*this);
}

void CTestObject::update()
{
}

void CTestObject::render()
{
    component_render();
}
