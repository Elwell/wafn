#!/usr/bin/python

# parser to grab table from website and extract site names / AS numbers
# and spit out as json after merging with position info

import ConfigParser
import json

config = ConfigParser.ConfigParser()
config.read('pos.cfg')
fc = { "type": "FeatureCollection", "features": [] }
for Node in config.sections():
    latlon = config.get(Node,'latlon')
    pos = latlon.split(',')
    pos = map(float,pos)
    # geoJSON wans lon,lat
    lonlat = [pos[1],pos[0]]
    f = {"type": "Feature","properties":{"Node":Node},"geometry":{"type":"Point","coordinates":lonlat}}
    fc['features'].append(f)

print json.dumps(fc, indent=4,)
