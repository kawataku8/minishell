
#include "../include/parse.h"
#include "../libft/libft.h"

#include <stdlib.h>
#include <stdio.h>

void del_tokennode(void *content)
{
	free(((t_token*)content)->word);
	free((t_token*)content);
}

int main(void)
{
	t_list *lst = NULL;
	t_token *newtoken;


	newtoken = (t_token*)malloc(sizeof(t_token));
	newtoken->type = 1;
	newtoken->word = ft_strdup("FIRST");
	ft_lstadd_back(&lst,ft_lstnew((void*)newtoken));

	newtoken = (t_token*)malloc(sizeof(t_token));
	newtoken->type = 2;
	newtoken->word = ft_strdup("SECOND");
	ft_lstadd_back(&lst,ft_lstnew((void*)newtoken));

	
	t_list *cur_lst = lst;
	while(cur_lst != NULL)
	{
		printf("%d,%s\n",((t_token*)cur_lst->content)->type,((t_token*)cur_lst->content)->word);
		cur_lst = cur_lst->next;
	}
	printf("%d,%s\n",((t_token*)lst->content)->type,((t_token*)lst->content)->word);
	

	// ft_lstdelone(lst,&del_content);
	ft_lstclear(&lst, &del_tokennode);
	
	return 0;
}