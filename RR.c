#include <stdio.h>

struct pcb {
    int pid, at, bt, ct, wt, tat, isc, remaining;
};

typedef struct pcb PCB;
PCB temp;
int n,tq,currentpro,timeline=0,completedp=0,x=0;
float total_WT = 0, total_TAT = 0;

void RoundRobin(PCB p[]){
    int i,j;
    while(completedp != n){
        for(i=0;i<n;i++){
            if(!p[i].isc){
                currentpro = i;
                while(p[currentpro].remaining > 0 && x < tq){
                    p[currentpro].remaining--;
                    timeline++;
                    x++;
                }
                x=0;
                if(p[currentpro].remaining == 0){
                    p[currentpro].isc = 1;
                    completedp++;
                    p[currentpro].ct = timeline;
                    p[currentpro].tat = p[currentpro].ct - p[currentpro].at;
                    p[currentpro].wt = p[currentpro].tat - p[currentpro].bt;
                    total_WT += p[currentpro].wt;
                    total_TAT += p[currentpro].tat;
                }
            }
        }
    }
}


void Display(PCB p[]){
    printf("\nPID\tAT\tBT\tWT\tTAT\tCT\n");
    for(int i = 0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].wt,p[i].tat,p[i].ct);
    }
    printf("Avg WT: %0.2f\n", (float)((total_WT)/n));
    printf("Avg TAT: %0.2f", (float)((total_TAT)/n));
}

void main(){

    int i,j;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    PCB p[n];
    printf("Enter time quantum: ");
    scanf("%d",&tq);
    for(i=0;i<n;i++){
        printf("Enter the burst time and arrival time of process %d: ",i+1);
        p[i].pid = i+1;
        scanf("%d%d",&p[i].bt,&p[i].at);
        p[i].remaining = p[i].bt;
        p[i].isc = 0;
    }
    //sorting acc to arrival time
    for(i=0; i<n; i++){
        for(j=i+1; j<n; j++){
            if(p[i].at > p[j].at){
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    RoundRobin(p);
    Display(p);
}
