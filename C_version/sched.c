#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct core{
	struct process* p; // process currently running on this core
	int proc_time; // cumulative time 
	int busy;      // either 0 or 1
};

// virtual computer struct
struct computer
{
	struct core cores[4]; // 4 cores
	long time;   // milliseconds
};

// struct to store process information
struct process
{
	char * process_ID;
	int arrival_time;   // when this process arrives (e.g., being created)
	int service_time;  // the amount of time this process needs to run on a core to finish
	int io; // boolean io value 
};

struct node
{
	struct process* p; // the process pointed by this link
	struct node *next; // the pointer to the next link
};


//head for the processes queue
struct node* head;
//tail for the processes queue
struct node* tail;
//head for the arrival queue
struct node* pending_head;
//tail for the arrival queue
struct node* pending_tail;
int proc_num; //number of processes in the queue, waiting to be scheduled and not running
int quantum; // the amount of time in milliseconds a process can run on a core before being swapped out
//struct for computer
struct computer computer;


struct Queue{
	int size;
	struct node** head;
	struct node** tail;
};


struct Queue * initializeQueue(struct node ** head_val, struct node ** tail_val){
	struct Queue * pqueue = malloc(sizeof(struct Queue) + (sizeof(struct Node *))*2 + (sizeof(int) * 3) +
	                               (sizeof(char * )* 5 + (sizeof(struct process *))));
	pqueue->size = 0;
	pqueue->head = head_val;
	pqueue->tail = tail_val;
	return pqueue;
}

struct process * initializeProcess(char * process_id, int service, int arrival, int io){
	struct process * proc = malloc (sizeof(int)*3 + sizeof(struct process *) +
	                                sizeof(char * )* 50);
	proc->process_ID = malloc (sizeof(char * ) * 50);
	strcpy(proc->process_ID, process_id);
	proc->service_time = service;
	proc->arrival_time = arrival;
	proc->io = io;
	return proc;
}
int QueueSize(struct Queue *pqueue){
	return pqueue->size;
}

int IsQueueEmpty(struct Queue *pqueue){
	return ((pqueue->size)==0);
}

int headEmpty(){
	if ((head==NULL) && (tail==NULL)){
		return true;
	}
	return false;
}
void Enqueue(struct Queue *pqueue, char * process, int service, int arrival, int io){
	pqueue->size++;
	struct node * temp = malloc(sizeof(struct node * ) + (sizeof(struct process *) +
	                                                      sizeof(int) * 3 + sizeof(char * )* 50));
	temp->p = initializeProcess(process, service, arrival, io);
	if ((*pqueue->head)== NULL){
		temp->next = NULL;
		(*pqueue->head) = temp;
		(*pqueue->tail) = temp;
		return;
	}
	(*pqueue->tail)->next = temp;
	(*pqueue->tail) = temp;
	temp->next = NULL;
}


void Dequeue(struct Queue * pqueue){
	pqueue->size--;
	if (pqueue->size<0){
		pqueue->size=0;
	}
	if ((*pqueue->head) == NULL){
		return;
	}
	struct node * temp = *pqueue->head;
	*pqueue->head = (*(pqueue->head))->next;
	if ((*pqueue->head) == NULL){
		(*pqueue->tail) = NULL;
	}
//	free(temp->p->process_ID);
//	free(temp->p);
//  Pointer and ID free'd in remove_proc
	free(temp);
}

void display_queue(struct Queue * pqueue){
	struct node * curr = *(pqueue->head);
	struct node * temp;

	while(curr){
		printf("Process Id: %-3s, Service Time: %-2d Arrival Time: %-2d IO: %-2d\n", curr->p->process_ID,
		       curr->p->service_time, curr->p->arrival_time, curr->p->io);
		temp = curr;
		curr = curr->next;
	}
}


