#include "framework.h"
#include "CLilloki.h"
#include "CTears.h"
CLilloki::CLilloki()
{
}

CLilloki::~CLilloki()
{
}

void CLilloki::ItemUse(fVec2 dir)
{
	fPoint pos = GetOwnObj()->GetPos();
	CTears* tears = new CTears;
	tears->SetPos(fPoint(pos.x + 10, pos.y));
	tears->SetDir(fVec2(1, 0));
	CreateObj(tears, GROUP_GAMEOBJ::TEARS);

	CTears* tears1 = new CTears;
	tears1->SetPos(fPoint(pos.x , pos.y + 10));
	tears1->SetDir(fVec2(0, 1));
	CreateObj(tears1, GROUP_GAMEOBJ::TEARS);

	CTears* tears2 = new CTears;
	tears2->SetPos(fPoint(pos.x - 10, pos.y));
	tears2->SetDir(fVec2(-1, 0));
	CreateObj(tears2, GROUP_GAMEOBJ::TEARS);


	CTears* tears3 = new CTears;
	tears3->SetPos(fPoint(pos.x , pos.y - 10));
	tears3->SetDir(fVec2(0, -1));
	CreateObj(tears3, GROUP_GAMEOBJ::TEARS);


}

CLilloki* CLilloki::Create()
{
	return new CLilloki();
}
