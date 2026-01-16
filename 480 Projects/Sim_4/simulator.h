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
    int timeRemaining;
    bool preempted;   // time left for process
    struct PCB *next; // next PCB in queue
} PCB;

typedef struct
{
    OpCodeType *operation;
    ConfigDataType *config;
    int pid;
    char *timeStr;
} ThreadArgs;

typedef struct Messages
{
    char message[255];
    struct Messages *next;
} Messages;

typedef struct
{
    Messages *head;
    Messages *tail;
    int count;
} MessageBuffer;

typedef struct MemoryData
{
    int pid;
    int MemoryBase;
    int MemoryLimit;
    struct MemoryData *next;
} MemoryData;

typedef struct MemoryManager
{
    MemoryData *head;
} MemoryManager;

typedef struct Interrupts
{
    int pid;
    OpCodeType *operation;
    double completionTime;
    struct Interrupts *next;
} Interrupts;

typedef struct
{
    Interrupts *head;
} InterruptQueue;

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
                 PCB *pcb, const char *status, ConfigDataType *configPtr, MessageBuffer *messagebuffer);

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
void addToQueue(PCB *pcb, PCB **queue, int *processCount);

void addToBlockedQueue(PCB **blockedQueue, PCB *pcb);

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
PCB *getProcessSched(ConfigDataType *configPtr, PCB **readyQueue, int *processCount);

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
void freeQueue(PCB **queue, int *processCount);

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
void output(const char *message, ConfigDataType *configPtr, MessageBuffer *messagebuffer);

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
                   ConfigDataType *configPtr, MessageBuffer *messagebuffer);

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
void stateChange(char *timeStr, PCB *pcb, const char *oldState,
                 const char *newState, ConfigDataType *configPtr, MessageBuffer *messagebuffer);

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
Name: freeProcess
Process: Removes and frees all memory allocations for a specific process
         from the memory manager's linked list
Function Input/Parameters:
  - Pointer to MemoryManager (MemoryManager *)
  - Process ID to clear (int)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: free
*/
void freeProcess(MemoryManager *memoryManager, int pid);

/*
Name: freeAll
Process: Removes and frees all memory allocations for all processes
         from the memory manager's linked list
Function Input/Parameters:
  - Pointer to MemoryManager (MemoryManager *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: free
*/
void freeAll(MemoryManager *memoryManager);

/*
Name: allocateMemory
Process: Allocates memory for a process
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: malloc
*/
int allocateMemory(MemoryManager *memoryManager, int pid, int base,
                   int limit, int maxMemory);

/*
Name: ProcessAccess
Process: Accesses memory for a process
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: malloc
*/
int ProcessAccess(MemoryManager *memoryManager, int pid, int base,
                  int limit, int maxMem);

/*
Name: writeMemoryOutput
Process: writes the memory output to the output file
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: printf
*/

void writeMemoryOutput(char *timeStr, int pid, OpCodeType *op,
                       MemoryManager *memoryManager, int maxMemory,
                       ConfigDataType *configPtr, MessageBuffer *messagebuffer);

/*
Name: avaliableMemory
Process: returns the amount of avaliable memory
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: malloc
*/
void avaliableMemory(MemoryManager *memoryManager,
                     ConfigDataType *config, int pid, MessageBuffer *messagebuffer);

/*
Name: DisplayEnd
Process: displays the end of a process
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: printf
*/
void DisplayEnd(MemoryManager *memoryManager, ConfigDataType *config, int pid, MessageBuffer *messagebuffer);

void addInterruptToQueue(InterruptQueue *intQueue, int pid, OpCodeType *op, double completionTime);

Interrupts *removeInterruptFromQueue(InterruptQueue *intQueue, double currentTime);

void writeBufferOutput(MessageBuffer *messagebuffer, ConfigDataType *configPtr);

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