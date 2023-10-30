import extend3
# help(extend3)

dog1 = extend3.Dog("Molly")
print(dog1)
print(dog1.bark())

dog2 = extend3.pet_store()
print(dog2)
# print(dog2.bark()) # No attribute!

pdog = extend3.pet_store2()
print(pdog)
print(type(pdog))
print(pdog.bark())
