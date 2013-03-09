#!/usr/bin/python

# parser to grab table from website and extract site names / AS numbers

from bs4 import BeautifulSoup
import ConfigParser
import urllib

meta = 'http://www.wafreenet.org/Network'

print 'digraph G {'

config = ConfigParser.RawConfigParser()

f = urllib.urlopen(meta)

soup = BeautifulSoup(f)

t = soup.find("table")
for row in t.findAll("tr"):
   cell = row.findAll("td")
   site = cell[0].text.strip()
   link = str(cell[3].text)
   links = map(str.strip,link.split(','))

   for s in links:
      print '"%s"-> "%s";' % (site,s)

print '}'
