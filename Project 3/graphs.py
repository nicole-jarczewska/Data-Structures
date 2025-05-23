import csv
import numpy as np
import matplotlib.pyplot as plt

OPERATIONS = ["insert", "remove"]
SIZES = [10000, 20000, 50000, 100000, 200000, 500000, 1000000]
LF = [10, 25, 50, 75]
divider = 1000000

results = {
    "MOD": {op: {lf: [] for lf in LF} for op in OPERATIONS},
    "FIB": {op: {lf: [] for lf in LF} for op in OPERATIONS},
    "SQR": {op: {lf: [] for lf in LF} for op in OPERATIONS},
}


for func in results:
    for operation in OPERATIONS:
        for lf in LF:
            for size in SIZES:
                filename = f"results/{func}_{operation}{size}_{lf}%_average.csv"
                total_time = 0

                with open(filename) as csvfile:
                    reader = csv.reader(csvfile)
                    for row in reader:
                        if row:
                            total_time += float(row[0])

                mean_time = total_time / 100 / divider
                results[func][operation][lf].append(mean_time)


def loading_factor(results, operation, lf):
    plt.figure(figsize=(10, 6))
    for func, label, color in [("MOD", "Funkcja oparta na operacji modulo","#fc0356"),
                               ("FIB", "Haszowanie fibonacciego", "#0318fc"),
                               ("BIT", "Mid-square", "#08962f")]:
        plt.plot(SIZES, results[func][operation][lf], label=label, marker='o', color=color)

    title = {"insert": "dodawania elementu", "remove": "usunięcia elementu"}[operation]
    plt.title(f"Porównanie operacji {title} dla LF = {lf}%")
    plt.xlabel("Rozmiar zbioru")
    plt.ylabel("Średni czas wykonania [ms]")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.legend()
    plt.show()


def all(results, func, operation):
    plt.figure(figsize=(10, 6))
    colors = ['#fc0356', '#ffb300', '#0da1b9', '#7d3c98']

    for idx, lf in enumerate(LF):
        plt.plot(SIZES, results[func][operation][lf], label=f'LF = {lf}%', marker='o', color=colors[idx])

    title = {"insert": "dodawania elementu", "remove": "usunięcia elementu"}[operation]
    func_labels = {"MOD": "Funkcja oparta na operacji modulo", "FIB": "Haszowanie fibonacciego", "SQR": "Mid-Square"}

    plt.title(f"{func_labels[func]} - operacja {title} dla różnych LF")
    plt.xlabel("Rozmiar zbioru")
    plt.ylabel("Średni czas wykonania [ms]")
    plt.grid(True, linestyle="--", linewidth=0.5)
    plt.legend()
    plt.show()

for operation in OPERATIONS:
    for lf in LF:
        loading_factor(results, operation, lf)

# Show plots for all LFs for one structure
for func in ["MOD", "FIB", "BIT"]:
    for operation in OPERATIONS:
        all(results, func, operation)