#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

const int MAX_INT = numeric_limits<int>::max();
const int MIN_INT = numeric_limits<int>::min();

// Structure to represent a process
struct process_struct
{
    int pid;                     // Process ID
    int at;                      // Arrival Time
    int bt;                      // Burst Time
    int ct, wt, tat, start_time; // Completion Time, Waiting Time, Turnaround Time, Start Time
} ps[100];                       // Array to store process_struct for each process

int main()
{
    int n;
    bool is_completed[100] = {false}; // Array to track whether a process is completed or not
    int current_time = 0;             // Current time during scheduling
    int completed = 0;                // Number of completed processes
    cout << "Enter number of processes: ";
    cin >> n;
    int sum_tat = 0, sum_wt = 0, total_idle_time = 0, prev = 0, length_cycle;
    float cpu_utilization;
    int max_completion_time, min_arrival_time;

    // Set the output stream to display floating-point numbers in fixed-point notation with two digits after the decimal point.
    cout << fixed << setprecision(2);

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++)
    {
        ps[i].pid = i + 1;
        cout << "\nEnter Process " << i + 1 << " Arrival Time: ";
        cin >> ps[i].at;
        cout << "\nEnter Process " << i + 1 << " Burst Time: ";
        cin >> ps[i].bt;
    }

    // Scheduling loop
    while (completed != n)
    {
        int min_index = -1;
        int minimum = MAX_INT;

        // Find the process with the minimum burst time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && !is_completed[i])
            {
                if (ps[i].bt < minimum)
                {
                    minimum = ps[i].bt;
                    min_index = i;
                }
                if (ps[i].bt == minimum)
                {
                    if (ps[i].at < ps[min_index].at)
                    {
                        minimum = ps[i].bt;
                        min_index = i;
                    }
                }
            }
        }

        // If no process is available, increment the current time
        if (min_index == -1)
        {
            current_time++;
        }
        else
        {

            // Process found, update process information
            ps[min_index].start_time = current_time;
            ps[min_index].ct = ps[min_index].start_time + ps[min_index].bt;
            ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
            ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;

            // Update metrics and flags
            sum_tat += ps[min_index].tat;
            sum_wt += ps[min_index].wt;
            total_idle_time += (ps[min_index].start_time - prev);
            completed++;
            is_completed[min_index] = true;
            current_time = ps[min_index].ct;
            prev = current_time;
        }
    }

    // Calculate cycle length, completion time, and arrival time metrics
    max_completion_time = MIN_INT;
    min_arrival_time = MAX_INT;
    for (int i = 0; i < n; i++)
    {
        max_completion_time = max(max_completion_time, ps[i].ct);
        min_arrival_time = min(min_arrival_time, ps[i].at);
    }
    length_cycle = max_completion_time - min_arrival_time;

    // Sort processes based on arrival time for display
    sort(ps, ps + n, [](const process_struct &a, const process_struct &b)
         { return a.at < b.at; });

    // Display process information
    // Display process information
    cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
        cout << ps[i].pid << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << endl;
    cout << endl;

    // Calculate and display average turnaround time, waiting time, and CPU utilization
    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;
    cout << "\nCPU Utilization(Percentage)= " << cpu_utilization * 100;
    return 0;
}