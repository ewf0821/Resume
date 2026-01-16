// header files

#include "simulator.h"

// global variables becuase i dont know how to do it without them
PCB *processQueue = NULL;
int processCount = 0;

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
void addToQueue(PCB *pcb)
{
    // if queue is empty
    if (processQueue == NULL)
    {
        // set queue to process
        processQueue = pcb;
    }
    // else
    else
    {
        // set temp to queue
        PCB *current = processQueue;
        // while temp has a next
        while (current->next)
            current = current->next;
        // set next to process
        current->next = pcb;
    }

    // increment process count
    processCount++;
}

/*
Name: getProcess
Process: Retrieves and removes the next process from the queue
Function Input/Parameters: none
Function Output/Parameters: none
Function Output/Returned: Pointer to next PCB in queue (PCB *)
Device Input/device: none
Device Output/device: none
Dependencies: none
*/
PCB *getProcess()
{
    // if queue is empty
    if (processQueue == NULL)
    {
        // return null
        return NULL;
    }

    // set temp to head
    PCB *nextProcess = processQueue;
    // set head to next
    processQueue = nextProcess->next;
    // set next to null
    nextProcess->next = NULL;
    // decrement process count
    processCount--;
    // return the pcb
    return nextProcess;
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
void freeQueue()
{
    // initalize variables
    // current head and temp next
    PCB *current = processQueue;
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
    processQueue = NULL;
    // set process count to 0
    processCount = 0;
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
void stateChange(char *timeStr, int pid, const char *oldState,
                 const char *newState, ConfigDataType *configPtr)
{
    // initialize variables
    char write[255];
    PCB *pcb = processQueue;

    // while the pcb is not null
    while (pcb != NULL)
    {
        // if pcb matches pid
        if (pcb->pid == pid)
        {
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
            // if new state is exit
            else if (compareString(newState, "EXIT") == STR_EQ)
            {
                // set state to exit
                pcb->state = EXIT_STATE;
            }
        }
        // set pcb to next in queue
        pcb = pcb->next;
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
    // else return
    else
    {
        // return
        return;
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
    // initialize process queue and count
    processQueue = NULL;
    processCount = 0;
    // buffer to store the time string
    char timeStr[STR_ARG_LEN];
    // thread for io simulation
    pthread_t thread;

    // start timer
    // function: accessTimer
    accessTimer(ZERO_TIMER, timeStr);

    // print start message
    // function: systemMessage
    systemMessage(timeStr, "Simulator start", configPtr);

    // force cpu scheduling to fcfs-n
    if (configPtr->cpuSchedCode != CPU_SCHED_FCFS_N_CODE)
    {
        // set to FCFS
        configPtr->cpuSchedCode = CPU_SCHED_FCFS_N_CODE;
    }

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
            addToQueue(newPCB);
            // write the state change from new to ready
            accessTimer(LAP_TIMER, timeStr);
            stateChange(timeStr, processCount, "NEW", "READY", configPtr);
        }
        // move to the next node
        metaDataMstrPrt = metaDataMstrPrt->nextNode;
    }
    // while the process queue is not empty
    PCB *currentPCB;
    while ((currentPCB = getProcess()) != NULL)
    {
        // write process selection
        accessTimer(LAP_TIMER, timeStr);
        WriteOutput(timeStr, NULL, NULL, currentPCB, NULL, configPtr);

        // write the state change from ready to running
        // function: accessTimer, stateChange
        accessTimer(LAP_TIMER, timeStr);
        stateChange(timeStr, currentPCB->pid, "READY", "RUNNING", configPtr);

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
            if (compareString(currentOp->command, "mem") != STR_EQ)
            {
                // write the operation start
                // function: accessTimer, WriteOperation
                accessTimer(LAP_TIMER, timeStr);
                WriteOutput(timeStr, &currentPCB->pid, currentOp, NULL,
                            "start", configPtr);

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
        // write the state change from running to exit
        stateChange(timeStr, currentPCB->pid, "RUNNING", "EXIT", configPtr);

        // free the current pcb
        // function: free
        free(currentPCB);
    }
    // stop the timer
    accessTimer(STOP_TIMER, timeStr);

    // print end message
    systemMessage(timeStr, "Simulator stop", configPtr);
    systemMessage(timeStr, "Simulator end", configPtr);
}