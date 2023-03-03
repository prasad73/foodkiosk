import serial
import json
import traceback
import sys
import time
from urllib.request import urlopen

Open_door_place_order = [False, False, False, False, False, False, False, False, False, False, False, False]
Open_door_pick_order = [False, False, False, False, False, False, False, False, False, False, False, False]

url = "https://locker-api.versicles.com/locker/locker@lulumall.json"

try:
    connection = serial.Serial(port="COM4", baudrate=115200, bytesize=8, parity='N',stopbits=1)
    connection.reset_input_buffer()
except serial.SerialException as var:
    print('An Exception Occured')
    print('Exception Details -> ', var)
else:
    print("Serial port Opened @ COM4")

while True:

        try:
                time.sleep(2)
                response = urlopen(url)
                data_json = json.loads(response.read())

                for i in range(0,12):
                    boxNumber = str(data_json['locker_boxes'][i]['number'])
                    state = data_json['locker_boxes'][i]['is_locked']
                    order_status = data_json['locker_boxes'][i]['order']
                    if(state == True):
                        if order_status is None:
                            if(Open_door_place_order[i] == False):
                                Open_door_place_order[i] = True
                                Open_door_pick_order[i] = False
                                if(boxNumber == '1'):
                                    connection.write(b'J')
                                    print('J')                                    
                                elif(boxNumber == '2'):
                                    connection.write(b'G')
                                    print('G')
                                elif(boxNumber == '3'):
                                    connection.write(b'D')
                                    print('D')
                                elif(boxNumber == '4'):
                                    connection.write(b'A')
                                    print('A')
                                elif(boxNumber == '5'):
                                    connection.write(b'K')
                                    print('K')
                                elif(boxNumber == '6'):
                                    connection.write(b'H')
                                    print('H')
                                elif(boxNumber == '7'):
                                    connection.write(b'E')
                                    print('E')
                                elif(boxNumber == '8'):
                                    connection.write(b'B')
                                    print('B')
                                elif(boxNumber == '9'):
                                    connection.write(b'L')
                                    print('L')
                                elif(boxNumber == '10'):
                                    connection.write(b'I')
                                    print('I')
                                elif(boxNumber == '11'):
                                    connection.write(b'F')
                                    print('F')
                                elif(boxNumber == '12'):
                                    connection.write(b'C')
                                    print('C')
                        else:
                            if(Open_door_pick_order[i] == False):
                                Open_door_pick_order[i] = True
                                Open_door_place_order[i] = False
                                if(boxNumber == '1'):
                                    connection.write(b'j')
                                    print('j')
                                elif(boxNumber == '2'):
                                    connection.write(b'g')
                                    print('g')
                                elif(boxNumber == '3'):
                                    connection.write(b'd')
                                    print('d')
                                elif(boxNumber == '4'):
                                    connection.write(b'a')
                                    print('a')
                                elif(boxNumber == '5'):
                                    connection.write(b'k')
                                    print('k')
                                elif(boxNumber == '6'):
                                    connection.write(b'h')
                                    print('h')
                                elif(boxNumber == '7'):
                                    connection.write(b'e')
                                    print('e')
                                elif(boxNumber == '8'):
                                    connection.write(b'b')
                                    print('b')
                                elif(boxNumber == '9'):
                                    connection.write(b'l')
                                    print('l')
                                elif(boxNumber == '10'):
                                    connection.write(b'i')
                                    print('i')
                                elif(boxNumber == '11'):
                                    connection.write(b'f')
                                    print('f')
                                elif(boxNumber == '12'):
                                    connection.write(b'c')
                                    print('c')
        except KeyError:
                print("Crosscheck Parsed JSON Data")
        except Exception as e:
                print("Error: " + str(e))
                print(traceback.format_exc())       

#data = connection.readline().decode("utf-8")
#print(data)    
