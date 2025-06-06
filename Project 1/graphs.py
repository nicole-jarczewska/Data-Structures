import csv
import numpy as np
import matplotlib.pyplot as plt

DT_results = {
    "add_front": [],
    "add_back": [],
    "append_index": [],
    "delete_first": [],
    "delete_last": [],
    "delete_index": [],
    "find_value": []
}

LL_results = {
    "add_front": [],
    "add_back": [],
    "append_index": [],
    "delete_first": [],
    "delete_last": [],
    "delete_index": [],
    "find_value": []
}

OPERATIONS = list(DT_results.keys())


SIZES = [10000, 50000, 100000, 500000, 1000000, 2000000, 5000000]

for operation in OPERATIONS:
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

for operation in OPERATIONS:
    for size in SIZES:
        total_time = 0
        filename = f"results/LL_{operation}_{size}.csv"

        try:
            with open(filename) as csvfile:
                reader = csv.reader(csvfile)
                next(reader) 

                for row in reader:
                    if row:
                        total_time += float(row[0])
        except FileNotFoundError:
            print(f"File not found: {filename}")
            LL_results[operation].append(None)
            continue

        mean_time = total_time / 100 
        LL_results[operation].append(mean_time)

def plot_comparison_for_operation(DT_results, LL_results, operation, SIZES):
    TITLES = {
    "add_front": "dodawania elementu na początku",
    "add_back": "dodawania elementu na końcu",
    "append_index": "dodawania elementu na wybranym indeksie",
    "delete_first": "usunięcia pierwszego elementu",
    "delete_last": "usunięcia ostatniego elementu",
    "delete_index": "usunięcia elementu z wybranego indeksu",
    "find_value": "wyszukania elementu"}

    plt.figure(figsize=(10, 6))

    dt_times = DT_results.get(operation, [])
    ll_times = LL_results.get(operation, [])
    

    if not dt_times or not ll_times:
        return  
    
    plt.plot(SIZES, dt_times, label=f'Tablica dynamiczna', marker='o', color='#fc0356')
    
    plt.plot(SIZES, ll_times, label=f'Lista wiązana', marker='o', color='#0318fc')
    

    title = TITLES.get(operation, operation)

    plt.title(f'Porównanie operacji {title} ')
    plt.xlabel('Rozmiar zbioru')
    plt.ylabel('Średni czas wykonania [ns]')
    plt.xscale("log")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)

    plt.legend()
    plt.grid(True)
    
    plt.show()


for operation in OPERATIONS:
    plot_comparison_for_operation(DT_results, LL_results, operation, SIZES)