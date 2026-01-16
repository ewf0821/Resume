// header files

#include "simulator.h"

/*
Name: createPCB
Process: Initializes a PCB for a new process, allocates memory,
         sets state, program counter, time remaining, and next pointer
Function Input/Parameters:
    - Process ID (int)
    - Pointer to first OpCodeType (OpCodeType *)
    - Pointer to configuration data (ConfigDataType *)
Function Output/Parameters: none
Function Output/Returned: Pointer to newly created PCB (PCB *)
Device Input/device: none
Device Output/device: none
Dependencies: printf, malloc
*/
PCB *createPCB(int pid, OpCodeType *firstOp, ConfigDataType *configPtr)
{
    // dynamically allocate memory for the PCB
    PCB *pcbNode = (PCB *)malloc(sizeof(PCB));
    // if the memory allocation fails
    if (pcbNode == NULL)
    {
        // print error message
        // function: printf
        printf("ERROR: Could not allocate memory for new PCB\n");
        // return null
        return NULL;
    }

    // set the properties of the new PCB
    pcbNode->pid = pid;                // set the process ID
    pcbNode->state = NEW_STATE;        // set the state
    pcbNode->programCounter = firstOp; // set the program counter
    pcbNode->timeRemaining = 0;        // set the time remaining
    pcbNode->next = NULL;              // set the next pointer

    // return the newPCB
    return pcbNode;
}

/*
Name: addToQueue
Process: Adds a PCB to the end of the process queue
Function Input/Parameters: Pointer to PCB (PCB *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: none
*/
void addToQueue(PCB *pcb, PCB **queue, int *processCount)
{
    // if queue is empty
    if (*queue == NULL)
    {
        // set queue to process
        *queue = pcb;
    }
    // else
    else
    {
        // set temp to queue
        PCB *current = *queue;
        // while temp has a next
        while (current->next)
            current = current->next;
        // set next to process
        current->next = pcb;
    }

    // increment process count
    (*processCount)++;
}

/*
Name: getProcessSched
Process: Retrieves and removes the next process from the queue
Function Input/Parameters: none
Function Output/Parameters: none
Function Output/Returned: Pointer to next PCB in queue (PCB *)
Device Input/device: none
Device Output/device: none
Dependencies: none
*/
PCB *getProcessSched(ConfigDataType *configPtr, PCB **readyQueue, int *processCount)
{
    // if queue is empty
    if (*readyQueue == NULL)
    {
        // return null
        return NULL;
    }

    // initialize pointers for traversing the queue
    PCB *nextProcess = *readyQueue;
    PCB *previousNode = NULL;
    PCB *currentNode = *readyQueue;
    PCB *previousCurrent = NULL;

    // check if FCFS
    if (configPtr->cpuSchedCode == CPU_SCHED_FCFS_N_CODE)
    {
        // select the first process
        nextProcess = *readyQueue;
        // remove it from the queue by moving head to next
        *readyQueue = nextProcess->next;
    }
    // else if schedule is SJF
    else if (configPtr->cpuSchedCode == CPU_SCHED_SJF_N_CODE)
    {
        // start with first as the shrtest
        nextProcess = currentNode;

        // iterate through the queue to find SJ
        while (currentNode != NULL)
        {
            // if current has less time remaining
            if (currentNode->timeRemaining < nextProcess->timeRemaining)
            {
                // update the shortest process to current
                nextProcess = currentNode;
                // track the node before the new shortest
                previousNode = previousCurrent;
            }
            // move to the next node in queue
            previousCurrent = currentNode;
            currentNode = currentNode->next;
        }
        // if SJ is at head
        if (previousNode == NULL)
        {
            // move head pointer to next
            *readyQueue = nextProcess->next;
        }
        // else
        else
        {
            // link previous node to next node
            previousNode->next = nextProcess->next;
        }
    }
    // else if schedule is RR
    else if (configPtr->cpuSchedCode == CPU_SCHED_RR_P_CODE)
    {
        // select the first process
        nextProcess = *readyQueue;
        // remove it from the queue by moving head to next
        *readyQueue = nextProcess->next;
    }
    // else if schedule is SRTF
    else if (configPtr->cpuSchedCode == CPU_SCHED_SRTF_P_CODE)
    {
        // start with first as the shortest
        nextProcess = currentNode;

        // while currentNode is not null
        while (currentNode != NULL)
        {
            // if currentNode has less time remaining
            if (currentNode->timeRemaining < nextProcess->timeRemaining)
            {
                // set next to current
                nextProcess = currentNode;
                // set previous to to previous
                previousNode = previousCurrent;
            }
            // set previous to current to move forward
            previousCurrent = currentNode;
            // set current ot the next node
            currentNode = currentNode->next;
        }
        // if previous node is null
        if (previousNode == NULL)
        {
            // move head to next
            *readyQueue = nextProcess->next;
        }
        // else
        else
        {
            // link previous to next
            previousNode->next = nextProcess->next;
        }
    }
    // else if schedule is FCFS
    else if (configPtr->cpuSchedCode == CPU_SCHED_FCFS_P_CODE)
    {
        // select the first process
        nextProcess = *readyQueue;
        // remove it from the queue by moving head to next
        *readyQueue = nextProcess->next;
    }

    // set next pointer to null
    nextProcess->next = NULL;
    // decrement process count
    (*processCount)--;
    // return the pcb
    return nextProcess;
}

