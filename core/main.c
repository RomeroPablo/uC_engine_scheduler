// simulator for AMDs micro engine scheduler
#include <stdio.h>

/* Requirements
fair & efficient scheduling for gpu workloads
mulitple priority levels
same level of priority => equal amount execution time
user focused work (compositor) should receive larger amount of time, but not starve the GPU
real-time work should run immediately and can infinitely starve work in lower priority levels
low priority works when other levels are idle
*/

/* Scheduling Requirements
4 levels of queue prioritization -
Real time:
    lowest possible launch latency
Focus:
    no progress guarantee for lower priority levels
Normal:
    majority of gpu execution time in the absence of Real time work
Low:
    ensures forward progress for the normal level work
*/

/* HW architecture

Kernel Mode Driver
        |
        | ADD_QUEUE packet
        V
       (∞) -> API Processor -> [ Scheduling context ] 
                                        |
                                        v
                                   GPU Scheduler
                                    /       \   
                                Map Q's   Map Q's ...
                                 /             \   
                    |   [(∞) (∞) ... ] |   [(∞) (∞) ... ] |
                    |        /         |         \        |
                    |   [GFX Q Mgr]    | [Compute Q Mgr]  | 
                            |                    |        
                           (∞)                  (∞)      
                            \                    /      
                           [     3D/CS Complex    ]

    1. Driver submits ADD_QUEUE packet
    2. API processor adds the queue to a list
    3. The scheduler selects the hw_q where queue will be mapped
    4. Scheduler maps the user queue onto the selected hw_q
    5. Queue manager selects a mapped queue and runs it on hardware


*/

/*
   We should focus on implementing this in discrete steps/modules
   e.g.

   Scheduler API - 
    commands that indicate the scheduler to events such as queue creation, desctruction, suspension, priority, etc.

   Scheduler Context -
    where app maintains queue/scheduling state  or configuration
    the state of both the API processor and Core scheduler
    which consists of
        HW resource state:
        HQD State - Current Queue Mapped, queue Type, Scheduled Time
        VMID State - Current Process mapped
        GDS State - current proc. using GDS partition

        Process Scheduling State:
        Sheduling Level State - Process List, Grace Period, normalband %, has_ready_q's
        Process State - Gang list for each context priority (-7/+7), processquantum, running time carryover
        Per Gang State - queuelist, running time carryover, gang quantum

    API Processor - 
        Processes the APIs submitted by the driver, and modifies scheduler state

    Core Scheduler - 
        Looks at sched. state, decide next set of sched. actions and applies them
        e.g. mapping a q when it is created, or suspending as req.
        Algo described later

    Interrupt Handler -
        Handles Interrupts from various HW blocks
        e.g. reads API data from the fetcher or collects the busy, idle state of various hardware queues
    
    
   API processor
   Core Scheduler
   Interrupt Handler
*/

// systolic array emulation through GPU wavegroups
// domain decomposition vs functional decomposition
// load balancing
// measure using G = computation / communication

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
