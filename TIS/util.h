#ifndef _TinyImageServer_TIS_util_h_
#define _TinyImageServer_TIS_util_h_
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
		
		LOG(vm);
		
		json.Set(vm);
	}
};



Vector<Jsonew> GetDrivesSummaryInfo();
Vector<Jsonew> GetDrivesInfo();
Vector<Jsonew> GetServerInfo();

#endif
