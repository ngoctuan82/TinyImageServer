#ifndef _TinyImageServer_TIS_poco_h_
#define _TinyImageServer_TIS_poco_h_
#include <Skylark/Skylark.h>
#include <Core/Core.h>
#include "TISDB.h"
#include "util.h"

using namespace Upp;



template <typename T>
struct DataPacket
{
	String Status;
	bool IsError;
	Vector<T> Data;
	DataPacket(){ this->IsError= false; this->Status=""; this->Data.Clear(); }
	void Jsonize ( JsonIO & json ){
		
		json
		("Status",Status)
		("IsError",IsError)
		("Data", Data)
		;
	}
	void SetError(String error)
	{
		this->IsError = true;
		this->Status = error;
	}
};


/*
	convert the structure of schema to json
*/

struct D_USERINFO:  Moveable<D_USERINFO>
{
	S_USERINFO  data;
	//-----------------------------------------------
	D_USERINFO()
	{
		data.ID = -1;
		data.STATUS =1;
		data.SESSION =-1;
	};

	D_USERINFO ( S_USERINFO & obj ) : data ( obj ) {}

	D_USERINFO ( int id ) : data ( GetById ( id ).data ) {}

	String ToString() const
	{
		return data.ToString();
	}

	void Jsonize ( JsonIO & json );

	// CRUD
	D_USERINFO Create ( Http& http );				// API
	D_USERINFO Create ( S_USERINFO& http );			// API
	D_USERINFO Edit ( Http& http );					// API
	D_USERINFO Edit ( S_USERINFO& http );			// API
	
	
	
	void Delete ( Http& http );						// API

	Vector<D_USERINFO> Retrieve ( Http& http );		// API
	String RetrieveAsJson ( Http& http );			// API

	D_USERINFO Login ( Http& http );				// API
	//------------------------------------------------
	D_USERINFO GetByApiKey ( int apikey );
	D_USERINFO GetByApiKey ( Http& http );
	D_USERINFO GetByEmail ( String email );
	D_USERINFO GetById ( int id );
	D_USERINFO GetBySession ( int session );
	
	bool ValidateUserApiKey ( Http & http, bool isAdmin = false);
	
	//
	int GetHashValue ( String email ) const
	{
		int hash = CombineHash ( email, 10 + email.GetCount() );
		return abs ( hash );
	};				// get hash value for apikey
	
	int GetSummary();
};



struct D_USERSETTING:  Moveable<D_USERSETTING>
{
	S_USERSETTING  data;

	D_USERSETTING() { data.ID =-1; }

	D_USERSETTING ( S_USERSETTING & obj ) : data ( obj ) {}

	D_USERSETTING ( int id ) : data ( GetById ( id ).data ) {}

	String ToString() const
	{
		return data.ToString();
	}

	void Jsonize ( JsonIO & json );

	// CRUD
	D_USERSETTING Create ( Http& http );				// API
	D_USERSETTING Create ( S_USERSETTING& http );				// API
	D_USERSETTING Edit ( Http& http );					// API
	D_USERSETTING Edit ( S_USERSETTING& http );					// API
	
	
	void Delete ( Http& http );					// API

	Vector<D_USERSETTING> Retrieve ( Http& http );	// API
	String RetrieveAsJson ( Http& http );			// API
	//------------------------------------------------
	D_USERSETTING GetById ( int id );
	//------------------------------------------------

};

struct D_ADMINSETTING:  Moveable<D_ADMINSETTING>
{
	S_ADMINSETTING  data;

	D_ADMINSETTING() {data.ID =-1; }

	D_ADMINSETTING ( S_ADMINSETTING & obj ) : data ( obj ) {}

	D_ADMINSETTING ( int id ) : data ( GetById ( id ).data ) {}

	String ToString() const
	{
		return data.ToString();
	}

	//------------------------------------------------
	void Jsonize ( JsonIO & json );

	// CRUD
	D_ADMINSETTING Create ( Http& http );				// API
	D_ADMINSETTING Create ( S_ADMINSETTING& http );				// API
	D_ADMINSETTING Edit ( Http& http );					// API
	D_ADMINSETTING Edit ( S_ADMINSETTING& http );					// API
	
	void Delete ( Http& http );					// API

	Vector<D_ADMINSETTING> Retrieve ( Http& http );	// API
	String RetrieveAsJson ( Http& http );			// API
	//------------------------------------------------
	D_ADMINSETTING GetById ( int id );
	//------------------------------------------------
};

struct D_IMAGEFILE:  Moveable<D_IMAGEFILE>
{
	S_IMAGEFILE  data;

	D_IMAGEFILE() {data.ID =-1;data.STATUS = 1; }

	D_IMAGEFILE ( S_IMAGEFILE & obj ) : data ( obj ) {}

	D_IMAGEFILE ( int id ) : data ( GetById ( id ).data ) {}

	String ToString() const
	{
		return data.ToString();
	}

	void Jsonize ( JsonIO & json );
	// CRUD
	D_IMAGEFILE Create ( Http& http );				// API
	D_IMAGEFILE Create ( S_IMAGEFILE & obj);				// API
	D_IMAGEFILE Edit ( Http& http );					// API
	D_IMAGEFILE Edit ( S_IMAGEFILE& http );					// API
	
	void Delete ( Http& http );					// API

	Vector<D_IMAGEFILE> Retrieve ( Http& http );	// API
	String RetrieveAsJson ( Http& http );			// API
	//------------------------------------------------
	D_IMAGEFILE GetById ( int id );
	D_IMAGEFILE GetByFileName ( String filename  );
	//------------------------------------------------
	
