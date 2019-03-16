#include "util.h"
#include "Poco.h"

void D_BACKUPRESTORETASK::Jsonize(JsonIO & json)
{
	json
	("ID",data.ID )
	("USERID",data.USERID)
	("ISBACKUPTASK",data.ISBACKUPTASK)
	("CREATEDDATE",data.CREATEDDATE)
	("FINISHDATE",data.FINISHDATE)
	("SOURCEFOLDERPATH",data.SOURCEFOLDERPATH)
	("TARGETFOLDERPATH",data.TARGETFOLDERPATH)
	("PROCCESED",data.PROCCESED)
	("TOTALFILES",data.TOTALFILES)
//	("STATUS",data.STATUS) // when we have finishdate means it done

	;
}

D_BACKUPRESTORETASK D_BACKUPRESTORETASK::Create(Http& http){
	
	S_BACKUPRESTORETASK pObj; // params container
	
	try{
		//pObj.ID=atoi((String)http["ID"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.ISBACKUPTASK=atoi((String)http["ISBACKUPTASK"]);
		pObj.CREATEDDATE=atoi((String)http["CREATEDDATE"]);
		pObj.FINISHDATE=atoi((String)http["FINISHDATE"]);
		pObj.SOURCEFOLDERPATH=((String)http["SOURCEFOLDERPATH"]);
		pObj.TARGETFOLDERPATH=((String)http["TARGETFOLDERPATH"]);
		pObj.PROCCESED=atoi((String)http["PROCCESED"]);
		pObj.TOTALFILES=atoi((String)http["TOTALFILES"]);
	//	pObj.STATUS=atoi((String)http["STATUS"]);
	}
	catch(...)
	{
		Cout() << "Error D_BACKUPRESTORETASK::Create";
	}
	
	return Create(pObj);
}


D_BACKUPRESTORETASK D_BACKUPRESTORETASK::Create(S_BACKUPRESTORETASK& pObj){
	
	
	// check any 
	D_BACKUPRESTORETASK tObj = GetById(pObj.ID);
	
	if(tObj.data.ID < 0)
	{
		SQL *  Insert( BACKUPRESTORETASK )
				//(ID,pObj.ID)
				(USERID,pObj.USERID)
				(ISBACKUPTASK,pObj.ISBACKUPTASK)
				(CREATEDDATE,pObj.CREATEDDATE)
				(FINISHDATE,pObj.FINISHDATE)
				(SOURCEFOLDERPATH,pObj.SOURCEFOLDERPATH)
				(TARGETFOLDERPATH,pObj.TARGETFOLDERPATH)
				(PROCCESED,pObj.PROCCESED)
				(TOTALFILES,pObj.TOTALFILES)
			//	(STATUS,pObj.STATUS)

				;
		//----------------------------------------
		Cout()<<"\nCreated Transformation Setting:"<<tObj<<"\n"; 
	}
	else
	{
		Cout()<<"\nTransformation Setting existed:"<<tObj.data.ID<<"\n";
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
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.ISBACKUPTASK=atoi((String)http["ISBACKUPTASK"]);
		pObj.CREATEDDATE=atoi((String)http["CREATEDDATE"]);
		pObj.FINISHDATE=atoi((String)http["FINISHDATE"]);
		pObj.SOURCEFOLDERPATH=((String)http["SOURCEFOLDERPATH"]);
		pObj.TARGETFOLDERPATH=((String)http["TARGETFOLDERPATH"]);
		pObj.PROCCESED=atoi((String)http["PROCCESED"]);
		pObj.TOTALFILES=atoi((String)http["TOTALFILES"]);
	//	pObj.STATUS=atoi((String)http["STATUS"]);
	}
	catch(...)
	{
		Cout() << "Error D_BACKUPRESTORETASK::Update";
	}
	// check any same email registered
	D_BACKUPRESTORETASK tObj = GetById(pObj.ID);
	
//	Cout()<<"\npObj"<<pObj<<"\n";
//	Cout()<<"tObj"<<tObj<<"\n";	
//	Cout()<<"Hash Key"<< GetHashValue(pObj.EMAIL)<<"\n";
//	Cout()<<"Data ID Key"<< tObj.data.ID <<"\n";

	if(tObj.data.ID > 0)
	{
		SQL *  Update( BACKUPRESTORETASK )
				
				(USERID,pObj.USERID)
				(ISBACKUPTASK,pObj.ISBACKUPTASK)
				(CREATEDDATE,pObj.CREATEDDATE)
				(FINISHDATE,pObj.FINISHDATE)
				(SOURCEFOLDERPATH,pObj.SOURCEFOLDERPATH)
				(TARGETFOLDERPATH,pObj.TARGETFOLDERPATH)
				(PROCCESED,pObj.PROCCESED)
				(TOTALFILES,pObj.TOTALFILES)
			//	(STATUS,pObj.STATUS)
				
				.Where( ID == pObj.ID);
		//----------------------------------------
		tObj = GetById(pObj.ID);
		Cout()<<"\n Backup Restore Update:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\n Backup Restore did not exist:"<<tObj.data.ID<<"\n";
	}
	return tObj;
}

