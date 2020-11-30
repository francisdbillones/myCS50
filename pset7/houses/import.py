from cs50 import SQL
import sys
import csv

def main():
    if (len(sys.argv) != 2):
        print("Usage: python/3 import.py csvfile.csv")
        return
    
    db = SQL("sqlite:///students.db")
    csvfile = sys.argv[1]
    
    with open(csvfile, "r") as csvfile:
        reader = csv.DictReader(csvfile)
        
        for row in reader:
            name = row['name'].split()
            house = row['house']
            birth = row['birth']
            
            first = name[0]
            last = name[-1]
            middle = None
            
            #first name is the first word, last name is the last word, middle name is anything in between.
            if len(name) > 2:
                middle = name[1]
                for i in range(2, len(name)-1):
                    middle += " " + name[i]
            
            db.execute("INSERT INTO students('first', 'middle', 'last', 'house', 'birth') VALUES(?,?,?,?,?)", first, middle, last, house, birth)
            
main()
