#!/usr/bin/env python3
import random
import subprocess
import os
import time
import argparse
from datetime import datetime
from tqdm import tqdm  # You'll need to install this package: pip install tqdm

def check_executable():
    if not os.path.exists('./push_swap'):
        raise FileNotFoundError("push_swap executable not found in current directory")
    if not os.access('./push_swap', os.X_OK):
        raise PermissionError("push_swap executable doesn't have execution permissions")

def generate_unique_numbers(count):
    numbers = random.sample(range(-2147483648, 2147483647), count)
    return numbers

def test_push_swap(numbers):
    input_str = ' '.join(map(str, numbers))
    
    try:
        start_time = time.time()
        process = subprocess.Popen(['./push_swap'] + list(map(str, numbers)), 
                                 stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE)
        output, error = process.communicate()
        execution_time = time.time() - start_time
        
        if error:
            print(f"Error output: {error.decode()}")
            return None, None
            
        moves = len(output.decode().strip().split('\n'))
        return moves, execution_time
    except Exception as e:
        print(f"Error running push_swap: {e}")
        return None, None

def save_failing_case(numbers, moves, test_number, execution_time):
    if not os.path.exists('failing_cases'):
        os.makedirs('failing_cases')
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    filename = f'failing_cases/fail_case_{test_number}_{moves}_moves_{timestamp}.txt'
    with open(filename, 'w') as f:
        f.write(f"Test Date: {datetime.now()}\n")
        f.write(f"Number of moves: {moves}\n")
        f.write(f"Execution time: {execution_time:.4f} seconds\n")
        f.write(f"Numbers: {' '.join(map(str, numbers))}\n")
    return filename

def parse_arguments():
    parser = argparse.ArgumentParser(description='Test push_swap program')
    parser.add_argument('--tests', type=int, default=500,
                       help='Number of tests to run (default: 500)')
    parser.add_argument('--max-moves', type=int, default=5500,
                       help='Maximum allowed moves (default: 5500)')
    parser.add_argument('--numbers', type=int, default=500,
                       help='Number of integers to sort (default: 500)')
    return parser.parse_args()

def main():
    args = parse_arguments()
    
    try:
        check_executable()
    except Exception as e:
        print(f"Error: {e}")
        return

    print("\n=== Push_swap Testing Script ===")
    print(f"Starting tests at: {datetime.now()}")
    print(f"Number of tests: {args.tests}")
    print(f"Numbers per test: {args.numbers}")
    print(f"Maximum allowed moves: {args.max_moves}\n")

    failing_cases = 0
    max_moves_seen = 0
    total_moves = 0
    total_time = 0
    
    progress_bar = tqdm(range(args.tests), desc="Running tests")
    
    for i in progress_bar:
        numbers = generate_unique_numbers(args.numbers)
        moves, execution_time = test_push_swap(numbers)
        
        if moves is None:
            print(f"\nTest {i+1} failed to execute")
            continue
            
        max_moves_seen = max(max_moves_seen, moves)
        total_moves += moves
        total_time += execution_time
        
        progress_bar.set_postfix({'moves': moves, 'time': f"{execution_time:.2f}s"})
        
        if moves > args.max_moves:
            failing_cases += 1
            filename = save_failing_case(numbers, moves, i+1, execution_time)
            print(f"\nTest {i+1} exceeded {args.max_moves} moves ({moves} moves)")
            print(f"Failing case saved to: {filename}")
    
    avg_moves = total_moves / args.tests
    avg_time = total_time / args.tests
    
    print("\n=== Testing Summary ===")
    print(f"Total tests run: {args.tests}")
    print(f"Average moves per test: {avg_moves:.2f}")
    print(f"Average time per test: {avg_time:.4f} seconds")
    print(f"Maximum moves seen: {max_moves_seen}")
    print(f"Number of cases exceeding {args.max_moves} moves: {failing_cases}")
    print(f"Testing completed at: {datetime.now()}")

if __name__ == "__main__":
    main()