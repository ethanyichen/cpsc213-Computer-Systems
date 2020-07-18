.pos 0x0
                 ld   $sb, r5			# stack pointer = address stack base
                 inca r5				# stack pointer = address after stack base
                 gpc  $6, r6  			# r6 = pc + 6 (set return address)
                 j    0x300   			# main()
                 halt
.pos 0x100								# pointer to int array
                 .long 0x00001000		# int *p = arr;
.pos 0x200
                 ld   (r5), r0            # r0 = a load first parameter from stack
                 ld   4(r5), r1           # r1 = b load second parameter from stack (callee prologue)
                 ld   $0x100, r2          # r2 = &p
                 ld   (r2), r2            # r2 = p = &arr
                 ld   (r2, r1, 4), r3     # r3 = arr[b]
                 add  r3, r0              # r0 = arr[b] + a
                 st   r0, (r2, r1, 4)     # arr[b] = arr[b] + a
                 j    (r6)                # return
.pos 0x300
                 ld   $-12, r0           # r0 = -12
                 add  r0, r5             # r5 = r0 + r5 = allocate space for local variable and return address (callee prologue)
                 st   r6, 8(r5)          # store return address to stack
                 ld   $1, r0             # r0 = 1
                 st   r0, (r5)           # save value of local c to stack
                 ld   $2, r0             # r0 = 2
                 st   r0, 4(r5)          # save value of local d to stack
                 ld   $-8, r0            # r0 = -8
                 add  r0, r5             # allocate space for ping's parameter (caller prologue)
                 ld   $3, r0             # r0 = 3
                 st   r0, (r5)           # save value of first parameter 3 to stack
                 ld   $4, r0             # r0 = 4
                 st   r0, 4(r5)          # save value of second parameter 4 to stack
                 gpc  $6, r6             # set return address
                 j    0x200              # ping(3, 4)
                 ld   $8, r0             # r0 = 8
                 add  r0, r5             # deallocate space of parameters (caller epilogue)
                 ld   (r5), r1           # r1 = c; load value of local c from stack
                 ld   4(r5), r2          # r2 = d; load value of local d from stack
                 ld   $-8, r0            # r0 = -8;
                 add  r0, r5             # allocate space for ping's parameter (caller prologue)
                 st   r1, (r5)           # save value of first parameter c to stack
                 st   r2, 4(r5)          # save value of second parameter d to stack
                 gpc  $6, r6             # set return address
                 j    0x200              # ping(c,d)
                 ld   $8, r0             # r0 = 8
                 add  r0, r5             # deallocate space of parameters (caller epilogue)
                 ld   8(r5), r6          # load return address from stack
                 ld   $12, r0            # r0 = 12
                 add  r0, r5             # deallocate space of local variables and return address on stack (callee epilogue)
                 j    (r6)               # return
.pos 0x1000
                 .long 0        # arr[0]
                 .long 0        # arr[1]
                 .long 0        # arr[2]
                 .long 0        # arr[3]
                 .long 0        # arr[4]
                 .long 0        # arr[5]
                 .long 0        # arr[6]
                 .long 0        # arr[7]
                 .long 0        # arr[8]
                 .long 0        # arr[9]
.pos 0x8000
# These are here so you can see (some of) the stack contents.
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
sb: .long 0
