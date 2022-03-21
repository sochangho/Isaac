#include "framework.h"
#include "CCenterObject.h"

CCenterObject::CCenterObject()
{
}

CCenterObject::~CCenterObject()
{
}

CCenterObject* CCenterObject::Clone()
{
    return nullptr;
}

void CCenterObject::update()
{
}

void CCenterObject::render()
{
    component_render();
}
