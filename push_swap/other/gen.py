import random
from itertools import product
import time

class PatternSequenceGenerator:
    def __init__(self, n, min_val=0, max_val=20, max_attempts=1000):
        """Initialize the generator with parameters."""
        self.n = n
        self.min_val = min_val
        self.max_val = max_val
        self.max_attempts = max_attempts
    
    def generate_all_patterns(self):
        """Generate all possible up/down patterns."""
        return list(product([True, False], repeat=self.n))
    
    def is_valid_sequence(self, numbers, pattern):
        """Check if a sequence follows the given pattern."""
        for i in range(self.n):
            current = numbers[i]
            next_idx = (i + 1) % self.n
            next_val = numbers[next_idx]
            
            if pattern[i]:  # Should go up
                if next_val <= current:
                    return False
            else:  # Should go down
                if next_val >= current:
                    return False
        return True
    
    def is_all_same_pattern(self, pattern):
        """Check if pattern is all ups or all downs."""
        return all(pattern) or not any(pattern)
    
    def generate_circular_sequence(self, is_ascending):
        """Generate a sequence that works in a circle (all ups or all downs)."""
        available_numbers = list(range(self.min_val, self.max_val + 1))
        
        for _ in range(self.max_attempts):
            # Take a random subset
            numbers = random.sample(available_numbers, self.n)
            
            # For ascending (all ups), rotate until smallest number is first
            # For descending (all downs), rotate until largest number is first
            if is_ascending:
                min_idx = numbers.index(min(numbers))
            else:
                min_idx = numbers.index(max(numbers))
            
            # Rotate the list
            numbers = numbers[min_idx:] + numbers[:min_idx]
            
            # Verify it works as a circular sequence
            if self.is_valid_sequence(numbers, [is_ascending] * self.n):
                return numbers
                
        return None

    def generate_sequence(self, pattern):
        """Generate a random sequence following the given pattern."""
        # Special handling for all-up or all-down patterns
        if self.is_all_same_pattern(pattern):
            return self.generate_circular_sequence(pattern[0])
            
        # Normal case handling
        available_numbers = list(range(self.min_val, self.max_val + 1))
        
        for _ in range(self.max_attempts):
            numbers = random.sample(available_numbers, self.n)
            if self.is_valid_sequence(numbers, pattern):
                return numbers
        
        return None

    def generate_all_sequences(self):
        """Generate sequences for all possible patterns."""
        patterns = self.generate_all_patterns()
        results = {}
        
        print(f"Generating {2**self.n} different patterns...")
        start_time = time.time()
        
        for i, pattern in enumerate(patterns, 1):
            pattern_str = ''.join('↑' if p else '↓' for p in pattern)
            sequence = None
            retries = 0
            
            while sequence is None and retries < 3:
                sequence = self.generate_sequence(pattern)
                retries += 1
            
            if sequence is None:
                print(f"Warning: Could not generate valid sequence for pattern {pattern_str}")
                results[pattern_str] = "Failed to generate"
            else:
                results[pattern_str] = sequence
            
            # Progress update
            if i % 4 == 0:
                print(f"Progress: {i}/{2**self.n} patterns processed")
        
        end_time = time.time()
        print(f"\nGeneration completed in {end_time - start_time:.2f} seconds")
        return results

def main():
    # Get user input with validation
    while True:
        try:
            n = int(input("Enter the sequence length (2-6 recommended): "))
            if n <= 0:
                print("Please enter a positive number")
                continue
            if n > 8:
                print("Warning: Large numbers may take very long to process")
                confirm = input("Do you want to continue? (y/n): ")
                if confirm.lower() != 'y':
                    continue
            break
        except ValueError:
            print("Please enter a valid number")
    
    # Get range input with validation
    while True:
        try:
            min_val = int(input("Enter minimum value (default 0): ") or "0")
            max_val = int(input("Enter maximum value (default 20): ") or "20")
            if min_val >= max_val:
                print("Maximum value must be greater than minimum value")
                continue
            if max_val - min_val < n:
                print(f"Range must be at least {n} numbers wide")
                continue
            break
        except ValueError:
            print("Please enter valid numbers")
    
    # Create generator and generate sequences
    generator = PatternSequenceGenerator(n, min_val, max_val)
    sequences = generator.generate_all_sequences()
    
    # Print results in a cleaner format
    print("\nGenerated sequences:")
    print("-" * 50)
    for pattern, sequence in sequences.items():
        valid = "✓" if sequence != "Failed to generate" else "✗"
        print(f"{valid} Pattern {pattern}: {sequence}")

if __name__ == "__main__":
    main()