import tkinter as tk
from tkinter import ttk, messagebox
import subprocess

# ------------------ GUI SETUP ------------------ #
root = tk.Tk()
root.title("CPU Scheduling Simulator")
root.geometry("800x600")

# Label for instructions
tk.Label(root, text="Enter processes in format: PID Arrival Burst [Priority] (one per line)").pack(pady=10)

# Text box for process input
input_text = tk.Text(root, height=10, width=80)
input_text.pack()

# Dropdown for algorithm selection
tk.Label(root, text="Choose Scheduling Algorithm").pack(pady=10)
algo_var = tk.StringVar()
algo_menu = ttk.Combobox(root, textvariable=algo_var, values=[
    "FCFS", "SJF", "SRTF", "Round Robin", "Priority"
])
algo_menu.pack()
algo_menu.current(0)

# Function to run the simulation
def run_simulation():
    algo = algo_var.get()
    input_data = input_text.get("1.0", tk.END).strip()
    
    if not input_data:
        messagebox.showwarning("Input Missing", "Please enter process details.")
        return

    # Write input.txt file
    with open("input.txt", "w") as f:
        f.write(f"ALGO: {algo}\n")
        f.write(input_data)

    try:
        # Run the C++ executable
        subprocess.run(["scheduler/scheduler_sim.exe"], check=True)
    except Exception as e:
        messagebox.showerror("Execution Error", f"Error running C++ executable:\n{e}")
        return

    # Read and display output.txt
    try:
        with open("output.txt", "r") as f:
            output = f.read()
        output_box.delete("1.0", tk.END)
        output_box.insert(tk.END, output)
    except:
        messagebox.showerror("Error", "Failed to read output.txt.")

# Button to simulate
tk.Button(root, text="Simulate", command=run_simulation).pack(pady=20)

# Output label and box
tk.Label(root, text="Simulation Output").pack()
output_box = tk.Text(root, height=15, width=80, bg="#f0f0f0")
output_box.pack()

# Start the app
root.mainloop()
