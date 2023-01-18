void cpuUsage()
{
	unsigned numCPUs;
	float totalCpuUsage;
	processor_info_array_t cpuInfo;
	mach_msg_type_number_t numCpuInfo;
    int mib[2U] = { CTL_HW, HW_NCPU };
    size_t sizeOfNumCPUs = sizeof(numCPUs);
    int status = sysctl(mib, 2U, &numCPUs, &sizeOfNumCPUs, NULL, 0U);
    if(status)
        numCPUs = 1;
	std::cout<<"numCPUs:"<<numCPUs<<std::endl;
	CPUUsageLock = [[NSLock alloc] init];
	[CPUUsageLock lock];
	for(unsigned i = 0U; i < numCPUs; ++i) {
		float inUse, total;
		inUse = cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_USER] + cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_SYSTEM] + cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_NICE];
        total = inUse + cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_IDLE];
		std::cout<<"inUse:"<<inUse<<std::endl;
		std::cout<<"total:"<<total<<std::endl;
		float usagePercentage = inUse / total
		std::cout<<"usagePercentage:"<<usagePercentage<<std::endl;
		totalCpuUsage += usagePercentage;
	}
	usagePer = totalCpuUsage/numCPUs;
	std::cout<<"usagePer:"<<usagePer<<std::endl;
	[CPUUsageLock unlock];
}