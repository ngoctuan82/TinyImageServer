/*
    DataPacket class which converts JSON received from server 
*/
class DataPacket
{
    constructor(obj)
    {
        this.Status="";
        this.IsError= false;
        this.Data=[];
        try{
            this.Status = obj.Status;
            this.IsError = obj.IsError;
            this.Data = JSON.parse(obj.Data);
        }
        catch(e){ console.log("DataPacket parses error:"+ e); }
    }
}

class USERINFO
{
    constructor(id,email,password,apikey,fullname,phone,dateofbirth,status,isadmin)
        this.ID=id;
        this.EMAIL=email;
        this.PASSWORD=password;
        this.APIKEY=apikey;
        this.FULLNAME=fullname;
        this.PHONE=phone;
        this.DATEOFBIRTH=dateofbirth;
        this.STATUS=status;
        this.ISADMIN=isadmin;
	}
}
	


class USERSETTING
{
    constructor(id,userid,maxfilesize,fileextension){
        this.ID=id;
        this.USERID=userid;
        this.MAXFILESIZE=maxfilesize;
        this.FILEEXTENSION=fileextension;
    }
}
	


class ADMINSETTING
{
    constructor(id,rootpath,staticpath,imagepath,backuppath,serverport,hostname){
        this.ID=id;
        this.ROOTPATH=rootpath;
        this.STATICPATH=staticpath;
        this.IMAGEPATH=imagepath;
        this.BACKUPPATH=backuppath;
        this.SERVERPORT=serverport;
        this.HOSTNAME=hostname;
    }
}
	

class 
IMAGEFILE
{
    constructor(id,userid,filename,modifieddate,filetype,filesize,realfilepath,width,height,tag,description){
        this.ID=id;
        this.USERID=userid;
        this.FILENAME=filename;
        this.MODIFIEDDATE=modifieddate;
        this.FILETYPE=filetype;
        this.FILESIZE=filesize;
        this.REALFILEPATH=realfilepath;
        this.WIDTH=width;
        this.HEIGHT=height;
        this.TAG=tag;
        this.DESCRIPTION=description;
    }
}
	

class 
DAILYSUMMARY
{
    constructor(id,userid,logdate,noofuploadfile,noofdownloadfile,totaluploadsize,totaldownloadsize){
        this.ID=id;
        this.USERID=userid;
        this.LOGDATE=logdate;
        this.NOOFUPLOADFILE=noofuploadfile;
        this.NOOFDOWNLOADFILE=noofdownloadfile;
        this.TOTALUPLOADSIZE=totaluploadsize;
        this.TOTALDOWNLOADSIZE=totaldownloadsize;
    }
}
	

class 
BACKUPRESTORETASK
{
    constructor(id,userid,isbackuptask,createddate,finishdate,sourcefolderpath,targetfolderpath,proccesed,totalfiles,status){
        this.ID=id;
        this.USERID=userid;
        this.ISBACKUPTASK=isbackuptask;
        this.CREATEDDATE=createddate;
        this.FINISHDATE=finishdate;
        this.SOURCEFOLDERPATH=sourcefolderpath;
        this.TARGETFOLDERPATH=targetfolderpath;
        this.PROCCESED=proccesed;
        this.TOTALFILES=totalfiles;
        this.STATUS=status;
    }
}
	


class 
TRANSFORMATIONSETTING
{
    constructor(id,userid,transformtype,deletedoriginalfile,proccessorder){
        this.ID=id;
        this.USERID=userid;
        this.TRANSFORMTYPE=transformtype;
        this.DELETEDORIGINALFILE=deletedoriginalfile;
        this.PROCCESSORDER=proccessorder;
    }
}
	

class 
TRANSFORMATIONTASK
{
    constructor(
id,transformationsettingid,createddate,finishdate,fullsourcefilepath,fulltargetfildepath,status
){
        this.ID=id;
        this.TRANSFORMATIONSETTINGID=transformationsettingid;
        this.CREATEDDATE=createddate;
        this.FINISHDATE=finishdate;
        this.FULLSOURCEFILEPATH=fullsourcefilepath;
        this.FULLTARGETFILDEPATH=fullsourcefilepath;
        this.STATUS=status;
    }
}
	
