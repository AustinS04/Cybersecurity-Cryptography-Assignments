import time
from sympy import factorint
n = 0x7c5cfe617c286a27ffc10ecf88a8d35ebbf1e30320af
start_time = time.time()
factors = factorint(n)
print(factors)
end_time = time.time()
elapsed = end_time - start_time
print(f"Done in {elapsed:.6f} seconds")

