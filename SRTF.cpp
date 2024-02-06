
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

// Structure to represent a process
struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

// Function to compare processes based on arrival time
bool compareArrivalTime(const Process &a, const Process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << endl;

    Process processes[n];

    // Input arrival time and burst time for each process
    cout << "Enter Arrival Time and Burst Time for each process:\n\n";
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << endl;
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> processes[i].burstTime;
        cout << endl;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Sort processes based on arrival time
    sort(processes, processes + n, compareArrivalTime);

    int currentTime = 0;
    int completedProcesses = 0;
    int total_idle_time = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    // Scheduling loop
    while (completedProcesses < n)
    {
        int shortestIndex = -1;
        int shortestTime = INT_MAX;

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestTime && processes[i].remainingTime > 0)
            {
                shortestIndex = i;
                shortestTime = processes[i].remainingTime;
            }
        }

        // If no process is available, increment the current time
        if (shortestIndex == -1)
        {
            total_idle_time++;
            currentTime++;
        }
        else
        {
            // Process found, update process information
            processes[shortestIndex].remainingTime--;
            currentTime++;

            if (processes[shortestIndex].remainingTime == 0)
            {
                // Process completed, update completion time and metrics

                processes[shortestIndex].completionTime = currentTime;
                processes[shortestIndex].turnaroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
                processes[shortestIndex].waitingTime = processes[shortestIndex].turnaroundTime - processes[shortestIndex].burstTime;

                // Update total metrics and display completion message

                total_turnaround_time += processes[shortestIndex].turnaroundTime;
                total_waiting_time += processes[shortestIndex].waitingTime;

                cout << "Process " << processes[shortestIndex].id << " completed at time " << currentTime << endl;
                completedProcesses++;
            }
        }
    }

    // Calculate cycle length, completion time, and arrival time metrics
    int max_completion_time = INT_MIN;
    int min_arrival_time = INT_MAX;
    int length_cycle;
    total_idle_time = 0;

    for (int i = 0; i < n; i++)
    {
        max_completion_time = max(max_completion_time, processes[i].completionTime);
        min_arrival_time = min(min_arrival_time, processes[i].arrivalTime);
    }
    length_cycle = max_completion_time - min_arrival_time;

    // Display process information
    cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
        cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t" << processes[i].burstTime << "\t\t" << processes[i].completionTime << "\t"
             << processes[i].turnaroundTime << "\t" << processes[i].waitingTime << endl;
    cout << endl;

    // Calculate and display average turnaround time, waiting time, and CPU utilization
    float cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    cout << "\nAverage Turn Around time= " << (float)total_turnaround_time / n;
    cout << "\nAverage Waiting Time= " << (float)total_waiting_time / n;
    cout << "\nCPU Utilization(Percentage)= " << cpu_utilization * 100;

    return 0;
}