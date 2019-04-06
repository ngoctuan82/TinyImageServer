#include "util.h"
#include "Poco.h"

void D_USERSETTING::Jsonize(JsonIO & json)
{
	json
	("ID",data.ID )
	("USERID",data.USERID)
	("MAXFILESIZE",data.MAXFILESIZE)
	("FILEEXTENSION",data.FILEEXTENSION)
	;
}


D_USERSETTING D_USERSETTING::Create(Http& http){
	
	S_USERSETTING pObj; // params container
	
	try{
	//	pObj.ID =atoi((String)http["ID"]);
		pObj.MAXFILESIZE=atoi((String)http["MAXFILESIZE"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.FILEEXTENSION= (String)http["FILEEXTENSION"];
	}
	catch(...)
	{
		Cout() << "Error D_USERSETTING::Create";
	}

	return Create(pObj);
}


D_USERSETTING D_USERSETTING::Create(S_USERSETTING& pObj){
	
	
	// check any same email registered
	D_USERSETTING tObj = GetByUserId(pObj.USERID);
	
	if(tObj.data.ID < 0)
	{
		SQL *  Insert( USERSETTING )
				//(ID,pObj.ID)
				(USERID,pObj.USERID)
				(MAXFILESIZE,pObj.MAXFILESIZE)
				(FILEEXTENSION,pObj.FILEEXTENSION)
				;
		int id= SQL.GetInsertedId();
		tObj = tObj.GetById(id);
		//----------------------------------------
		Cout()<<"\nCreated D_USERSETTING:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\nUser Setting existed:"<<tObj.data.USERID<<"\n";
	}
	return tObj;
}

/*
	update user information based on ID
	ex:
		http://127.0.0.1:8001/tis/api/user/update?ID=3&EMAIL=user23@simaget.com&PASSWORD=12345&FULLNAME=user2%20simaget&PHONE=987654321&DATEOFBIRTH=2000/03/01
*/
D_USERSETTING D_USERSETTING::Edit(Http& http){
	S_USERSETTING pObj; // params container
	
	try{
		pObj.ID =atoi((String)http["ID"]);
		pObj.MAXFILESIZE=atoi((String)http["MAXFILESIZE"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.FILEEXTENSION= (String)http["FILEEXTENSION"];
	}
	catch(...)
	{
		Cout() << "Error D_USERSETTING::Update";
	}
	return Edit(pObj);
}

D_USERSETTING D_USERSETTING::Edit(S_USERSETTING& pObj){
	
	// check any same email registered
	D_USERSETTING tObj = GetById(pObj.ID);

	if(tObj.data.ID > 0)
	{
		SQL *  Update( USERSETTING )
				(USERID,pObj.USERID)
				(MAXFILESIZE,pObj.MAXFILESIZE)
				(FILEEXTENSION,pObj.FILEEXTENSION)
				.Where( ID == pObj.ID);
		//----------------------------------------
		tObj = GetById(pObj.ID);
		Cout()<<"\nUpdated User Setting:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\nUser Setting did not exist:"<<tObj.data.ID<<"\n";
		tObj=Create(pObj);
	}
	return tObj;
}


void D_USERSETTING::Delete(Http& http){
	// do not delete setting?
}

Vector<D_USERSETTING> D_USERSETTING::Retrieve(Http& http){
		
	S_USERSETTING pObj; // params container
	PAGINATION pager(http); // extract pager
	
	try{		
		pObj.ID =atoi((String)http["ID"]);
		pObj.MAXFILESIZE=atoi((String)http["MAXFILESIZE"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.FILEEXTENSION= (String)http["FILEEXTENSION"];
	}
	catch(...)
	{
		Cout() << "error get params";
	}
	
	int row =0;
	//------------------------
	SqlBool where;
	if(pObj.ID>0) where = ID == pObj.ID;
	if(pObj.FILEEXTENSION.IsEmpty()==false) where =where &&  FILEEXTENSION == pObj.FILEEXTENSION;
	if(pObj.USERID>0) where =where &&  USERID == pObj.USERID;
	if(pObj.MAXFILESIZE>0) where =where &&  MAXFILESIZE == pObj.MAXFILESIZE;
	//------------------------
	Cout()<<pObj<<"\n";
	
	SQL *  Select ( SqlAll() ).From ( USERSETTING ).Where(where).OrderBy ( ID ).Limit(pager.OFFSET, pager.SIZE);
	
	Vector<D_USERSETTING>  vector;
	S_USERSETTING x;

	while ( SQL.Fetch ( x ) ){
		vector.Add ( D_USERSETTING(x) );
		row++;
		if(row >= pager.SIZE) break;
	}
	//--------------------------------------------------------
	return vector;
}

String D_USERSETTING::RetrieveAsJson(Http& http){
	return StoreAsJson(Retrieve(http),true); 
}

/*
	get user setting by id
*/
D_USERSETTING D_USERSETTING::GetById(int id){
	
	D_USERSETTING  rs;
	S_USERSETTING x;
	
	try{
		SqlBool where;
		where = ID == id;// condition
		
		SQL *  Select ( SqlAll() ).From ( USERSETTING ).Where(where).Limit(1);;
	
		while ( SQL.Fetch ( x ) ){
			rs = D_USERSETTING(x);
			break;
		}
	}
	catch(...){
		Cout() << "Error D_USERSETTING::Get(String id)";
	}
	return  rs;
	
}

/*
	get user setting by id
*/
D_USERSETTING D_USERSETTING::GetByUserId(int uid){
	
	D_USERSETTING  rs;
	S_USERSETTING x;
	
	try{
		SqlBool where;
		where = USERID == uid;// condition
		
		SQL *  Select ( SqlAll() ).From ( USERSETTING ).Where(where).Limit(1);;
	
		while ( SQL.Fetch ( x ) ){
			rs = D_USERSETTING(x);
			break;
		}
		
		if(x.ID<0)
		{
			rs.data.USERID = uid;
			rs.data.FILEEXTENSION = "png jpg bmp";
			rs.data.MAXFILESIZE = 10;
			rs = rs.Create(rs.data);
		}
	}
	catch(...){
		Cout() << "Error D_USERSETTING::Get(String id)";
	}
	return  rs;
	
}