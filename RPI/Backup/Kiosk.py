#!/usr/bin/env python3
# box_status="1:0:1:0:1:0:0:0:0:0:&"

import traceback
import sys

import serial
import MySQLdb
import time
from urllib.request import urlopen
import json

Serial_ports = ['/dev/ttyACM0', '/dev/ttyACM1']
port_1st_failed = False

url = "https://locker-api.versicles.com/locker/locker@mot.json"

# Open database connection
db = MySQLdb.connect("localhost","admin","vs12345","Vendigo_S1" )

# prepare a cursor object using cursor() method
cursor = db.cursor()
Bstatus = "SELECT BoxStatus FROM BoxStatus"

send_data = False
send_data_counter_occupied=[0,0,0,0,0,0,0,0,0,0]
send_data_counter_open=[0,0,0,0,0,0,0,0,0,0]

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
               send_data_counter_occupied[i] = 0
               send_data_counter_open[i] +=1
               if send_data_counter_open[i] > 1000:  
                  send_data_counter_open[i] = 10
            else:
               boxstatus += "1:"
               send_data_counter_occupied[i] += 1
               send_data_counter_open[i] =0
               if send_data_counter_occupied[i] > 1000:
                  send_data_counter_occupied[i] = 10
         boxstatus.strip()
         boxstatus+='&'
         # print("send_data_counter_open = " + str(send_data_counter_open))
         # print("send_data_counter_occupied = " + str(send_data_counter_occupied))
               
         print("boxstatus_command = " + boxstatus)
         for i in range (0,10):
            global send_data
            if (send_data_counter_open[i] > 0) and (send_data_counter_open[i] <= 1):
               send_data = True
            if (send_data_counter_occupied[i] > 0) and (send_data_counter_occupied[i] <= 1):
               send_data = True
         if send_data == True:
            print("send_data")
            ser.write(bytes(boxstatus, 'utf-8'))
            time.sleep(1)
            ser.flushOutput()
            send_data = False

      except Exception:
         print("DB Exception")
         print(traceback.format_exc())
         # or
         print(sys.exc_info()[2])

if __name__ == '__main__':
   while True:
      try:
         ser = serial.Serial(str(Serial_ports[0]), 115200, timeout=2)

         if ser.isOpen()==True:
            ser.reset_input_buffer()
            break

      except serial.SerialException:
         # print("Crosscheck port Options")
         ser = serial.Serial(str(Serial_ports[1]), 115200, timeout=2)
         if ser.isOpen()==True:
            ser.reset_input_buffer()
            break


   while True:
      try:
         time.sleep(5)

         response = urlopen(url)
         # storing the JSON response 
         data_json = json.loads(response.read())
  
         # db = MySQLdb.connect("localhost","admin","vs12345","Vendigo_S1" )
         # cursor1 = db.cursor()
         for i in range(0,10):
            boxNumber = str(data_json['locker_boxes'][i]['number'])
            state = data_json['locker_boxes'][i]['is_locked']
            if(state == True):
               box_status = '1'
            elif(state == False):
               box_status = '0'
            # print("box_status = " + str(box_status))
            # print("boxNumber = " + str(boxNumber))
            cursor.execute ("""
            UPDATE BoxStatus  
            SET BoxStatus=%s
            WHERE BoxNumber=%s
            """, (box_status, boxNumber))
            #DB_Update = "UPDATE BoxStatus SET BoxStatus = '1' WHERE BoxNumber = 'box_number'"
            db.commit()
         # db.close()
         process_db()
         # break

         # for i in range(0,10):
            # print(data_json['locker_boxes'][i]['number'])
            # print(data_json['locker_boxes'][i]['id'])
            # print(data_json['locker_boxes'][i]['name'])
            # print(data_json['locker_boxes'][i]['is_locked'])
            # print(data_json['locker_boxes'][i]['order'])
            # print("------------------------------------")
      except KeyError :
         print("Crosscheck Parsed JSOn Data")
      except Exception as e:
         print("Error in Main Loop")
         print('Error: '+ str(e))
         print(traceback.format_exc())
         db.rollback()

   # disconnect from server
   db.close()