void read_file(struct Queue * PendingQueue)
{
	int i,i2;
	FILE* file = fopen("input.txt", "r");
	char line[90];
	char name[100];
	char service_time[3];
	char arrival_time[3];
	fgets(line, sizeof(line), file);
	//Queue Initialized Here
	while (fgets(line, sizeof(line), file)) {
		//printf("%s", line);
		i=0;
		while(line[i]!=' '&&i<90){name[i]=line[i];i++;}
		if(i>90)break;
		name[i]=0;
		i2=++i;
		while(line[i]!=' '&&i<90){service_time[i-i2]=line[i];i++;}
		if(i>90)break;
		service_time[i]=0;
		i2=++i;
		while(line[i]!=' '&&i<90){arrival_time[i-i2]=line[i];i++;}
		if(i>90)break;
		arrival_time[i]=0;
		printf("name: %s, service_time: %d, arrival_time: %d\n",name,atoi(service_time), atoi(arrival_time));

		Enqueue(PendingQueue, name, atoi(service_time), atoi(arrival_time), 0);
	}

	fclose(file);
	return;

}


//this function call simulates one millisecond of time on the computer
void run_one_step()
{
	int i;
	computer.time++;
	printf("Processing all 4 cores, current Computer time=%lu \n",computer.time);
	for(i=0;i<4;i++)
	{
		if(computer.cores[i].busy)
		{
			computer.cores[i].p->service_time--; 
			computer.cores[i].proc_time++;
			printf("Core[%d]: %s, service_time= %d,been on core for: %d \n",i,computer.cores[i].p->process_ID,computer.cores[i].p->service_time,computer.cores[i].proc_time);


			if(computer.cores[i].proc_time>quantum)
				printf("WARNING: Process on Core[%d] should not run longer than quantum\n",i);
			if(computer.cores[i].p->service_time<0)
				printf("WARNING: Process on core[%d] stayed longer than its service time.\n",i);
		}
	}
}


void run_one_step_p3()
{
	int rndm,i;
	computer.time++;
	printf("Processing all 4 cores, current Computer time=%lu \n",computer.time);
	for(i=0;i<4;i++)
	{
		if(computer.cores[i].busy)
		{
			if(computer.cores[i].p->io==1)
				printf("WARNING: Process on core[%d] has io trigerred, please remove from core, reset io signal and place it back in queue\n",i);
			if(computer.cores[i].p->io==0)
			{
				computer.cores[i].p->service_time--;
				rndm=rand()%10+1;
				if(rndm==10)computer.cores[i].p->io=1;
			}
			computer.cores[i].proc_time++;
			printf("Core[%d]: process %s, service_time= %d,been on core for: %d \n",i,computer.cores[i].p->process_ID,computer.cores[i].p->service_time,computer.cores[i].proc_time);


			if(computer.cores[i].proc_time>quantum)
				printf("WARNING: Process on Core[%d] should not run longer than quantum\n",i);
			if(computer.cores[i].p->service_time<0)
				printf("WARNING: Process on core[%d] stayed longer than its service time.\n",i);
		}
	}
}


void sched_proc(struct process*p,int core_id)
{
	if(computer.cores[core_id].busy==0)
	{
		printf("Process[%s] with service_time %d has been added to core %d\n",p->process_ID,p->service_time,core_id);
		computer.cores[core_id].busy=1;
		computer.cores[core_id].p=p;
		computer.cores[core_id].proc_time=0;
		proc_num --; //
	}
	else printf("ERROR: must call remove_proc to remove current process before adding another to the core.\n");
}
 
