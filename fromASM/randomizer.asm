list p=18f25k22
#include "p18f25k22.inc"

UDATA 
base RES 1
CODE
GLOBAL Randomize

Randomize:
	movwf		base
	rlcf			base,W
	rlcf			base,W
	BTFSC		base,4
	xorlw		1
	btfsc		base,5
	xorlw		1
	btfsc		base,3
	xorlw		1
	;movwf		base
return

end
	