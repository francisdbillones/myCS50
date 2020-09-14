from cs50 import get_string

def main():
	text = get_string("Text: ")

	sentence_enders = [".", "!", "?"]
	letter_count = 0
	sentence_count = 0
	word_count = 1

	for char in text:
		if char.isalpha():
			letter_count += 1

		elif char == " ":
			word_count += 1

		elif char in sentence_enders:
			sentence_count += 1

	calculate_readability(letter_count, word_count, sentence_count)

def calculate_readability(letter_count, word_count, sentence_count):
	L = (letter_count / word_count) * 100
	S = (sentence_count / word_count) * 100

	index = 0.0588 * L - 0.296 * S - 15.8

	if 1 <= index < 16:
		print(f"Grade {round(index)}")

	else:
		print("Before Grade 1") if index < 1 else print("Grade 16+")

main()
