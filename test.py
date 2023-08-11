from cpp_grad import Value

a = Value(-4.123)
b = Value(2.0)
c = a + b
c.backward()
print(c)

