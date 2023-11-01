import numpy as np
from numba import njit

@njit
def go(path, value, room, estimate, estimate_all, item_count, picks, values, weights):
    max_value = 0
    stack = [(np.delete(path, 0), value, room, estimate)]

    while stack:
        path, value, room, estimate = stack.pop()

        if len(path) == item_count:
            if value > max_value:
                max_value = value
                result_path = path
                result_value = value
                estimate_all = max(value, estimate_all)
            continue

        item_index = len(path)
        item_value = values[item_index]
        item_weight = weights[item_index]
        item_pick = picks[item_index]

        _estimate = estimate

        if room - item_weight >= 0:
            new_path = np.append(path, 1)  # Append 1 to indicate the item is picked
            stack.append((new_path, value + item_value, room - item_weight, estimate))

        if item_pick == 1:
            _estimate -= item_value

        if _estimate >= estimate_all:
            new_path = np.append(path, 0)  # Append 0 to indicate the item is not picked
            stack.append((new_path, value, room, _estimate))

    return result_path, result_value

def solve_it(input_data):
    lines = input_data.split('\n')
    first_line = lines[0].split()
    item_count = int(first_line[0])
    capacity = int(first_line[1])

    values = np.zeros(item_count, dtype=np.int32)
    weights = np.zeros(item_count, dtype=np.int32)
    picks = np.zeros(item_count, dtype=np.int32)

    for i in range(1, item_count + 1):
        line = lines[i]
        parts = line.split()
        values[i - 1] = int(parts[0])
        weights[i - 1] = int(parts[1])

    max_estimate = 0
    left_room = capacity

    print(values, weights)

    while left_room > 0:
        available_items = np.where((weights <= left_room) & (picks == 0))[0]
        if len(available_items) == 0:
            break

        value_densities = values[available_items] / weights[available_items]
        max_value_density_index = np.argmax(value_densities)
        max_value_density_item = available_items[max_value_density_index]

        if weights[max_value_density_item] <= left_room:
            left_room -= weights[max_value_density_item]
            picks[max_value_density_item] = 1
            max_estimate += values[max_value_density_item]
        else:
            max_estimate += value_densities[max_value_density_index] * left_room
            left_room = 0

    value = 0
    taken = np.zeros(item_count, dtype=np.int32)
    estimate_all = 0

    result_path, result_value = go(np.array([0], dtype=np.int64), value, capacity, max_estimate, estimate_all, item_count, picks, values, weights)

    value = result_value
    taken = result_path

    output_data = str(value) + ' ' + str(0) + '\n'
    output_data += ' '.join(map(str, taken))
    return output_data

if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        file_location = sys.argv[1].strip()
        with open(file_location, 'r') as input_data_file:
            input_data = input_data_file.read()
        print(solve_it(input_data))
    else:
        print('This test requires an input file.  Please select one from the data directory. (i.e. python solver.py ./data/ks_4_0)')