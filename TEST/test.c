#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "../libft/libft.h"

int main(void)
{
	char **str = ft_split(";ls|wc;;echo hello;;",';');

	int i = 0;
	while (str[i] != NULL)
	{
		printf("%s\n",str[i]);
		i++;
	}
	

	exit(1);
	return 0;
}