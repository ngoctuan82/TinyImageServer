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

struct Crud {

	SqlId       table;
	SqlId       key;
	SqlSet      columns;
	//-------------------------------------------

	void Create(Http& http);

	void Edit(Http& http);
	
	void Delete(Http& http);
	
	void Select(Http& http);

	typedef Crud CLASSNAME;

	Crud() { key = SqlId("ID"); columns = SqlSet(SqlAll()); }
};




#endif
