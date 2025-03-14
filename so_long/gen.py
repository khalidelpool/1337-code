import random
from collections import deque
import sys

def generate_map(width, height):
    if width < 5 or height < 5:
        raise ValueError("Map dimensions must be at least 5x5.")
    
    # Create an empty map filled with walls
    map_grid = [['1' for _ in range(width)] for _ in range(height)]
    
    # Create inner walkable area with improved obstacle generation
    for y in range(1, height - 1):
        for x in range(1, width - 1):
            if random.random() > 0.75:  # 25% chance of an obstacle
                map_grid[y][x] = '1'
            else:
                map_grid[y][x] = '0'
    
    # Place the player
    px, py = random.randint(1, width - 2), random.randint(1, height - 2)
    map_grid[py][px] = 'P'
    
    # Place the exit, ensuring it's not on the player
    while True:
        ex, ey = random.randint(1, width - 2), random.randint(1, height - 2)
        if (ex, ey) != (px, py):
            map_grid[ey][ex] = 'E'
            break
    
    # Place at least one collectible and ensure it's reachable
    collectibles = max(1, (width * height) // 20)
    placed = 0
    while placed < collectibles:
        cx, cy = random.randint(1, width - 2), random.randint(1, height - 2)
        if map_grid[cy][cx] == '0':
            map_grid[cy][cx] = 'C'
            if is_valid_path(map_grid, px, py, cx, cy):
                placed += 1
            else:
                map_grid[cy][cx] = '0'  # Reset if unreachable
    
    # Place enemies (V characters)
    enemy_count = max(1, (width * height) // 25)  # Scale with map size
    placed_enemies = 0
    while placed_enemies < enemy_count:
        vx, vy = random.randint(1, width - 2), random.randint(1, height - 2)
        if map_grid[vy][vx] == '0':
            # Temporarily place enemy
            map_grid[vy][vx] = 'V'
            # Check if the exit is still reachable after placing the enemy
            if is_valid_path(map_grid, px, py, ex, ey):
                placed_enemies += 1
            else:
                # Enemy blocks the path, remove it
                map_grid[vy][vx] = '0'
    
    # Ensure all collectibles are reachable
    for y in range(height):
        for x in range(width):
            if map_grid[y][x] == 'C' and not is_valid_path(map_grid, px, py, x, y):
                # If collectible is not reachable, convert it to free space
                map_grid[y][x] = '0'
    
    # Final check to ensure the map has a valid path from P to E
    if not is_valid_path(map_grid, px, py, ex, ey):
        return generate_map(width, height)  # Regenerate if no valid path
    
    return '\n'.join(''.join(row) for row in map_grid)

def is_valid_path(map_grid, px, py, ex, ey):
    """
    Check if there's a valid path from (px, py) to (ex, ey).
    Valid path can only go through free spaces ('0'), collectibles ('C'), and exit ('E').
    Cannot go through enemies ('V') or obstacles ('1').
    """
    height, width = len(map_grid), len(map_grid[0])
    visited = set()
    queue = deque([(px, py)])
    visited.add((px, py))
    
    while queue:
        x, y = queue.popleft()
        if (x, y) == (ex, ey):
            return True
        
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if (0 <= nx < width and 0 <= ny < height and 
                (nx, ny) not in visited and map_grid[ny][nx] in {'0', 'E', 'C'}):
                visited.add((nx, ny))
                queue.append((nx, ny))
    
    return False

def save_map_to_file(map_data, filename="map.ber"):
    with open(filename, "w") as f:
        f.write(map_data + "\n")
    print(f"Map saved to {filename}")

def main():
    # Default random size
    width, height = random.randint(5, 42), random.randint(5, 23)
    filename = "map.ber"
    
    # Check if custom size is provided as command line arguments
    if len(sys.argv) >= 3:
        try:
            width = int(sys.argv[1])
            height = int(sys.argv[2])
            
            # Validate dimensions
            if width < 5 or height < 5:
                print("Warning: Map dimensions must be at least 5x5. Using minimum values.")
                width = max(5, width)
                height = max(5, height)
            
            # Check for custom filename
            if len(sys.argv) >= 4:
                filename = sys.argv[3]
                if not filename.endswith('.ber'):
                    filename += '.ber'
                    
        except ValueError:
            print("Error: Width and height must be integers. Using random values.")
    
    print(f"Generating map with dimensions {width}x{height}")
    map_data = generate_map(width, height)
    save_map_to_file(map_data, filename)

if __name__ == "__main__":
    main()