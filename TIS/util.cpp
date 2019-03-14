#include "util.h"
#include "SysInfo/SysInfo.h"
#include <Core/Core.h>

using namespace Upp;

/*
	Get summary info of drive: total free, total used
*/
Vector<ValueMap> GetDrivesSummaryInfo(){
	Vector<ValueMap> rs;
	
	Vector<String> drives;
	
	uint64 sumFreeBytes=0, sumTotalBytesUser=0;
	String drivesStr;
	
	drives = GetDriveList();
	for (int i = 0; i < drives.GetCount(); ++i) {
		String type, volume, fileSystem;
		int maxName;
		bool mounted = GetDriveInformation(drives[i], type, volume, maxName, fileSystem);
		if (mounted) {
			uint64 freeBytesUser, totalBytesUser, totalFreeBytes;
			if(GetDriveSpace(drives[i], freeBytesUser, totalBytesUser, totalFreeBytes))
			{
				drivesStr<<drives[i]<<";";
				sumFreeBytes += freeBytesUser;
				sumTotalBytesUser += totalBytesUser;
			}
			//else can not access this drive
		}
	}
	
	
	ValueMap vm;
	vm
		("Drives",drivesStr )
		("Total", BytesToString(sumTotalBytesUser)  )
		("Free", BytesToString(sumFreeBytes)  )
		("Usage", BytesToString(sumTotalBytesUser-sumFreeBytes) )
		;
	rs.Add(vm);
				
	return rs;
}
/*
	Get all drives info 
*/
Vector<ValueMap> GetDrivesInfo(){

	Vector< ValueMap > rs;
	
	Vector<String> drives;
	drives = GetDriveList();
	for (int i = 0; i < drives.GetCount(); ++i) {
		String type, volume, fileSystem;
		int maxName;
		bool mounted = GetDriveInformation(drives[i], type, volume, maxName, fileSystem);
		if (mounted) {
			uint64 freeBytesUser, totalBytesUser, totalFreeBytes;
			if(GetDriveSpace(drives[i], freeBytesUser, totalBytesUser, totalFreeBytes))
			{
				ValueMap vm;
				vm
					("Drive", drives[i] )
					("Total", BytesToString(totalBytesUser) )
					("Free", BytesToString(totalFreeBytes) )
					("Usage", BytesToString(totalBytesUser-totalFreeBytes) )
					;
				rs.Add(vm);
			}
			//else can not access this drive
		}
	}
	return rs;
}
