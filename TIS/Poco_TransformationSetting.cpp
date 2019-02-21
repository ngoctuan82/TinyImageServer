#include "util.h"
#include "Poco.h"

void D_TRANSFORMATIONSETTING::Jsonize(JsonIO & json)
{
	json
	("ID",data.ID )
	("USERID",data.USERID)
	("TRANSFORMTYPE",data.TRANSFORMTYPE)
	("DELETEDORIGINALFILE",data.DELETEDORIGINALFILE)
	("PROCCESSORDER",data.PROCCESSORDER)

	;
}

D_TRANSFORMATIONSETTING D_TRANSFORMATIONSETTING::Create(Http& http){
	
	S_TRANSFORMATIONSETTING pObj; // params container
	
	try{
		//pObj.ID=atoi((String)http["ID"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.TRANSFORMTYPE=atoi((String)http["TRANSFORMTYPE"]);
		pObj.DELETEDORIGINALFILE=atoi((String)http["DELETEDORIGINALFILE"]);
		pObj.PROCCESSORDER=atoi((String)http["PROCCESSORDER"]);
	}
	catch(...)
	{
		Cout() << "Error D_TRANSFORMATIONSETTING::Create";
	}
	// check any same email registered
	D_TRANSFORMATIONSETTING tObj = GetById(pObj.ID);
	
	//	Cout()<<"\npObj"<<pObj<<"\n";
	//	Cout()<<"tObj"<<tObj<<"\n";	
	//	Cout()<<"Hash Key"<< GetHashValue(pObj.EMAIL)<<"\n";
	//	Cout()<<"Data ID Key"<< tObj.data.ID <<"\n";

	if(tObj.data.ID < 0)
	{
		SQL *  Insert( TRANSFORMATIONSETTING )
				//(ID,pObj.ID)
				(USERID,pObj.USERID)
				(TRANSFORMTYPE,pObj.TRANSFORMTYPE)
				(DELETEDORIGINALFILE,pObj.DELETEDORIGINALFILE)
				(PROCCESSORDER,pObj.PROCCESSORDER)
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
D_TRANSFORMATIONSETTING D_TRANSFORMATIONSETTING::Edit(Http& http){
	S_TRANSFORMATIONSETTING pObj; // params container
	
	try{
	pObj.ID=atoi((String)http["ID"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.TRANSFORMTYPE=atoi((String)http["TRANSFORMTYPE"]);
		pObj.DELETEDORIGINALFILE=atoi((String)http["DELETEDORIGINALFILE"]);
		pObj.PROCCESSORDER=atoi((String)http["PROCCESSORDER"]);
	}
	catch(...)
	{
		Cout() << "Error D_TRANSFORMATIONSETTING::Update";
	}
	// check any same email registered
	D_TRANSFORMATIONSETTING tObj = GetById(pObj.ID);
	
//	Cout()<<"\npObj"<<pObj<<"\n";
//	Cout()<<"tObj"<<tObj<<"\n";	
//	Cout()<<"Hash Key"<< GetHashValue(pObj.EMAIL)<<"\n";
//	Cout()<<"Data ID Key"<< tObj.data.ID <<"\n";

	if(tObj.data.ID > 0)
	{
		SQL *  Update( TRANSFORMATIONSETTING )
				(USERID,pObj.USERID)
				(TRANSFORMTYPE,pObj.TRANSFORMTYPE)
				(DELETEDORIGINALFILE,pObj.DELETEDORIGINALFILE)
				(PROCCESSORDER,pObj.PROCCESSORDER)
				.Where( ID == pObj.ID);
		//----------------------------------------
		tObj = GetById(pObj.ID);
		Cout()<<"\n Daily Summary Update:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\n Daily Summary did not exist:"<<tObj.data.ID<<"\n";
	}
	return tObj;
}

void D_TRANSFORMATIONSETTING::Delete(Http& http){
	// do not delete setting?
}

Vector<D_TRANSFORMATIONSETTING> D_TRANSFORMATIONSETTING::Retrieve(Http& http){
		
	S_TRANSFORMATIONSETTING pObj; 	// params container
	PAGINATION pager(http); 		// extract pager
	
	try{
		pObj.ID=atoi((String)http["ID"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.TRANSFORMTYPE=atoi((String)http["TRANSFORMTYPE"]);
		pObj.DELETEDORIGINALFILE=atoi((String)http["DELETEDORIGINALFILE"]);
		pObj.PROCCESSORDER=atoi((String)http["PROCCESSORDER"]);
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
	if(pObj.TRANSFORMTYPE>0) where =where &&  TRANSFORMTYPE == pObj.TRANSFORMTYPE;
	if(pObj.DELETEDORIGINALFILE>0) where =where &&  DELETEDORIGINALFILE == pObj.DELETEDORIGINALFILE;
	if(pObj.PROCCESSORDER>0) where =where &&  PROCCESSORDER == pObj.PROCCESSORDER;
	
	//------------------------
	Cout()<<pObj<<"\n";
	
	SQL *  Select ( SqlAll() ).From ( TRANSFORMATIONSETTING ).Where(where).OrderBy ( ID ).Limit(pager.OFFSET, pager.SIZE);
	
	Vector<D_TRANSFORMATIONSETTING>  vector;
	S_TRANSFORMATIONSETTING x;

	while ( SQL.Fetch ( x ) ){
		vector.Add ( D_TRANSFORMATIONSETTING(x) );
		row++;
		if(row >= pager.SIZE) break;
	}
	//--------------------------------------------------------
	return vector;
}

String D_TRANSFORMATIONSETTING::RetrieveAsJson(Http& http){
	return StoreAsJson(Retrieve(http),true); 
}

/*
	get user setting by id
*/
D_TRANSFORMATIONSETTING D_TRANSFORMATIONSETTING::GetById(int id){
	
	D_TRANSFORMATIONSETTING  rs;
	S_TRANSFORMATIONSETTING x;
	
	try{
		SqlBool where;
		where = ID == id;// condition
		
		SQL *  Select ( SqlAll() ).From ( TRANSFORMATIONSETTING ).Where(where).Limit(1);
	
		while ( SQL.Fetch ( x ) ){
			rs = D_TRANSFORMATIONSETTING(x);
			break;
		}
	}
	catch(...){
		Cout() << "Error D_TRANSFORMATIONSETTING::Get(String id)";
	}
	return  rs;
	
}