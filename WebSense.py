#!/usr/bin/python
# parser to make use of json telemetry from WAFN sites
# Andrew Elwell <Andrew.Elwell@gmail.com> April 2013

import urllib2
import json
import csv
from os.path import exists
import time

source = 'http://203.59.39.17/env/tic/'
log = 'tic.csv'
needheader = False

# check file exists, if not we need to write header
if not exists(log):
	needheader = True

# For TIC we know the expected fields
fields = ["timestamp","WARG_BATT_V","WAFN_BATT_V","WAFN_PV180_V", "WAFN_LOAD_A","WAFN_PV230_V", "WAFN_PANEL_A"]
out = csv.DictWriter(open("tic.csv","a"),fields)

if needheader:
	out.writeheader()

while True:
	f = urllib2.urlopen(source)
	html =  f.read()
	# take timestamp after we get the data. 
	ts = time.time()
	f.close()
	
	j = html.split('<pre>')[1].split('\r\n')[1] # UGH ugly++
	data = json.loads(j)
	data['TIC']['timestamp']=ts


	out.writerow(data['TIC'])
	print json.dumps(data)

	time.sleep(15)
