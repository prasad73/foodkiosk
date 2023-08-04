# import urllib library
from urllib.request import urlopen
  
# import json
import json
# store the URL in url as 
# parameter for urlopen
# url = "https://api.github.com"
url = "https://locker-api.versicles.com/locker/locker@mot.json"
  
# store the response of URL
response = urlopen(url)
  
# storing the JSON response 
# from url in data
data_json = json.loads(response.read())
  
# print the json response
# print(data_json)
# print(data_json.keys())
# print(data_json.values())
# print(data_json['id'])
# print(data_json['name'])
for i in range(0,10):
	print(data_json['locker_boxes'][i]['number'])
	print(data_json['locker_boxes'][i]['id'])
	print(data_json['locker_boxes'][i]['name'])
	print(data_json['locker_boxes'][i]['is_locked'])
	print(data_json['locker_boxes'][i]['order'])
	print("------------------------------------")