void remove_proc(int core_id)
{
	printf("Process[%s] at core %d has been removed from core with remaining service_time=%d\n",
	       computer.cores[core_id].p->process_ID,core_id,computer.cores[core_id].p->service_time);

	// if the process has finished all its service time, terminate and clean up
	if(computer.cores[core_id].p->service_time<=0)
	{
		computer.cores[core_id].busy=0;
		// free up allocated memory for process ID and struct upon termination of a process
		free(computer.cores[core_id].p->process_ID);
		free(computer.cores[core_id].p);
		computer.cores[core_id].proc_time=0;
	}
		// the process needs to run for more time, put it back into the queue for future scheduling
	else
	{
		computer.cores[core_id].proc_time=0;
		// reinsert back to the queue
		if(tail==NULL)
		{
			// in case queue is empty, i.e. all nodes struct were freed and there are no processes in the queue, this will become the first one
			tail=head=malloc(sizeof(struct node));
			head->p=computer.cores[core_id].p;
			head->next=NULL;
			proc_num++;
			computer.cores[core_id].busy=0;
		}
		else
		{

			tail->next = malloc(sizeof(struct node));
			tail=tail->next;
			tail->p=computer.cores[core_id].p;
			tail->next=NULL;
			proc_num++;
			computer.cores[core_id].busy=0;


		}

	}

}

// a demo running 4 processes until they're finished. The scheduling is done explicitly, not using
// a scheduling algorithm. 
void demo()
{
	int i;
	struct process *p0,*p1,*p2,*p3;
	p0=malloc(sizeof(struct process));
	p1=malloc(sizeof(struct process));
	p2=malloc(sizeof(struct process));
	p3=malloc(sizeof(struct process));

	p0->process_ID=malloc(sizeof(50));
	p1->process_ID=malloc(sizeof(50));
	p2->process_ID=malloc(sizeof(50));
	p3->process_ID=malloc(sizeof(50));

	strcpy(p0->process_ID,"first");
	strcpy(p1->process_ID,"Second");
	strcpy(p2->process_ID,"Third");
	strcpy(p3->process_ID,"Fourth");

	//assign arrival time
	p0->arrival_time=0;
	p1->arrival_time=0;
	p2->arrival_time=0;
	p3->arrival_time=0;

	//assign service time
	p0->service_time=16;
	p1->service_time=17;
	p2->service_time=19;
	p3->service_time=21;

	proc_num=4;


	//schedule process to each core
	sched_proc(p0,0);
	sched_proc(p1,1);
	sched_proc(p2,2);
	sched_proc(p3,3);

	for(i=0;i<16;i++)run_one_step();
	remove_proc(0);
	run_one_step();
	remove_proc(1);
	run_one_step();
	run_one_step();
	remove_proc(2);
	run_one_step();
	remove_proc(3);
	sched_proc(head->p,0);

	//NOTE: you must free struct node after scheduling the process. 

	//head==tail since it was the only one added now to remove it we just make pointer pointing to NULL
	head=NULL;
	tail=NULL;
	run_one_step();
	remove_proc(0);
	printf("DONE\n");
}

void init()
{
	quantum=20;
	head=tail=NULL;
	pending_head = pending_tail = NULL;
}

int IsComputerEmpty(){
	for (int i=0;i<4;i++){
		if (computer.cores[i].busy == 1 || proc_num > 0){
			return false;
		}
	}
	return true;
}

