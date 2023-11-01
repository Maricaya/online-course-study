#!/usr/bin/python
# -*- coding: utf-8 -*-
from collections import namedtuple
Item = namedtuple("Item", ['index', 'value', 'weight', 'pick'])
from numba import njit

# class Item:
    # def __init__(self, index, value, weight, pick):
    #     self.index = index
    #     self.value = value
    #     self.weight = weight
    #     self.pick = pick

    # def update_pick(self, new_pick):
    #     self.pick = new_pick

    # def print(self):
    #     print("index", self.index, "value", self.value, "weight", self.weight, "pick", self.pick)


def sort_path_by_item_index(path, items):
    item_indices = {item.index: index for index, item in enumerate(items)}
    sorted_path = sorted(path, key=lambda x: item_indices[x])
    return sorted_path

def solve_it(input_data):

    # Modify this code to run your optimization algorithm

    # parse the input
    lines = input_data.split('\n')

    firstLine = lines[0].split()
    item_count = int(firstLine[0])
    capacity = int(firstLine[1])
    max_estimate = 0

    items = []

    for i in range(1, item_count+1):
        line = lines[i]
        parts = line.split()
        items.append(Item(i-1, int(parts[0]), int(parts[1]), 0))
        # max_estimate += int(parts[0])

    left_room = capacity

    while left_room>0:
        max_value_density = max(items, key=lambda x: x.value/x.weight if x.pick == 0 else 0)
        if max_value_density.weight <= left_room:
            left_room -=  max_value_density.weight
            # max_value_density.update_pick(1)
            max_value_density = max_value_density._replace(pick=1)
            max_estimate += max_value_density.value
        else:
            max_estimate += (max_value_density.value/max_value_density.weight) * left_room
            left_room = 0

    # 排序
    items.sort(key=lambda x: x.value / x.weight, reverse=True)

    value = 0
    taken = [0]*len(items)
    estimate_all = 0
    result = {}

    def go(path, value, room, estimate):
        nonlocal estimate_all
        nonlocal result
        max_value = 0
        stack = [(path, value, room, estimate)]

        while stack:
            path, value, room, estimate = stack.pop()

            if len(path) == len(items):
                if value > max_value:
                    max_value = value
                    # 计算 weight
                    result = {
                        "path": path,
                        "value": value,
                    }
                    estimate_all = max(value, estimate_all)
                continue

            item = items[len(path)]

            _estimate = estimate

            if room  - item.weight >= 0:
                stack.append((path + [1], value + item.value, room - item.weight, estimate))

            if item.pick == 1:
                _estimate -=  item.value

            # 这句再想想问题
            if _estimate >= estimate_all:
                # print("estimate_all", estimate_all)
                stack.append((path + [0], value, room, _estimate))

    go([], value, capacity, max_estimate)

    # max_result = max(result, key=lambda x: x['value'])
    value = result["value"]
    taken = sort_path_by_item_index(result["path"], items)

    # prepare the solution in the specified output format
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

