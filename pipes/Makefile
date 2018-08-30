named_echo_rcvr: named_echo_sndr
	gcc named_echo_rcvr.c -o named_echo_rcvr	
named_echo_sndr: unnamed_echoes
	gcc named_echo_sndr.c -o named_echo_sndr
unnamed_echoes:
	gcc unnamed_echoes.c -o unnamed_echoes
clean:
	rm named_echo_rcvr named_echo_sndr unnamed_echoes 
