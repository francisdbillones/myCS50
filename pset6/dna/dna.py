import sys
import csv

def main():
	# check for correct usage
	if len(sys.argv) != 3:
		print("Usage: python dna.py database.csv sequence.txt")
		exit(1)

	# open database
	database_file = open(sys.argv[1])
	database = csv.DictReader(database_file)

	sequence_file = open(sys.argv[2])
	sequence = sequence_file.read()

	STR_types = database.fieldnames # get all STR types available in the database

	scanned_sequence = check_for_strs(sequence, STR_types)

	was_there_a_match = False
	for person in database:
		match = True

		for STR in STR_types:
			if STR == "name":
				continue
				
			if int(person[STR]) != scanned_sequence[STR]:
				match = False

		if match:
			print(person['name'])
			was_there_a_match = True

	if was_there_a_match == False:
		print("No match")


 	#TODO

def check_for_strs(sequence, STR_types):
	current_position = 0

	STR_longest_runs = dict.fromkeys(STR_types, 0)

	# go through each element in dna sequence
	while current_position < len(sequence):
		#express that current position is STR
		is_str = False
		# check for each STR
		for STR in STR_types:
				
			# create a new run
			current_run = 0

			if sequence[current_position: current_position + len(STR)] == STR:
				if sequence[current_position + len(STR): current_position + 2*(len(STR))] == STR:
					while sequence[current_position: current_position + len(STR)] == STR:
						is_str = True

						#jump to the next position
						current_position += len(STR)

						#update current run
						current_run += 1

					if current_run > STR_longest_runs[STR]:
						STR_longest_runs[STR] = current_run

				else:
					current_run = 1
					if current_run > STR_longest_runs[STR]:
						STR_longest_runs[STR] = current_run

		if is_str == False:
			current_position += 1
	
	return STR_longest_runs


main()

#current position = 0, so that it will start at the start of the string. It will then check for each STR in the given STR_types. If the
#current substring matches an str, it will jump to the next substring, checking whether the next substring is the same as the current STR.