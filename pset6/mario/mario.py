from cs50 import get_int

def main():
	while True:
		height = get_int("Height: ")
		if 0<height<9:
			break

	draw_triangle(height)

def draw_triangle(height):
	count = height
	for i in range(height):
		for a in range(count - i - 1):
			print(" ", end="")

		for b in range(i + 1):
			print("#", end="")

		print("  ", end="")

		for c in range(i + 1): 
			print("#", end="")

		print()

main()


