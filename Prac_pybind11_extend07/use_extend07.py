import extend7 as ext

# animal = ext.Animal()
# print(call_go(animal)) # Error! pure virtual

dog = ext.Dog()
print(ext.call_go(dog))

husky = ext.Husky()
print(ext.call_go(husky))

class Cat(ext.Animal):
    def go(self, n_times):
        return "meow! " * n_times


cat = Cat()
print(ext.call_go(cat))


class Dachshund(ext.Dog):
    def bark(self):
        return "yap!"


dach = Dachshund()
print(ext.call_go(dach))

class ShihTzu(ext.Dog):
    def bark(self):
        return "yip!"

shih = ShihTzu()
print(ext.call_go(shih))
