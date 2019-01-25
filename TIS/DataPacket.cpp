#include "poco.h"



// how to map object to json strings
void DataPacket::Jsonize(	JsonIO & json)
{
	json
	("Status",Status)
	("IsError",IsError)
	("Data", Data)
	;
}
