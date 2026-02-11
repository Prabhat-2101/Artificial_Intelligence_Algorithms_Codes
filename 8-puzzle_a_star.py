import heapq


class EightPuzzleSolver:
    def __init__(self, initial_state, goal_state):
        self.initial_state = tuple(tuple(row) for row in initial_state)
        self.goal_state = tuple(tuple(row) for row in goal_state)
        self.dims = [len(initial_state), len(initial_state[0])]
        self.dirs = [(-1, 0), (1, 0), (0, 1), (0, -1)]
        self.cost = None

    def valid_location(self, i, j):
        return 0 <= i < self.dims[0] and 0 <= j < self.dims[1]

    def calculate_heuristic(self, state):
        misplaced = 0
        for i in range(self.dims[0]):
            for j in range(self.dims[1]):
                if state[i][j] != 0 and state[i][j] != self.goal_state[i][j]:
                    misplaced += 1
        return misplaced

    def find_blank(self, state):
        for i in range(self.dims[0]):
            for j in range(self.dims[1]):
                if state[i][j] == 0:
                    return i, j
        return -1, -1

    def solve(self):
        start_state = self.initial_state
        goal_state = self.goal_state

        start_h = self.calculate_heuristic(start_state)
        pq = [(start_h, 0, start_state)]  # (f, g, state)
        best_g = {start_state: 0}

        while pq:
            f_n, g_n, state = heapq.heappop(pq)

            if state == goal_state:
                self.cost = g_n
                return g_n

            if g_n > best_g.get(state, float("inf")):
                continue

            iloc, jloc = self.find_blank(state)

            for di, dj in self.dirs:
                niloc, njloc = iloc + di, jloc + dj
                if not self.valid_location(niloc, njloc):
                    continue

                next_state = [list(row) for row in state]
                next_state[niloc][njloc], next_state[iloc][jloc] = (
                    next_state[iloc][jloc],
                    next_state[niloc][njloc],
                )
                next_state = tuple(tuple(row) for row in next_state)

                new_g = g_n + 1
                if new_g >= best_g.get(next_state, float("inf")):
                    continue

                best_g[next_state] = new_g
                h_n = self.calculate_heuristic(next_state)
                heapq.heappush(pq, (new_g + h_n, new_g, next_state))

        self.cost = -1
        return -1

    def print_result(self):
        if self.cost == -1 or self.cost is None:
            print("No solution found.")
        else:
            print(f"Minimum cost to solve the puzzle: {self.cost}")


initial = [
    [2,8,3],
    [1,6,4],
    [7,0,5],
]

goal = [
    [1,2,3],
    [8,0,4],
    [7,6,5],
]

solver = EightPuzzleSolver(initial, goal)
solver.solve()
solver.print_result()
