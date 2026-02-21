"""
0-1 Knapsack Problem using Z3 Optimize

Problem Description:
--------------------
We are given:
- n items
- Each item has a weight and a profit
- A knapsack with fixed capacity
- A constraint on how many items must be selected

Goal:
-----
Maximize total profit such that:
1. Total weight equals the knapsack capacity
2. Exactly `items_count` items are selected
3. Each item is either selected (1) or not selected (0)

This is modeled using Z3's Optimize() solver.
"""

from z3 import *

# -----------------------------
# Problem Data
# -----------------------------

n = 6  # Number of items

weights = [4, 8, 5, 6, 3, 7]     # Weight of each item
profits = [6, 12, 8, 7, 4, 11]   # Profit of each item

cap = 20           # Knapsack capacity
items_count = 4    # Exact number of items to select

# -----------------------------
# Decision Variables
# -----------------------------

# Boolean variable for each item:
# True  -> item is selected
# False -> item is not selected
i_bool = [Bool(f'i_{i+1}') for i in range(n)]

# -----------------------------
# Convert Boolean to Integer
# -----------------------------
# Z3 does not automatically treat Bool as 0/1.
# We convert:
#   True  -> 1
#   False -> 0
# using If(condition, 1, 0)

weight_term = []
profit_term = []

for i in range(n):
    weight_term.append(If(i_bool[i], weights[i], 0))
    profit_term.append(If(i_bool[i], profits[i], 0))

# -----------------------------
# Optimization Model
# -----------------------------

s = Optimize()

# Constraint 1:
# Exactly `items_count` items must be selected
s.add(Sum([If(b, 1, 0) for b in i_bool]) == items_count)

# Constraint 2:
# Total weight must equal knapsack capacity
s.add(Sum(weight_term) == cap)

# Objective:
# Maximize total profit
s.maximize(Sum(profit_term))

# -----------------------------
# Solve and Output
# -----------------------------

if s.check() == sat:
    model = s.model()

    print("Selected Items:")
    total_weight = 0
    total_profit = 0

    for i in range(n):
        if model[i_bool[i]]:
            print(f"Item {i+1} -> Weight: {weights[i]}, Profit: {profits[i]}")
            total_weight += weights[i]
            total_profit += profits[i]

    print("\nTotal Weight:", total_weight)
    print("Total Profit:", total_profit)

else:
    print("No solution found.")
