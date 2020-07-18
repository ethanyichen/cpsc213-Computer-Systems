.pos 0x100
start:
    ld $sb, r5			# stack pointer = address of stack base
    inca    r5			# stack pointer = address of after stack base 
    gpc $6, r6			# r6 = pc + 6 (set return address)
    j main				# call main()
    halt				# stop

f:
    deca r5				# allocate callee part of f's frame (callee f prologue)
    ld $0, r0			# r0 = 0 = bit_count
    ld 4(r5), r1		# r1 = l0 = x[temp_i] load value of argument x[temp_i] from stack
    ld $0x80000000, r2	# r2 = 0x80000000
f_loop:
    beq r1, f_end		# if (x[temp_i] = 0) goto +6
    mov r1, r3			# r3 = x[temp_i]
    and r2, r3			# r3 = x[temp_i] & 0x80000000 result is either 0x80000000 or 0x00000000
    beq r3, f_if1		# if ((x[temp_i] & 0x80000000) = 0) goto +1
    inc r0				# bit_count++
f_if1:
    shl $1, r1			# r1 = x[temp_i] << 1
    br f_loop			# goto -7
f_end:
    inca r5				# deallocate callee part of f's frame (callee f epilogue)
    j(r6)				# return bit_count

main:
    deca r5				# allocate callee part of main's frame (callee main prologue)
    deca r5				# allocate callee part of main's frame
    st r6, 4(r5)		# store return address to stack
    ld $8, r4			# r4 = temp_i = 8 array/loop counter
main_loop:
    beq r4, main_end	# if (temp_i = 0) goto +11
    dec r4				# temp_i--
    ld $x, r0			# r0 = &x
    ld (r0,r4,4), r0	# r0 = a0 = x[temp_i] value of argument
    deca r5				# allocate space for x[temp_i] on the stack (caller main prologue)
    st r0, (r5)			# l0 = a0 store value of argument x[temp_i] to stack
    gpc $6, r6			# set return address
    j f					# call f(x[temp_i])
    inca r5				# deallocate x[temp_i] from the stack (caller main epilogue)
    ld $y, r1			# r1 = &y
    st r0, (r1,r4,4)	# y[temp_i] = f(x[temp_i]) = bit_count
    br main_loop		# goto -13
main_end:
    ld 4(r5), r6		# load return address from stack (callee main epilogue)
    inca r5				# deallocate callee part from main's frame
    inca r5				# deallocate callee part from main's frame
    j (r6)				# return

.pos 0x2000
x:
    .long 1				# x[0]
    .long 2				# x[1]
    .long 3				# x[2]
    .long -1			# x[3]
    .long -2			# x[4]
    .long 0				# x[5]
    .long 184			# x[6]
    .long 340057058		# x[7]

y:
    .long 0				# y[0]
    .long 0				# y[1]
    .long 0				# y[2]
    .long 0				# y[3]
    .long 0				# y[4]
    .long 0				# y[5]
    .long 0				# y[6]
    .long 0				# y[7]

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

