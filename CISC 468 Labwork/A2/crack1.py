import math
import time

n = 0x1e6f1558fe63761406be065a9e07b060f8360b2725b09f4071
start = int(math.sqrt(n)-1)
start_time = time.time()

for i in range(start,0,-2):
	if (n%i == 0):
		print("Found one!")
		print(i)
		break

end_time = time.time()
elapsed = end_time - start_time
print(f"Done in {elapsed:.6f} seconds")


