from extend5 import Pet

p = Pet("aaa", Pet.Cat)
print(p)
print(p.type)
print(int(p.type))
print(Pet.Kind.__members__)
print(p.attr)
print(p.attr.age)
