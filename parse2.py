#!/usr/bin/python

# parser to grab table from website and extract site names / AS numbers
# and spit out as json after merging with position info

from bs4 import BeautifulSoup
import ConfigParser
import urllib
import geojson

meta = 'http://www.wafreenet.org/Network/IPAllocations'

config = ConfigParser.ConfigParser()
config.read('pos.cfg')

f = urllib.urlopen(meta)

soup = BeautifulSoup(f)

t = soup.find("table")
for row in t.findAll("tr"):
   cell = row.findAll("td")
   IP, AS, Node, Name, Location, Contact = cell
   Node = Node.text.strip()
   AS = AS.text.strip()
   Name = Name.text.strip()
   IP = IP.text.strip()
   # print AS,Name,Node

   if config.has_section(Node):
       latlon = config.get(Node,'latlon')
       pos = latlon.split(',')
       pos = map(float,pos)
       # geoJSON wans lon,lat
       lonlat = [pos[1],pos[0]]

       f = geojson.Feature(properties={"Name":Name,"Node":Node, "AS":AS}, 
           geometry={"type":"Point","coordinates":lonlat},)

       print f
