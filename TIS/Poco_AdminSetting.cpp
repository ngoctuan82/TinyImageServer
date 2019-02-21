#include "util.h"
#include"poco.h"

void D_ADMINSETTING::Jsonize(JsonIO & json)
{
	
	json
	("ID",data.ID )
	("ROOTPATH",data.ROOTPATH)
	("STATICPATH",data.STATICPATH)
	("IMAGEPATH",data.IMAGEPATH)
	("BACKUPPATH",data.BACKUPPATH)
	("SERVERPORT",data.SERVERPORT)
	("HOSTNAME",data.HOSTNAME)

	;
}


D_ADMINSETTING D_ADMINSETTING::Create(Http& http){
	
	S_ADMINSETTING pObj; // params container
	
	try{
	//	pObj.ID =atoi((String)http["ID"]);
		pObj.ROOTPATH=((String)http["ROOTPATH"]);
		pObj.STATICPATH=((String)http["STATICPATH"]);
		pObj.IMAGEPATH=((String)http["IMAGEPATH"]);
		pObj.BACKUPPATH=((String)http["BACKUPPATH"]);
		pObj.SERVERPORT=((String)http["SERVERPORT"]);
		pObj.HOSTNAME=((String)http["HOSTNAME"]);
	}
	catch(...)
	{
		Cout() << "Error D_ADMINSETTING::Create";
	}
	D_ADMINSETTING tObj = GetById(pObj.ID);
	//	Cout()<<"\npObj"<<pObj<<"\n";
	//	Cout()<<"tObj"<<tObj<<"\n";	
	//	Cout()<<"Hash Key"<< GetHashValue(pObj.EMAIL)<<"\n";
	//	Cout()<<"Data ID Key"<< tObj.data.ID <<"\n";

	if(tObj.data.ID < 0)
	{
		SQL *  Insert( ADMINSETTING )
				//(ID,pObj.ID)
				(ROOTPATH,pObj.ROOTPATH)
				(STATICPATH,pObj.STATICPATH)
				(IMAGEPATH,pObj.IMAGEPATH)
				(BACKUPPATH,pObj.BACKUPPATH)
				(SERVERPORT,pObj.SERVERPORT)
				(HOSTNAME,pObj.HOSTNAME)
				;
		//----------------------------------------
		Cout()<<"\nCreated ADMINSETTING:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\nUser Setting existed:"<<tObj.data.HOSTNAME<<"\n";
	}
	return tObj;
}

/*
	update user information based on ID
	ex:
		http://127.0.0.1:8001/tis/api/user/update?ID=3&EMAIL=user23@simaget.com&PASSWORD=12345&FULLNAME=user2%20simaget&PHONE=987654321&DATEOFBIRTH=2000/03/01
*/
D_ADMINSETTING D_ADMINSETTING::Edit(Http& http){
	S_ADMINSETTING pObj; // params container
	
	try{
		pObj.ID =atoi((String)http["ID"]);
		pObj.ROOTPATH=((String)http["ROOTPATH"]);
		pObj.STATICPATH=((String)http["STATICPATH"]);
		pObj.IMAGEPATH=((String)http["IMAGEPATH"]);
		pObj.BACKUPPATH=((String)http["BACKUPPATH"]);
		pObj.SERVERPORT=((String)http["SERVERPORT"]);
		pObj.HOSTNAME=((String)http["HOSTNAME"]);
	}
	catch(...)
	{
		Cout() << "Error D_ADMINSETTING::Update";
	}
	// check any same email registered
	D_ADMINSETTING tObj = GetById(pObj.ID);
	/*
		Cout()<<"\npObj"<<pObj<<"\n";
		Cout()<<"tObj"<<tObj<<"\n";	
		Cout()<<"Hash Key"<< GetHashValue(pObj.EMAIL)<<"\n";
		Cout()<<"Data ID Key"<< tObj.data.ID <<"\n";
	*/
	if(tObj.data.ID > 0)
	{
		SQL *  Update( ADMINSETTING )
				(ROOTPATH,pObj.ROOTPATH)
				(STATICPATH,pObj.STATICPATH)
				(IMAGEPATH,pObj.IMAGEPATH)
				(BACKUPPATH,pObj.BACKUPPATH)
				(SERVERPORT,pObj.SERVERPORT)
				(HOSTNAME,pObj.HOSTNAME)
				.Where( ID == pObj.ID);
		//----------------------------------------
		tObj = GetById(pObj.ID);
		Cout()<<"\nUpdated Admin Setting:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\nAdmin Setting did not exist:"<<tObj.data.ID<<"\n";
	}
	return tObj;
}

