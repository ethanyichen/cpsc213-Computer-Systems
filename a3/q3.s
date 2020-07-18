.pos 0x100
                 ld $3, r0                # r0 = 3
                 ld $a, r1                # r1 = address of a
                 st r0, (r1)              # a = 3

                 ld $p, r0                # r0 = address of p
                 st r1, (r0)              # p = &a

                 ld (r0), r1              # r1 = p
                 ld (r1), r2              # r2 = *p
                 dec r2                   # r2 = *p - 1
                 st r2, (r1)              # *p = *p - 1

                 ld $b, r1                # r1 = address of b = &b[0]
                 st r1, (r0)              # p = &b[0]

                 ld (r0), r1              # r1 = p = address of b
                 inca r1                  # r1 = p + 4 = address of b[1]
                 st r1, (r0)              # p++

                 ld $b, r5                # r5 = address of b
                 ld $a, r2                # r2 = address of a
                 ld (r2), r2              # r2 = a
                 ld (r5, r2, 4), r3       # r3 = b[a]
                 ld (r0), r4              # r4 = p
                 st r3, (r4, r2, 4)       # p[a] = b[a]

                 ld (r5), r1              # r1 = b = b[0]
                 st r1, 12(r4)            # *(p+3) = b[0]
                 halt

.pos 0x1000
a:		         .long 0x00000001         # a
.pos 0x2000
p:  	   	     .long 0x00000003         # p
.pos 0x3000
b:               .long 0x00000001         # b[0]
                 .long 0x00000002         # b[1]
                 .long 0x00000003         # b[2]
                 .long 0x00000004         # b[3]
                 .long 0x00000005         # b[4]
