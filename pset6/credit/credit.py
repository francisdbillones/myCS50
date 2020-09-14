from cs50 import get_int
from sys import exit
import math

def main():
	card = get_card("Enter your card number:")

	length = int_len(card)

	if not(length == 13 or length == 15 or length == 16):
		print("INVALID")
		exit(1)

	card_copy = card

	checksum = check_checksum(card_copy)

	if checksum:
		card_type = check_card_type(card, length)

		print(f"{card_type}")
		exit(0)

def get_card(question):
	while True:
		card = get_int(f"{question}")

		if card > 0:
			return card

def int_len(card):
	digits = int(math.log10(card))+1
	return digits

def check_checksum(card):
	#separate checksums for every other digit in card number
	checksum1 = 0
	checksum2 = 0

	#Luhn's algorithm
	while card > 0:
		checksum2 += card % 10

		#remove last digit from card
		card //= 10

		checksum1 += (((card % 10) * 2) // 10) + (((card % 10) * 2) % 10)

		card //= 10

	#calculate total
	totalChecksum = checksum1 + checksum2

	#check whether total checksum is valid checksum
	if totalChecksum % 10 == 0:
		return True
	return False

def check_card_type(card, length):
	##list of valid card headers according to type
	#amex headers
	amex = [34, 37]
	#mastercard headers
	mastercard = [51, 52, 53, 54, 55]
	#visa headers
	visa = [4]

	##separate according to lengths

	#if 13 digits
	if length == 13:

		#if first digit is a visa header, return "VISA"
		if int(str(card)[:1]) in visa:
			return "VISA"

	#else if 15 digits
	elif length == 15:

		#if first 2 digits is an amex header, return "AMEX"
		if int(str(card)[:2]) in amex:
			return "AMEX"

	#else if 16 digits
	elif length == 16:

		#if first 2 digits is a mastercard header, return "MASTERCARD"
		if int(str(card)[:2]) in mastercard:
			return "MASTERCARD"

		#else if first digit is visa header, return "VISA"
		elif int(str(card)[:1]) in visa:
			return "VISA"

	#if doesn't qualify for any card type, just return "INVALID"
	return "INVALID"

main()












