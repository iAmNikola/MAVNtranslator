.globl main

.data
m1:	6

m2:	5

.text
main:
		I_LA	t0, m1
		I_LW	t1, 0(t0)
		I_LA	t0, m2
		I_LW	t0, 0(t0)
		I_ADD	t0, t1, t0
