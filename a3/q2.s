.pos 0x100
                 ld $0, r0                # r0 = 0
                 ld $tmp, r1              # r1 = address of tmp
                 st r0, (r1)              # tmp = 0

                 ld $tos, r1              # r1 = address of tos
                 st r0, (r1)              # tos = 0

                 ld $a, r2                # r2 = address of a
                 ld (r2, r0, 4), r3       # r3 = a[0]
                 ld $s, r4                # r4 = address of s
                 ld (r1), r5              # r5 = tos
                 st r3, (r4, r5, 4)       # s[tos] = a[0]

                 inc r5                   # r5 = tos + 1
                 st r5, (r1)              # tos++

                 ld $1, r0                # r0 = 1
                 ld (r2, r0, 4), r3       # r3 = a[1]
                 st r3, (r4, r5, 4)       # s[tos] = a[1]

                 inc r5                   # r5 = tos + 1
                 st r5, (r1)              # tos++

                 ld $2, r0                # r0 = 2
                 ld (r2, r0, 4), r3       # r3 = a[2]
                 st r3, (r4, r5, 4)       # s[tos] = a[2]

                 inc r5                   # r5 = tos + 1
                 st r5, (r1)              # tos++

                 dec r5                   # r5 = tos - 1
                 st r5, (r1)              # tos--

                 ld (r4, r5, 4), r3       # r3 = s[tos]
                 ld $tmp, r2              # r2 = address of tmp
                 st r3, (r2)              # tmp = s[tos]

                 dec r5                   # r5 = tos - 1
                 st r5, (r1)              # tos--

                 ld (r4, r5, 4), r3       # r3 = s[tos]
                 ld (r2), r0              # r0 = tmp
                 add r3, r0               # r0 = tmp + s[tos]
                 st r0, (r2)              # tmp = tmp + s[tos]

                 dec r5                   # r5 = tos - 1
                 st r5, (r1)              # tos--

                 ld (r4, r5, 4), r3       # r3 = s[tos]
                 ld (r2), r0              # r0 = tmp
                 add r3, r0               # r0 = tmp + s[tos]
                 st r0, (r2)              # tmp = tmp + s[tos]
                 halt

.pos 0x1000
a:  	   	     .long 0x00000001         # a[0]
     	   	     .long 0x00000002         # a[1]
				 .long 0x00000003         # a[2]
.pos 0x2000
s:               .long 0x00000001         # s[0]
                 .long 0x00000002         # s[1]
                 .long 0x00000003         # s[2]
                 .long 0x00000004         # s[3]
                 .long 0x00000005         # s[4]
.pos 0x3000
tos:		     .long 0x00000001         # tos
.pos 0x4000
tmp:  	   	     .long 0x00000003         # tmp
