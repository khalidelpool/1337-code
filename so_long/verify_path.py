import time
from collections import deque


# arr =	[[0, 7, 0, 0],
# 		 [0, 7, 0, 0],
# 		 [0, 7, 3, 0],
# 		 [0, 7, 0, 0]]

map =  [list("11111111"),
		list("10C000E1"),
		list("10000011"),
		list("10P00001"),
		list("11111111")]

row, col = len(map), len(map[0])
start = (3, 2)

def next_to(node):
	result = []
	moves = [(0, 1), (1, 0), (-1, 0), (0, -1)]

	for move in moves:
		x = node[0] + move[0]
		y = node[1] + move[1]
		if x < row and y < col and x > -1 and y > -1:
			if map[x][y] != '1':
				result.append((x, y))

	return result

q = deque()
visited = []
q.append(start)
visited.append(start)

def print_map():
	for i in range(0, row):
		for j in range(0, col):
			print(map[i][j], end='')
			# if j < col - 1:
			# 	print(' ', end = '')
		print()
	print('-------------------------------------------')

def print_node(node):
	print(map[node[0]][node[1]])

try:
	while q:
		node = q.popleft()
		neighbours = next_to(node)
		
		for next in neighbours:
			if next not in visited:
				
				q.append(next)
				visited.append(next)
				print('in')
				map[next[0]][next[1]] = '1'
				
		print(q)
		print(f'node is: {node}')
		print(f'visited: {visited}')
		print_map()
		time.sleep(2)
except:
	print(visited)
	print('error')

if (1, 6) in visited:
	print('valid map')
else:
	print('invalid, no path found')