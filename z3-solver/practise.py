from z3 import *

# Step 1: Declare variables
x = Int('x')
y = Int('y')

# Step 2: Create solver
s = Solver()

# Step 3: Add constraints
s.add(x + y == 10)
s.add(x > 0)
s.add(y > 0)
s.add(x < y)

# Step 4: Check
if s.check() == sat:
    m = s.model()
    print("Solution found:")
    print("x =", m[x])
    print("y =", m[y])
else:
    print("No solution")