import extend6

# help(extend6)

c = extend6.MyClass()
print(c)

print(c.myFunction(extend6.SomeType(111)))

# print(extend6.f(3, 5)) # Error!
print(extend6.f(3, b=5))

print(extend6.floats_preferred(1.0))
print(extend6.floats_preferred(2))
print(extend6.floats_only(3.0))
# print(extend6.floats_only(4)) # Error!

dog = extend6.Dog()
print(extend6.bark(dog))
print(extend6.bark(None))

cat = extend6.Cat()
print(extend6.meow(cat))
# print(extend6.meow(None)) # Error!

extend6.set(1)
extend6.set("aaa")
extend6.setInt(2)
extend6.setString("bbb")
