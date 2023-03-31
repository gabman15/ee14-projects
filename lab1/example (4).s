; --- INSTRUCTION MEMORY ---
	AREA main, CODE, READONLY
	EXPORT __main
	ENTRY
__main PROC
	MOVS r1,#0x00
	LDR r2,=total
	STR r1,[r2,#0x00]
	MOVS r0,#0x00
	B Check
Loop LDR r1,=a
	LDR r1,[r1,r0,LSL #2]
	LDR r2,=total
	LDR r2,[r2,#0x00]
	ADD r1,r1,r2
	LDR r2,=total
	STR r1,[r2,#0x00]
	ADDS r0,r0,#1
Check CMP r0,#0x0A
	BLT Loop
	NOP
Stop B Stop
	ENDP
 ; --- DATA MEMORY ---
	AREA data, DATA, READWRITE
a DCD 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
total DCD 0
	END
