# KF Game Port
iptables -A FORWARD -p udp --destination-port 7707 -j ACCEPT
# KF Query Port
iptables -A FORWARD -p udp --destination-port 7708 -j ACCEPT
# GameSpy KF
iptables -A FORWARD -p udp --destination-port 7717 -j ACCEPT
# KF Master Server
iptables -A FORWARD -p tcp --destination-port 28852 -j ACCEPT
# KF ListenPort
iptables -A FORWARD -p tcp --destination-port 8075 -j ACCEPT
# KF Steam Port
iptables -A FORWARD -p udp --destination-port 20560 -j ACCEPT
# COD4 Port
iptables -A FORWARD -p udp --destination-port 28960 -j ACCEPT
# SSH Port
iptables -A FORWARD -p udp --destination-port 28960 -j ACCEPT
# SSH Port
iptables -A FORWARD -p tcp --destination-port 22 -j ACCEPT
# Web Servers
iptables -A FORWARD -p tcp --destination-port 80 -j ACCEPT
# OpenVPN Ports
iptables -A FORWARD -p udp --destination-port 1194 -j ACCEPT
# OpenVPN Ports
iptables -A FORWARD -p tcp --destination-port 1194 -j ACCEPT

# OpenVPN Ports
iptables -A FORWARD -p tcp --destination-port 1777 -j ACCEPT
# OpenVPN Ports
iptables -A FORWARD -p udp --destination-port 1777 -j ACCEPT

# OpenVPN Ports
iptables -A FORWARD -p tcp --destination-port 1778 -j ACCEPT
# OpenVPN Ports
iptables -A FORWARD -p udp --destination-port 1778 -j ACCEPT

# Mumble Servers
iptables -A FORWARD -p udp --destination-port 64738 -j ACCEPT
# Mumble Servers
iptables -A FORWARD -p tcp --destination-port 64738 -j ACCEPT

# DC Port (Only allow connecting, no downloads)
iptables -A FORWARD -p tcp --destination-port 7777 -j ACCEPT

# DC Port (Only allow connecting, no downloads)
iptables -A FORWARD -p udp --destination-port 7777 -j ACCEPT
# IRC
iptables -A FORWARD -p udp --destination-port 6667 -j ACCEPT
# AirView
iptables -A FORWARD -p udp --destination-port 18888 -j ACCEPT
# Sensors
iptables -A FORWARD -p tcp --destination-port 2014 -j ACCEPT
# SDR
iptables -A FORWARD -p tcp --destination-port 1234 -j ACCEPT


### SOURCE PORT BELOW

# KF Game Port
iptables -A FORWARD -p udp --source-port 7707 -j ACCEPT
# KF Query Port
iptables -A FORWARD -p udp --source-port 7708 -j ACCEPT
# GameSpy KF
iptables -A FORWARD -p udp --source-port 7717 -j ACCEPT
# KF Master Server
iptables -A FORWARD -p tcp --source-port 28852 -j ACCEPT
# KF ListenPort
iptables -A FORWARD -p tcp --source-port 8075 -j ACCEPT
# KF Steam Port
iptables -A FORWARD -p udp --source-port 20560 -j ACCEPT
# COD4 Port
iptables -A FORWARD -p udp --source-port 28960 -j ACCEPT
# SSH Port
iptables -A FORWARD -p udp --source-port 28960 -j ACCEPT
# SSH Port
iptables -A FORWARD -p tcp --source-port 22 -j ACCEPT
# Web Servers
iptables -A FORWARD -p tcp --source-port 80 -j ACCEPT
# OpenVPN Ports
iptables -A FORWARD -p udp --source-port 1194 -j ACCEPT
# OpenVPN Ports
iptables -A FORWARD -p tcp --source-port 1194 -j ACCEPT

# OpenVPN Ports
iptables -A FORWARD -p tcp --source-port 1777 -j ACCEPT
# OpenVPN Ports
iptables -A FORWARD -p udp --source-port 1777 -j ACCEPT

# OpenVPN Ports
iptables -A FORWARD -p tcp --source-port 1778 -j ACCEPT
# OpenVPN Ports
iptables -A FORWARD -p udp --source-port 1778 -j ACCEPT

# Mumble Servers
iptables -A FORWARD -p udp --source-port 64738 -j ACCEPT
# Mumble Servers
iptables -A FORWARD -p tcp --source-port 64738 -j ACCEPT

# DC Port (Only allow connecting, no downloads)
iptables -A FORWARD -p tcp --source-port 7777 -j ACCEPT

# DC Port (Only allow connecting, no downloads)
iptables -A FORWARD -p udp --source-port 7777 -j ACCEPT

# IRC
iptables -A FORWARD -p udp --source-port 6667 -j ACCEPT

# AirView
iptables -A FORWARD -p udp --source-port 18888 -j ACCEPT
# Sensors
iptables -A FORWARD -p tcp --source-port 2014 -j ACCEPT
# SDR
iptables -A FORWARD -p tcp --source-port 1234 -j ACCEPT

iptables -A FORWARD -p tcp -j DROP
iptables -A FORWARD -p udp -j DROP
