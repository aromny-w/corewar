.name "TestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTestTest"
.comment "This is a test"

shhhhhhhhhhesh:
test:	aff r1	
		#sti r1, %:live, %1
		#sti r1, %:live, %1
		#ld %-19, r1
		#live %9223372036854775808
		#add r16, r1, r1
		#live %-9223372036854775808
		#ld %2147483647, r1
		#zjmp %:test

live:	live %0

