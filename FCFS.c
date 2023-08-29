#include <stdio.h>

struct pcb {
    int pid, at, bt, ct, wt, tat;
};

typedef struct pcb PCB;
PCB temp;
int n;
float total_WT = 0, total_TAT = 0;


void CalcWT(PCB p[]) {
    p[0].wt = 0;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i-1].ct - p[i].at;
        total_WT += p[i].wt;
    }
}


void CalcTAT(PCB p[]){
        for(int i = 0; i<n; i++){
                p[i].tat = p[i].bt + p[i].wt;
                total_TAT += p[i].tat;
        }
}

void CalcCT(PCB p[]){
        p[0].ct = p[0].bt;
        for(int i = 1; i<n; i++){
                p[i].ct = p[i-1].ct + p[i].bt;
        }
}

void Display(PCB p[]){
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i<n; i++){
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tat);
    }
    printf("Avg WT: %0.2f\t", (float)((total_WT)/n));
    printf("Avg TAT: %0.2f", (float)((total_TAT)/n));

}

void main(){

    int i,j;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    PCB p[n];
    for(i=0;i<n;i++){
        printf("Enter burst time and arrival time of process %d: ",i+1);
        p[i].pid = i+1;
        scanf("%d%d",&p[i].bt,&p[i].at);
    }
    //sorting acc to AT
    for(i=0; i<n; i++){
        for(j=i+1; j<n; j++){
            if(p[i].at > p[j].at){
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    CalcCT(p);
    CalcWT(p);
    CalcTAT(p);
    Display(p);
}