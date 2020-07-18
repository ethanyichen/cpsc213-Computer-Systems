.pos 0x100
				 ld $data, r0             # r0 = address of data[0]
				 ld $i, r1                # r1 = address of i
				 ld (r1), r1              # r1 = i
				 ld (r0, r1, 4), r2       # r2 = data[i]
				 inc r1                   # r1 = i + 1
				 ld (r0, r1, 4), r0       # r0 = data[i + 1]
				 add r2, r0               # r0 = data[i] + data[i + 1]
				 ld $y, r1                # r1 = address of y
				 st r0, (r1)              # y = data[i] + data[i + 1]
				 ld (r1), r0              # r0 = y
				 ld $0xff, r1             # r1 = 0xff
				 and r1, r0               # r0 = y & 0xff
				 ld $x, r1                # r1 = address of x
				 st r0, (r1)              # x = y & 0xff
				 halt                     # halt
				 
.pos 0x1000
data:            .long 0x0000ff01         # data[0]
				 .long 0x0000ff22         # data[1]
				 .long 0x0000f323        # data[2]
				 .long 0x0000f674         # data[3]
.pos 0x2000
i:  	   	     .long 0x00000001         # i
.pos 0x3000
x:  	   	     .long 0x02000002         # x
.pos 0x4000
y:  	   	     .long 0x06000003         # y