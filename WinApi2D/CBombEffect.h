#pragma once
#include "CEffect.h"
class CBombEffect : public CEffect
{
   private:

   public:
	   CBombEffect();
	   ~CBombEffect();

	   virtual CBombEffect* Clone();
	   
	   virtual void update();
	   virtual void render();

};

