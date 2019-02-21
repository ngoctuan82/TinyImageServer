#include "util.h"
#include "Poco.h"

void D_IMAGEFILE::Jsonize(JsonIO & json)
{
	json
	("ID",data.ID)
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


D_IMAGEFILE D_IMAGEFILE::Create(Http& http){
	
	S_IMAGEFILE pObj; // params container
	
	try{
	//	pObj.ID =atoi((String)http["ID"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.FILENAME=((String)http["FILENAME"]);
		pObj.MODIFIEDDATE=atoi((String)http["MODIFIEDDATE"]);
		pObj.FILETYPE=((String)http["FILETYPE"]);
		pObj.FILESIZE=atoi((String)http["FILESIZE"]);
		pObj.REALFILEPATH=((String)http["REALFILEPATH"]);
		pObj.WIDTH=atoi((String)http["WIDTH"]);
		pObj.HEIGHT=atoi((String)http["HEIGHT"]);
		pObj.TAG=((String)http["TAG"]);
		pObj.DESCRIPTION=((String)http["DESCRIPTION"]);
	}
	catch(...)
	{
		Cout() << "Error D_IMAGEFILE::Create";
	}
	// check any same email registered
	D_IMAGEFILE tObj = GetById(pObj.ID);
	
		//	Cout()<<"\npObj"<<pObj<<"\n";
		//	Cout()<<"tObj"<<tObj<<"\n";	
		//	Cout()<<"Hash Key"<< GetHashValue(pObj.EMAIL)<<"\n";
		//	Cout()<<"Data ID Key"<< tObj.data.ID <<"\n";

	if(tObj.data.ID < 0)
	{
		SQL *  Insert( IMAGEFILE )
				//(ID,pObj.ID)
				(USERID,pObj.USERID)
				(FILENAME,pObj.FILENAME)
				(MODIFIEDDATE,pObj.MODIFIEDDATE)
				(FILETYPE,pObj.FILETYPE)
				(FILESIZE,pObj.FILESIZE)
				(REALFILEPATH,pObj.REALFILEPATH)
				(WIDTH,pObj.WIDTH)
				(HEIGHT,pObj.HEIGHT)
				(TAG,pObj.TAG)
				(DESCRIPTION,pObj.DESCRIPTION)

				;
		//----------------------------------------
		Cout()<<"\nCreated Image file:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\nImage File existed:"<<tObj.data.FILENAME<<"\n";
	}
	return tObj;
}

/*
	update user information based on ID
	ex:
		http://127.0.0.1:8001/tis/api/user/update?ID=3&EMAIL=user23@simaget.com&PASSWORD=12345&FULLNAME=user2%20simaget&PHONE=987654321&DATEOFBIRTH=2000/03/01
*/
D_IMAGEFILE D_IMAGEFILE::Edit(Http& http){
	S_IMAGEFILE pObj; // params container
	
	try{
		pObj.ID =atoi((String)http["ID"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.FILENAME=((String)http["FILENAME"]);
		pObj.MODIFIEDDATE=atoi((String)http["MODIFIEDDATE"]);
		pObj.FILETYPE=((String)http["FILETYPE"]);
		pObj.FILESIZE=atoi((String)http["FILESIZE"]);
		pObj.REALFILEPATH=((String)http["REALFILEPATH"]);
		pObj.WIDTH=atoi((String)http["WIDTH"]);
		pObj.HEIGHT=atoi((String)http["HEIGHT"]);
		pObj.TAG=((String)http["TAG"]);
		pObj.DESCRIPTION=((String)http["DESCRIPTION"]);
	}
	catch(...)
	{
		Cout() << "Error D_IMAGEFILE::Update";
	}
	// check any same email registered
	D_IMAGEFILE tObj = GetById(pObj.ID);
	
//	Cout()<<"\npObj"<<pObj<<"\n";
//	Cout()<<"tObj"<<tObj<<"\n";	
//	Cout()<<"Hash Key"<< GetHashValue(pObj.EMAIL)<<"\n";
//	Cout()<<"Data ID Key"<< tObj.data.ID <<"\n";

	if(tObj.data.ID > 0)
	{
		SQL *  Update( IMAGEFILE )
				
				(USERID,pObj.USERID)
				(FILENAME,pObj.FILENAME)
				(MODIFIEDDATE,pObj.MODIFIEDDATE)
				(FILETYPE,pObj.FILETYPE)
				(FILESIZE,pObj.FILESIZE)
				(REALFILEPATH,pObj.REALFILEPATH)
				(WIDTH,pObj.WIDTH)
				(HEIGHT,pObj.HEIGHT)
				(TAG,pObj.TAG)
				(DESCRIPTION,pObj.DESCRIPTION)
				.Where( ID == pObj.ID);
		//----------------------------------------
		tObj = GetById(pObj.ID);
		Cout()<<"\nUpdated Image File:"<<tObj<<"\n";
	}
	else
	{
		Cout()<<"\nImage File did not exist:"<<tObj.data.ID<<"\n";
	}
	return tObj;
}

void D_IMAGEFILE::Delete(Http& http){
	// do not delete setting?
}

Vector<D_IMAGEFILE> D_IMAGEFILE::Retrieve(Http& http){
		
	S_IMAGEFILE pObj; // params container
	PAGINATION pager(http); // extract pager
	
	try{		
		pObj.ID =atoi((String)http["ID"]);
		pObj.USERID=atoi((String)http["USERID"]);
		pObj.FILENAME=((String)http["FILENAME"]);
		pObj.MODIFIEDDATE=atoi((String)http["MODIFIEDDATE"]);
		pObj.FILETYPE=((String)http["FILETYPE"]);
		pObj.FILESIZE=atoi((String)http["FILESIZE"]);
		pObj.REALFILEPATH=((String)http["REALFILEPATH"]);
		pObj.WIDTH=atoi((String)http["WIDTH"]);
		pObj.HEIGHT=atoi((String)http["HEIGHT"]);
		pObj.TAG=((String)http["TAG"]);
		pObj.DESCRIPTION=((String)http["DESCRIPTION"]);
	}
	catch(...)
	{
		Cout() << "error get params";
	}
	
	int row =0;
	//------------------------
	SqlBool where;
	if(pObj.ID>0) where = ID == pObj.ID;
	if(pObj.USERID>0) where =where &&  USERID == pObj.USERID;
	if(pObj.FILENAME.IsEmpty()==false) where =where &&  Like(FILENAME, Wild("*"+pObj.FILENAME + "*"));
	if(pObj.MODIFIEDDATE>0) where =where &&  MODIFIEDDATE == pObj.MODIFIEDDATE;
	if(pObj.FILETYPE.IsEmpty()==false) where =where &&  Like(FILETYPE, Wild("*"+pObj.FILETYPE + "*"));
	if(pObj.FILESIZE>0) where =where &&  FILESIZE == pObj.FILESIZE;
	if(pObj.REALFILEPATH.IsEmpty()==false) where =where &&  Like(REALFILEPATH, Wild("*"+pObj.REALFILEPATH + "*"));
	if(pObj.WIDTH>0) where =where &&  WIDTH == pObj.WIDTH;
	if(pObj.HEIGHT>0) where =where &&  HEIGHT == pObj.HEIGHT;
	if(pObj.TAG.IsEmpty()==false) where =where &&  Like(TAG, Wild("*"+pObj.TAG + "*"));
	if(pObj.DESCRIPTION.IsEmpty()==false) where =where &&  Like(DESCRIPTION, Wild("*"+pObj.DESCRIPTION + "*"));
	//------------------------
	Cout()<<pObj<<"\n";
	
	SQL *  Select ( SqlAll() ).From ( IMAGEFILE ).Where(where).OrderBy ( ID ).Limit(pager.OFFSET, pager.SIZE);
	
	Vector<D_IMAGEFILE>  vector;
	S_IMAGEFILE x;

	while ( SQL.Fetch ( x ) ){
		vector.Add ( D_IMAGEFILE(x) );
		row++;
		if(row >= pager.SIZE) break;
	}
	//--------------------------------------------------------
	return vector;
}

String D_IMAGEFILE::RetrieveAsJson(Http& http){
	return StoreAsJson(Retrieve(http),true); 
}

/*
	get user setting by id
*/
D_IMAGEFILE D_IMAGEFILE::GetById(int id){
	
	D_IMAGEFILE  rs;
	S_IMAGEFILE x;
	
	try{
		SqlBool where;
		where = ID == id;// condition
		
		SQL *  Select ( SqlAll() ).From ( IMAGEFILE ).Where(where).Limit(1);
	
		while ( SQL.Fetch ( x ) ){
			rs = D_IMAGEFILE(x);
			break;
		}
	}
	catch(...){
		Cout() << "Error D_IMAGEFILE::Get(String id)";
	}
	return  rs;
	
}