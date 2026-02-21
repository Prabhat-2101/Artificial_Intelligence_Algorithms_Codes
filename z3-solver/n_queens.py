"""
-N-Queens Problem solved using Z3 (Constraint Satisfaction Problem)

This program models and solves the classic N-Queens puzzle using the Z3 SMT solver.

Problem Description:
--------------------
Place N queens on an N×N chessboard such that:
1. No two queens share the same row.
2. No two queens share the same column.
3. No two queens share the same diagonal.

Modeling Strategy:
------------------
- We use one integer variable per column.
- Q[i] represents the row position (1–N) of the queen placed in column i.
- Since each variable represents a unique column, column conflicts are inherently avoided.
- Row and diagonal constraints are explicitly enforced.

Constraint Programming Approach:
---------------------------------
This is formulated as a CSP (Constraint Satisfaction Problem):
- Variables: Q[0] ... Q[N-1]
- Domains: {1, 2, ..., N}
- Constraints:
    * AllDifferent(Q)  → no same row
    * Diagonal constraints → no diagonal attacks
"""

from z3 import *

n = 4  # Number of queens (and board size)

# Q[i] represents the row position of the queen in column i
Q = [Int(f'x_{i}') for i in range(n)]

# Initialize Z3 solver
s = Solver()

# ----------------------------
# Domain Constraints
# ----------------------------
# Each queen must be placed in a valid row (1 through N)
for i in range(n):
    s.add(Q[i] >= 1)
    s.add(Q[i] <= n)

# ----------------------------
# Constraint Definitions
# ----------------------------
for i in range(n):
    for j in range(i + 1, n):

        # Row constraint: Ensure no two queens are placed in the same row
        s.add(Q[i] != Q[j])

        # Diagonal constraints:
        # Two queens are on the same diagonal if: |Q[i] - Q[j]| == |i - j|
        s.add(Q[i] - Q[j] != i - j)
        s.add(Q[i] - Q[j] != j - i)

# ----------------------------
# Solve and Output
# ----------------------------
solution_count = 0

# Enumerate all solutions
while s.check() == sat:
    model = s.model()
    solution_count += 1

    # Extract solution
    solution = [model[Q[i]].as_long() for i in range(n)]
    print(f"Solution {solution_count}: {solution}")

    # Add blocking clause to avoid same solution again
    s.add(Or([Q[i] != solution[i] for i in range(n)]))

print(f"\nTotal solutions found: {solution_count}")
