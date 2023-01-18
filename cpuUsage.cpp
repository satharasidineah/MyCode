#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <iostream>
int main() {
    natural_t cpuCount;
    processor_info_array_t cpuInfo;
    mach_msg_type_number_t cpuInfoCount;
    unsigned int i;
    float cpuLoad = 0;

    // Get the number of CPUs
    kern_return_t kernError = host_processor_info(mach_host_self(), PROCESSOR_CPU_LOAD_INFO, &cpuCount, &cpuInfo, &cpuInfoCount);
    if (kernError != KERN_SUCCESS) {
        printf("Error getting CPU count: %d\n", kernError);
        return -1;
    }

    // Calculate the CPU load
    for (i = 0; i < cpuCount; i++) {
        cpuLoad += cpuInfo[i].cpu_ticks[CPU_STATE_USER] + cpuInfo[i].cpu_ticks[CPU_STATE_NICE] + cpuInfo[i].cpu_ticks[CPU_STATE_SYSTEM];
    }

    // Deallocate the CPU info
    vm_deallocate(mach_task_self(), (vm_address_t)cpuInfo, cpuInfoCount * sizeof(natural_t));

    float cpuPer =  (cpuLoad / (float)cpuCount);
	std::cout<<"cpuPer:::"<<cpuPer<<std::endl;
}