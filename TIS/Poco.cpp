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
		pObj.EMAIL.Trim(0);
		pObj.PASSWORD =(String)http["PASSWORD"];
		pObj.APIKEY= GetApikey(pObj.EMAIL);    // gen the api key
		pObj.FULLNAME =(String)http["FULLNAME"];
		pObj.PHONE =(String)http["PHONE"];
		pObj.DATEOFBIRTH=(String)http["DATEOFBIRTH"];
		pObj.STATUS=atoi((String)http["STATUS"]);
	//	pObj.ISADMIN= atoi((String)http["ISADMIN"]);
	}
	catch(...)
	{
		Cout() << "error get params";
	}
	// check any same email registered
	D_USERINFO tObj = GetByApiKey(pObj.APIKEY);
	
	Cout()<<"\npObj"<<pObj<<"\n";
	Cout()<<"tObj"<<tObj<<"\n";
	
	if(tObj.data.ID >0)
	{
		SQL *  Insert( USERINFO )(EMAIL,PASSWORD, APIKEY,FULLNAME,PHONE, DATEOFBIRTH, STATUS, ISADMIN)(pObj.EMAIL,pObj.PASSWORD, pObj.APIKEY,pObj.FULLNAME,pObj.PHONE, pObj.DATEOFBIRTH, pObj.STATUS, 0);
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
void D_USERINFO::Update(Http& http){
	
}
void D_USERINFO::Delete(Http& http){
	
}
Vector<D_USERINFO> D_USERINFO::Retrieve(Http& http){
	
	int page = 1;
	int size = 20;
	
	S_USERINFO pObj; // params container
	
	try{
		
		String sSize = (String)http["SIZE"];
		String sPage = (String)http["PAGE"];
		
		page = sPage.IsEmpty()?0:atoi(sPage);
		size = sSize.IsEmpty()?20:atoi(sSize);
		
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
	
	int offset = page * size;
	int row =0;
	//-------------
	SqlBool where;
	if(pObj.ID>0) where = ID == pObj.ID;
	if(pObj.EMAIL.IsEmpty()==false) where =where &&  EMAIL == pObj.EMAIL;
	if(pObj.FULLNAME.IsEmpty()==false) where =where &&  Like(FULLNAME, Wild("*"+pObj.FULLNAME + "*"));
	if(pObj.APIKEY>0) where =where &&  APIKEY == pObj.APIKEY;
//	if(pObj.ISADMIN>=0) where =where && ISADMIN == pObj.ISADMIN;

	Cout()<<pObj<<"\n";
	
	SQL *  Select ( SqlAll() ).From ( USERINFO ).Where(where).OrderBy ( ID, FULLNAME ).Limit(offset, size);
	
	Vector<D_USERINFO>  vector;
	S_USERINFO x;

	while ( SQL.Fetch ( x ) ){
		vector.Add ( D_USERINFO(x) );
		row++;
		if(row >= size) break;
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
	email.Trim(0);
	int apikey = GetApikey(email);
	return GetByApiKey(apikey);
}

D_USERINFO D_USERINFO::GetById(int id){
	
	D_USERINFO  rs;
	S_USERINFO x;
	
	try{
		SqlBool where;
		where = ID == id;// condition
		
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

//-----------------------------------------------------------------
void D_USERSETTING::Jsonize(JsonIO & json)
{
	json
	("ID",data.ID )
	("USERID",data.USERID)
	("MAXFILESIZE",data.MAXFILESIZE)
	("FILEEXTENSION",data.FILEEXTENSION)

	;
}

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