/*
Name: addToBlockedQueue
Process: Adds a PCB to the blocked queue
Function Input/Parameters:
    - Pointer to blocked queue (PCB **)
    - Pointer to PCB (PCB *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: none
*/
void addToBlockedQueue(PCB **blockedQueue, PCB *pcb)
{
    // set state to block
    pcb->state = BLOCKED_STATE;

    // if queue is empty
    if (*blockedQueue == NULL)
    {
        // set queue to process
        *blockedQueue = pcb;
        // set next to null
        pcb->next = NULL;
    }
    // else queue isnt empty
    else
    {
        // set temp to queue
        PCB *current = *blockedQueue;
        // while the next is not null
        while (current->next != NULL)
        {
            /// move to next
            current = current->next;
        }
        // set next as pcb
        current->next = pcb;
        // set next to null
        pcb->next = NULL;
    }
}

/*
Name: addInterruptToQueue
Process: adds an interrupt to the queue
Function Input/Parameters: none
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: none
*/
void addInterruptToQueue(InterruptQueue *InterruptQueue, int pid, OpCodeType *op, double completionTime)
{
    // allocate memory for interrupt
    Interrupts *interrupt = (Interrupts *)malloc(sizeof(Interrupts));

    /// if the allocation fails
    if (interrupt == NULL)
    {
        // print error
        printf("Error allocating memory\n");
    }
    else
    {
        // set the values for interrupt
        interrupt->pid = pid;
        interrupt->operation = op;
        interrupt->completionTime = completionTime;
        interrupt->next = NULL;

        // if the queue is empty or the completion time is less than the head
        if (InterruptQueue->head == NULL || completionTime < InterruptQueue->head->completionTime)
        {
            // set the next to the head
            interrupt->next = InterruptQueue->head;
            InterruptQueue->head = interrupt;
        }
        // else
        else
        {
            // set current to the head
            Interrupts *current = InterruptQueue->head;
            // cnext is not null and the next completion time is less than completion time
            while (current->next != NULL && current->next->completionTime <= completionTime)
            { // move to next
                current = current->next;
            }
            // set the next
            interrupt->next = current->next;
            // set current to next
            current->next = interrupt;
        }
    }
}

/*
Name: removeInterruptFromQueue
Process:checks for andremoves an interrupt from the queue
Function Input/Parameters: none
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: none
*/

