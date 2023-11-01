class Item:
  def __init__(self, index, value, weight, pick):
      self.index = index
      self.value = value
      self.weight = weight
      self.pick = pick

  def update_pick(self, new_pick):
      self.pick = new_pick

  def print(self):
      print("index", self.index, "value", self.value, "weight", self.weight, "pick", self.pick)

path = [0, 1, 2]
items = [
    {'index': 2},
    {'index': 0},
    {'index': 1}
]

def sort_path_by_item_index(path, items):
    item_indices = {item.index: index for index, item in enumerate(items)}
    sorted_path = sorted(path, key=lambda x: item_indices[x])
    return sorted_path

# 示例用法
path = [2, 0, 1]
items = [
    Item(index=2, value=10, weight=5, pick=0),
    Item(index=0, value=5, weight=2, pick=0),
    Item(index=1, value=8, weight=3, pick=0)
]

sorted_path = sort_path_by_item_index(path, items)
print(sorted_path)