#include "TISDB.h"

#include <Sql/sch_schema.h>
#include <Sql/sch_source.h>
/*
 Implementation for tisdb with sqlite3
 reference from tutorial of U++ with SQL
*/

void InitTISModel()
{
	#ifdef _DEBUG
		SqlSchema sch(SQLITE3);
		All_Tables(sch);
		SqlPerformScript(sch.Upgrade());
		SqlPerformScript(sch.Attributes());
		sch.SaveNormal();
	#endif
}

/*
	Open SQLite
*/
void OpenSQLite(Sqlite3Session& sqlite3)
{
	if(!sqlite3.Open(ConfigFile(DBFILE))) {
		LOG("Can't create or open TIS database file\n");
		Exit(1);
	}
#ifdef _DEBUG
	sqlite3.LogErrors();
	sqlite3.SetTrace();
#endif
	SQL = sqlite3;
}

/*
	init database
*/
void InitTISDB()
{
	Sqlite3Session sqlsession;
	OpenSQLite(sqlsession);
	SqlSchema sch(SQLITE3);
	All_Tables(sch);
	SqlPerformScript(sch.Upgrade());
	SqlPerformScript(sch.Attributes());
	
	// insert some data to table
	SQL * Insert(USERINFO)	(FULLNAME,"TIS Admin")
								(EMAIL,"admin@simaget.com")
								(PASSWORD,"1234")
								(APIKEY,"")
								(PHONE,"123456789")
								(DATEOFBIRTH,"2018/01/01")
								(STATUS, 1) // 0: DEACTIVE, 1: ACTIVE
								(ISADMIN,1)	// 1: ADMIN ACCOUNT	
								;

	SQL * Insert(USERINFO)	(FULLNAME,"TIS USER")
								(EMAIL,"user@simaget.com")
								(PASSWORD,"1234")
								(APIKEY,"")
								(PHONE,"123456789")
								(DATEOFBIRTH,"2018/01/01")
								(STATUS, 1) // 0: DEACTIVE, 1: ACTIVE
								(ISADMIN,0)	// 1: ADMIN ACCOUNT	
								;
}

//-------------------------------
