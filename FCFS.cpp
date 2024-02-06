#include <iostream>
#include <vector>
using namespace std;

struct Process
{
    int pid;            // Process ID
    int arrivalTime;    // Arrival time
    int burstTime;      // Burst time
    int waitingTime;    // Waiting time
    int completionTime; // Completion time
    int turnAroundTime; // Turnaround time
};


int main()
{
    int size;
    int current_time = 0; // Initialize current_time
    double total_turnaround_time = 0;
    double total_waiting_time = 0;
    double total_burst_time = 0;

    cout << "How many processes?: ";
    cin >> size;

    vector<Process> proc(size);

    for (int i = 0; i < size; i++)
    {
        proc[i].pid = i + 1;
        cout << "P[" << i + 1 << "] Arrival Time: ";
        cin >> proc[i].arrivalTime;
        cout << "P[" << i + 1 << "] Burst Time: ";
        cin >> proc[i].burstTime;
        total_burst_time += proc[i].burstTime;
    }

    for (int j = 0; j < size - 1; j++)
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (proc[i].arrivalTime > proc[i + 1].arrivalTime)
            {
                swap(proc[i], proc[i + 1]);
            }
        }
    }

    // Calculate completion time, turnaround time, and waiting time
    for (int i = 0; i < size; i++)
    {
        proc[i].completionTime = max(current_time, proc[i].arrivalTime) + proc[i].burstTime;
        proc[i].turnAroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnAroundTime - proc[i].burstTime;
        current_time = proc[i].completionTime;

        total_turnaround_time += proc[i].turnAroundTime;
        total_waiting_time += proc[i].waitingTime;
    }

    // Output table
    cout << "Process\t\tArrival Time\t Burst Time\t Completion Time\t Turn Around Time\t Waiting Time" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "P[" << proc[i].pid << "]\t\t" << proc[i].arrivalTime << "\t\t " << proc[i].burstTime << "\t\t " << proc[i].completionTime << "\t\t\t " << proc[i].turnAroundTime << "\t\t\t " << proc[i].waitingTime << endl;
    }

    // Calculate averages
    double avg_turnaround_time = total_turnaround_time / size;
    double avg_waiting_time = total_waiting_time / size;
    double cpu_utilization = total_burst_time / current_time;

    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "CPU Utilization: " << cpu_utilization << endl;

    return 0;
}