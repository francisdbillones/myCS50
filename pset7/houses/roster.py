from cs50 import SQL
import sys

def main():
    # usage
    if len(sys.argv) != 2:
        print("Usage: python/3 roster.py {name of house})")
    
    db = SQL("sqlite:///students.db")
    house = sys.argv[1]
    
    roster = db.execute("SELECT first, middle, last, birth FROM students WHERE house = %s ORDER BY last, first;", house)
    
    for student in roster:
        first = student['first']
        last = student['last']
        if student['middle'] == None:
            middle = ""
        else:
            middle = ' ' + student['middle']
        
        birth = str(student['birth'])
        
        print(first + middle + ' ' + last + ", born in " + birth)

main()
