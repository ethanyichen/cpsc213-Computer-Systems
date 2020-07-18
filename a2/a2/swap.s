.pos 0x100
                 
				 ld   $t, r0              # r0 = address of t
				 ld   (r0), r1            # r1 = t
				 ld   $array, r2          # r2 = address of array[0]
				 ld   (r2), r3            # r3 = array[0]
				 st   r3, (r0)            # t = array[0]
				 
				 mov  r2, r4
				 inca r4                  # r4 = address of array[1]
				 ld   (r4), r5            # r5 = array[1]
				 st   r5, (r2)            # array[0] = array[1]
				 
				 ld   (r0), r1            # r1 = t
				 st   r1, (r4)			  # array[1] = t
				 halt                     # halt
				 
.pos 0x1000
t:               .long 0x00000001         # t
.pos 0x2000
array:  	     .long 0x00000002         # array[0]
                 .long 0x00000003         # array[1]