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


	DeleteFile(ConfigFile(DBFILE)); // for this example, always create a new DB
	InitTISDB();

	TISApp().Run();	
}
