.name "anti-zork"
.comment "YOU'RE NOT ALIIIIVE"

init:	sti r1, %:live, %1
		ld %4, r4

reset:	ld %0, r5

live:	live %1
		ldi %:reset, r5, r3
		add r3, r6, r6
		zjmp %312
		add r5, r4, r5
		sti r3, %300, r5
		ld %0, r6
		zjmp %:live
