// Write a multithreaded program that implements the banker's algorithm. Create n threads that request and release resources from the bank. The banker will grant the request only if it leaves the system in a safe state. It is important that shared data be safe from concurrent access. To ensure safe access to shared data, you can use mutex locks.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

int nResources,
    nProcesses;
int *resources;
int **allocated;
int **maxRequired;
int **need;
int *safeSeq;

bool getSafeSeq() {
	// get safe sequence - use safeSeq[]
	return true;
}

void* processCode(void* arg) {
	// thread code
}

int main(int argc, char** argv) {
        printf("\nNumber of processes? ");
        scanf("%d", &nProcesses);

        printf("\nNumber of resources? ");
        scanf("%d", &nResources);

        resources = (int *)malloc(nResources * sizeof(*resources));
        printf("\nCurrently Available resources (R1 R2 ...)? ");
        for(int i=0; i<nResources; i++)
                scanf("%d", &resources[i]);

        allocated = (int **)malloc(nProcesses * sizeof(*allocated));
        for(int i=0; i<nProcesses; i++)
                allocated[i] = (int *)malloc(nResources * sizeof(**allocated));

        maxRequired = (int **)malloc(nProcesses * sizeof(*maxRequired));
        for(int i=0; i<nProcesses; i++)
                maxRequired[i] = (int *)malloc(nResources * sizeof(**maxRequired));

        // allocated
        printf("\n");
        for(int i=0; i<nProcesses; i++) {
                printf("\nResource allocated to process %d (R1 R2 ...)? ", i+1);
                for(int j=0; j<nResources; j++)
                        scanf("%d", &allocated[i][j]);
        }
        printf("\n");

	// maximum required resources
        for(int i=0; i<nProcesses; i++) {
                printf("\nMaximum resource required by process %d (R1 R2 ...)? ", i+1);
                for(int j=0; j<nResources; j++)
                        scanf("%d", &maxRequired[i][j]);
        }
        printf("\n");

	// calculate need matrix
        need = (int **)malloc(nProcesses * sizeof(*need));
        for(int i=0; i<nProcesses; i++)
                need[i] = (int *)malloc(nResources * sizeof(**need));

        for(int i=0; i<nProcesses; i++)
                for(int j=0; j<nResources; j++)
                        need[i][j] = maxRequired[i][j] - allocated[i][j];

	// get safe sequence
	safeSeq = (int *)malloc(nProcesses * sizeof(*safeSeq));
        for(int i=0; i<nProcesses; i++) safeSeq[i] = -1;

        if(!getSafeSeq()) {
                printf("\nUnsafe State! The processes leads the system to a unsafe state.\n\n");
                exit(-1);
        }

        printf("\n\nSafe Sequence Found : ");
        for(int i=0; i<nProcesses; i++) {
                printf("%-3d", safeSeq[i]+1);
        }
        printf("\nExecuting Processes...\n\n");
        sleep(1);
	
	// run threads
	pthread_t processes[nProcesses];
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        for(int i=0; i<nProcesses; i++)
                pthread_create(&processes[i], &attr, processCode, (void *)i);

        for(int i=0; i<nProcesses; i++)
                pthread_join(processes[i], NULL);

        printf("\nAll Processes Finished\n");	
	
	// free resources
        free(resources);
        for(int i=0; i<nProcesses; i++) {
                free(allocated[i]);
                free(maxRequired[i]);
		free(need[i]);
        }
        free(allocated);
        free(maxRequired);
	free(need);
        free(safeSeq);
}
