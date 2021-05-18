#include <stdlib.h>
#include <stdio.h>

#include "../libft/libft.h"

int main(void)
{	

	char **split_words = ft_split("echo hello;;ls",';');
	
	int i = 0;
	while (split_words[i] != NULL)
	{
		printf("%s\n",split_words[i]);
		i++;
	}
	
	exit(1);
	return 0;
}