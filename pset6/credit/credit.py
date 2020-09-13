import cs50 
import exit

def main():
	card = get_card("Enter your card number:")

	length = int_len(card)

	if not(length == 13 or length == 15 or length == 16):
		print("INVALID")
		exit(1)

	









