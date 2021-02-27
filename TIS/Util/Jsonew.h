#ifndef _TIS_TinyImageServer_TIS_Jsonew_h_
#define _TIS_TinyImageServer_TIS_Jsonew_h_
#include <Core/Core.h>

using namespace Upp;

/*
	implement for json which can be jsonized
*/
struct Jsonew:Moveable<Jsonew>, public Json
{
	Jsonew(){}

	void Jsonize(JsonIO & json)
	{
		ValueMap vm  = ParseJSON(ToString());		
		//LOG(vm);		
		json.Set(vm);
	}
};


#endif