Interrupts *removeInterruptFromQueue(InterruptQueue *InterruptQueue, double currentTime)
{
    // if the queue is empty
    if (InterruptQueue->head == NULL)
    {
        // return null
        return NULL;
    }
    // if the head completion time is greater than the current time
    if (InterruptQueue->head->completionTime > currentTime)
    {
        // return null
        return NULL;
    }

    // remove the head
    Interrupts *interrupt = InterruptQueue->head;
    // set head to next
    InterruptQueue->head = interrupt->next;
    // set next to null
    interrupt->next = NULL;

    // return the interrupt
    return interrupt;
}

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
void freeQueue(PCB **queue, int *processCount)
{
    // initalize variables
    // current head and temp next
    PCB *current = *queue;
    PCB *nextNode = NULL;

    // iterate through the queue
    while (current != NULL)
    {
        nextNode = current->next;
        // free the current node
        // function: free
        free(current);
        // set current to next node
        current = nextNode;
    }

    // set queue to null
    *queue = NULL;
    // set process count to 0
    *processCount = 0;
}

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
void *runTimerforCycle(void *arg)
{
    // initialize the data
    ThreadArgs *args = (ThreadArgs *)arg;

    // run the timer arg 2 times ioCycleRate
    // function: runTimer
    runTimer(args->operation->intArg2 * args->config->ioCycleRate);
    // free the data
    // function: free
    free(args);
    // return
    return NULL;
}

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
void output(const char *message, ConfigDataType *configPtr)
{
    // static file pointer for multiple function calls
    static FILE *writeFile = NULL;

    // if logging to monitor or both
    if (configPtr->logToCode == LOGTO_MONITOR_CODE ||
        configPtr->logToCode == LOGTO_BOTH_CODE)
    {
        // print message
        // function: printf
        printf("%s\n", message);
    }

    // if logging to file or both
    if (configPtr->logToCode == LOGTO_FILE_CODE ||
        configPtr->logToCode == LOGTO_BOTH_CODE)
    {
        // if file not open
        if (!writeFile)
        {
            // open file
            // function: fopen
            writeFile = fopen(configPtr->logToFileName, "w");
            // if file still doesnt open print error
            // function: printf
            if (!writeFile)
            {
                printf("Unable to open log file\n");
                // return
                return;
            }
        }
        // else file already open
        // write message
        // function: fprintf
        fprintf(writeFile, "%s\n", message);
    }
}

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
                   ConfigDataType *configPtr)
{
    // initialze variables
    char write[255];

    // format the message
    // function: sprintf
    sprintf(write, "%s, OS: %s", timeStr, message);
    // output message
    // function: output
    output(write, configPtr);
}

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
                 const char *newState, ConfigDataType *configPtr)
{
    // initialize variables
    char write[255];
    int pid = -1;

    // while the pcb is not null
    if (pcb != NULL)
    {
        // set pid to current pcb
        pid = pcb->pid;
        // if new state is ready
        if (compareString(newState, "READY") == STR_EQ)
        {
            // set state to ready
            pcb->state = READY_STATE;
        }
        // if new state is running
        else if (compareString(newState, "RUNNING") == STR_EQ)
        {
            // set state to running
            pcb->state = RUNNING_STATE;
        }
        // if new state is blocked
        else if (compareString(newState, "BLOCKED") == STR_EQ)
        {
            // set state to blocked
            pcb->state = BLOCKED_STATE;
        }
        // if new state is exit
        else if (compareString(newState, "EXIT") == STR_EQ)
        {
            // set state to exit
            pcb->state = EXIT_STATE;
        }
    }
    // format the state change message with timestamp, PID, old state,
    // and new state
    // function: sprintf
    sprintf(write, "%s, OS: Process %d set from %s to %s", timeStr, pid,
            oldState, newState);
    // output the formatted message
    // function: output
    output(write, configPtr);
}

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
                 PCB *pcb, const char *status, ConfigDataType *configPtr)
{
    // buffer to store formatted message
    char write[255];

    // Case 1: if pid, op, and status are not null
    if (pid != NULL && op != NULL && status != NULL)
    {
        // check if operation command is cpu
        if (compareString(op->command, "cpu") == STR_EQ)
        {
            // format cpu operation message
            // function: sprintf
            sprintf(write, "%s, Process: %d, cpu %s operation %s",
                    timeStr, *pid, op->strArg1, status);
        }
        // else command is io
        else
        {
            // format io operation message
            // function: sprintf
            sprintf(write, "%s, Process: %d, %s %s operation %s",
                    timeStr, *pid, op->strArg1, op->inOutArg, status);
        }
    }
    // case 2: if pid, op, and status are null
    else if (pcb != NULL && status == NULL)
    {
        // format messaege with time remaining
        // function: sprintf
        sprintf(write, "\n%s, OS: Process %d selected with %d ms remaining",
                timeStr, pcb->pid, pcb->timeRemaining);
    }

    // case 3: if pid, op, and status are null
    else if (pcb != NULL && (status == NULL ||
                             compareString(status, "end") == STR_EQ))
    {
        // format message for end
        // function: sprintf
        sprintf(write, "\n%s, OS: Process %d ended", timeStr, pcb->pid);
    }

    // output the formatted message
    // function: output
    output(write, configPtr);
}

