#include"poco.h"



// how to map object to json strings
void DataPacket::Jsonize(JsonIO & json)
{
	json
	("Status",Status)
	("IsError",IsError)
	("Data", Data)
	;
}



void D_USERINFO::Jsonize(JsonIO & json)
{
	json
	("ID",data.ID)
	("EMAIL",data.EMAIL)
	("PASSWORD",data.PASSWORD) // debug onlly password shouldnt show when return data
	("APIKEY",data.APIKEY)
	("FULLNAME",data.FULLNAME )
	("PHONE",data.PHONE )
	("DATEOFBIRTH",data.DATEOFBIRTH)
	("STATUS",data.STATUS)
	("ISADMIN",data.ISADMIN)
	;
}

D_USERINFO D_USERINFO::Create(Http& http){
	
	S_USERINFO pObj; // params container
	
	try{
	//	pObj.ID =atoi((String)http["ID"]);
		pObj.EMAIL =((String)http["EMAIL"]);
		pObj.PASSWORD =(String)http["PASSWORD"];
			pObj.PASSWORD = AsString(GetHashValue(pObj.PASSWORD));
		pObj.APIKEY= GetHashValue(pObj.EMAIL);    // gen the api key
		pObj.FULLNAME =(String)http["FULLNAME"];
		pObj.PHONE =(String)http["PHONE"];
		pObj.DATEOFBIRTH=(String)http["DATEOFBIRTH"];
		pObj.STATUS=atoi((String)http["STATUS"]);
	//	pObj.ISADMIN= atoi((String)http["ISADMIN"]);
	}
	catch(...)
	{
		Cout() << "Error D_USERINFO::Create";
	}
	// check any same email registered
	D_USERINFO tObj = GetByApiKey(pObj.APIKEY);
	
//	Cout()<<"\npObj"<<pObj<<"\n";
//	Cout()<<"tObj"<<tObj<<"\n";	
//	Cout()<<"Hash Key"<< GetHashValue(pObj.EMAIL)<<"\n";
//	Cout()<<"Data ID Key"<< tObj.data.ID <<"\n";


	
	if(tObj.data.ID < 0)
	{
		SQL *  Insert( USERINFO )
				//(ID,pObj.ID)
				(EMAIL,pObj.EMAIL)
				(PASSWORD,pObj.PASSWORD)
				(APIKEY,pObj.APIKEY)
				(FULLNAME,pObj.FULLNAME)
				(PHONE,pObj.PHONE)
				(DATEOFBIRTH,pObj.DATEOFBIRTH)
				(STATUS,pObj.STATUS)
				(ISADMIN,0);
		//----------------------------------------
		tObj = GetByApiKey(pObj.APIKEY);
		Cout()<<"\nCreated User:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\nUser existed:"<<tObj.data.EMAIL<<"\n";
	}
	return tObj;
}

/*
	update user information based on ID
	ex:
		http://127.0.0.1:8001/tis/api/user/update?ID=3&EMAIL=user23@simaget.com&PASSWORD=12345&FULLNAME=user2%20simaget&PHONE=987654321&DATEOFBIRTH=2000/03/01
*/
D_USERINFO D_USERINFO::Edit(Http& http){
	S_USERINFO pObj; // params container
	
	try{
		pObj.ID =atoi((String)http["ID"]);    // most important
		pObj.EMAIL =((String)http["EMAIL"]);
		pObj.PASSWORD =(String)http["PASSWORD"];	
			pObj.PASSWORD =AsString(GetHashValue(pObj.PASSWORD));
		pObj.APIKEY= GetHashValue(pObj.EMAIL);    // gen the api key
		pObj.FULLNAME =(String)http["FULLNAME"];
		pObj.PHONE =(String)http["PHONE"];
		pObj.DATEOFBIRTH=(String)http["DATEOFBIRTH"];
		pObj.STATUS=atoi((String)http["STATUS"]);
	//	pObj.ISADMIN= atoi((String)http["ISADMIN"])>0?1:0; // dont allow  privillege admin right
	}
	catch(...)
	{
		Cout() << "Error D_USERINFO::Update";
	}
	// check any same email registered
	D_USERINFO tObj = GetById(pObj.ID);
	
	Cout()<<"\npObj"<<pObj<<"\n";
	Cout()<<"tObj"<<tObj<<"\n";	
	Cout()<<"Hash Key"<< GetHashValue(pObj.EMAIL)<<"\n";
	Cout()<<"Data ID Key"<< tObj.data.ID <<"\n";

	
	if(tObj.data.ID > 0)
	{
		SQL *  Update( USERINFO )
				//(ID,pObj.ID)
				(EMAIL,pObj.EMAIL)
				(PASSWORD,pObj.PASSWORD)
				(APIKEY,pObj.APIKEY)
				(FULLNAME,pObj.FULLNAME)
				(PHONE,pObj.PHONE)
				(DATEOFBIRTH,pObj.DATEOFBIRTH)
				(STATUS,pObj.STATUS)
			//	(ISADMIN,pObj.ISADMIN) // dont update this 
				.Where( ID == pObj.ID);
		//----------------------------------------
		tObj = GetByApiKey(pObj.APIKEY);
		Cout()<<"\nUpdated User:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\nUser did not exist:"<<tObj.data.EMAIL<<"\n";
	}
	return tObj;
}
void D_USERINFO::Delete(Http& http){
	
}
Vector<D_USERINFO> D_USERINFO::Retrieve(Http& http){
	
	int page = 1;
	int size = 20;
	
	S_USERINFO pObj; // params container
	PAGINATION pager(http);
	try{
		pObj.ID =atoi((String)http["ID"]);
		pObj.EMAIL =(String)http["EMAIL"];
	//	pObj.PASSWORD =(String)http["PASSWORD"];
		pObj.APIKEY=atoi((String)http["APIKEY"]);
		pObj.FULLNAME =(String)http["FULLNAME"];
		pObj.PHONE =(String)http["PHONE"];
	//	pObj.DATEOFBIRTH=(String)http["DATEOFBIRTH"];
	//	pObj.STATUS=(String)http["STATUS"];
	//	pObj.ISADMIN= atoi((String)http["ISADMIN"]);
 
	}
	catch(...)
	{
		Cout() << "error get params";
	}
	int row =0;
	//-------------
	SqlBool where;
	if(pObj.ID>0) where = ID == pObj.ID;
	if(pObj.EMAIL.IsEmpty()==false) where =where &&  EMAIL == pObj.EMAIL;
	if(pObj.FULLNAME.IsEmpty()==false) where =where &&  Like(FULLNAME, Wild("*"+pObj.FULLNAME + "*"));
	if(pObj.APIKEY>0) where =where &&  APIKEY == pObj.APIKEY;
//	if(pObj.ISADMIN>=0) where =where && ISADMIN == pObj.ISADMIN;

	Cout()<<pObj<<"\n";
	
	SQL *  Select ( SqlAll() ).From ( USERINFO ).Where(where).OrderBy ( ID, FULLNAME ).Limit(pager.OFFSET, pager.SIZE);
	
	Vector<D_USERINFO>  vector;
	S_USERINFO x;

	while ( SQL.Fetch ( x ) ){
		vector.Add ( D_USERINFO(x) );
		row++;
		if(row >= pager.SIZE) break;
	}
	//--------------------------------------------------------
	return vector;
	

}

