#include "util.h"
#include "Poco.h"

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

D_DAILYSUMMARY D_DAILYSUMMARY::Create(Http& http){
	
	S_DAILYSUMMARY pObj; // params container
	
	try{
		//pObj.ID=atoi((String)http["ID"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.LOGDATE=atoi((String)http["LOGDATE"]);
		pObj.NOOFUPLOADFILE=atoi((String)http["NOOFUPLOADFILE"]);
		pObj.NOOFDOWNLOADFILE=atoi((String)http["NOOFDOWNLOADFILE"]);
		pObj.TOTALUPLOADSIZE=atoi((String)http["TOTALUPLOADSIZE"]);
		pObj.TOTALDOWNLOADSIZE=atoi((String)http["TOTALDOWNLOADSIZE"]);
	}
	catch(...)
	{
		Cout() << "Error D_DAILYSUMMARY::Create";
	}
	
	return Create(pObj);
}



D_DAILYSUMMARY D_DAILYSUMMARY::Create(S_DAILYSUMMARY& pObj){
	
	// check any same email registered
	D_DAILYSUMMARY tObj = GetById(pObj.ID);
	pObj.LOGDATE =GetSysDate().Get();
	
	if(tObj.data.ID < 0)
	{
		SQL *  Insert( DAILYSUMMARY )
				(USERID,pObj.USERID)
				(LOGDATE,pObj.LOGDATE)
				(NOOFUPLOADFILE,pObj.NOOFUPLOADFILE)
				(NOOFDOWNLOADFILE,pObj.NOOFDOWNLOADFILE)
				(TOTALUPLOADSIZE,pObj.TOTALUPLOADSIZE)
				(TOTALDOWNLOADSIZE,pObj.TOTALDOWNLOADSIZE)
				;
		//----------------------------------------
		Cout()<<"\nCreated Daily Summary:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\nDaily Summary existed:"<<tObj.data.ID<<"\n";
	}
	return tObj;
}