/*
Name: findTime
Process: Calculates total time required to complete all operations
         in a process's metadata
Function Input/Parameters:
    - Pointer to metadata (OpCodeType *)
    - Pointer to configuration data (ConfigDataType *)
Function Output/Parameters: none
Function Output/Returned: Total execution time (int)
Device Input/device: none
Device Output/device: none
Dependencies: compareString
*/
int findTime(OpCodeType *op, ConfigDataType *configPtr)
{
    // initalize variables
    int Time = 0; // start at 0 time

    // while op has more pointers to go to
    while (op != NULL && compareString(op->command, "app") != STR_EQ)
    {
        // if dev
        if (compareString(op->command, "dev") == STR_EQ)
        {
            // add arg 2 * the io cycle rate for the time
            Time += op->intArg2 * configPtr->ioCycleRate;
        }
        // else
        else if (compareString(op->command, "cpu") == STR_EQ)
        {
            // add arg 2 * the proc cycle rate for the time
            Time += op->intArg2 * configPtr->procCycleRate;
        }
        // move the pointer
        op = op->nextNode;
    }
    // return the total time
    return Time;
}

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
void freeProcess(MemoryManager *memoryManager, int pid)
{
    // initalize variables
    MemoryData *current = memoryManager->head;
    MemoryData *prev = NULL;
    MemoryData *temp = NULL;

    // check if memory manager is not null
    if (memoryManager != NULL)
    {
        // set current to the head
        current = memoryManager->head;

        // iterate through the list
        while (current != NULL)
        {
            // if the pid matches
            if (current->pid == pid)
            {
                // set current node to temp node
                temp = current;

                // if node is the head
                if (prev == NULL)
                {
                    // move head to next node
                    memoryManager->head = current->next;
                    // move current to next node
                    current = current->next;
                }
                // else node is at middle or end
                else
                {
                    // link previous to the next node
                    prev->next = current->next;
                    // move currnet to next node
                    current = current->next;
                }
                // free temp
                free(temp);
            }
            // else pids dont match
            else
            {
                // move to next node
                prev = current;
                current = current->next;
            }
        }
    }
}

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
void freeAll(MemoryManager *memoryManager)
{
    // initialize variables
    MemoryData *current = NULL;
    MemoryData *temp = NULL;

    // check if memory manager is valid
    if (memoryManager != NULL)
    {
        // set current to the head
        current = memoryManager->head;
        // interate through the lsit
        while (current != NULL)
        {
            // set temp to current
            temp = current;
            // move current
            current = current->next;
            // free temp
            free(temp);
        }
        // set the head to null
        memoryManager->head = NULL;
    }
}

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
                   int limit, int maxMemory)
{
    // initialize the end of the emmory
    int end = base + limit - 1;

    // check if the memory is valid if not
    if (base < 0 || end >= maxMemory)
    {
        // return 0
        return 0;
    }

    // check if the memory is already allocated
    for (MemoryData *current = memoryManager->head; current != NULL;
         current = current->next)
    {
        // set current start and end to the end
        int currentStart = current->MemoryBase;
        int currentEnd = currentStart + current->MemoryLimit - 1;

        // if end is less than current start or base is greater than current end
        if (!(end < currentStart || base > currentEnd))
        {
            // return 0
            return 0;
        }
    }

    // allocate memory
    MemoryData *newNode = malloc(sizeof(MemoryData));
    if (!newNode)
    {
        // if error print error and return 0
        // function: printf
        printf("ERROR: Could not allocate memory\n");
        return 0;
    }

    // set all the data for the new node
    newNode->pid = pid;
    newNode->MemoryBase = base;
    newNode->MemoryLimit = limit;
    newNode->next = memoryManager->head;
    memoryManager->head = newNode;

    // return 1
    return 1;
}

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
                  int limit, int maxMem)