int main()
{
	struct Queue * PendingQueue = initializeQueue(&pending_head, &pending_tail);
	struct Queue * ProcessingQueue = initializeQueue(&head, &tail);
	init();
//	printf("\t*******Starting Demo*******\n");
//	demo();
	printf("\t*******Reading Input*******\n");
	read_file(PendingQueue);
	/* 
	 * handle memory allocation/deallocation properly so there's no leak
	 */
	int Dequeue_counter;
	struct node * pending_head_pointer;
	struct node * processing_head_pointer;
	while(1){
		pending_head_pointer = pending_head;
		while(pending_head_pointer){
			//Don't iterate for no reason
			if (pending_head_pointer->p->arrival_time > computer.time){
				break;
			}
			if (pending_head_pointer->p->arrival_time == computer.time){
				Enqueue(ProcessingQueue, pending_head_pointer->p->process_ID, pending_head_pointer->p->service_time,
				        pending_head_pointer->p->arrival_time, pending_head_pointer->p->io);
				//Clear Memory Leak Thanks valgrind
				free(pending_head->p->process_ID);
				free(pending_head->p);
				pending_head_pointer = (pending_head_pointer)->next;
				Dequeue(PendingQueue);
				continue;
			}
			pending_head_pointer = (pending_head_pointer)->next;
		}
		processing_head_pointer = head;
		Dequeue_counter = 0;
		while (processing_head_pointer){
			for (int x = 0; x < 4; x++){
				if (computer.cores[x].busy==0){
					sched_proc(processing_head_pointer->p, x);
					Dequeue_counter++;
					break;
				}
			}
			processing_head_pointer = (processing_head_pointer)->next;
		}
		for (int i=0;i<Dequeue_counter; i++){
			Dequeue(ProcessingQueue);
		}
		run_one_step();
		for (int x=0;x<4;x++){
			if (computer.cores[x].busy == 1){
				if (computer.cores[x].p->service_time==0){
					remove_proc(x);
					continue;
				}
				if (computer.cores[x].proc_time==quantum){
					remove_proc(x);
					continue;
				}
			}
		}
		if (IsComputerEmpty() && IsQueueEmpty(PendingQueue) && headEmpty()){
			free(PendingQueue);
			free(ProcessingQueue);
			break;
		}
	}


	computer.time = 0;
	init();
	Dequeue_counter = 0;
	PendingQueue = initializeQueue(&pending_head, &pending_tail);
	ProcessingQueue = initializeQueue(&head, &tail);
	read_file(PendingQueue);
	while(1){
		pending_head_pointer = pending_head;
		while(pending_head_pointer){
			//Don't iterate for no reason
			if (pending_head_pointer->p->arrival_time > computer.time){
				break;
			}
			if (pending_head_pointer->p->arrival_time == computer.time){
				Enqueue(ProcessingQueue, pending_head_pointer->p->process_ID, pending_head_pointer->p->service_time,
				        pending_head_pointer->p->arrival_time, pending_head_pointer->p->io);
				//Clear Memory Leak Thanks valgrind
				free(pending_head->p->process_ID);
				free(pending_head->p);
				pending_head_pointer = (pending_head_pointer)->next;
				Dequeue(PendingQueue);
				continue;
			}
			pending_head_pointer = (pending_head_pointer)->next;
		}
		processing_head_pointer = head;
		Dequeue_counter = 0;
		while (processing_head_pointer){
			for (int x = 0; x < 4; x++){
				if (computer.cores[x].busy==0){
					sched_proc(processing_head_pointer->p, x);
					Dequeue_counter++;
					break;
				}
			}
			processing_head_pointer = (processing_head_pointer)->next;
		}
		for (int i=0;i<Dequeue_counter; i++){
			Dequeue(ProcessingQueue);
		}
		run_one_step_p3();
		for (int x=0;x<4;x++){
			if (computer.cores[x].p != NULL){
				if (computer.cores[x].p->service_time==0){
					continue;
				}
				if (computer.cores[x].p->io == 1){
//					printf("\n IO tRIGGER  %s at %d left\n", computer.cores[x].p->process_ID, computer.cores[x].p->service_time);
					computer.cores[x].p->io = 0;
					computer.cores[x].proc_time=0;
					if(tail==NULL)
					{
						tail=head=malloc(sizeof(struct node));
						head->p=computer.cores[x].p;
						head->next=NULL;
						proc_num++;
						computer.cores[x].busy=0;
					}
					else
					{
						tail->next = malloc(sizeof(struct node));
						tail=tail->next;
						tail->p=computer.cores[x].p;
						tail->next=NULL;
						proc_num++;
						computer.cores[x].busy=0;
					}
			}
			}
		}
		for (int x=0;x<4;x++){
			if (computer.cores[x].busy == 1){
				if (computer.cores[x].p->service_time==0){
					remove_proc(x);
					continue;
				}
				if (computer.cores[x].proc_time==quantum){
					remove_proc(x);
					continue;
				}
			}
		}
		if (IsComputerEmpty() && IsQueueEmpty(PendingQueue) && headEmpty()){
			free(PendingQueue);
			free(ProcessingQueue);
			break;
		}
	}




 	printf("\t*******Done*******\n");
	return 0;
}
