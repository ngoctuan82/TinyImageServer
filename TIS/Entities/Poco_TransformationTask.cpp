#include "util.h"
#include "Poco.h"

#include "util.h"
#include "Poco.h"

void D_TRANSFORMATIONTASK::Jsonize(JsonIO & json)
{
	json
	("ID",data.ID )
	("TRANSFORMATIONSETTINGID",data.TRANSFORMATIONSETTINGID)
	("MODIFIEDDATE",data.MODIFIEDDATE)
	("FULLSOURCEFILEPATH",data.FULLSOURCEFILEPATH)
	("FULLTARGETFILDEPATH",data.FULLTARGETFILDEPATH)
	("STATUS",data.STATUS)

	;
}


D_TRANSFORMATIONTASK D_TRANSFORMATIONTASK::Create(Http& http){
	
	S_TRANSFORMATIONTASK pObj; // params container
	
	try{
		//pObj.ID=atoi((String)http["ID"]);
		pObj.TRANSFORMATIONSETTINGID=atoi((String)http["TRANSFORMATIONSETTINGID"]);
		pObj.MODIFIEDDATE=Time().Get();
		pObj.FULLSOURCEFILEPATH=((String)http["FULLSOURCEFILEPATH"]);
		pObj.FULLTARGETFILDEPATH=((String)http["FULLTARGETFILDEPATH"]);
		pObj.STATUS=atoi((String)http["STATUS"]);
	}
	catch(...)
	{
		Cout() << "Error D_TRANSFORMATIONTASK::Create";
	}

	return Create(pObj);
}


D_TRANSFORMATIONTASK D_TRANSFORMATIONTASK::Create(S_TRANSFORMATIONTASK& pObj){
	
	
	D_TRANSFORMATIONTASK tObj = GetById(pObj.ID);
	
	if(tObj.data.ID < 0)
	{
		SQL *  Insert( TRANSFORMATIONTASK )
				//(ID,pObj.ID)
				(TRANSFORMATIONSETTINGID,pObj.TRANSFORMATIONSETTINGID)
				(MODIFIEDDATE,pObj.MODIFIEDDATE)
				(FULLSOURCEFILEPATH,pObj.FULLSOURCEFILEPATH)
				(FULLTARGETFILDEPATH,pObj.FULLTARGETFILDEPATH)
				(STATUS,pObj.STATUS)
				;
		//----------------------------------------
		Cout()<<"\nCreated Transformation Task:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\nTransformation Task existed:"<<tObj.data.ID<<"\n";
	}
	return tObj;
}

/*
	update user information based on ID
	ex:
		http://127.0.0.1:8001/tis/api/user/update?ID=3&EMAIL=user23@simaget.com&PASSWORD=12345&FULLNAME=user2%20simaget&PHONE=987654321&DATEOFBIRTH=2000/03/01
*/
D_TRANSFORMATIONTASK D_TRANSFORMATIONTASK::Edit(Http& http){
	S_TRANSFORMATIONTASK pObj; // params container
	
	try{
		pObj.ID=atoi((String)http["ID"]);
		pObj.TRANSFORMATIONSETTINGID=atoi((String)http["TRANSFORMATIONSETTINGID"]);
		pObj.MODIFIEDDATE=Time().Get();
		pObj.FULLSOURCEFILEPATH=((String)http["FULLSOURCEFILEPATH"]);
		pObj.FULLTARGETFILDEPATH=((String)http["FULLTARGETFILDEPATH"]);
		pObj.STATUS=atoi((String)http["STATUS"]);
	}
	catch(...)
	{
		Cout() << "Error D_TRANSFORMATIONTASK::Update";
	}
	
	return Edit(pObj);
}

D_TRANSFORMATIONTASK D_TRANSFORMATIONTASK::Edit(S_TRANSFORMATIONTASK& pObj){
	
	D_TRANSFORMATIONTASK tObj = GetById(pObj.ID);

	if(tObj.data.ID > 0)
	{
		SQL *  Update( TRANSFORMATIONTASK )
				(TRANSFORMATIONSETTINGID,pObj.TRANSFORMATIONSETTINGID)
				(MODIFIEDDATE,pObj.MODIFIEDDATE)
				(FULLSOURCEFILEPATH,pObj.FULLSOURCEFILEPATH)
				(FULLTARGETFILDEPATH,pObj.FULLTARGETFILDEPATH)
				(STATUS,pObj.STATUS)
				.Where( ID == pObj.ID);
		//----------------------------------------
		tObj = GetById(pObj.ID);
		Cout()<<"\n Daily Summary Update:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\n Daily Summary did not exist:"<<tObj.data.ID<<"\n";
		tObj = Create(pObj);
	}
	return tObj;
}

void D_TRANSFORMATIONTASK::Delete(Http& http){
	// do not delete setting?
}

Vector<D_TRANSFORMATIONTASK> D_TRANSFORMATIONTASK::Retrieve(Http& http){
		
	S_TRANSFORMATIONTASK pObj; 	// params container
	PAGINATION pager(http); 		// extract pager
	
	try{
		pObj.ID=atoi((String)http["ID"]);
		pObj.TRANSFORMATIONSETTINGID=atoi((String)http["TRANSFORMATIONSETTINGID"]);
		pObj.MODIFIEDDATE=atoi((String)http["MODIFIEDDATE"]);
		pObj.FULLSOURCEFILEPATH=((String)http["FULLSOURCEFILEPATH"]);
		pObj.FULLTARGETFILDEPATH=((String)http["FULLTARGETFILDEPATH"]);
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
	if(pObj.TRANSFORMATIONSETTINGID>0) where =where &&  TRANSFORMATIONSETTINGID == pObj.TRANSFORMATIONSETTINGID;
	if(pObj.STATUS>0) where =where &&  STATUS == pObj.STATUS;
		
	//------------------------
	Cout()<<pObj<<"\n";
	
	SQL *  Select ( SqlAll() ).From ( TRANSFORMATIONTASK ).Where(where).OrderBy ( ID ).Limit(pager.OFFSET, pager.SIZE);
	
	Vector<D_TRANSFORMATIONTASK>  vector;
	S_TRANSFORMATIONTASK x;

	while ( SQL.Fetch ( x ) ){
		vector.Add ( D_TRANSFORMATIONTASK(x) );
		row++;
		if(row >= pager.SIZE) break;
	}
	//--------------------------------------------------------
	return vector;
}

String D_TRANSFORMATIONTASK::RetrieveAsJson(Http& http){
	return StoreAsJson(Retrieve(http),true); 
}

/*
	get user setting by id
*/
D_TRANSFORMATIONTASK D_TRANSFORMATIONTASK::GetById(int id){
	
	D_TRANSFORMATIONTASK  rs;
	S_TRANSFORMATIONTASK x;
	
	try{
		SqlBool where;
		where = ID == id;// condition
		
		SQL *  Select ( SqlAll() ).From ( TRANSFORMATIONTASK ).Where(where).Limit(1);
	
		while ( SQL.Fetch ( x ) ){
			rs = D_TRANSFORMATIONTASK(x);
			break;
		}
	}
	catch(...){
		Cout() << "Error D_TRANSFORMATIONTASK::Get(String id)";
	}
	return  rs;
	
}