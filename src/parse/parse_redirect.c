
#include "../../include/parse.h"
#include "../../include/validator.h"

int is_red_token(t_token *token)
{
	if (RDIR <= token->type && token->type <= LLDIR)
		return (token->type);
	return (0);
}

t_list *get_red_filepath_token(t_list *cur_token)
{
	while (cur_token != NULL)
	{
		if (((t_token*)cur_token->content)->type == STR)
			break ;
	}
	return (cur_token);
}


int connect_redirect(int red_type,int red_fd,char *red_filepath)
{
	int open_mode;
	
	if (red_type == RDIR)
	{
		
	}
	else if (red_type == LDIR || red_type == LLDIR)
	{

	}
}

void set_red_fd(int *red_fd, int red_type)
{
	if (*red_fd > -1)
		return ;
	if (red_type == RDIR || red_type == RRDIR)
		*red_fd = 1;
	else if (red_type == LDIR || red_type == LLDIR)
		*red_fd = 0;
}

void parse_redirect(t_list *token_list)
{
	t_list *cur_token;
	t_list *last_token;
	int red_fd;
	int red_type;
	char *red_filepath;
	
	last_token = token_list;
	cur_token = token_list->next;
	while(cur_token != NULL)
	{
		if ((red_type = is_red_token(((t_token*)cur_token->content))) != 0)
		{
			// TODO: get userinput for heredoc
			// if (red_type == LLDIR)
			// {
			// 	get_heredoc();
			// }

			// TODO: error handle if red_fd is out of range of integer
			red_fd = -1;
			if (((t_token*)last_token->content)->type == REDFD)
				red_fd = ft_atoi(((t_token*)last_token->content)->word);
			set_red_fd(&red_fd, red_type);

			// TODO: error handle if get_red_filepath_token returns NULL
			cur_token = get_red_filepath_token(cur_token);
			red_filepath = ((t_token*)cur_token->content)->word;
			// TODO: error handle if file donesnt' exist
			connect_redirect(red_type, red_fd, red_filepath);
		}

		last_token = cur_token;
		cur_token = cur_token->next;
	}

	

}