D_BACKUPRESTORETASK D_BACKUPRESTORETASK::Edit(S_BACKUPRESTORETASK& pObj){
	
	// check any same email registered
	D_BACKUPRESTORETASK tObj = GetById(pObj.ID);
	
	if(tObj.data.ID > 0)
	{
		SQL *  Update( BACKUPRESTORETASK )
				
				(USERID,pObj.USERID)
				(ISBACKUPTASK,pObj.ISBACKUPTASK)
				(CREATEDDATE,pObj.CREATEDDATE)
				(FINISHDATE,pObj.FINISHDATE)
				(SOURCEFOLDERPATH,pObj.SOURCEFOLDERPATH)
				(TARGETFOLDERPATH,pObj.TARGETFOLDERPATH)
				(PROCCESED,pObj.PROCCESED)
				(TOTALFILES,pObj.TOTALFILES)
			//	(STATUS,pObj.STATUS)
				
				.Where( ID == pObj.ID);
		//----------------------------------------
		tObj = GetById(pObj.ID);
		Cout()<<"\n Backup Restore Update:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\n Backup Restore did not exist:"<<tObj.data.ID<<"\n";
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
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.ISBACKUPTASK=atoi((String)http["ISBACKUPTASK"]);
		pObj.CREATEDDATE=atoi((String)http["CREATEDDATE"]);
		pObj.FINISHDATE=atoi((String)http["FINISHDATE"]);
		
		pObj.SOURCEFOLDERPATH=((String)http["SOURCEFOLDERPATH"]);
		pObj.TARGETFOLDERPATH=((String)http["TARGETFOLDERPATH"]);
		
		pObj.PROCCESED=atoi((String)http["PROCCESED"]);
		pObj.TOTALFILES=atoi((String)http["TOTALFILES"]);
	//	pObj.STATUS=atoi((String)http["STATUS"]);
	}
	catch(...)
	{
		Cout() << "Error get params";
	}
	
	int row =0;
	//------------------------
	SqlBool where;
	
	if(pObj.ID>0) where = ID == pObj.ID;
	if(pObj.USERID>0) where =where &&  USERID == pObj.USERID;
	if(pObj.ISBACKUPTASK>0) where =where &&  ISBACKUPTASK == pObj.ISBACKUPTASK;
	if(pObj.CREATEDDATE>0) where =where &&  CREATEDDATE == pObj.CREATEDDATE;
	if(pObj.FINISHDATE>0) where =where &&  FINISHDATE == pObj.FINISHDATE;
	
	if(pObj.SOURCEFOLDERPATH.IsEmpty()==false) where =where &&  Like(SOURCEFOLDERPATH, Wild("*"+pObj.SOURCEFOLDERPATH + "*"));
	if(pObj.TARGETFOLDERPATH.IsEmpty()==false) where =where &&  Like(TARGETFOLDERPATH, Wild("*"+pObj.TARGETFOLDERPATH + "*"));
	
	if(pObj.PROCCESED>0) where =where &&  PROCCESED == pObj.PROCCESED;
	if(pObj.TOTALFILES>0) where =where &&  TOTALFILES == pObj.TOTALFILES;
	//if(pObj.STATUS>0) where =where &&  STATUS == pObj.STATUS;
	
	//------------------------
	Cout()<<pObj<<"\n";
	
	SQL *  Select ( SqlAll() ).From ( BACKUPRESTORETASK ).Where(where).OrderBy ( ID ).Limit(pager.OFFSET, pager.SIZE);
	
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

// get total users in system
int D_BACKUPRESTORETASK::GetSummary(){
	
	int  rs;
	S_BACKUPRESTORETASK x;
	
	try{
		SqlBool where;
		where = ISBACKUPTASK == 1;// condition 0 means blocked
		where = where && FINISHDATE >0;
		
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