#include"poco.h"
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
	
	return Create(pObj);
}


D_USERINFO D_USERINFO::Create(S_USERINFO& pObj){

	// check any same email registered
	D_USERINFO tObj = GetByApiKey(pObj.APIKEY);
	
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
	
	return Edit(pObj);
}

D_USERINFO D_USERINFO::Edit(S_USERINFO& pObj){
	// check any same email registered
	D_USERINFO tObj = GetById(pObj.ID);
	
	if(tObj.data.ID > 0)
	{
		SQL *  Update( USERINFO )
				//(ID,pObj.ID)
				(EMAIL,pObj.EMAIL)
				(PASSWORD,pObj.PASSWORD)
				(APIKEY,pObj.APIKEY)
				(SESSION,pObj.SESSION)
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
		tObj = Create(pObj);
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
		pObj.PASSWORD =((String)http["PASSWORD"]);
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
	if(pObj.PASSWORD.IsEmpty()==false) where =where &&  PASSWORD == pObj.PASSWORD;
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
		// generate session id
		
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


D_USERINFO D_USERINFO::GetByApiKey(Http & http){
	
	String userId = http[0];// api key always on first param
	D_USERINFO user;
	
	try
	{
		int apikey = atoi(userId);
		user= GetByApiKey(apikey);
		
	}
	catch(...)
	{
		
	}
	
	return user;
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
		
		SQL *  Select ( SqlAll() ).From ( USERINFO ).Where(where).Limit(1);;
	
		
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

D_USERINFO D_USERINFO::GetBySession(int session){
	
	D_USERINFO  rs;
	S_USERINFO x;
	
	try{
		SqlBool where;
		where = SESSION == session;// condition
		
		SQL *  Select ( SqlAll() ).From ( USERINFO ).Where(where).Limit(1);;
	
		while ( SQL.Fetch ( x ) ){
			rs = D_USERINFO(x);
			break;
		}
		
	}
	catch(...){
		Cout() << "Error D_USERINFO::Get(int session)";
	}
	return  rs;
	
}
/*
	validate the user api key from http params
*/
bool D_USERINFO::ValidateUserApiKey(Http &http, bool isAdmin){
	String userId = http[0];// api key always on first param
	bool rs = false;
	
	try
	{
		int apikey = atoi(userId);
		D_USERINFO user= GetByApiKey(apikey);
		
		if(user.data.ID >0) rs =true;
	}
	catch(...)
	{
		rs =false;
	}
	
	return rs;
}

//-----------------------------------------------------------------








// get total users in system
int D_USERINFO::GetSummary(){
	
	int  rs;
	S_USERINFO x;
	
	try{
		SqlBool where;
		where = STATUS >= 1;// condition 0 means blocked
		
		SQL *  Select ( Count(USERID) ).From ( USERINFO ).Where(where);;
		
		while ( SQL.Fetch (  ) ){
			rs = SQL[0];
			break;
		}
		
	}
	catch(...){
		Cout() << "Error D_USERINFO::GetSummary()";
	}
	return  rs;
	
}
