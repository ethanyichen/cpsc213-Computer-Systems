.pos 0x0
                 ld   $0x1028, r5
                 ld   $0xfffffff4, r0
                 add  r0, r5            # sp = stack base
                 ld   $0x200, r0        # r0 = &num[0]
                 ld   0x0(r0), r0       # r0 = num[0]
                 st   r0, 0x0(r5)       # store argument num[0] to stack
                 ld   $0x204, r0        # r0 = &num[1]
                 ld   0x0(r0), r0       # r0 = num[1]
                 st   r0, 0x4(r5)       # store argument num[1] to stack
                 ld   $0x208, r0        # r0 = &num[2]
                 ld   0x0(r0), r0       # r0 = num[2]
                 st   r0, 0x8(r5)       # store argument num[2] to stack
                 gpc  $6, r6            # set return address
                 j    0x300             # call q2(num[0], num[1], num[2])
                 ld   $0x20c, r1        # r1 = &n
                 st   r0, 0x0(r1)       # n = q2(num[0], num[1], num[2])
                 halt
.pos 0x200
                 .long 0x00000000       # num[0]
                 .long 0x00000000       # num[1]
                 .long 0x00000000       # num[2]
                 .long 0x00000000       # n
.pos 0x300
                 ld   0x0(r5), r0       # r0 = x
                 ld   0x4(r5), r1       # r1 = y
                 ld   0x8(r5), r2       # r2 = z
                 ld   $0xfffffff6, r3   # r3 = -10
                 add  r3, r0            # r0 = x - 10
                 mov  r0, r3            # r3 = x - 10
                 not  r3                # r3 = ~(x - 10)
                 inc  r3                # r3 = 10 - x
                 bgt  r3, L6            # if (x < 10) goto L6
                 mov  r0, r3            # r3 = x - 10
                 ld   $0xfffffff8, r4   # r4 = -8
                 add  r4, r3            # r3 = x - 18
                 bgt  r3, L6            # if (x > 18) goto L6
                 ld   $0x400, r3        # r3 = &jt
                 ld   (r3, r0, 4), r3   # r3 = jt[x-10]
                 j    (r3)              # goto *jt[x-10]
.pos 0x330
                 add  r1, r2            # r2 = y + z
                 br   L7                # goto L7
                 not  r2                # r2 = ~z
                 inc  r2                # r2 = -z
                 add  r1, r2            # r2 = y - z
                 br   L7                # goto L7
                 not  r2                # r2 = ~z
                 inc  r2                # r2 = -z
                 add  r1, r2            # r2 = y - z
                 bgt  r2, L0            # if (y > z) goto L0
                 ld   $0x0, r2          # r2 = 0
                 br   L1                # goto L1
L0:              ld   $0x1, r2          # r2 = 1
L1:              br   L7                # goto L7
                 not  r1                # r1 = ~y
                 inc  r1                # r1 = -y
                 add  r2, r1            # r1 = z - y
                 bgt  r1, L2            # if (z > y) goto L2
                 ld   $0x0, r2          # r2 = 0
                 br   L3                # goto L3
L2:              ld   $0x1, r2          # r2 = 1
L3:              br   L7                # goto L7
                 not  r2                # r2 = ~z
                 inc  r2                # r2 = -z
                 add  r1, r2            # r2 = y - z
                 beq  r2, L4            # if (y = z) goto L4
                 ld   $0x0, r2          # r2 = 0
                 br   L5                # goto L5
L4:              ld   $0x1, r2          # r2 = 1
L5:              br   L7                # goto L7
L6:              ld   $0x0, r2          # r2 = 0
                 br   L7                # goto L7
L7:              mov  r2, r0            # r0 = q2(num[0], num[1], num[2])
                 j    0x0(r6)           # return to main
.pos 0x400
                 .long 0x00000330       # jt[0]
                 .long 0x00000384       # jt[1]
                 .long 0x00000334       # jt[2]
                 .long 0x00000384       # jt[3]
                 .long 0x0000033c       # jt[4]
                 .long 0x00000384       # jt[5]
                 .long 0x00000354       # jt[6]
                 .long 0x00000384       # jt[7]
                 .long 0x0000036c       # jt[8]
.pos 0x1000
                 .long 0x00000000       # stack
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
                 .long 0x00000000
