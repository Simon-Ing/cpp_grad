from cpp_grad import Value

a = Value(1)
b = Value(2)
c = a + b
c.backward()
print(a)
print(b)
print(c)