{
    // initialize end
    int end = base + limit - 1;

    // check if memory is valid
    if (base < 0 || end >= maxMem)
    {
        // if not return 0
        return 0;
    }

    // check through the list of allocated memory
    for (MemoryData *current = memoryManager->head; current != NULL;
         current = current->next)
    {
        // check memory of the pid
        if (current->pid == pid)
        {
            int currentStart = current->MemoryBase;
            int currentEnd = currentStart + current->MemoryLimit - 1;

            // if a valid in the memory
            if (base >= currentStart && end <= currentEnd)
            {
                // return 1
                return 1;
            }
        }
    }
    // else return 0
    return 0;
}

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
                       ConfigDataType *configPtr)
{
    // buffer to store formatted message
    char write[255];

    // check if operation is memory allocation
    if (compareString(op->strArg1, "allocate") == STR_EQ)
    {
        // format the message
        // function: sprintf
        sprintf(write, "%s, Process: %d, mem allocate request (%d, %d)",
                timeStr, pid, op->intArg2, op->intArg3);

        // output the message
        // function: output
        output(write, configPtr);

        // attempt to allocate memory and check if successful
        if (allocateMemory(memoryManager, pid, op->intArg2, op->intArg3, maxMemory))
        {
            // format success message
            // function: sprintf
            sprintf(write, "%s, Process: %d, mem allocate success (%d, %d)",
                    timeStr, pid, op->intArg2, op->intArg3);

            // output success message
            // function: output
            output(write, configPtr);
        }
        // else allocation failed
        else
        {
            // format failure message
            // function: sprintf
            sprintf(write, "%s, Process: %d, mem allocate failure (%d, %d)",
                    timeStr, pid, op->intArg2, op->intArg3);

            // output failure message
            // function: output
            output(write, configPtr);
        }
    }

    // check if operation is memory access
    else if (compareString(op->strArg1, "access") == STR_EQ)
    {
        // format the message
        // function: sprintf
        sprintf(write, "%s, Process: %d, mem access request (%d, %d)",
                timeStr, pid, op->intArg2, op->intArg3);

        // output the message
        // function: output
        output(write, configPtr);

        // attempt to access memory and check if successful
        if (ProcessAccess(memoryManager, pid, op->intArg2, op->intArg3, maxMemory))
        {
            // format success message
            // function: sprintf
            sprintf(write, "%s, Process: %d, mem access success (%d, %d)",
                    timeStr, pid, op->intArg2, op->intArg3);

            // output success message
            // function: output
            output(write, configPtr);
        }
        else
        {
            // format failure message
            // function: sprintf
            sprintf(write, "%s, Process: %d, mem access failure (%d, %d)",
                    timeStr, pid, op->intArg2, op->intArg3);

            // output failure message
            // function: output
            output(write, configPtr);
        }
    }
}

