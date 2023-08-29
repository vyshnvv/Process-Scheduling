// NON PREEMPTIVE PRIORITY SCHEDULING
// SMALLER INTEGER VALUE -> HIGHER PRIORITY
#include <stdio.h>
struct pcb {
    int pid, at, bt, ct, wt, tat, isc, prio;
};
typedef struct pcb PCB;
PCB temp;
int n, timeline = 0, highprio, completed=0;
float total_WT = 0, total_TAT = 0;

void CalcWTnCT(PCB p[]){
    int i,j;
    while(completed!=n){
        for(i=0; i<n; i++){
            if(!p[i].isc){
                highprio = i;
                for(j=0; j<n; j++){
                    if(((p[j].at<=timeline) && !p[j].isc && (p[j].prio < p[highprio].prio || (p[j].prio == p[highprio].prio && p[j].at < p[highprio].at)))){
                        highprio = j;
                    }
            }
            p[highprio].isc = 1;
            completed++;
            if(highprio == 0){
                p[highprio].wt = 0;
                p[highprio].ct = p[highprio].bt;
            }
            else{
                p[highprio].wt = timeline - p[highprio].at;
                p[highprio].ct = timeline + p[highprio].bt;
            }
            total_WT += p[highprio].wt;
            timeline += p[highprio].bt;
            }
        }
        
    }

}

void CalcTAT(PCB p[]){
    for(int i=0; i<n; i++){
        p[i].tat = p[i].bt + p[i].wt;
        total_TAT += p[i].tat;
    }
}

void Display(PCB p[]){
    printf("\nPID\tAT\tBT\tWT\tTAT\tCT\tPrio\n");
    for(int i = 0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].wt,p[i].tat,p[i].ct,p[i].prio);
    }
    printf("Avg WT: %0.2f\n", (float)((total_WT)/n));
    printf("Avg TAT: %0.2f", (float)((total_TAT)/n));
}


void main(){
    int i,j;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    PCB p[n];
    for(i=0;i<n;i++){
        printf("Enter the burst time,arrival time and priority of process %d: ",i+1);
        p[i].pid = i+1;
        scanf("%d%d%d",&p[i].bt,&p[i].at,&p[i].prio);
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
    CalcWTnCT(p);
    CalcTAT(p);
    Display(p);
}
