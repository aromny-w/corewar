.name "Test"
.comment "This is a test"

test:	live %-9223372036854775808
		ld %2147483647, r1