void D_ADMINSETTING::Delete(Http& http){
	// do not delete setting?
}

/*
*/
Vector<D_ADMINSETTING> D_ADMINSETTING::Retrieve(Http& http){
			
	S_ADMINSETTING pObj; // params container
	PAGINATION pager(http); // extract pager
	
	try{		
		pObj.ID =atoi((String)http["ID"]);
		pObj.ROOTPATH=((String)http["ROOTPATH"]);
		pObj.STATICPATH=((String)http["STATICPATH"]);
		pObj.IMAGEPATH=((String)http["IMAGEPATH"]);
		pObj.BACKUPPATH=((String)http["BACKUPPATH"]);
		pObj.SERVERPORT=((String)http["SERVERPORT"]);
		pObj.HOSTNAME=((String)http["HOSTNAME"]);
	}
	catch(...)
	{
		Cout() << "Error get params";
	}
	
	int row =0;
	//------------------------
	SqlBool where;
	
	if(pObj.ID>0) where = ID == pObj.ID;
	
	if(pObj.ROOTPATH.IsEmpty()==false) where = where &&  ROOTPATH == pObj.ROOTPATH;
	if(pObj.STATICPATH.IsEmpty()==false) where = where &&  STATICPATH == pObj.STATICPATH;
	if(pObj.IMAGEPATH.IsEmpty()==false) where = where &&  IMAGEPATH == pObj.IMAGEPATH;
	if(pObj.BACKUPPATH.IsEmpty()==false) where = where &&  BACKUPPATH == pObj.BACKUPPATH;
	if(pObj.SERVERPORT.IsEmpty()==false) where = where &&  SERVERPORT == pObj.SERVERPORT;
	if(pObj.HOSTNAME.IsEmpty()==false) where = where &&  HOSTNAME == pObj.HOSTNAME;
	
	//------------------------
	Cout()<<"\n"<<pObj<<"\n";
	
	SQL *  Select ( SqlAll() ).From ( ADMINSETTING ).Where(where).OrderBy ( ID ).Limit(pager.OFFSET, pager.SIZE);
	
	Vector<D_ADMINSETTING>  vector;
	S_ADMINSETTING x;

	while ( SQL.Fetch ( x ) ){
		vector.Add ( D_ADMINSETTING(x) );
		row++;
		if(row >= pager.SIZE) break;
	}
	//--------------------------------------------------------
	return vector;
}

String D_ADMINSETTING::RetrieveAsJson(Http& http){
	return StoreAsJson(Retrieve(http),true); 
}

/*
	Get Admin Setting by ID
*/
D_ADMINSETTING D_ADMINSETTING::GetById(int id){
	
	D_ADMINSETTING rs;
	S_ADMINSETTING x;
	
	try{
		SqlBool where;
		where = ID == id;// condition
		
		SQL *  Select ( SqlAll() ).From ( ADMINSETTING ).Where(where).Limit(1);;
	
		while ( SQL.Fetch ( x ) ){
			rs = D_ADMINSETTING(x);
			break;
		}
	}
	catch(...){
		Cout() << "Error D_ADMINSETTING::Get(String id)";
	}
	return  rs;
	
}