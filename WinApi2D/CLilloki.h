#pragma once
#include "CItem.h"
class CLilloki : public CItem
{
private:

public:
	CLilloki();
	~CLilloki();

	virtual void ItemUse(fVec2 dir);
	virtual CLilloki* Create();


};