	int GetSummary();
};

struct D_DAILYSUMMARY:  Moveable<D_DAILYSUMMARY>
{
	S_DAILYSUMMARY  data;


	D_DAILYSUMMARY() {data.ID =-1;data.NOOFDOWNLOADFILE=0; data.NOOFUPLOADFILE=0; data.TOTALDOWNLOADSIZE=0; data.TOTALUPLOADSIZE=0; }

	D_DAILYSUMMARY ( S_DAILYSUMMARY & obj ) : data ( obj ) {}

	D_DAILYSUMMARY ( int id ) : data ( GetById ( id ).data ) {}

	String ToString() const
	{
		return data.ToString();
	}

	void Jsonize ( JsonIO & json );
	// CRUD
	D_DAILYSUMMARY Create ( Http& http );				// API
	D_DAILYSUMMARY Edit ( Http& http );					// API
	
	D_DAILYSUMMARY Create ( S_DAILYSUMMARY& http );				// API
	D_DAILYSUMMARY Edit ( S_DAILYSUMMARY& http );					// API
	
	void Delete ( Http& http );					// API

	Vector<D_DAILYSUMMARY> Retrieve ( Http& http );	// API
	String RetrieveAsJson ( Http& http );			// API
	//------------------------------------------------
	void UpdateUpload(int userid, int size);
	void UpdateDownload(int userid, int size);
	//------------------------------------------------
	D_DAILYSUMMARY GetById ( int id );
	D_DAILYSUMMARY GetByLogDate ( int logdate );
	D_DAILYSUMMARY GetByUserIDLogDate (int userid, int logdate );
	//------------------------------------------------
	
	int GetDailyDownload(); // total download today
	Vector<Jsonew> GetMonthlyDownload();
};

struct D_TRANSFORMATIONSETTING:  Moveable<D_TRANSFORMATIONSETTING>
{
	S_TRANSFORMATIONSETTING  data;


	D_TRANSFORMATIONSETTING() {data.ID =-1; }

	D_TRANSFORMATIONSETTING ( S_TRANSFORMATIONSETTING & obj ) : data ( obj ) {}

	D_TRANSFORMATIONSETTING ( int id ) : data ( GetById ( id ).data ) {}

	String ToString() const
	{
		return data.ToString();
	}

	void Jsonize ( JsonIO & json );

	// CRUD
	D_TRANSFORMATIONSETTING Create ( Http& http );				// API
	D_TRANSFORMATIONSETTING Create ( S_TRANSFORMATIONSETTING& http );				// API
	D_TRANSFORMATIONSETTING Edit ( Http& http );					// API
	D_TRANSFORMATIONSETTING Edit ( S_TRANSFORMATIONSETTING& http );					// API
	
	
	void Delete ( Http& http );					// API

	Vector<D_TRANSFORMATIONSETTING> Retrieve ( Http& http );	// API
	String RetrieveAsJson ( Http& http );			// API
	//------------------------------------------------
	D_TRANSFORMATIONSETTING GetById ( int id );
	//------------------------------------------------
};

struct D_TRANSFORMATIONTASK:  Moveable<D_TRANSFORMATIONTASK>
{
	S_TRANSFORMATIONTASK  data;


	D_TRANSFORMATIONTASK() {data.ID =-1; }

	D_TRANSFORMATIONTASK ( S_TRANSFORMATIONTASK & obj ) : data ( obj ) {}

	D_TRANSFORMATIONTASK ( int id ) : data ( GetById ( id ).data ) {}

	String ToString() const
	{
		return data.ToString();
	}

	void Jsonize ( JsonIO & json );

	// CRUD
	D_TRANSFORMATIONTASK Create ( Http& http );				// API
	D_TRANSFORMATIONTASK Create ( S_TRANSFORMATIONTASK& http );				// API
	D_TRANSFORMATIONTASK Edit ( Http& http );					// API
	D_TRANSFORMATIONTASK Edit ( S_TRANSFORMATIONTASK& http );					// API
	
	void Delete ( Http& http );					// API

	Vector<D_TRANSFORMATIONTASK> Retrieve ( Http& http );	// API
	String RetrieveAsJson ( Http& http );			// API
	//------------------------------------------------
	D_TRANSFORMATIONTASK GetById ( int id );
	//------------------------------------------------
};

struct D_BACKUPRESTORETASK :  Moveable<D_BACKUPRESTORETASK>
{
	S_BACKUPRESTORETASK  data;


	D_BACKUPRESTORETASK() {data.ID =-1; }

	D_BACKUPRESTORETASK ( S_BACKUPRESTORETASK & obj ) : data ( obj ) {}

	D_BACKUPRESTORETASK ( int id ) : data ( GetById ( id ).data ) {}

	String ToString() const
	{
		return data.ToString();
	}

	void Jsonize ( JsonIO & json );

	// CRUD
	D_BACKUPRESTORETASK Create ( Http& http );				// API
	D_BACKUPRESTORETASK Create ( S_BACKUPRESTORETASK& http );				// API
	D_BACKUPRESTORETASK Edit ( Http& http );					// API
	D_BACKUPRESTORETASK Edit ( S_BACKUPRESTORETASK& http );					// API
	
	void Delete ( Http& http );					// API

	Vector<D_BACKUPRESTORETASK> Retrieve ( Http& http );	// API
	String RetrieveAsJson ( Http& http );			// API
	//------------------------------------------------
	D_BACKUPRESTORETASK GetById ( int id );
	//------------------------------------------------
	
	int GetSummary();
};



#endif