/*
Name: avaliableMemory
Process: returns the amount of avaliable memory
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: malloc
*/
void avaliableMemory(MemoryManager *memoryManager, ConfigDataType *config, int pid)
{
    // check if memory display is enabled
    if (!config->memDisplay ||
        !(config->logToCode == LOGTO_MONITOR_CODE || config->logToCode == LOGTO_BOTH_CODE))
        return;

    // initialize pointer for memory list
    MemoryData *current = memoryManager->head;
    // track end of previous memory block
    int prevEnd = -1;

    // iterate through all allocated memory blocks
    while (current != NULL)
    {
        // check if there is free memory between blocks
        if (current->MemoryBase > prevEnd + 1)
        {
            // print free memory
            // function: printf
            printf("%d [Open, P#: x, 0-0 ] %d\n", prevEnd + 1, current->MemoryBase - 1);
        }

        // Print used memory
        // function: printf
        printf("%d [Used, P#: %d, %d-%d ] %d\n",
               current->MemoryBase,
               current->pid,
               current->MemoryBase,
               current->MemoryBase + current->MemoryLimit - 1,
               current->MemoryLimit);

        // update prevEnd to end of current block
        prevEnd = current->MemoryBase + current->MemoryLimit - 1;
        // move to next block
        current = current->next;
    }

    // Print free memory after last used block
    if (prevEnd < config->memAvailable - 1)
    {
        // print remaining free memory
        //  function: printf
        printf("%d [Open, P#: x, 0-0 ] %d\n", prevEnd + 1, config->memAvailable - 1);
    }

    // print end of display
    // function: printf
    printf("-------------------------------------------------\n");
}

