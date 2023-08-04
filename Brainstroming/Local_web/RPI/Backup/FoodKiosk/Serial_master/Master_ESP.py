#!/usr/bin/env python3

import serial
import MySQLdb
import time
# import sys

# import urllib library
from urllib.request import urlopen
  
# import json
import json

# box_status="1:0:1:0:1:0:0:0:0:0:&"

url = "https://locker-api.versicles.com/locker/locker@mot.json"
response = urlopen(url)
  
# storing the JSON response 
data_json = json.loads(response.read())

# Open database connection
db = MySQLdb.connect("localhost","admin","vs12345","Vendigo_S1" )

# prepare a cursor object using cursor() method
cursor = db.cursor()
Bstatus = "SELECT BoxStatus FROM BoxStatus"


def process_db():
      try:
         # Execute the SQL command
         cursor.execute(Bstatus)
         global boxstatus
         boxstatus = ""
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
               boxstatus += "0:"
               # print("Box: " + str(i+1) + " Free")
               # if i != 9:
               #    boxstatus += "0:"
               # else:
               #    boxstatus += "0"
            else:
               boxstatus += "1:"
               # print("Box: " + str(i+1) + " Occupied")
               # if i != 9:
               #    boxstatus += "1:"
               # else:
               #    boxstatus += "1"
         boxstatus.strip()
         boxstatus+='&'
               
         print("boxstatus_command = " + boxstatus)
         ser.write(bytes(boxstatus, 'utf-8'))
         # ser.write("1:1:1:0:0:0:1:1:1:1".encode('utf-8'))
         time.sleep(1)
         ser.flushOutput()
         # ser.write(b'1:1:1:0:0:0:1:1:1:1')
         # if(boxstatus == "0:0:0:0:0:0:0:0:0:0") ser.write(bytes(b'1111111111'))

      except Exception:
         exc_type, value, traceback = sys.exc_info()
         print("Failed with exception [%s]" % exc_type.__name__)
         # print("Issue with operation, Kindly Crosscheck Database script!!!!")


      

if __name__ == '__main__':
   while True:
      try:
         ser = serial.Serial('/dev/ttyACM0', 115200, timeout=2)
         if ser.isOpen()==True:
            ser.reset_input_buffer()
            break
      except serial.SerialException:
         print("Connecting with other port")
         #ser = serial.Serial('/dev/ttyUSB1', 115200, timeout=5)

      
   while True:
        process_db()
        time.sleep(1)
        # if ser.in_waiting > 0:
        #     line = ser.readline().decode('utf-8').rstrip()
        #     print(line)
   # disconnect from server
   db.close()
