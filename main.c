// simulator for AMDs micro engine scheduler

/*requirements: 
   fair & efficient scheduling for gpu workloads
   mulitple priority levels
   same level of priority => equal amount execution time
   user focused work (compositor) should receive larger amount of time, but not starve the GPU
   real-time work should run immediately and can infinitely starve work in lower priority levels
   low priority works when other levels are idle
*/

#include "stdio.h"

/* 4 levels of queue prioritization
Real time:
    lowest possible launch latency
Focus:
    no progress guarantee for lower priority levels
Normal:
    majority of gpu execution time in the absence of Real time work
Low:
    ensures forward progress for the normal level work
*/
enum priority {
    realTime,
    focus,
    normal,
    low
} typedef priority_t;

int main(){
    priority_t x = realTime;
    printf("[+] prio: %i \n", x);
    return 0;
}
