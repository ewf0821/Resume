#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdio.h>
#include <pthread.h>
#include "datatypes.h"
#include "configops.h"
#include "metadataops.h"
#include "SimTimer.h"

// PCB struct
typedef struct PCB
{
    int pid;                    // unique process id
    ProcessState state;         // process state
    OpCodeType *programCounter; // pointer to current operation
    int timeRemaining;          // time left for process
    struct PCB *next;           // next PCB in queue
} PCB;

typedef struct
{
    OpCodeType *operation;
    ConfigDataType *config;
    int pid;
    char *timeStr;
} ThreadArgs;

/*
Name: createPCB
Process: initialized a PCB for a new process, allocates memory, sets state,
    priority, program counter, time remaining, and next pointer
Function Input/Parameters: process ID (int), priority (int),
    program counter (OpCodeType *), configuration data (ConfigDataType *)
Function Output/Parameters: new PCB (PCB *)
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: printf, malloc
*/
PCB *createPCB(int pid, OpCodeType *firstOp, ConfigDataType *configPtr);

/*
Name: addToQueue
Process: adds a process to the queue
Function Input/Parameters: process (PCB *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: TBD
*/
void addToQueue(PCB *pcb);

/*
Name: getProcess
Process: gets the next process from the queue
Function Input/Parameters: none
Function Output/Parameters: process (PCB *)
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: TBD
*/
PCB *getProcess();

/*
Name: freeQueue
Process: Frees all memory associated with the process queue
Function Input/Parameters: none
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: free
*/
void freeQueue();

/*
Name: runTimerforCycle
Process: Runs a timer for a calculated I/O cycle time in a new thread
Function Input/Parameters: void pointer to ThreadArgs (void *)
Function Output/Parameters: none
Function Output/Returned: void pointer (void *)
Device Input/device: none
Device Output/device: none
Dependencies: runTimer, free
*/
void *runTimerforCycle(void *arg);

/*
Name: output
Process: Handles logging to monitor, file, or both based on configuration
Function Input/Parameters:
    - Message to log (const char *)
    - Pointer to configuration data (ConfigDataType *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: monitor, file
Dependencies: printf, fopen, fprintf
*/
void output(const char *message, ConfigDataType *configPtr);

/*
Name: systemMessage
Process: Formats and outputs a system-level message
Function Input/Parameters:
    - Time string (char *)
    - Message string (const char *)
    - Pointer to configuration data (ConfigDataType *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: monitor, file (based on config)
Dependencies: sprintf, output
*/
void systemMessage(char *timeStr, const char *message,
                   ConfigDataType *configPtr);

/*
Name: stateChange
Process: Changes and logs the state of a process
Function Input/Parameters:
    - Time string (char *)
    - Process ID (int)
    - Old state (const char *)
    - New state (const char *)
    - Pointer to configuration data (ConfigDataType *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: monitor, file (based on config)
Dependencies: compareString, output
*/
void stateChange(char *timeStr, int pid, const char *oldState,
                 const char *newState, ConfigDataType *configPtr);

/*
Name: WriteOutput
Process: Handles logging to monitor, file, or both based on configuration
Function Input/Parameters:
    - Time string (char *)
    - Process ID (int)
    - OpCodeType
    - PCB
    - Status (const char *)
    - Pointer to configuration data (ConfigDataType *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: monitor, file
Dependencies: compareString, sprintf
*/
void WriteOutput(char *timeStr, int *pid, OpCodeType *op,
                 PCB *pcb, const char *status, ConfigDataType *configPtr);

/*
Name: findTime
Process: calculates the total time for a process
Function Input/Parameters: metadata (OpCodeType *),
                            configuration data (ConfigDataType *)
Function Output/Parameters: total time (int)
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: None
*/

int findTime(OpCodeType *op, ConfigDataType *configPtr);

/*
Name: runSim
Process: primary simulation driver
Function Input/Parameters: configuation data (ConfigDataType *),
                           metadata (OpCodeType *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: TBD
*/
void runSim(ConfigDataType *configPtr, OpCodeType *metaDataMstrPrt);

#endif