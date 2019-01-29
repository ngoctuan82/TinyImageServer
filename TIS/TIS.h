#ifndef _TinyImageServer_TIS_TIS_h_
#define _TinyImageServer_TIS_TIS_h_

#include <Skylark/Skylark.h>
#include <plugin/sqlite3/Sqlite3.h>

using namespace Upp;
/* // define the database model for TIS project. 

#define  MODEL         <TIS/Model.sch>
#define  SCHEMADIALECT <plugin/sqlite3/Sqlite3Schema.h>
#include <Sql/sch_header.h>

*/

struct TISApp : SkylarkApp {
	TISApp() {
		root = "tis";
		path <<";" << "/home/tony/MyApps/TinyImageServer/TIS/html/"; // development path
		path << ";"<<"/html"; // deployment path for current folder
	#ifdef _DEBUG
		prefork = 0;
		use_caching = false;
	#endif
	}
};

#endif
