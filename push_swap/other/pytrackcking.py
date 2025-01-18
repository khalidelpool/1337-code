class Stacks:
    def __init__(self, capacity):
        self.a = []
        self.b = []
        self.capacity = capacity

    def copy(self):
        new_stacks = Stacks(self.capacity)
        new_stacks.a = self.a.copy()
        new_stacks.b = self.b.copy()
        return new_stacks

    # Stack operations
    def swap_a(self):
        if len(self.a) >= 2:
            self.a[0], self.a[1] = self.a[1], self.a[0]

    def swap_b(self):
        if len(self.b) >= 2:
            self.b[0], self.b[1] = self.b[1], self.b[0]

    def push_a(self):
        if self.b:
            self.a.insert(0, self.b.pop(0))

    def push_b(self):
        if self.a:
            self.b.insert(0, self.a.pop(0))

    def rotate_a(self):
        if len(self.a) >= 2:
            self.a.append(self.a.pop(0))

    def rotate_b(self):
        if len(self.b) >= 2:
            self.b.append(self.b.pop(0))

    def reverse_rotate_a(self):
        if len(self.a) >= 2:
            self.a.insert(0, self.a.pop())

    def reverse_rotate_b(self):
        if len(self.b) >= 2:
            self.b.insert(0, self.b.pop())

    def is_sorted(self):
        return len(self.b) == 0 and all(self.a[i] <= self.a[i + 1] for i in range(len(self.a) - 1))

class StackSorter:
    def __init__(self):
        self.OPERATIONS = ["sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"]
        self.INITIAL_MAX_DEPTH = 5
        self.DEPTH_INCREMENT = 3
        self.MAX_SIZE = 500
        self.best_solution = {"operations": None, "count": float('inf')}
        self.current_max_depth = float('inf')

    def apply_operation(self, stacks, op):
        if op == "sa":
            stacks.swap_a()
        elif op == "sb":
            stacks.swap_b()
        elif op == "ss":
            stacks.swap_a()
            stacks.swap_b()
        elif op == "pa":
            stacks.push_a()
        elif op == "pb":
            stacks.push_b()
        elif op == "ra":
            stacks.rotate_a()
        elif op == "rb":
            stacks.rotate_b()
        elif op == "rr":
            stacks.rotate_a()
            stacks.rotate_b()
        elif op == "rra":
            stacks.reverse_rotate_a()
        elif op == "rrb":
            stacks.reverse_rotate_b()
        elif op == "rrr":
            stacks.reverse_rotate_a()
            stacks.reverse_rotate_b()

    def update_best_solution(self, current_solution):
        if len(current_solution) < self.best_solution["count"]:
            self.best_solution["operations"] = current_solution.copy()
            self.best_solution["count"] = len(current_solution)
            self.current_max_depth = len(current_solution) - 1

    def solve(self, stacks, current_solution, depth):
        if depth > self.current_max_depth:
            return

        if stacks.is_sorted():
            self.update_best_solution(current_solution)
            return

        for op in self.OPERATIONS:
            temp_stacks = stacks.copy()
            self.apply_operation(temp_stacks, op)
            current_solution.append(op)
            self.solve(temp_stacks, current_solution, depth + 1)
            current_solution.pop()

    def solve_iterative(self, stacks):
        max_depth = self.INITIAL_MAX_DEPTH
        solution_found = False

        while not solution_found and max_depth <= self.MAX_SIZE:
            self.current_max_depth = max_depth
            self.solve(stacks, [], 0)

            if self.best_solution["count"] != float('inf'):
                solution_found = True
            else:
                max_depth += self.DEPTH_INCREMENT

    def print_solution(self):
        if self.best_solution["count"] != float('inf'):
            for op in self.best_solution["operations"]:
                print(op)
        else:
            print("No solution found")

def main():
    print("enter the numbers: ", end="")
    try:
        numbers = list(map(int, input().strip().split()))
        if not numbers:
            print("No numbers provided")
            return

        stacks = Stacks(len(numbers))
        stacks.a = numbers

        print("Initial stack A:", " ".join(map(str, stacks.a)))

        sorter = StackSorter()
        sorter.solve_iterative(stacks)

        print("Solution steps:")
        sorter.print_solution()

    except ValueError:
        print("Invalid input. Please enter space-separated integers.")

if __name__ == "__main__":
    main()