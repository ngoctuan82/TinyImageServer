#include "TIS.h"



CONSOLE_APP_MAIN
{
#ifdef _DEBUG
	StdLogSetup(LOG_FILE|LOG_COUT);
	Ini::skylark_log = true;
#endif

	TISApp().Run();	
}
