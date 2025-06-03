import csv
import numpy as np
import matplotlib.pyplot as plt
import os

OPERATIONS = ["insert", "remove"]
SIZES = [100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000]
LF = [10, 25, 50, 75] #
divider = 1

results = {
    "MOD": {op: {lf: [] for lf in LF} for op in OPERATIONS},
    "FIB": {op: {lf: [] for lf in LF} for op in OPERATIONS},
    "BIT": {op: {lf: [] for lf in LF} for op in OPERATIONS},
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
                               ("BIT", "Bit mix", "#08962f")]:
        plt.plot(SIZES, results[func][operation][lf], label=label, marker='o', color=color)

    title = {"insert": "dodawania elementu", "remove": "usunięcia elementu"}[operation]
    plt.title(f"Porównanie operacji {title} dla Load factor = {lf}%")
    plt.xlabel("Rozmiar zbioru")
    plt.ylabel("Średni czas wykonania [ns]")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.legend()
    plt.savefig(f"plots/{operation}_{lf}.png")
    # plt.show()


def all(results, func, operation):
    plt.figure(figsize=(10, 6))
    colors = ['#fc0356', '#ffb300', '#0da1b9', '#7d3c98']

    for idx, lf in enumerate(LF):
        plt.plot(SIZES, results[func][operation][lf], label=f'LF = {lf}%', marker='o', color=colors[idx])

    title = {"insert": "dodawania elementu", "remove": "usunięcia elementu"}[operation]
    func_labels = {"MOD": "Funkcja oparta na operacji modulo", "FIB": "Haszowanie fibonacciego", "BIT": "Bit mix"}

    plt.title(f"{func_labels[func]} - operacja {title} dla różnych Load factor")
    plt.xlabel("Rozmiar zbioru")
    plt.ylabel("Średni czas wykonania [ns]")
    plt.grid(True, linestyle="--", linewidth=0.5)
    plt.legend()
    plt.savefig(f"plots/{func}_{operation}.png")
    # plt.show()

for operation in OPERATIONS:
    for lf in LF:
        loading_factor(results, operation, lf)

for func in ["MOD", "FIB", "BIT"]:
    for operation in OPERATIONS:
        all(results, func, operation)

########histograms########

def read_csv_data(file_path):
    bin_indices = []
    counts = []
    with open(file_path, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            bin_indices.append(int(row['bin_index']))
            counts.append(int(row['count']))
    return bin_indices, counts

def plot_distribution(csv_file, title, save_path=None):
    bin_indices, counts = read_csv_data(csv_file)

    plt.figure(figsize=(10, 5))
    plt.bar(bin_indices, counts, color='lightblue', edgecolor='black')
    plt.xlabel("Indeks")
    plt.ylabel("Ilość elementów")
    plt.title(title)
    plt.grid(axis='y', linestyle='--', alpha=0.7)

    if save_path:
        plt.savefig(save_path)
        plt.close()
        print(f"Saved plot to {save_path}")
    else:
        plt.show()

hash_types = {
    "DMOD": "funkcji haszującej modulo",
    "DFIB": "haszowania fibonacciego",
    "DBIT": "haszowania na przesunięciach bitowych",
}

# Output directory for saving plots
output_dir = "plots"
os.makedirs(output_dir, exist_ok=True)

SIZES2 = [100, 200, 500]

for size in SIZES2:
    for load_factor in LF:
        for prefix, hash_name in hash_types.items():
            csv_filename = f"histograms/{prefix}_{size}_filled_{load_factor}.csv"
            title = f"Histogram dla {hash_name} (rozmiar tablicy: {size}, wypełniona w {load_factor}%)"
            save_path = os.path.join(output_dir, f"{prefix}_{size}_filled_{load_factor}.png")

            # Check if file exists before plotting to avoid errors
            if os.path.exists(csv_filename):
                plot_distribution(csv_filename, title, save_path)
            else:
                print(f"Warning: File not found: {csv_filename}")
