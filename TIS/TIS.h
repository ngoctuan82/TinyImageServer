#ifndef _TinyImageServer_TIS_TIS_h_
#define _TinyImageServer_TIS_TIS_h_

#include <Skylark/Skylark.h>

using namespace Upp;

/*
#define  MODEL         <TinyImageServer/TIS/tisdb.sch>
#define  SCHEMADIALECT <plugin/sqlite3/Sqlite3Schema.h>
#include <Sql/sch_header.h>
#include <Sql/sch_schema.h>
#include <Sql/sch_source.h>
// include db functionalities
*/

struct TISApp : SkylarkApp {
	
	virtual void WorkThread();
	
	TISApp() {
		root = "tis";
		path <<";" << "/home/tony/MyApps/TinyImageServer/TIS/html/"; 	// development path
		path << ";"<<"/html";
		path << ";"<<".";
		path << ";C:/upp/MyApps/TinyImageServer/TIS";
		path << ";/home/tony/MyApps/TinyImageServer/TIS"		; 											// deployment path for current folder
		
		threads= 1; // because sqlite3 does not work correct with multiple threads
		
	#ifdef _DEBUG
		prefork = 0;
		use_caching = false;
	#endif
	}
	
};




#endif