/*
	update user information based on ID
	ex:
		http://127.0.0.1:8001/tis/api/user/update?ID=3&EMAIL=user23@simaget.com&PASSWORD=12345&FULLNAME=user2%20simaget&PHONE=987654321&DATEOFBIRTH=2000/03/01
*/
D_DAILYSUMMARY D_DAILYSUMMARY::Edit(Http& http){
	S_DAILYSUMMARY pObj; // params container
	
	try{
		pObj.ID=atoi((String)http["ID"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.LOGDATE=atoi((String)http["LOGDATE"]);
		pObj.NOOFUPLOADFILE=atoi((String)http["NOOFUPLOADFILE"]);
		pObj.NOOFDOWNLOADFILE=atoi((String)http["NOOFDOWNLOADFILE"]);
		pObj.TOTALUPLOADSIZE=atoi((String)http["TOTALUPLOADSIZE"]);
		pObj.TOTALDOWNLOADSIZE=atoi((String)http["TOTALDOWNLOADSIZE"]);
	}
	catch(...)
	{
		Cout() << "Error D_DAILYSUMMARY::Update";
	}
	// check any same email registered
	D_DAILYSUMMARY tObj = GetById(pObj.ID);
	
//	Cout()<<"\npObj"<<pObj<<"\n";
//	Cout()<<"tObj"<<tObj<<"\n";	
//	Cout()<<"Hash Key"<< GetHashValue(pObj.EMAIL)<<"\n";
//	Cout()<<"Data ID Key"<< tObj.data.ID <<"\n";

	if(tObj.data.ID > 0)
	{
		SQL *  Update( DAILYSUMMARY )
				(USERID,pObj.USERID)
				(LOGDATE,pObj.LOGDATE)
				(NOOFUPLOADFILE,pObj.NOOFUPLOADFILE)
				(NOOFDOWNLOADFILE,pObj.NOOFDOWNLOADFILE)
				(TOTALUPLOADSIZE,pObj.TOTALUPLOADSIZE)
				(TOTALDOWNLOADSIZE,pObj.TOTALDOWNLOADSIZE)
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


/*
	update user information based on ID
	ex:
		http://127.0.0.1:8001/tis/api/user/update?ID=3&EMAIL=user23@simaget.com&PASSWORD=12345&FULLNAME=user2%20simaget&PHONE=987654321&DATEOFBIRTH=2000/03/01
*/
D_DAILYSUMMARY D_DAILYSUMMARY::Edit(S_DAILYSUMMARY& pObj){
	
	
	// check any same email registered
	D_DAILYSUMMARY tObj = GetById(pObj.ID);
	

	if(tObj.data.ID > 0)
	{
		SQL *  Update( DAILYSUMMARY )
				(USERID,pObj.USERID)
				(LOGDATE,pObj.LOGDATE)
				(NOOFUPLOADFILE,pObj.NOOFUPLOADFILE)
				(NOOFDOWNLOADFILE,pObj.NOOFDOWNLOADFILE)
				(TOTALUPLOADSIZE,pObj.TOTALUPLOADSIZE)
				(TOTALDOWNLOADSIZE,pObj.TOTALDOWNLOADSIZE)
				.Where( ID == pObj.ID);
		//----------------------------------------
		tObj = GetById(pObj.ID);
		Cout()<<"\n Daily Summary Update:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\n Daily Summary did not exist:"<<tObj.data.ID<<"\n";
		tObj=Create(pObj);//create it
	}
	return tObj;
}

void D_DAILYSUMMARY::Delete(Http& http){
	// do not delete setting?
}

Vector<D_DAILYSUMMARY> D_DAILYSUMMARY::Retrieve(Http& http){
		
	S_DAILYSUMMARY pObj; // params container
	PAGINATION pager(http); // extract pager
	
	try{		
		pObj.ID=atoi((String)http["ID"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.LOGDATE=atoi((String)http["LOGDATE"]);
		pObj.NOOFUPLOADFILE=atoi((String)http["NOOFUPLOADFILE"]);
		pObj.NOOFDOWNLOADFILE=atoi((String)http["NOOFDOWNLOADFILE"]);
		pObj.TOTALUPLOADSIZE=atoi((String)http["TOTALUPLOADSIZE"]);
		pObj.TOTALDOWNLOADSIZE=atoi((String)http["TOTALDOWNLOADSIZE"]);
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
	if(pObj.LOGDATE>0) where =where &&  LOGDATE == pObj.LOGDATE;
	if(pObj.NOOFUPLOADFILE>0) where =where &&  NOOFUPLOADFILE == pObj.NOOFUPLOADFILE;
	if(pObj.NOOFDOWNLOADFILE>0) where =where &&  NOOFDOWNLOADFILE == pObj.NOOFDOWNLOADFILE;
	if(pObj.TOTALUPLOADSIZE>0) where =where &&  TOTALUPLOADSIZE == pObj.TOTALUPLOADSIZE;
	if(pObj.TOTALDOWNLOADSIZE>0) where =where &&  TOTALDOWNLOADSIZE == pObj.TOTALDOWNLOADSIZE;
	
	//------------------------
	Cout()<<pObj<<"\n";
	
	SQL *  Select ( SqlAll() ).From ( DAILYSUMMARY ).Where(where).OrderBy ( ID ).Limit(pager.OFFSET, pager.SIZE);
	
	Vector<D_DAILYSUMMARY>  vector;
	S_DAILYSUMMARY x;

	while ( SQL.Fetch ( x ) ){
		vector.Add ( D_DAILYSUMMARY(x) );
		row++;
		if(row >= pager.SIZE) break;
	}
	//--------------------------------------------------------
	return vector;
}

String D_DAILYSUMMARY::RetrieveAsJson(Http& http){
	return StoreAsJson(Retrieve(http),true); 
}

/*
	get user setting by id
*/
D_DAILYSUMMARY D_DAILYSUMMARY::GetById(int id){
	
	D_DAILYSUMMARY  rs;
	S_DAILYSUMMARY x;
	
	try{
		SqlBool where;
		where = ID == id;// condition
		
		SQL *  Select ( SqlAll() ).From ( DAILYSUMMARY ).Where(where).Limit(1);
	
		while ( SQL.Fetch ( x ) ){
			rs = D_DAILYSUMMARY(x);
			break;
		}
	}
	catch(...){
		Cout() << "Error D_DAILYSUMMARY::Get(String id)";
	}
	return  rs;
	
}

/*
	get user setting by id
*/
D_DAILYSUMMARY D_DAILYSUMMARY::GetByLogDate(int logdate){
	
	D_DAILYSUMMARY  rs;
	S_DAILYSUMMARY x;
	
	try{
		SqlBool where;
		where = LOGDATE == logdate;// condition
		
		SQL *  Select ( SqlAll() ).From ( DAILYSUMMARY ).Where(where).Limit(1);
	
		while ( SQL.Fetch ( x ) ){
			rs = D_DAILYSUMMARY(x);
			break;
		}
	}
	catch(...){
		Cout() << "Error D_DAILYSUMMARY::Get(String id)";
	}
	return  rs;
	
}

/*
	update share image info
*/
void D_DAILYSUMMARY::UpdateDownload(int userid, int size){
	
	//update daily summary
	int today = GetSysDate().Get();
	
	D_DAILYSUMMARY daily;
	daily = daily.GetByUserIDLogDate(userid, today);
	daily.data.USERID = userid;
	daily.data.LOGDATE = today;
	daily.data.NOOFDOWNLOADFILE +=1;
	daily.data.TOTALDOWNLOADSIZE += size;
	daily.Edit(daily.data);
}

/*
	update when upload file
*/
void D_DAILYSUMMARY::UpdateUpload(int userid, int size){
	
	//update daily summary
	int today = Date().Get();
	
	D_DAILYSUMMARY daily;
	daily = daily.GetByUserIDLogDate(userid, today);
	daily.data.USERID = userid;
	daily.data.LOGDATE = today;
	daily.data.NOOFUPLOADFILE += 1;
	daily.data.TOTALUPLOADSIZE += size;
	daily.Edit(daily.data);
}

/*
	get user setting by user id and logdate
*/
D_DAILYSUMMARY D_DAILYSUMMARY::GetByUserIDLogDate(int userid, int logdate){
	
	D_DAILYSUMMARY  rs;
	S_DAILYSUMMARY x;
	
	try{
		SqlBool where;
		where = LOGDATE == logdate;// condition
		where = where && USERID == userid;// condition
		
		SQL *  Select ( SqlAll() ).From ( DAILYSUMMARY ).Where(where).Limit(1);
	
		while ( SQL.Fetch ( x ) ){
			rs = D_DAILYSUMMARY(x);
			break;
		}
	}
	catch(...){
		Cout() << "Error D_DAILYSUMMARY::Get(userid, logdate)";
	}
	return  rs;
	
}

// get total download in system
int D_DAILYSUMMARY::GetDailyDownload(){
	
	int  rs;
	D_DAILYSUMMARY d;
	S_DAILYSUMMARY x;
	
	try{
		Date today = GetSysDate();
		
		SqlBool where;
		where = LOGDATE == today.Get();// 
		
		SQL *  Select ( SqlSum(NOOFDOWNLOADFILE) ).From ( DAILYSUMMARY ).Where(where).GroupBy(LOGDATE);
		
		while ( SQL.Fetch () ){
			rs = SQL[0];
			break;
		}
		
	}
	catch(...){
		Cout() << "Error D_USERINFO::GetSummary()";
	}
	return  rs;
	
}


// get total download in system
Vector<Jsonew> D_DAILYSUMMARY::GetMonthlyDownload(){
	
	
	Vector<Jsonew> d;
	S_DAILYSUMMARY x;
	
	try{
		Date today = GetSysDate();
		Date last30 = AddMonths(today, -1);
		//Cout()<<" last 30:"<< last30.Get() << " today: "<< today.Get();
		SqlBool where;
		where = LOGDATE > last30.Get() && LOGDATE <= today.Get();// 
		
		SQL *  Select (LOGDATE, SqlSum(NOOFUPLOADFILE),SqlSum(NOOFDOWNLOADFILE), SqlSum(TOTALUPLOADSIZE),SqlSum(TOTALDOWNLOADSIZE))
			.From ( DAILYSUMMARY )
			.Where(where)
			.GroupBy(LOGDATE).OrderBy(LOGDATE);
		
		where = LOGDATE == today.Get();// 
		
		/*
			INT_	(LOGDATE)
			INT_	(NOOFUPLOADFILE)
			INT_	(NOOFDOWNLOADFILE)
			INT_	(TOTALUPLOADSIZE)
			INT_	(TOTALDOWNLOADSIZE)
		*/
	
		
		while ( SQL.Fetch() ){
			Jsonew k;
			Date date;
			date.Set(SQL[0]);
			
			k
			("LOGDATE", AsString(date) )
			("NOOFUPLOADFILE", SQL[1] )
			("NOOFDOWNLOADFILE", SQL[2] )
			("TOTALUPLOADSIZE", SQL[3] )
			("TOTALDOWNLOADSIZE", SQL[4] );
						
			d.Add(k);
		}
		
	}
	catch(...){
		Cout() << "Error D_USERINFO::GetMonthlySummary()";
	}
	return  d;
	
}