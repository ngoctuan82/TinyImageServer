#ifndef _TinyImageServer_TIS_tisdb_h_
#define _TinyImageServer_TIS_tisdb_h_
#include "TIS.h"

#include <Core/Core.h>
#include <plugin/sqlite3/Sqlite3.h>

using namespace Upp;

#define  MODEL         <TinyImageServer/TIS/tisdb.sch>
#define  SCHEMADIALECT <plugin/sqlite3/Sqlite3Schema.h>
#include <Sql/sch_header.h>


// include db functionalities
const String DBFILE ="TISDB";

void InitTISDB();
void InitTISModel();
void OpenSQLite(Sqlite3Session& sqlite3);

//----------------------------------------------

struct PAGINATION {

	int SIZE = 20;
	int PAGE = 1;
	int OFFSET = SIZE*PAGE;

	typedef PAGINATION CLASSNAME;

	PAGINATION(Http & http) {
		try{
			String sSize = (String)http["SIZE"];
			String sPage = (String)http["PAGE"];
			
			this->PAGE = sPage.IsEmpty()?0:abs(atoi(sPage));
			this->SIZE = sSize.IsEmpty()?20:abs(atoi(sSize));
			this->OFFSET = this->PAGE * this->SIZE;
		}
		catch(...)
		{
			Cout() << "Error get params PAGINATION";
		}
	}
};

struct ORDER {

	String COL = "ID";
	int DESC = 1;
	
	typedef ORDER CLASSNAME;

	ORDER(Http & http) {
		try{
			String sCol = (String)http["ORDERBY"];
			int sDesc = atoi((String)http["DESC"]);
			
			this->COL = sCol.IsEmpty()?"ID":sCol;
			this->DESC = sDesc?1:0;
		}
		catch(...)
		{
			Cout() << "Error get params ORDER";
		}
	}
};


#endif
