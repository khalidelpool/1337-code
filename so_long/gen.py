import random
from collections import deque

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
    
    # Ensure the map has a valid path from P to E
    if not is_valid_path(map_grid, px, py, ex, ey):
        return generate_map(width, height)  # Regenerate if no valid path
    
    return '\n'.join(''.join(row) for row in map_grid)

def is_valid_path(map_grid, px, py, ex, ey):
    height, width = len(map_grid), len(map_grid[0])
    visited = set()
    queue = deque([(px, py)])
    
    while queue:
        x, y = queue.popleft()
        if (x, y) == (ex, ey):
            return True
        
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if (1 <= nx < width - 1 and 1 <= ny < height - 1 and 
                (nx, ny) not in visited and map_grid[ny][nx] in {'0', 'E', 'C'}):
                visited.add((nx, ny))
                queue.append((nx, ny))
    
    return False

def save_map_to_file(map_data, filename="map.ber"):
    with open(filename, "w") as f:
        f.write(map_data + "\n")
    print(f"Map saved to {filename}")

# Generate and save map
width, height = random.randint(5, 42), random.randint(5, 23)  # Random dimensions within max
map_data = generate_map(width, height)
save_map_to_file(map_data)
