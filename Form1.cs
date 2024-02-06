using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics; // For DllImport
namespace scheduling
{
    public partial class Form1 : Form
    {

         [DllImport("FCFS.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PerformFCFS(int size, Process[] proc);

        // Define your controls
        private DataGridView dataGridView;
        private TextBox processIdTextBox;
        private TextBox arrivalTimeTextBox;
        private TextBox burstTimeTextBox;
        private Button addButton;
        private DataGridView detailedDataGridView;
          private ComboBox schedulingMethodComboBox; // Declare it here


            public class Process
        {
            public int pid { get; set; } // Process ID
            public int arrivalTime { get; set; } // Arrival time
            public int burstTime { get; set; } // Burst time
            public int waitingTime { get; set; } // Waiting time
            public int completionTime { get; set; } // Completion time
            public int turnAroundTime { get; set; } // Turnaround time
        }

        public Form1()
        {
            InitializeComponent();

            InitializeControls();
        }

       private void InitializeControls()
{
    // Set window size
    this.Size = new System.Drawing.Size(1080, 600); // Set width to 800 and height to 600

    // Header label for CPU Scheduling Simulator
    Label headerLabel = new Label();
    headerLabel.Text = "CPU Scheduling Simulator";
    headerLabel.AutoSize = true;
    headerLabel.Font = new Font("Arial", 16, FontStyle.Bold);
    headerLabel.Location = new System.Drawing.Point(10, 10);
    this.Controls.Add(headerLabel);

    // Initialize the first DataGridView for adding processes
    dataGridView = new DataGridView();
    dataGridView.Location = new System.Drawing.Point(10, 50); // Adjusted Y position
    dataGridView.Size = new System.Drawing.Size(600, 150); // Set width to 600
    dataGridView.Columns.Add("ProcessID", "Process ID");
    dataGridView.Columns.Add("ArrivalTime", "Arrival Time");
    dataGridView.Columns.Add("BurstTime", "Burst Time");
    this.Controls.Add(dataGridView);

    // Initialize TextBoxes for process details
    processIdTextBox = new TextBox();
    processIdTextBox.Location = new System.Drawing.Point(10, 210); // Adjusted Y position
    processIdTextBox.Size = new System.Drawing.Size(100, 20);
    this.Controls.Add(processIdTextBox);

    arrivalTimeTextBox = new TextBox();
    arrivalTimeTextBox.Location = new System.Drawing.Point(130, 210); // Adjusted Y position
    arrivalTimeTextBox.Size = new System.Drawing.Size(100, 20);
    this.Controls.Add(arrivalTimeTextBox);

    burstTimeTextBox = new TextBox();
    burstTimeTextBox.Location = new System.Drawing.Point(250, 210); // Adjusted Y position
    burstTimeTextBox.Size = new System.Drawing.Size(100, 20);
    this.Controls.Add(burstTimeTextBox);

    // Initialize Button to add processes
    addButton = new Button();
    addButton.Text = "Add Process";
    addButton.Location = new System.Drawing.Point(370, 208); // Adjusted Y position
    addButton.Size = new System.Drawing.Size(100, 30); // Set height to 30
    addButton.Click += new EventHandler(AddProcessButton_Click);
    this.Controls.Add(addButton);

    // Add space between the "Add Process" button and the second DataGridView
    int spaceBetweenControls = 20;

      Button calculateButton = new Button();
            calculateButton.Text = "Calculate";
            calculateButton.Location = new System.Drawing.Point(620, 70 + spaceBetweenControls); // Adjusted Y position
            calculateButton.Size = new System.Drawing.Size(200, 30); // Set height to 30
            calculateButton.BackColor = System.Drawing.Color.Blue; // Set background color to blue
            calculateButton.Click += new EventHandler(CalculateButton_Click);
            this.Controls.Add(calculateButton);

    // GroupBox for displaying calculation results
GroupBox resultsGroupBox = new GroupBox();
resultsGroupBox.Text = "Calculation Results";
resultsGroupBox.Location = new System.Drawing.Point(620, 130 + spaceBetweenControls * 2); // Adjusted Y position
resultsGroupBox.Size = new System.Drawing.Size(250, 180); // Increase the size
this.Controls.Add(resultsGroupBox);

// Labels for results
Label averageTurnaroundLabel = new Label();
averageTurnaroundLabel.Text = "Average Turnaround Time:";
averageTurnaroundLabel.AutoSize = true;
averageTurnaroundLabel.Location = new System.Drawing.Point(20, 30); // Adjusted Y position
resultsGroupBox.Controls.Add(averageTurnaroundLabel);

Label averageWaitingLabel = new Label();
averageWaitingLabel.Text = "Average Waiting Time:";
averageWaitingLabel.AutoSize = true;
averageWaitingLabel.Location = new System.Drawing.Point(20, 80); // Adjusted Y position
resultsGroupBox.Controls.Add(averageWaitingLabel);

Label throughputLabel = new Label();
throughputLabel.Text = "Throughput:";
throughputLabel.AutoSize = true;
throughputLabel.Location = new System.Drawing.Point(20, 130); // Adjusted Y position
resultsGroupBox.Controls.Add(throughputLabel);

// Input fields for results
TextBox averageTurnaroundTextBox = new TextBox();
averageTurnaroundTextBox.Location = new System.Drawing.Point(20, 50); // Adjusted Y position
averageTurnaroundTextBox.Size = new System.Drawing.Size(210, 20); // Adjusted width
averageTurnaroundTextBox.Text = "0";
averageTurnaroundTextBox.ReadOnly = true;
resultsGroupBox.Controls.Add(averageTurnaroundTextBox);

TextBox averageWaitingTextBox = new TextBox();
averageWaitingTextBox.Location = new System.Drawing.Point(20, 100); // Adjusted Y position
averageWaitingTextBox.Size = new System.Drawing.Size(210, 20); // Adjusted width
averageWaitingTextBox.Text = "0";
averageWaitingTextBox.ReadOnly = true;
resultsGroupBox.Controls.Add(averageWaitingTextBox);

TextBox throughputTextBox = new TextBox();
throughputTextBox.Location = new System.Drawing.Point(20, 150); // Adjusted Y position
throughputTextBox.Size = new System.Drawing.Size(210, 20); // Adjusted width
throughputTextBox.Text = "0";
throughputTextBox.ReadOnly = true;

resultsGroupBox.Controls.Add(throughputTextBox);


    // Initialize the second DataGridView for detailed process information
    detailedDataGridView = new DataGridView();
    detailedDataGridView.Location = new System.Drawing.Point(10, 250 + spaceBetweenControls); // Adjusted Y position
    detailedDataGridView.Size = new System.Drawing.Size(600, 150); // Set width to 600
    detailedDataGridView.Columns.Add("ProcessID", "Process ID");
    detailedDataGridView.Columns.Add("ArrivalTime", "Arrival Time");
    detailedDataGridView.Columns.Add("BurstTime", "Burst Time");
    detailedDataGridView.Columns.Add("CompletedTime", "Completed Time");
    detailedDataGridView.Columns.Add("WaitingTime", "Waiting Time");
    detailedDataGridView.Columns.Add("TurnaroundTime", "Turnaround Time");
    this.Controls.Add(detailedDataGridView);

    // Label for the ComboBox
    Label schedulingMethodLabel = new Label();
    schedulingMethodLabel.Text = "Select Scheduling Method:";
    schedulingMethodLabel.AutoSize = true;
    schedulingMethodLabel.Location = new System.Drawing.Point(620, 50); // Adjusted Y position
    this.Controls.Add(schedulingMethodLabel);

    // ComboBox for selecting scheduling methods
      schedulingMethodComboBox = new ComboBox();
            schedulingMethodComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            schedulingMethodComboBox.Items.AddRange(new string[] { "First Come First Served", "Shortest Job First", "Shortest Remaining Time First" });
            schedulingMethodComboBox.Location = new System.Drawing.Point(620, 70); // Adjusted Y position
            schedulingMethodComboBox.Size = new System.Drawing.Size(200, 20);
            this.Controls.Add(schedulingMethodComboBox);
}


        private void AddProcessButton_Click(object sender, EventArgs e)
        {
            // Validate input
            int processId, arrivalTime, burstTime;
            if (!int.TryParse(processIdTextBox.Text, out processId) ||
                !int.TryParse(arrivalTimeTextBox.Text, out arrivalTime) ||
                !int.TryParse(burstTimeTextBox.Text, out burstTime))
            {
                MessageBox.Show("Invalid input. Please enter integers for Process ID, Arrival Time, and Burst Time.");
                return;
            }

            // Add process details to the first DataGridView
            dataGridView.Rows.Add(processId, arrivalTime, burstTime);

            // Clear TextBoxes
            processIdTextBox.Clear();
            arrivalTimeTextBox.Clear();
            burstTimeTextBox.Clear();
        }

private void CalculateButton_Click(object sender, EventArgs e)
{
    // Handle logic for calculating based on the selected scheduling method
   string selectedMethod = schedulingMethodComboBox.SelectedItem?.ToString();


    if (selectedMethod == null)
    {
        MessageBox.Show("Please select a scheduling method.");
        return;
    }

    if (selectedMethod == "First Come First Served")
    {
        // Prepare data structures to hold process details
        List<Process> processes = new List<Process>();

        // Read process details from the DataGridView
        foreach (DataGridViewRow row in dataGridView.Rows)
        {
            if (!row.IsNewRow)
            {
                Process process = new Process();
                process.pid = Convert.ToInt32(row.Cells["ProcessID"].Value);
                process.arrivalTime = Convert.ToInt32(row.Cells["ArrivalTime"].Value);
                process.burstTime = Convert.ToInt32(row.Cells["BurstTime"].Value);
                processes.Add(process);
            }
        }

     
        PerformFCFS(processes.Count, processes.ToArray());


    }
    else if (selectedMethod == "Shortest Job First")
    {
        // Implement Shortest Job First algorithm
    }
    else if (selectedMethod == "Shortest Remaining Time First")
    {
        // Implement Shortest Remaining Time First algorithm
    }
    else
    {
        MessageBox.Show("Invalid scheduling method selected.");
    }
}


                // Call the C++ FCFS algorithm
         
        
    }
}
