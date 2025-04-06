import csv
import numpy as np
import matplotlib.pyplot as plt

addFront = []
addBack = []
removeFront = []
removeBack = []
contains = []

OPERATIONS = ["addFront", "addBack", "removeFront", "removeBack"]
SIZES = [1000, 10000, 50000, 100000, 500000, 1000000]


for operation in OPERATIONS:
    for size in SIZES:
        total_time = 0
        filename = f"results/{operation}_{size}.csv"
        
        with open(filename) as csvfile:
            spamreader = csv.reader(csvfile, delimiter=';', quotechar='|')
            
            for row in spamreader:
                total_time += float(row[0])


        mean_time = total_time / 100  
        if operation == "addFront":
            addFront.append(mean_time)
        elif operation == "addBack":
            addBack.append(mean_time)
        elif operation == "removeFront":
            removeFront.append(mean_time)
        elif operation == "removeBack":
            removeBack.append(mean_time)
        elif operation == "contains":
            contains.append(mean_time)



plt.figure(figsize=(10, 6))

plt.plot(SIZES, addFront, label="addFront", marker='o')
plt.plot(SIZES, addBack, label="addBack", marker='s')
plt.plot(SIZES, removeFront, label="removeFront", marker='^')
plt.plot(SIZES, removeBack, label="removeBack", marker='D')
plt.plot(SIZES, contains, label="contains", marker='x')

# Add titles and labels
plt.title('Mean Execution Time for Different Operations')
plt.xlabel('Size')
plt.ylabel('Mean Time (ms)')  # Adjust the unit if needed
plt.xscale('log')  # Optional: Use log scale for better visualization
plt.yscale('log')  # Optional: Use log scale for better visualization

# Add grid and legend
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()

# Show the plot
plt.tight_layout()
plt.show()