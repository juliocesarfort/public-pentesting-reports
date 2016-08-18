#!/bin/sh

rm -f socktryall-*-*-*.out

for f in 2 17; do # PF_INET PF_PACKET
for t in 2 3 10; do # SOCK_DGRAM SOCK_RAW SOCK_PACKET
for p in 0 6 255 768; do # IPPROTO_IP IPPROTO_TCP IPPROTO_RAW htons(ETH_P_ALL)
#	strace -e socket ./sockanysniff $f $t $p 2>&1 |
#		tee socktryall-$f-$t-$p.out
	strace -e socket ./sockanysniff $f $t $p &> socktryall-$f-$t-$p.out
done; done; done
