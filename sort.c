
#include<stdlib.h>
#include<stdio.h>

#define max 100

typedef struct{
	int processNumber;
	int priority;
	int arrivalTime;
	int burstTime;
	int waitingTime;
	int turnAroundTime;
	int temp;
	int remainingTime;
}process;


process Process[max], TempProcess; 


void sort(int numberOfProcess){/* bubble sort struct */
	int i, index;

	for(i = 1; i < numberOfProcess; i++){
		for(index = 0; index < numberOfProcess - i; index++){
			if(Process[index].priority > Process[index+1].priority){
				TempProcess = Process[index];
				Process[index] = Process[index+1];
				Process[index+1] = TempProcess;
			}	
		}
	}
}