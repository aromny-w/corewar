#include "disasm.h"

// CHECK MORE
int32_t bin_to_num(uint8_t *val, size_t len)
{
	int32_t	sign;
	int32_t	res;
	size_t	i;

	i = 0;
	res = 0;
	sign = val[0] & 0x80 ? 1 : 0; //check first bit
	while (i < len)
	{
		if (sign)
			val[len - i - 1] = ~val[len - i - 1];
		res += val[len - i - 1] << (8 * i); // (2^8)^i
		i++;
	}
	res += sign;
	return (sign ? -res : res);
}