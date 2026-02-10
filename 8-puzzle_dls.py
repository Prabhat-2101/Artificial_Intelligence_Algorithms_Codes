class EightPuzzleSolver:
    def __init__(self, initial_state, goal_state):
        self.initial_state = initial_state
        self.goal_state = tuple(tuple(row) for row in goal_state)
        self.dims = [-1, -1]
        self.dirs = [[-1,0],[1,0],[0,1],[0,-1]]
        self.cost = 9999999
        self.max_depth = 10 

    def valid_location(self, i, j):
        return 0 <= i < self.dims[0] and 0 <= j < self.dims[1]

    def solve_recur(self, current_state, iloc, jloc, cost, visited):
        if cost > self.max_depth or cost >= self.cost:
            return

        state_key = tuple(tuple(row) for row in current_state)

        if state_key in visited:
            return

        if state_key == self.goal_state:
            self.cost = min(self.cost, cost)
            return

        visited.add(state_key)

        for d in self.dirs:
            niloc, njloc = iloc + d[0], jloc + d[1]
            if self.valid_location(niloc, njloc):
                current_state[niloc][njloc], current_state[iloc][jloc] = \
                    current_state[iloc][jloc], current_state[niloc][njloc]

                self.solve_recur(current_state, niloc, njloc, cost + 1, visited)

                current_state[niloc][njloc], current_state[iloc][jloc] = \
                    current_state[iloc][jloc], current_state[niloc][njloc]

        visited.remove(state_key)

    def solve(self):
        self.dims = [len(self.initial_state), len(self.initial_state[0])]

        for i in range(self.dims[0]):
            for j in range(self.dims[1]):
                if self.initial_state[i][j] == 0:
                    self.solve_recur(self.initial_state, i, j, 0, set())
                    return
    def print_result(self):
        if self.cost == 9999999:
            print(f"No solution found within the maximum depth {self.max_depth}.")
        else:
            print(f"Minimum cost to solve the puzzle: {self.cost}")


initial = [
    [0,1,2],
    [5,4,3],
    [7,6,8]
]

goal = [
    [1,2,3],
    [4,5,6],
    [7,8,0]
]
solver = EightPuzzleSolver(initial,goal)
solver.solve()
solver.print_result()