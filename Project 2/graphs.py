import csv
import numpy as np
import matplotlib.pyplot as plt

DT_results = {
    "add": [],
    "delete": [],
    "size": [],
    "peek": [],
    "modify": [],
}

LL_results = {
    "add": [],
    "delete": [],
    "size": [],
    "peek": [],
    "modify": [],
}

heap_results = {
    "add": [],
    "delete": [],
    "size": [],
    "peek": [],
    "modify": [],
}

OPERATIONS = list(DT_results.keys())
SIZES = [1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000] #
divider = 1000000

for operation in OPERATIONS:
    for size in SIZES:
        total_time = 0
        filename = f"results/DT_{operation}{size}.csv"

        with open(filename) as csvfile:
            reader = csv.reader(csvfile)

            for row in reader:
                if row: 
                    total_time += float(row[0])

        mean_time = total_time / 100 / divider
        DT_results[operation].append(mean_time)

for operation in OPERATIONS:
    for size in SIZES:
        total_time = 0
        filename = f"results/heap_{operation}{size}.csv"

        with open(filename) as csvfile:
            reader = csv.reader(csvfile)

            for row in reader:
                if row: 
                    total_time += float(row[0])

        mean_time = total_time / 100 / divider
        heap_results[operation].append(mean_time)

for operation in OPERATIONS:
    for size in SIZES:
        total_time = 0
        filename = f"results/LL_{operation}{size}.csv"

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

        mean_time = total_time / 100 / divider
        LL_results[operation].append(mean_time)

def plot_comparison_for_operation(LL_results, operation, SIZES):# DT_results,LL_results ,
    TITLES = {
    "add": "dodawania elementu",
    "delete": "usuniecia elementu",
    "size": "zwrócenia rozmiaru",
    "peek": "sprawdzenia kolejnego elementu do usunięcia",
    "modify": "modyfikacji priorytetu elementu",
    }

    plt.figure(figsize=(10, 6))

    # dt_times = DT_results.get(operation, [])
    ll_times = LL_results.get(operation, [])
    # heap_times = heap_results.get(operation, [])
    
    # plt.plot(SIZES, dt_times, label=f'Kolejka implementowana na tablicy dynamicznej', marker='o', color='#fc0356')
    
    plt.plot(SIZES, ll_times, label=f'Kolejka implementowana na liscie wiązanej', marker='o', color='#0318fc')

    # plt.plot(SIZES, heap_times, label=f'Kolejka implementowana na kopcu', marker='o', color='#08962f')
    

    title = TITLES.get(operation, operation)

    plt.title(f'Porównanie operacji {title} ')
    plt.xlabel('Rozmiar zbioru')
    plt.ylabel('Średni czas wykonania [ms]')
    #plt.xscale("log")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)

    plt.legend()
    plt.grid(True)
    
    plt.show()


for operation in OPERATIONS:
    plot_comparison_for_operation(LL_results, operation, SIZES) #, LL_results, heap_results