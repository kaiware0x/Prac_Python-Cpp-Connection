import extend09 as ext
import copy
import pickle

vec = ext.Vector2(2.0, 3.0)
print(vec)

pic = ext.Pickleable("aaa")
print(pic.value())
print(pic.extra())

cp = ext.Copyable()
shallowcp = copy.copy(cp)
deepcp = copy.deepcopy(cp, {})
print(cp)
print(shallowcp)
print(deepcp)

