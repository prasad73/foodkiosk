#!/usr/bin/python

import MySQLdb

# Open database connection
db = MySQLdb.connect("localhost","admin","vs12345","Vendigo_S1" )

# prepare a cursor object using cursor() method
cursor = db.cursor()
Bstatus = "SELECT BoxStatus FROM BoxStatus"
try:
   # Execute the SQL command
   
   cursor.execute(Bstatus)
   
   #Fetching complete column from the table
   result = cursor.fetchall();
   result = list(result)
   index = 0
   status=['0','0','0','0','0','0','0','0','0','0']
   while index < 10:
      status[index] = list(result[index])
      index += 1
   for i in range (0,10):
      if status[i] == ['0']:
         print("Box: " + str(i+1) + " Free")
      else:
         print("Box: " + str(i+1) + " Occupied")

except:
   print("Issue with operation, Kindly Crosscheck Database script!!!!")

# disconnect from server
db.close()