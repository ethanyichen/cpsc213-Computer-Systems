.pos 0x100
				 ld $a, r0                # r0 = address of a
				 ld $3, r1                # r1 = 3
				 ld (r0, r1, 4), r1       # r1 = a[3]
				 ld $i, r2                # r2 = address of i
				 st r1, (r2)              # i = a[3]

				 ld (r2), r1              # r1 = i
				 ld (r0, r1, 4), r1       # r1 = a[i]
				 st r1, (r2)              # i = a[i]

				 ld $p, r1                # r1 = address of p
                 ld $j, r2                # r2 = address of j
                 st r2, (r1)              # p = &j

                 ld $4, r3                # r3 = 4
                 ld (r1), r2              # r2 = p
                 st r3, (r2)              # *p = 4

                 ld $2, r2                # r2 = 2
                 ld (r0, r2, 4), r2       # r2 = a[2]
                 shl $2, r2               # r2 = a[2] * 4 = index offset
                 add r0, r2               # r2 = address of a + (a[2] * 4) = $a[a[2]]
                 st r2, (r1)              # p = $a[a[2]]

                 ld $4, r2                # r2 = 4
                 ld (r0, r2, 4), r0       # r0 = a[4]
                 ld (r1), r1              # r1 = p
                 ld (r1), r2              # r2 = *p
                 add r0, r2               # r2 = *p + a[4]
                 st r2, (r1)              # *p = *p + a[4]
                 halt

.pos 0x1000
i:               .long 0x00000001         # i
.pos 0x2000
j:				 .long 0x00000002         # j
.pos 0x3000
p:  	   	     .long 0x00000003         # p
.pos 0x4000
a:  	   	     .long 0x00000000         # a[0]
     	   	     .long 0x00000003         # a[1]
				 .long 0x00000008         # a[2]
     	   	     .long 0x00000005         # a[3]
				 .long 0x00000003         # a[4]
				 .long 0x00000002         # a[5]
     	   	     .long 0x00000003         # a[6]
				 .long 0x00000003         # a[7]
				 .long 0x00000009         # a[8]
     	   	     .long 0x00000003         # a[9]