from collections import deque
from typing import List, Dict, Set, Optional, Tuple
from dataclasses import dataclass
import time
from functools import lru_cache

@dataclass(frozen=True)
class StackState:
    a: tuple
    b: tuple

    def is_sorted(self) -> bool:
        return len(self.b) == 0 and all(self.a[i] <= self.a[i + 1] for i in range(len(self.a) - 1))

class OptimizedStacks:
    def __init__(self, numbers: List[int]):
        self.state = StackState(tuple(numbers), tuple())
    
    def _apply_operation(self, op: str) -> StackState:
        a = list(self.state.a)
        b = list(self.state.b)
        
        if op[0] == 's':  # swap operations
            if op in ('sa', 'ss') and len(a) >= 2:
                a[0], a[1] = a[1], a[0]
            if op in ('sb', 'ss') and len(b) >= 2:
                b[0], b[1] = b[1], b[0]
        
        elif op[0] == 'p':  # push operations
            if op == 'pa' and b:
                a.insert(0, b.pop(0))
            elif op == 'pb' and a:
                b.insert(0, a.pop(0))
        
        elif op[0] == 'r':  # rotate operations
            if len(op) == 2:  # single rotate
                if op == 'ra' and len(a) >= 2:
                    a.append(a.pop(0))
                elif op == 'rb' and len(b) >= 2:
                    b.append(b.pop(0))
            else:  # reverse rotate
                if op in ('rra', 'rrr') and len(a) >= 2:
                    a.insert(0, a.pop())
                if op in ('rrb', 'rrr') and len(b) >= 2:
                    b.insert(0, b.pop())
        
        return StackState(tuple(a), tuple(b))

class OptimizedStackSorter:
    OPERATIONS = ('sa', 'sb', 'ss', 'pa', 'pb', 'ra', 'rb', 'rr', 'rra', 'rrb', 'rrr')
    
    def __init__(self):
        self.visited_states: Set[StackState] = set()
        self.max_depth = 12  # Adjustable maximum depth
    
    def _get_heuristic(self, state: StackState) -> int:
        """Estimate minimum moves needed to sort from current state"""
        inversions = sum(1 for i in range(len(state.a))
                        for j in range(i + 1, len(state.a))
                        if state.a[i] > state.a[j])
        return inversions + len(state.b) * 2
    
    def solve(self, numbers: List[int]) -> Optional[List[str]]:
        initial_stacks = OptimizedStacks(numbers)
        initial_state = initial_stacks.state
        
        if initial_state.is_sorted():
            return []
        
        # Priority queue entries: (priority, depth, state, operations)
        queue = [(self._get_heuristic(initial_state), 0, initial_state, [])]
        self.visited_states = {initial_state}
        
        while queue:
            _, depth, current_state, ops = queue.pop(0)
            
            if depth >= self.max_depth:
                continue
            
            stacks = OptimizedStacks(list(current_state.a))
            stacks.state = current_state
            
            for op in self.OPERATIONS:
                new_state = stacks._apply_operation(op)
                
                if new_state not in self.visited_states:
                    self.visited_states.add(new_state)
                    new_ops = ops + [op]
                    
                    if new_state.is_sorted():
                        return new_ops
                    
                    priority = depth + 1 + self._get_heuristic(new_state)
                    queue.append((priority, depth + 1, new_state, new_ops))
            
            # Sort queue by priority
            queue.sort(key=lambda x: x[0])
        
        return None

class OptimizedPatternGenerator:
    def __init__(self, size: int, min_val: int = 0, max_val: int = 20):
        self.size = size
        self.min_val = min_val
        self.max_val = max_val
        self.numbers = list(range(min_val, max_val + 1))
    
    @lru_cache(maxsize=None)
    def _is_valid_pattern(self, pattern: tuple, sequence: tuple) -> bool:
        return all(
            sequence[i] < sequence[(i + 1) % len(sequence)] if pattern[i] 
            else sequence[i] > sequence[(i + 1) % len(sequence)]
            for i in range(len(sequence))
        )
    
    def generate_sequence(self, pattern: tuple) -> Optional[List[int]]:
        from itertools import permutations
        
        # Generate only needed permutations
        needed_numbers = min(self.size + 2, self.max_val - self.min_val + 1)
        for perm in permutations(self.numbers[:needed_numbers], self.size):
            if self._is_valid_pattern(pattern, tuple(perm)):
                return list(perm)
        return None

def main():
    # Get user input with validation
    size = int(input("Enter sequence length (2-6 recommended): "))
    min_val = int(input("Enter minimum value (default 0): ") or "0")
    max_val = int(input("Enter maximum value (default 20): ") or "20")
    
    # Create generator and generate sequences
    generator = OptimizedPatternGenerator(size, min_val, max_val)
    sorter = OptimizedStackSorter()
    
    # Generate and test patterns
    from itertools import product
    patterns = list(product([True, False], repeat=size))
    
    print(f"\nGenerating and testing {len(patterns)} patterns...")
    start_time = time.time()
    
    results = []
    for pattern in patterns:
        sequence = generator.generate_sequence(pattern)
        if sequence:
            solution = sorter.solve(sequence)
            pattern_str = ''.join('↑' if p else '↓' for p in pattern)
            # Store solution length or float('inf') if no solution
            solution_length = len(solution) if solution else float('inf')
            results.append((pattern_str, sequence, solution, solution_length))
    
    print(f"\nCompleted in {time.time() - start_time:.2f} seconds")
    
    # Sort results by number of operations (already sorted sequences first)
    results.sort(key=lambda x: x[3])
    
    # Print results
    print("\nResults (sorted by number of operations):")
    print("-" * 70)
    for pattern, sequence, solution, solution_length in results:
        if solution_length == 0:
            print(f"\nPattern {pattern}:")
            print(f"Sequence: {sequence}")
            print("Already sorted - no operations needed")
        elif solution_length != float('inf'):
            print(f"\nPattern {pattern}:")
            print(f"Sequence: {sequence}")
            print(f"Solution ({solution_length} operations):")
            print(' '.join(solution))
        else:
            print(f"\nPattern {pattern}:")
            print(f"Sequence: {sequence}")
            print("No solution found")
        print("-" * 70)

if __name__ == "__main__":
    main()

