
import matplotlib.pyplot as plt
import re

def parse_performance_data(file_path):
    data = {'SkipList': {}, 'Treap': {}, 'Red-Black Tree': {}}

    with open(file_path, 'r') as file:
        current_structure = None
        current_max_value = None
        current_operation = None
        for line in file:
            line = line.strip()
            if not line:
                continue
            if line.startswith('SkipList'):
                current_structure = 'SkipList'
            elif line.startswith('Treap'):
                current_structure = 'Treap'
            elif line.startswith('Red-Black Tree'):
                current_structure = 'Red-Black Tree'
            elif line.startswith('MaxValue'):
                max_value_str = re.search(r'\d+', line).group()
                current_max_value = int(max_value_str.replace(',', ''))
            elif line.startswith('Insertion'):
                current_operation = 'Insertion'
            elif line.startswith('Deletion'):
                current_operation = 'Deletion'
            elif line.startswith('Search'):
                current_operation = 'Search'
            else:
                elements, time_str = line.split(':')
                elements = int(re.search(r'(\d+(,\d+)*)', elements).group().replace(',', ''))
                time = float(time_str.strip())
                if current_max_value not in data[current_structure]:
                    data[current_structure][current_max_value] = {}
                if current_operation not in data[current_structure][current_max_value]:
                    data[current_structure][current_max_value][current_operation] = {'Elements': [], 'Time': []}
                data[current_structure][current_max_value][current_operation]['Elements'].append(elements)
                data[current_structure][current_max_value][current_operation]['Time'].append(time)

    return data


def draw(algo_data, algo_label, max_val):

    plt.plot(algo_data["Insertion"]["Elements"], algo_data["Insertion"]["Time"], marker='o', label="Insertion", color="purple")
    plt.plot(algo_data["Deletion"]["Elements"], algo_data["Deletion"]["Time"], marker='o', label="Deletion", color="red")
    plt.plot(algo_data["Search"]["Elements"], algo_data["Search"]["Time"], marker='o', label="Search", color="blue")

    plt.title(f'{algo_label} Performance on max value {max_val}')
    plt.xlabel('Size of Array (N)')
    plt.ylabel('Execution Time (seconds)')
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'{algo_label} at {max_val}.png')
    plt.show()

file_path = 'data.txt'
performance_data = parse_performance_data(file_path)
print(performance_data)

for key in performance_data:
    for max_val in performance_data[key]:
        draw(performance_data[key][max_val], key, max_val)