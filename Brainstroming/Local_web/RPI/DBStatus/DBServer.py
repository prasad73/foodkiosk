#!/usr/bin/python

import MySQLdb

# Open database connection
db = MySQLdb.connect("localhost","admin","vs12345","Vendigo_S1" )

# prepare a cursor object using cursor() method
cursor = db.cursor()

b1 = "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='1'"
b2 = "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='2'"
b3 = "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='3'"
b4 = "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='4'"
b5 = "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='5'"
b6 = "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='6'"
b7 = "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='7'"
b8 = "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='8'"
b9 = "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='9'"
b10 = "SELECT BoxStatus FROM BoxStatus WHERE BoxNumber='10'"
try:
   # Execute the SQL command
   print(cursor.execute(b1))
   print(cursor.execute(b2))
   print(cursor.execute(b3))
   print(cursor.execute(b4))
   print(cursor.execute(b5))
   print(cursor.execute(b6))
   print(cursor.execute(b7))
   print(cursor.execute(b8))
   print(cursor.execute(b9))
   print(cursor.execute(b10))

   # Fetch all the rows in a list of lists.

except:
   print "Error: unable to fecth data"

# disconnect from server
db.close()