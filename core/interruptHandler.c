//  Interrupt Table
//  Source       | Description
enum Interrupt{
    MEO_PIPE0,  // Gfx pipe
    ME1_PIPE0,  // First 4 Compute Pipes
    ME1_PIPE1,
    ME1_PIPE2,  
    ME1_PIPE3,
    ME2_PIPE0,  // Other 4 Compute Pipes
    ME2_PIPE1, 
    ME2_PIPE2,
    ME2_PIPE3,
    MES_P_FIFO, // Indicates new data in the MES queues
    HW_Q_MSG_I, // QueueManager interrupts
    SFTW_I,     // Caused by MES fw itself
    TIM_I,      // Used for Timer experiration
    UNP_ACC,    // Unprivleged access of MES registers
    EXT_I       // From Non-gfx blocks
}typedef interrupt_t;