/*
Name: DisplayEnd
Process: displays the end of a process
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: printf
*/
void DisplayEnd(MemoryManager *memoryManager, ConfigDataType *config, int pid)
{
    if (config->logToCode == LOGTO_MONITOR_CODE ||
        config->logToCode == LOGTO_BOTH_CODE)
    {
        printf("--------------------------------------------------\n");
        printf("After clear process %d success\n", pid);
        avaliableMemory(memoryManager, config, 0);
    }
}

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
void runSim(ConfigDataType *configPtr, OpCodeType *metaDataMstrPrt)
{
    // memory variables
    MemoryManager memoryManager;
    memoryManager.head = NULL;

    // initialize process queue and count
    int processCount = 0;
    double currentTime = 0.0;

    // buffer to store the time string
    char timeStr[STR_ARG_LEN];

    PCB *readyQueue = NULL;
    PCB *blockedQueue = NULL;
    InterruptQueue interruptQueue = {NULL};

    // thread for io simulation
    pthread_t thread;

    // start timer
    // function: accessTimer
    accessTimer(ZERO_TIMER, timeStr);

    // print start message
    // function: systemMessage
    systemMessage(timeStr, "Simulator start", configPtr);

    // while metadata is not null
    while (metaDataMstrPrt != NULL)
    {
        // check for app startcommand
        if (compareString(metaDataMstrPrt->command, "app") == STR_EQ &&
            compareString(metaDataMstrPrt->strArg1, "start") == STR_EQ)
        {
            // create a new pcb with metadata after app start node
            PCB *newPCB = createPCB(processCount, metaDataMstrPrt->nextNode,
                                    configPtr);

            // calculate total time for the process
            newPCB->timeRemaining = findTime(metaDataMstrPrt->nextNode,
                                             configPtr);
            // add process to the queue
            addToQueue(newPCB, &readyQueue, &processCount);
            // write the state change from new to ready
            accessTimer(LAP_TIMER, timeStr);
            stateChange(timeStr, newPCB, "NEW", "READY", configPtr);
        }
        // move to the next node
        metaDataMstrPrt = metaDataMstrPrt->nextNode;
    }
    if (configPtr->memDisplay &&
        (configPtr->logToCode == LOGTO_MONITOR_CODE ||
         configPtr->logToCode == LOGTO_BOTH_CODE))
    {
        printf("---------------------------------------------\n");
        printf("After memory initialization\n");
        avaliableMemory(&memoryManager, configPtr, 0);
    }
    // while the process queue is not empty
    PCB *currentPCB;
    while ((currentPCB = getProcessSched(configPtr, &readyQueue, &processCount)) != NULL)
    {
        // write process selection
        accessTimer(LAP_TIMER, timeStr);
        WriteOutput(timeStr, NULL, NULL, currentPCB, NULL, configPtr);

        // write the state change from ready to running
        // function: accessTimer, stateChange
        accessTimer(LAP_TIMER, timeStr);
        stateChange(timeStr, currentPCB, "READY", "RUNNING", configPtr);

        // print a blank line
        // function: printf
        printf("\n");

        // get the operatiion list for current process
        OpCodeType *currentOp = currentPCB->programCounter;

        // iterate through till app end
        while (currentOp != NULL && compareString(currentOp->command,
                                                  "app") != STR_EQ)
        {
            // skip memory op
            if (compareString(currentOp->command, "mem") == STR_EQ)
            {
                // write the operation start
                // function: accessTimer, WriteOperation
                accessTimer(LAP_TIMER, timeStr);
                // function: writeMemoryOutput
                writeMemoryOutput(timeStr, currentPCB->pid, currentOp, &memoryManager,
                                  configPtr->memAvailable, configPtr);
                // check if this is a memory allocate or access
                if (compareString(currentOp->strArg1, "allocate") == STR_EQ)
                {
                    // check if memory display is enabled and logging to monitor
                    if (configPtr->memDisplay &&
                        (configPtr->logToCode == LOGTO_MONITOR_CODE ||
                         configPtr->logToCode == LOGTO_BOTH_CODE))
                    {
                        // print a blank line
                        // function: printf
                        printf("---------------------------------------------\n");
                        // print message
                        // function: printf
                        printf("After allocate success\n");
                        // display current memory
                        //  function: avaliableMemory
                        avaliableMemory(&memoryManager, configPtr, currentPCB->pid);
                    }
                }
                // check if this is a memory access
                //  function: compareString
                else if (compareString(currentOp->strArg1, "access") == STR_EQ)
                {
                    // check if memory display is enabled and logging to monitor
                    if (configPtr->memDisplay &&
                        (configPtr->logToCode == LOGTO_MONITOR_CODE ||
                         configPtr->logToCode == LOGTO_BOTH_CODE))
                    {
                        // print a blank line
                        // function: printf
                        printf("---------------------------------------------\n");
                        // print message
                        // function: printf
                        printf("After access success\n");
                        // display current memory
                        //  function: avaliableMemory
                        avaliableMemory(&memoryManager, configPtr, currentPCB->pid);
                    }
                }
            }
            else
            {
                // write the operation start
                // function: accessTimer, WriteOperation
                accessTimer(LAP_TIMER, timeStr);
                WriteOutput(timeStr, &currentPCB->pid, currentOp,
                            NULL, "start", configPtr);
                // handle io using a thread
                if (compareString(currentOp->command, "dev") == STR_EQ)
                {
                    // thread arguments
                    ThreadArgs *threadArgs = malloc(sizeof(ThreadArgs));
                    threadArgs->operation = currentOp;
                    threadArgs->config = configPtr;
                    threadArgs->pid = currentPCB->pid;
                    threadArgs->timeStr = timeStr;

                    // create and wait for thread
                    pthread_create(&thread, NULL, runTimerforCycle, threadArgs);
                    pthread_join(thread, NULL);
                }
                else
                {
                    // simulate cpu time
                    runTimer(currentOp->intArg2 * configPtr->procCycleRate);
                }
                // log operation end
                accessTimer(LAP_TIMER, timeStr);
                WriteOutput(timeStr, &currentPCB->pid, currentOp,
                            NULL, "end", configPtr);
            }
            // move to next node
            currentOp = currentOp->nextNode;
        }
        // write the process end
        accessTimer(LAP_TIMER, timeStr);
        WriteOutput(timeStr, NULL, NULL, currentPCB, "end", configPtr);

        // Display memory state after clear
        DisplayEnd(&memoryManager, configPtr, currentPCB->pid);
        // free memory for this process
        freeProcess(&memoryManager, currentPCB->pid);
        // write the state change from running to exit
        stateChange(timeStr, currentPCB, "RUNNING", "EXIT", configPtr);

        // free the current pcb
        // function: free
        freeAll(&memoryManager);
    }
    // stop the timer
    accessTimer(STOP_TIMER, timeStr);

    // print end message
    systemMessage(timeStr, "Simulator stop", configPtr);
    systemMessage(timeStr, "Simulator end", configPtr);
}