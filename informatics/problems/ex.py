import json

file = open("items.json", "r", encoding="utf-8")
string = json.load(file)
unique = []
lst = []
for st in string:
    for elem in st["tags"]:
        if elem not in unique: unique.append(elem)
    if st["price"] > 1000:
        lst.append(st)

with open("expensive_items.json", "w", encoding="utf-8") as f:
    json.dump(lst, f, indent=4)
        

with open("report3.txt", "w") as f:
    for c in unique:
        f.write(c + "\n")