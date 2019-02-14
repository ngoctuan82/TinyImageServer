#ifndef _TinyImageServer_TIS_poco_h_
#define _TinyImageServer_TIS_poco_h_
#include <Core/Core.h>
#include "TISDB.h"
using namespace Upp;

struct DataPacket
{
	String Status;
	bool IsError;
	VectorMap<String, String> Data;
	void Jsonize(JsonIO & json);
};

/*
	convert the structure of schema to json
*/
struct Poco
{
	Poco();
	virtual void Jsonize(JsonIO & json); // base class
};

struct D_BACKUPRESTORETASK : Poco, Moveable<D_BACKUPRESTORETASK>
{
	S_BACKUPRESTORETASK  data;
	
	D_BACKUPRESTORETASK(S_BACKUPRESTORETASK & obj): data(obj){}
	String ToString() const { return data.ToString();}
};


struct D_USERINFO: Poco, Moveable<D_USERINFO>
{
	S_USERINFO  data;
	
	D_USERINFO(S_USERINFO & obj): data(obj){}
	String ToString() const { return data.ToString();}
};

struct D_USERSETTING: Poco, Moveable<D_USERSETTING>
{
	S_USERSETTING  data;
	
	D_USERSETTING(S_USERSETTING & obj): data(obj){}
	String ToString() const { return data.ToString();}
};

struct D_ADMINSETTING: Poco, Moveable<D_ADMINSETTING>
{
	S_ADMINSETTING  data;
	
	D_ADMINSETTING(S_ADMINSETTING & obj): data(obj){}
	String ToString() const { return data.ToString();}
};

struct D_IMAGEFILE: Poco, Moveable<D_IMAGEFILE>
{
	S_IMAGEFILE  data;
	
	D_IMAGEFILE(S_IMAGEFILE & obj): data(obj){}
	String ToString() const { return data.ToString();}
};

struct D_DAILYSUMMARY: Poco, Moveable<D_DAILYSUMMARY>
{
	S_DAILYSUMMARY  data;
	
	D_DAILYSUMMARY(S_DAILYSUMMARY & obj): data(obj){}
	String ToString() const { return data.ToString();}
};

struct D_TRANSFORMATIONSETTING: Poco, Moveable<D_TRANSFORMATIONSETTING>
{
	S_TRANSFORMATIONSETTING  data;
	
	D_TRANSFORMATIONSETTING(S_TRANSFORMATIONSETTING & obj): data(obj){}
	String ToString() const { return data.ToString();}
};

struct D_TRANSFORMATIONTASK: Poco, Moveable<D_TRANSFORMATIONTASK>
{
	S_TRANSFORMATIONTASK  data;
	
	D_TRANSFORMATIONTASK(S_TRANSFORMATIONTASK & obj): data(obj){}
	String ToString() const { return data.ToString();}
};



#endif
