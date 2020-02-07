.name "Test"
.comment "This is a test"

test:	live %2
		#add r16, r1, r1
		#live %-9223372036854775808
		#ld %2147483647, r1
		#zjmp %:test
