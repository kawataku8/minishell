#include <stdio.h>

int		loop(int x)
{
	if (x <= 1)
	{
		return (x);
	}
	printf("%d\n",x);
	x /= 2;
	
	return (loop(x));
}

int		main(void)
{
	int		x = 10;

	x = loop(x);
	printf("%d\n",x);
}