.pos 0x100
start:
    gpc $6, r6
    j updateAverage
    gpc $6, r6
    j sort
    gpc $6, r6
    j median
    halt






updateAverage:
    ld $s, r0               # r0 = &s
	ld (r0), r0				# r0 = s
    ld $0, r1               # r1 = 0
    ld $n, r2               # r2 = &n
    ld(r2), r2              # r2 = n
    not r2                  # r2 = ~n
    inc r2                  # r2 = -n

UAloop:
    mov r1, r3              # r3 = r1
    add r2, r3              # r3 = r1 - n
    not r3                  # r3 = ~(r1-n)
    inc r3                  # r3 = n - r1
    beq r3, UAdone          # if r1 = n, goto UAdone
	
	mov r0, r3
	mov r1, r4
	shl $3, r4
	add r4, r3
	mov r1, r4
	shl $4, r4
	add r4, r3
	
average:
    ld $0, r4               # r4 = sumOfGrades
    inca r3                 # r3 = &stu.grade[0]
    ld (r3), r7             # r7 = grade[0]
    add r7, r4              # r4 = grade[0]
    inca r3                 # r3 = &stu.grade[1]
    ld (r3), r7             # r7 = grade[1]
    add r7, r4              # r4 = grade[0] + grade[1]
    inca r3                 # r3 = &stu.grade[2]
    ld (r3), r7             # r7 = grade[2]
    add r7, r4              # r4 = grade[0] + grade[1] + grade[2]
    inca r3                 # r3 = &stu.grade[3]
    ld (r3), r7             # r7 = grade[3]
    add r7, r4              # r4 = grade[0] + grade[1] + grade[2] + grade[3]
    shr $2, r4              # r4 = sum/4 = average
    inca r3					# r3 = &stu.average
    st r4, (r3)             # store the computed average to memory

    inc r1                  # r1 ++
    br UAloop               # loop again

UAdone:
    j (r6)      # return




# swap addresses of student A and student B
# r4 = index of student A = smaller index
# r5 = index of student B = larger index
# r0, r1, r7 are used for calculations

# r4 = index of student A = smaller index
# r5 = index of student B = larger index
# r0, r1, r7 are used for calculations




# r4 = j-1 = index of student A = smaller index
# r5 = j   = index of student B = larger index
# r0, r1, r3, r7 are used for calculations
# r2 = i
sort:		ld $n, r2			# r2 = address of n
			ld (r2), r2			# r2 = n = number of students
			dec r2				# r2 = i = n-1
outloop:	beq r2, end_sort	# if (i = 0) goto +13
			ld $1, r5			# r5 = j = 1
inloop:		mov r2, r3			# r3 = i
			not r3				# r3 = ~i
			inc r3				# r3 = -i
			add r5, r3			# r3 = j - i
			bgt r3, end_inloop	# if (j > i) goto +7
			mov r5, r4			# r4 = j
			dec r4				# r4 = j-1

comp_avg:	ld $s, r3			# r3 = address of s
			ld (r3), r7
			mov r4, r0
			shl $3, r0
			add r0, r7
			mov r4, r0
			shl $4, r0
			add r0, r7			# r7 = address of student A
			ld 20(r7), r0		# r0 = average of student A
			
			ld (r3), r3
			mov r5, r1
			shl $3, r1
			add r1, r3
			mov r5, r1
			shl $4, r1
			add r1, r3			# r3 = address of student B
			ld 20(r3), r1		# r1 = average of student B
			
			mov r0, r4
			not r4
			inc r4              # r0 = -r0
			add r1, r4			# r4 = r4 - r0 = (if r4 is positive, average of student B is greater than A)
			bgt r4, end_if		# if (average of student B > A) goto end_if

swap: 		st r0, 20(r3)		# student A average = student B average
			st r1, 20(r7)  		# student B average = student A average
			ld (r7), r0			# r0 = student A ID
			ld (r3), r1			# r1 = student B ID
			st r0, (r3)			# student B ID = student A ID
			st r1, (r7)  		# student A ID = student B ID
			ld 4(r7), r0		# r0 = student A grade 1
			ld 4(r3), r1		# r1 = student B grade 1
			st r0, 4(r3)		# student B grade 1 = student A grade 1
			st r1, 4(r7)  		# student A grade 1 = student B grade 1
			ld 8(r7), r0		# r0 = student A grade 2
			ld 8(r3), r1		# r1 = student B grade 2
			st r0, 8(r3)		# student B grade 1 = student A grade 2
			st r1, 8(r7)  		# student A grade 1 = student B grade 2
			ld 12(r7), r0		# r0 = student A grade 3
			ld 12(r3), r1		# r1 = student B grade 3
			st r0, 12(r3)		# student B grade 1 = student A grade 3
			st r1, 12(r7)  		# student A grade 1 = student B grade 3
			ld 16(r7), r0		# r0 = student A grade 4
			ld 16(r3), r1		# r1 = student B grade 4
			st r0, 16(r3)		# student B grade 1 = student A grade 4
			st r1, 16(r7)  		# student A grade 1 = student B grade 4

end_if:	    inc r5				# r5 = j++
			br inloop			# goto -8
end_inloop:	dec r2				# r2 = i--
        	br outloop			# goto -14
end_sort:	j (r6)				# return



median:     ld $s, r7			# r7 = &s
			ld (r7), r7
            ld $n, r0			# r0 = &n
            ld (r0), r0			# r0 = n
            shr $1, r0			# r0 = r0 / 2
			
			mov r0, r1			# r0 = r1 = index of the median
			shl $3, r0			# r0 = r0 * 8
			shl $4, r1			# r1 = r0 * 16
			add r1, r0			# r0 = r0 + r1 = address offset
			add r0, r7			# r7 = r0 + r7 = address of the median student
			ld (r7), r7			# r7 = student id of the median
			
            ld $m, r0			# r0 = &m
            st r7, (r0)			# m = median student id
            j (r6)				# return




.pos 0x1000
n:  	.long 7 # just one student
m:  	.long 0 # put the answer here
s:  	.long base
		
.pos 0x4000
base:	.long 0001 # student ID
		.long 68 # grade 0
		.long 85 # grade 1
		.long 92 # grade 2
		.long 37 # grade 3
		.long 0 # computed average
		.long 0002 # student ID
		.long 0 # grade 0
		.long 3 # grade 1
		.long 68 # grade 2
		.long 99 # grade 3
		.long 0 # computed average
		.long 0003 # student ID
		.long 85 # grade 0
		.long 86 # grade 1
		.long 87 # grade 2
		.long 88 # grade 3
		.long 0 # computed average
		.long 0004 # student ID
		.long 85 # grade 0
		.long 76 # grade 1
		.long 55 # grade 2
		.long 88 # grade 3
		.long 0 # computed average
		.long 0005 # student ID
		.long 1 # grade 0
		.long 76 # grade 1
		.long 96 # grade 2
		.long 88 # grade 3
		.long 0 # computed average
		.long 0006 # student ID
		.long 85 # grade 0
		.long 90 # grade 1
		.long 90 # grade 2
		.long 88 # grade 3
		.long 0 # computed average
		.long 0007 # student ID
		.long 70 # grade 0
		.long 76 # grade 1
		.long 96 # grade 2
		.long 88 # grade 3
		.long 0 # computed average