String D_USERINFO::RetrieveAsJson(Http& http){
	return StoreAsJson(Retrieve(http),true); 
}

D_USERINFO D_USERINFO::Login(Http& http){
	Vector<D_USERINFO>  vector;
	vector = Retrieve(http);
	int count = vector.GetCount();
	D_USERINFO rs;
	
	if(count>0)
	{
		rs = vector[0];
	}
	return rs;
}

D_USERINFO D_USERINFO::GetByApiKey(int apikey){
	D_USERINFO  rs;
	S_USERINFO x;
	try{
		SqlBool where;
		where = APIKEY == apikey;// condition
		
		SQL *  Select ( SqlAll() ).From ( USERINFO ).Where(where).OrderBy ( ID, FULLNAME );
		
		
		while ( SQL.Fetch ( x ) ){
			rs = D_USERINFO(x);
			break;
		}
		
	}
	catch(...){
		Cout() << "Error D_USERINFO::Get(String apikey)";
	}
	return  rs;
	
}

D_USERINFO D_USERINFO::GetByEmail(String email){
	
	int apikey = GetHashValue(email);
	return GetByApiKey(apikey);
}

D_USERINFO D_USERINFO::GetById(int id){
	
	D_USERINFO  rs;
	S_USERINFO x;
	
	try{
		SqlBool where;
		where = ID == id;// condition
		
		SQL *  Select ( SqlAll() ).From ( USERINFO ).Where(where);
	
		
		while ( SQL.Fetch ( x ) ){
			rs = D_USERINFO(x);
			break;
		}
		
	}
	catch(...){
		Cout() << "Error D_USERINFO::Get(String apikey)";
	}
	return  rs;
	
}

//-----------------------------------------------------------------


void D_IMAGEFILE::Jsonize(JsonIO & json)
{
	json
	("ID",data.ID )
	("USERID",data.USERID)
	("FILENAME",data.FILENAME)
	("MODIFIEDDATE",data.MODIFIEDDATE)
	("FILETYPE",data.FILETYPE)
	("FILESIZE",data.FILESIZE)
	("REALFILEPATH",data.REALFILEPATH)
	("WIDTH",data.WIDTH)
	("HEIGHT",data.HEIGHT)
	("TAG",data.TAG)
	("DESCRIPTION",data.DESCRIPTION)

	;
}

void D_DAILYSUMMARY::Jsonize(JsonIO & json)
{
	json
	("ID",data.ID )
	("USERID",data.USERID)
	("LOGDATE",data.LOGDATE)
	("NOOFUPLOADFILE",data.NOOFUPLOADFILE)
	("NOOFDOWNLOADFILE",data.NOOFDOWNLOADFILE)
	("TOTALUPLOADSIZE",data.TOTALUPLOADSIZE)
	("TOTALDOWNLOADSIZE",data.TOTALDOWNLOADSIZE)

	;
}

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
	("STATUS",data.STATUS)

	;
}

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

void D_TRANSFORMATIONTASK::Jsonize(JsonIO & json)
{
	json
	("ID ",data.ID )
	("TRANSFORMATIONSETTINGID",data.TRANSFORMATIONSETTINGID)
	("CREATEDDATE",data.CREATEDDATE)
	("FINISHDATE",data.FINISHDATE)
	("FULLSOURCEFILEPATH",data.FULLSOURCEFILEPATH)
	("FULLTARGETFILDEPATH",data.FULLTARGETFILDEPATH)
	("STATUS",data.STATUS)
	;
}
