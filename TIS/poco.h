#ifndef _TinyImageServer_TIS_poco_h_
#define _TinyImageServer_TIS_poco_h_
#include <Skylark/Skylark.h>
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
struct D_USERINFO:  Moveable<D_USERINFO>
{
	S_USERINFO  data;
	//-----------------------------------------------
	D_USERINFO(){ data.ID = -1; };
	D_USERINFO(S_USERINFO & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
	
	// CRUD
	D_USERINFO Create(Http& http);				// API
	void Update(Http& http);					// API
	void Delete(Http& http);					// API
	
	Vector<D_USERINFO> Retrieve(Http& http);	// API
	String RetrieveAsJson(Http& http);			// API
	
	D_USERINFO Login(Http& http);				// API
	//------------------------------------------------
	D_USERINFO GetByApiKey(int apikey);
	D_USERINFO GetByEmail(String email);
	D_USERINFO GetById(int id);
	//
	int GetApikey(String email) const {return CombineHash(email,10+email.GetCount());};				// get hash value for apikey
};

struct D_BACKUPRESTORETASK :  Moveable<D_BACKUPRESTORETASK>
{
	S_BACKUPRESTORETASK  data;
	
	
	D_BACKUPRESTORETASK(){}
	D_BACKUPRESTORETASK(S_BACKUPRESTORETASK & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
	
	
	
};



struct D_USERSETTING:  Moveable<D_USERSETTING>
{
	S_USERSETTING  data;
	
	D_USERSETTING(){}
	D_USERSETTING(S_USERSETTING & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
};

struct D_ADMINSETTING:  Moveable<D_ADMINSETTING>
{
	S_ADMINSETTING  data;
	
	D_ADMINSETTING(){}
	D_ADMINSETTING(S_ADMINSETTING & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
};

struct D_IMAGEFILE:  Moveable<D_IMAGEFILE>
{
	S_IMAGEFILE  data;
	
	D_IMAGEFILE(){}
	D_IMAGEFILE(S_IMAGEFILE & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
};

struct D_DAILYSUMMARY:  Moveable<D_DAILYSUMMARY>
{
	S_DAILYSUMMARY  data;
	
	
	D_DAILYSUMMARY(){}
	D_DAILYSUMMARY(S_DAILYSUMMARY & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
};

struct D_TRANSFORMATIONSETTING:  Moveable<D_TRANSFORMATIONSETTING>
{
	S_TRANSFORMATIONSETTING  data;
	
	
	D_TRANSFORMATIONSETTING(){}
	D_TRANSFORMATIONSETTING(S_TRANSFORMATIONSETTING & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
};

struct D_TRANSFORMATIONTASK:  Moveable<D_TRANSFORMATIONTASK>
{
	S_TRANSFORMATIONTASK  data;
	
	
	D_TRANSFORMATIONTASK(){}
	D_TRANSFORMATIONTASK(S_TRANSFORMATIONTASK & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
};



#endif
