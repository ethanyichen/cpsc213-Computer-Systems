.pos 0x100
		ld $0, r0			# r0 = temp_i = 0
		ld $n, r1			# r1 = &n
		ld (r1), r1			# r1 = n
		not r1				# r0 = ~n
		inc r1				# r0 = -n
		ld $c, r2			# r2 = &c
		ld (r2), r2			# r2 = temp_c
		ld $a, r3			# r3 = &a
		ld $b, r4			# r4 = &b
loop:
		mov r1, r5			# r5 = -n
		add r0, r5			# r5 = temp_i - n
		beq r5, done		# if (temp_i = n) goto done
		ld (r3, r0, 4), r5	# r5 = a[temp_i]
		ld (r4, r0, 4), r7	# r7 = b[temp_i]
		not r5				# r5 = ~a[temp_i]
		inc r5				# r5 = -a[temp_i]
		add r5, r7			# r7 = b[temp_i] - a[temp_i]
		beq r7, then		# if (b[temp_i] = a[temp_i]) goto then
		bgt r7, then		# if (b[temp_i] > a[temp_i]) goto then
		inc r2				# r2 = temp_c + 1
then: 	inc r0				# temp_i++
		br loop				# goto loop
done:
		ld $i, r1 			# r1 = &i
		st r0, (r1) 		# i = temp_i
		ld $c, r3			# r3 = &c
		st r2, (r3)			# c = temp_c
		halt



.pos 0x1000
i:  	.long -1
n:  	.long 5
a:  	.long 10
		.long 20
		.long 30
		.long 40
		.long 50
b:  	.long 11
		.long 20
		.long 28
		.long 44
		.long 48
c:  	.long 0



