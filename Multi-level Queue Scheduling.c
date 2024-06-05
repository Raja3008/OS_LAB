#include <stdio.h>

void calculateTimes(int n, int at[], int bt[], int ct[], int tat[], int wt[]) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < at[i]) {
            currentTime = at[i];
        }
        ct[i] = currentTime + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        currentTime = ct[i];
    }
}

void printProcesses(int n, int pid[], int at[], int bt[], int ct[], int tat[], int wt[]) {
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int sysPid[n], sysat[n], sysbt[n], sysct[n], systat[n], syswt[n];
    int usrPid[n], usrat[n], usrbt[n], usrct[n], usrtat[n], usrwt[n];
    int sysCount = 0, usrCount = 0;

    for (int i = 0; i < n; i++) {
        int type, pid = i + 1, at, bt;

        printf("Enter Arrival time for process %d: ", pid);
        scanf("%d", &at);

        printf("Enter burst time for process %d: ", pid);
        scanf("%d", &bt);

        printf("Enter 1 if process %d is a system process, 2 if user process: ", pid);
        scanf("%d", &type);

        if (type == 1) {
            sysPid[sysCount] = pid;
            sysat[sysCount] = at;
            sysbt[sysCount] = bt;
            sysCount++;
        } else {
            usrPid[usrCount] = pid;
            usrat[usrCount] = at;
            usrbt[usrCount] = bt;
            usrCount++;
        }
    }

    for (int i = 0; i < sysCount - 1; i++) {
        for (int j = i + 1; j < sysCount; j++) {
            if (sysat[i] > sysat[j]) {
                int temp;

                temp = sysPid[i];
                sysPid[i] = sysPid[j];
                sysPid[j] = temp;

                temp = sysat[i];
                sysat[i] = sysat[j];
                sysat[j] = temp;

                temp = sysbt[i];
                sysbt[i] = sysbt[j];
                sysbt[j] = temp;
            }
        }
    }

    for (int i = 0; i < usrCount - 1; i++) {
        for (int j = i + 1; j < usrCount; j++) {
            if (usrat[i] > usrat[j]) {
                int temp;

                temp = usrPid[i];
                usrPid[i] = usrPid[j];
                usrPid[j] = temp;

                temp = usrat[i];
                usrat[i] = usrat[j];
                usrat[j] = temp;

                temp = usrbt[i];
                usrbt[i] = usrbt[j];
                usrbt[j] = temp;
            }
        }
    }

    printf("\nSystem Processes:\n");
    calculateTimes(sysCount, sysat, sysbt, sysct, systat, syswt);
    printProcesses(sysCount, sysPid, sysat, sysbt, sysct, systat, syswt);

    printf("\nUser Processes:\n");
    calculateTimes(usrCount, usrat, usrbt, usrct, usrtat, usrwt);
    printProcesses(usrCount, usrPid, usrat, usrbt, usrct, usrtat, usrwt);

    return 0;
}

