import csv
import numpy as np
import matplotlib.pyplot as plt


DT_results = {
    "addFront": [],
    "addBack": [],
    "removeFront": [],
    "removeBack": [],
    "contains": []
}

DT_OPERATIONS = list(DT_results.keys())
SIZES = [10000, 50000, 100000, 500000, 1000000, 2000000, 5000000]

for operation in DT_OPERATIONS:
    for size in SIZES:
        total_time = 0
        filename = f"results/DT_{operation}_{size}.csv"

        with open(filename) as csvfile:
            reader = csv.reader(csvfile)

            for row in reader:
                if row: 
                    total_time += float(row[0])

        mean_time = total_time / 100 
        DT_results[operation].append(mean_time)

LL_results = {
    "add_front": [],
    "add_back": [],
    "delete_first": [],
    "delete_last": [],
    "find_value": []
}

LL_OPERATIONS = list(LL_results.keys())

for operation in LL_OPERATIONS:
    for size in SIZES:
        total_time = 0
        filename = f"results/LL_{operation}_{size}.csv"

        try:
            with open(filename) as csvfile:
                reader = csv.reader(csvfile)
                next(reader)  # Skip header

                for row in reader:
                    if row:
                        total_time += float(row[0])
        except FileNotFoundError:
            print(f"File not found: {filename}")
            LL_results[operation].append(None)  # Append None for missing data
            continue

        mean_time = total_time / 100  # Assuming 100 measurements
        LL_results[operation].append(mean_time)

print(LL_results)
print(DT_results)

def plot_comparison_for_operation(DT_results, LL_results, operation, SIZES):
    plt.figure(figsize=(10, 6))
    
    # Get times for the specific operation from both DT and LL results
    dt_times = DT_results.get(operation, [])
    ll_times = LL_results.get(operation, [])
    
    # Check if both DT and LL results contain data
    if not dt_times or not ll_times:
        print(f"Data missing for operation: {operation}")
        return  # Skip plotting if no data available
    
    # Plot for Dynamic Table (DT) if data is available
    plt.plot(SIZES, dt_times, label=f'DT_{operation}', marker='o')
    
    # Plot for Linked List (LL) if data is available
    plt.plot(SIZES, ll_times, label=f'LL_{operation}', marker='o')
    
    # Title and labels
    plt.title(f'Comparison of {operation} (DT vs LL)')
    plt.xlabel('Size')
    plt.ylabel('Average Time (ns)')
    
    # Add legend and grid
    plt.legend()
    plt.grid(True)
    
    # Show plot
    plt.show()


OPERATIONS = ["addFront", "addBack", "removeFront", "removeBack", "contains"]

# Plot comparisons for each operation
for operation in OPERATIONS:
    plot_comparison_for_operation(DT_results, LL_results, operation, SIZES)