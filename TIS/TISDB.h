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
			
			this->PAGE = sPage.IsEmpty()?0:atoi(sPage);
			this->SIZE = sSize.IsEmpty()?20:atoi(sSize);
			this->OFFSET = this->PAGE * this->SIZE;
		}
		catch(...)
		{
			Cout() << "Error get params PAGINATION";
		}
	}
};




#endif
