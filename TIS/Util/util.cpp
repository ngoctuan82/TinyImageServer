#include "util.h"
#include "SysInfo/SysInfo.h"
#include <Core/Core.h>

using namespace Upp;

/*
	Get summary info of drive: total free, total used
*/
Vector<Jsonew> GetDrivesSummaryInfo(){
	Vector<Jsonew> rs;
	
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
	
	
	Jsonew vm;
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
Vector<Jsonew> GetDrivesInfo(){

	Vector< Jsonew > rs;
	
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
				Jsonew vm;
				vm
					("Drive", drives[i] )
					("TotalVal", AsString(totalBytesUser) )
					("FreeVal",  AsString(totalFreeBytes) )
					("UsageVal",  AsString(totalBytesUser-totalFreeBytes) )
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


/*
	Get all drives info 
*/
Vector<Jsonew> GetServerInfo(){

	Vector< Jsonew > rs;
	Vector<String> cpus;
	
	String manufacturer, productName, version, mbSerial;
	Date releaseDate;
	int numberOfProcessors;
	GetSystemInfo(manufacturer, productName, version, numberOfProcessors, mbSerial);
	
	String vendor, identifier, architecture; 
	int speed;
	for (int i = 0; i < numberOfProcessors; ++i) {
		GetProcessorInfo(i, vendor, identifier, architecture, speed);		
		cpus.Add(Format("Processor #%d: '%s', '%s', '%s', %d MHz", i, vendor, identifier, architecture, speed));	
	}
		
	int memoryLoad;
	uint64 totalPhys, freePhys, totalPageFile, freePageFile, totalVirtual, freeVirtual;
	if (!GetMemoryInfo(memoryLoad, totalPhys, freePhys, totalPageFile, freePageFile, totalVirtual, freeVirtual))		
		LOG("Cannot get memory info.");
	String memory = Format("Memory: In use:%d%c,  Total: '%s'",memoryLoad, BytesToString(totalPhys) );
	Jsonew vm;
	vm
		("CPU", cpus )
		("MEMORY", memory )
		;

	return rs;
}



