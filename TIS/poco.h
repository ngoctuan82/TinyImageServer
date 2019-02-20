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
	D_USERINFO Edit(Http& http);					// API
	void Delete(Http& http);					// API
	
	Vector<D_USERINFO> Retrieve(Http& http);	// API
	String RetrieveAsJson(Http& http);			// API
	
	D_USERINFO Login(Http& http);				// API
	//------------------------------------------------
	D_USERINFO GetByApiKey(int apikey);
	D_USERINFO GetByEmail(String email);
	D_USERINFO GetById(int id);
	//
	int GetHashValue(String email) const {int hash =CombineHash(email,10+email.GetCount()); return abs(hash);   };				// get hash value for apikey
};



struct D_USERSETTING:  Moveable<D_USERSETTING>
{
	S_USERSETTING  data;
	
	D_USERSETTING(){}
	D_USERSETTING(S_USERSETTING & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json);
	
	// CRUD
	D_USERSETTING Create(Http& http);				// API
	D_USERSETTING Edit(Http& http);					// API
	void Delete(Http& http);					// API
	
	Vector<D_USERSETTING> Retrieve(Http& http);	// API
	String RetrieveAsJson(Http& http);			// API	
	//------------------------------------------------
	D_USERSETTING GetById(int id);
	//------------------------------------------------
	
};

struct D_ADMINSETTING:  Moveable<D_ADMINSETTING>
{
	S_ADMINSETTING  data;
	
	D_ADMINSETTING(){}
	D_ADMINSETTING(S_ADMINSETTING & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	//------------------------------------------------
	void Jsonize(JsonIO & json); 
	
	// CRUD
	D_ADMINSETTING Create(Http& http);				// API
	D_ADMINSETTING Edit(Http& http);					// API
	void Delete(Http& http);					// API
	
	Vector<D_ADMINSETTING> Retrieve(Http& http);	// API
	String RetrieveAsJson(Http& http);			// API	
	//------------------------------------------------
	D_ADMINSETTING GetById(int id);
	//------------------------------------------------
};

struct D_IMAGEFILE:  Moveable<D_IMAGEFILE>
{
	S_IMAGEFILE  data;
	
	D_IMAGEFILE(){}
	D_IMAGEFILE(S_IMAGEFILE & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
	// CRUD
	D_IMAGEFILE Create(Http& http);				// API
	D_IMAGEFILE Edit(Http& http);					// API
	void Delete(Http& http);					// API
	
	Vector<D_IMAGEFILE> Retrieve(Http& http);	// API
	String RetrieveAsJson(Http& http);			// API	
	//------------------------------------------------
	D_IMAGEFILE GetById(int id);
	//------------------------------------------------
};

struct D_DAILYSUMMARY:  Moveable<D_DAILYSUMMARY>
{
	S_DAILYSUMMARY  data;
	
	
	D_DAILYSUMMARY(){}
	D_DAILYSUMMARY(S_DAILYSUMMARY & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json);
	// CRUD
	D_DAILYSUMMARY Create(Http& http);				// API
	D_DAILYSUMMARY Edit(Http& http);					// API
	void Delete(Http& http);					// API
	
	Vector<D_DAILYSUMMARY> Retrieve(Http& http);	// API
	String RetrieveAsJson(Http& http);			// API	
	//------------------------------------------------
	D_DAILYSUMMARY GetById(int id);
	//------------------------------------------------
};

struct D_TRANSFORMATIONSETTING:  Moveable<D_TRANSFORMATIONSETTING>
{
	S_TRANSFORMATIONSETTING  data;
	
	
	D_TRANSFORMATIONSETTING(){}
	D_TRANSFORMATIONSETTING(S_TRANSFORMATIONSETTING & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
	
	// CRUD
	D_TRANSFORMATIONSETTING Create(Http& http);				// API
	D_TRANSFORMATIONSETTING Edit(Http& http);					// API
	void Delete(Http& http);					// API
	
	Vector<D_TRANSFORMATIONSETTING> Retrieve(Http& http);	// API
	String RetrieveAsJson(Http& http);			// API	
	//------------------------------------------------
	D_TRANSFORMATIONSETTING GetById(int id);
	//------------------------------------------------
};

struct D_TRANSFORMATIONTASK:  Moveable<D_TRANSFORMATIONTASK>
{
	S_TRANSFORMATIONTASK  data;
	
	
	D_TRANSFORMATIONTASK(){}
	D_TRANSFORMATIONTASK(S_TRANSFORMATIONTASK & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 
	
	// CRUD
	D_TRANSFORMATIONTASK Create(Http& http);				// API
	D_TRANSFORMATIONTASK Edit(Http& http);					// API
	void Delete(Http& http);					// API
	
	Vector<D_TRANSFORMATIONTASK> Retrieve(Http& http);	// API
	String RetrieveAsJson(Http& http);			// API	
	//------------------------------------------------
	D_TRANSFORMATIONTASK GetById(int id);
	//------------------------------------------------
};
struct D_BACKUPRESTORETASK :  Moveable<D_BACKUPRESTORETASK>
{
	S_BACKUPRESTORETASK  data;
	
	
	D_BACKUPRESTORETASK(){}
	D_BACKUPRESTORETASK(S_BACKUPRESTORETASK & obj): data(obj){}
	String ToString() const { return data.ToString();}
	
	void Jsonize(JsonIO & json); 

	// CRUD
	D_BACKUPRESTORETASK Create(Http& http);				// API
	D_BACKUPRESTORETASK Edit(Http& http);					// API
	void Delete(Http& http);					// API
	
	Vector<D_BACKUPRESTORETASK> Retrieve(Http& http);	// API
	String RetrieveAsJson(Http& http);			// API	
	//------------------------------------------------
	D_BACKUPRESTORETASK GetById(int id);
	//------------------------------------------------
};



#endif
