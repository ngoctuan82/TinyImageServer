#include "util.h"
#include "Poco.h"
#include <Core/Core.h>

using namespace Upp;

void D_BACKUPRESTORETASK::Jsonize(JsonIO & json)
{
	Time time;
	time.Set(data.CREATEDDATE);
	json
	("ID",data.ID )
	///("USERID",data.USERID)
	("ISBACKUPTASK",data.ISBACKUPTASK)
	("CREATEDDATE",  time )
//	("FINISHDATE",data.FINISHDATE)
//	("SOURCEFOLDERPATH",data.SOURCEFOLDERPATH)
	("FOLDERPATH",data.FOLDERPATH)
//	("PROCCESED",data.PROCCESED)
//	("TOTALFILES",data.TOTALFILES)
	("STATUS",data.STATUS) // when we have finishdate means it done

	;
}

D_BACKUPRESTORETASK D_BACKUPRESTORETASK::Create(Http& http){
	
	S_BACKUPRESTORETASK pObj; // params container
	D_ADMINSETTING objAS;
	 
	try{
		//pObj.ID=atoi((String)http["ID"]);
		Time time=GetSysTime();
		int64 iTime = time.Get();
		LOG(iTime);
		
		pObj.ISBACKUPTASK=atoi((String)http["ISBACKUPTASK"]);
		pObj.CREATEDDATE= iTime;
		pObj.STATUS=0;
		
		objAS = objAS.GetById(1);
		
		pObj.FOLDERPATH = AppendFileName(objAS.data.BACKUPPATH, AsString(pObj.CREATEDDATE) );
		
	}
	catch(...)
	{
		Cout() << "Error D_BACKUPRESTORETASK::Create";
	}
	
	return Create(pObj);
}


D_BACKUPRESTORETASK D_BACKUPRESTORETASK::Create(S_BACKUPRESTORETASK& pObj){
	
	
	// check any proccessing row
	D_BACKUPRESTORETASK tObj = GetByStatus(0); // get proccesing status
	
	if(tObj.data.ID < 0)
	{
		SQL *  Insert( BACKUPRESTORETASK )
				(ISBACKUPTASK,pObj.ISBACKUPTASK)
				(CREATEDDATE,pObj.CREATEDDATE)
				(FOLDERPATH,pObj.FOLDERPATH)	
				(STATUS,pObj.STATUS)
				;
		int id = SQL.GetInsertedId();
		tObj = GetById(id);
		//----------------------------------------
		LOG("\nCreated D_BACKUPRESTORETASK :"<<tObj); 
	}
	else
	{
		LOG("\n D_BACKUPRESTORETASK  existed:"<<tObj.data.ID);
		tObj.data.ID = -1;
	}
	return tObj;
}

/*
	update user information based on ID
	ex:
		http://127.0.0.1:8001/tis/api/user/update?ID=3&EMAIL=user23@simaget.com&PASSWORD=12345&FULLNAME=user2%20simaget&PHONE=987654321&DATEOFBIRTH=2000/03/01
*/
D_BACKUPRESTORETASK D_BACKUPRESTORETASK::Edit(Http& http){
	S_BACKUPRESTORETASK pObj; // params container
	
	try{
		pObj.ID=atoi((String)http["ID"]);
		pObj.ISBACKUPTASK=atoi((String)http["ISBACKUPTASK"]);
		pObj.CREATEDDATE=atoi((String)http["CREATEDDATE"]);	
		pObj.FOLDERPATH=((String)http["FOLDERPATH"]);	
		pObj.STATUS=atoi((String)http["STATUS"]);
	}
	catch(...)
	{
		Cout() << "Error D_BACKUPRESTORETASK::Update";
	}
	
	return Edit(pObj);
}

D_BACKUPRESTORETASK D_BACKUPRESTORETASK::Edit(S_BACKUPRESTORETASK& pObj){
	
	// check any same email registered
	D_BACKUPRESTORETASK tObj = GetById(pObj.ID);
	
	if(tObj.data.ID > 0)
	{
		SQL *  Update( BACKUPRESTORETASK )
				(ISBACKUPTASK,pObj.ISBACKUPTASK)
				(CREATEDDATE,pObj.CREATEDDATE)
					(FOLDERPATH,pObj.FOLDERPATH)
				(STATUS,pObj.STATUS)
				
				.Where( ID == pObj.ID);
		//----------------------------------------
		tObj = GetById(pObj.ID);
		LOG("\n Backup Restore Update:"+tObj.ToString()+"\n");
	}
	else
	{
		LOG("\n Backup Restore did not exist:"+AsString(tObj.data.ID)+"\n");
		tObj = Create(pObj);
	}
	return tObj;
}

