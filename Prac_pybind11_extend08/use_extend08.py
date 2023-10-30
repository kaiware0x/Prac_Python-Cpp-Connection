import extend08 as ext

e1 = ext.Example(1)
e1 = ext.Example(2, 3)
e1 = ext.Example(4.0)
e1 = ext.Example("5555")

e2 = ext.Example()

print(ext.Aggregate(2, "aaa"))

print(ext.MyPrivateClass())

ext.MyDangerClass()