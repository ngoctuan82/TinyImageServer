#ifndef _TinyImageServer_TIS_TIS_h_
#define _TinyImageServer_TIS_TIS_h_

#include <Skylark/Skylark.h>

using namespace Upp;

struct TISApp : SkylarkApp {
	
	virtual void WorkThread();
	
	TISApp() {
		root = "tis";
		path="./TISDATA";// release
		
//		path <<";" << "/home/tony/MyApps/TinyImageServer/TIS/html/"; 	// development path
//		path << ";"<<"/html";
//		path << ";"<<".";
//		path << ";C:/upp/MyApps/TinyImageServer/TIS";
//		path << ";/home/tony/MyApps/TinyImageServer/TIS";// deployment path for current folder
		
		threads= 1; // because sqlite3 does not work correct with multiple threads
		
	#ifdef _DEBUG
		prefork = 0;
		use_caching = false;
	#endif
	}	
};

#endif
