#ifndef _TinyImageServer_TIS_poco_h_
#define _TinyImageServer_TIS_poco_h_
#include <Core/Core.h>
using namespace Upp;

struct DataPacket
{
	String Status;
	bool IsError;
	VectorMap<String, String> Data;
	
	void Jsonize(JsonIO & json);
}
;
#endif
