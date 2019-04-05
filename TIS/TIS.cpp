#include "TIS.h"
#include "TISDB.h"


void TISApp::WorkThread()
{
	Sqlite3Session sqlite3;
	OpenSQLite(sqlite3);
	RunThread();
}

CONSOLE_APP_MAIN
{
#ifdef _DEBUG
	StdLogSetup(LOG_FILE|LOG_COUT);
	Ini::skylark_log = true;
#endif


	Cout()<< "\n Directory "<<GetCurrentDirectory();
	Cout()<< "\n DB file "<< DBFILE;
	Cout()<< "\n Local file "<<NormalizePath(".");
	
//	DeleteFile(ConfigFile(DBFILE)); // for this example, always create a new DB
	InitTISDB();
	
	
	TISApp().Run();	
}