void D_BACKUPRESTORETASK::Delete(Http& http){
	// do not delete setting?
}

Vector<D_BACKUPRESTORETASK> D_BACKUPRESTORETASK::Retrieve(Http& http){
		
	S_BACKUPRESTORETASK pObj; 	// params container
	PAGINATION pager(http); 		// extract pager
	
	try{
		pObj.ID=atoi((String)http["ID"]);
	
		pObj.ISBACKUPTASK=atoi((String)http["ISBACKUPTASK"]);
		pObj.CREATEDDATE=atoi((String)http["CREATEDDATE"]);

		pObj.FOLDERPATH=((String)http["FOLDERPATH"]);
		pObj.STATUS=atoi((String)http["STATUS"]);
	}
	catch(...)
	{
		Cout() << "Error get params";
	}
	
	int row =0;
	//------------------------
	SqlBool where;
	
	if(pObj.ID>0) where = ID == pObj.ID;

	if(pObj.ISBACKUPTASK>0) where =where &&  ISBACKUPTASK == pObj.ISBACKUPTASK;
	if(pObj.CREATEDDATE>0) where =where &&  CREATEDDATE == pObj.CREATEDDATE;
	
	if(pObj.FOLDERPATH.IsEmpty()==false) where =where &&  Like(FOLDERPATH, Wild("*"+pObj.FOLDERPATH + "*"));
	
	if(pObj.STATUS>0) where =where &&  STATUS == pObj.STATUS;
	
	//------------------------
	Cout()<<pObj<<"\n";
	
	SQL *  Select ( SqlAll() ).From ( BACKUPRESTORETASK ).Where(where).OrderBy (Descending( ID)).Limit(pager.OFFSET, pager.SIZE);
	
	Vector<D_BACKUPRESTORETASK>  vector;
	S_BACKUPRESTORETASK x;

	while ( SQL.Fetch ( x ) ){
		vector.Add ( D_BACKUPRESTORETASK(x) );
		row++;
		if(row >= pager.SIZE) break;
	}
	//--------------------------------------------------------
	return vector;
}

String D_BACKUPRESTORETASK::RetrieveAsJson(Http& http){
	return StoreAsJson(Retrieve(http),true); 
}

/*
	get user setting by id
*/
D_BACKUPRESTORETASK D_BACKUPRESTORETASK::GetById(int id){
	
	D_BACKUPRESTORETASK  rs;
	S_BACKUPRESTORETASK x;
	
	try{
		SqlBool where;
		where = ID == id;// condition
		
		SQL *  Select ( SqlAll() ).From ( BACKUPRESTORETASK ).Where(where).Limit(1);
	
		while ( SQL.Fetch ( x ) ){
			rs = D_BACKUPRESTORETASK(x);
			break;
		}
	}
	catch(...){
		Cout() << "Error D_BACKUPRESTORETASK::Get(String id)";
	}
	return  rs;
	
}


/*
	get D_BACKUPRESTORETASK by proccessing status
*/
D_BACKUPRESTORETASK D_BACKUPRESTORETASK::GetByStatus(int status){
	
	D_BACKUPRESTORETASK  rs;
	S_BACKUPRESTORETASK x;
	
	try{
		SqlBool where;
		where = STATUS == status;// condition
		
		SQL *  Select ( SqlAll() ).From ( BACKUPRESTORETASK ).Where(where).OrderBy(Descending(ID)).Limit(1);
	
		while ( SQL.Fetch ( x ) ){
			rs = D_BACKUPRESTORETASK(x);
			break;
		}
	}
	catch(...){
		Cout() << "Error D_BACKUPRESTORETASK::Get(String id)";
	}
	return  rs;
	
}

// get total users in system
int D_BACKUPRESTORETASK::GetSummary(){
	
	int  rs;
	S_BACKUPRESTORETASK x;
	
	try{
		SqlBool where;
		where = ISBACKUPTASK == 1;// condition 0 means blocked
		where = where && STATUS >0;
		
		SQL *  Select ( Count(ID) ).From ( BACKUPRESTORETASK ).Where(where);;
		
		while ( SQL.Fetch () ){
			rs = SQL[0];
			break;
		}
		
	}
	catch(...){
		Cout() << "Error D_BACKUPRESTORETASK::GetSummary()";
	}
	return  rs;
	
}