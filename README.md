WA FreeNet Scripts
==================

Various scripts to do with the West Australian Wireless Freenet
see http://www.wafreenet.org/

Mapping
-------

A test node map is on http://wafn.elwell.org.uk/

To update list of nodes from Network table

	./get_links.py | dot -Tpng > links.png

Output can be seen [here](http://wafn.elwell.org.uk/links.png)

To populate JSON with list of nodes, make sure you have the postions of the 
nodes in `pos.cfg` in the format

	[Roleystone]
	latlon = -32.099765,116.051615
	
	[Rottnest]
	latlon = -32.001830,115.521347

ie, standard configfile, and then run the python scripts, redirecting stdout

Monitoring
----------

The WebSense sketch/scripts are for the power / environmental monitoring on site. Presently based on a pull service on an EtherTen ardunio,  may be adapted later to a push model to central service.

