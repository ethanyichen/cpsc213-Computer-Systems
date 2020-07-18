.pos 0x1000
code:
                  ld   $i, r0              # r0 = &i
                  ld   (r0), r0            # r0 = i
                  ld   $s, r1              # r1 = &s
                  ld   (r1, r0, 4), r3     # r3 = s.x[i]
                  ld   $v0, r2             # r2 = &v0
                  st   r3, (r2)            # v0 = s.x[i]
                  ld   $v1, r2             # r2 = &v1
                  ld   8(r1), r3           # r3 = s_y
                  ld   (r3, r0, 4), r4     # r4 = s.y[i]
                  st   r4, (r2)            # v1 = s.y[i]
                  ld   12(r1), r3          # r3 = s_z
                  ld   (r3, r0, 4), r4     # r4 = s.z->x[i]
                  ld   $v2, r2             # r2 = &v2
                  st   r4, (r2)            # v2 = s.z->x[i]
                  ld   16(r3), r3          # r3 = s_z_z
                  inca r3                  # r3 = s_z_z_x[1]
                  inca r3                  # r3 = s_z_z_y[0]
                  ld   (r3, r0 , 4), r4    # r4 = s_z_z_y[i]
                  ld   $v3, r2             # r2 = &v3
                  st   r4, (r2)            # v3 = s.z->z->y[i]
                  halt

.pos 0x2000
static:
i:                .long 0x00000001         # i
v0:               .long 0x00000005         # v0
v1:               .long 0x00000006         # v1
v2:               .long 0x00000007         # v2
v3:               .long 0x00000008         # v3
s:                .long 0x00000002         # s.x[0]
                  .long 0x00000003         # s.x[1]
                  .long 0x00003000         # s.y
                  .long 0x00003008         # s.z

.pos 0x3000
heap:
s_y:              .long 0x00000005         # s.y[0]
                  .long 0x00000003         # s.y[1]
s_z:              .long 0x00000002         # s.z->x[0]
                  .long 0x00000007         # s.z->x[1]
                  .long 0x00000008         # s.z->y[0]
                  .long 0x00000004         # s.z->y[1]
                  .long 0x00004000         # s.z->z

.pos 0x4000
heap:
s_z_z:           .long 0x00000005         # s.z->z->x[0]
                 .long 0x00000003         # s.z->z->x[1]
                 .long 0x00000004         # s.z->z->y[0]
                 .long 0x00000002         # s.z->z->y[1]
                 .long 0x00005000         # s.z->z->z
