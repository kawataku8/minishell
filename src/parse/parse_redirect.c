
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
		{
			((t_token*)cur_token->content)->type = REDFILEPATH;
			break ;
		}
		cur_token = cur_token->next;
	}
	return (cur_token);
}

//input	:
//output:good returns 1, open error returns 0
//description: 
int connect_redirect(int red_type,int red_fd,char *red_filepath)
{
	int open_mode;
	int file_fd;

	if (red_type == RDIR)
		file_fd = open(red_filepath, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else if (red_type == RRDIR)
		file_fd = open(red_filepath, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	else if (red_type == LDIR || red_type == LLDIR)
	{
		// TODO: if tyep is LLDIR red_filepath == NULL
		// if (red_type == LLDIR)
		// 	red_filepath = "../tmp/heredoc_tmp";
		file_fd = open(red_filepath, O_RDWR, S_IRWXU);
	}

	if (file_fd == -1)
	{
		// TODO: check errno and error handle 
		return 0;
	}
	close(red_fd);
	dup2(file_fd, red_fd);
	close(file_fd);

	return (1);
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
	char *heredoc_delim;
	
	last_token = token_list;
	cur_token = token_list->next;
	while(cur_token != NULL)
	{
		// token->type が >,>>,<,>>のどれかで if条件true
		if ((red_type = is_red_token(((t_token*)cur_token->content))) != 0)
		{

			// TODO: error handle if red_fd is out of range of integer
			red_fd = -1;
			if (((t_token*)last_token->content)->type == REDFD)
				red_fd = ft_atoi(((t_token*)last_token->content)->word);

			// >, >> -> red_fd = 1.   <, << -> red_fd = 0
			set_red_fd(&red_fd, red_type);


			// TODO: error handle if get_red_filepath_token returns NULL
			if (red_type == LLDIR)
				red_filepath = ft_strdup("tmp/heredoc_tmp");
			else
			{
				cur_token = get_red_filepath_token(cur_token);
				red_filepath = ((t_token *)cur_token->content)->word;
			}
			// TODO: error handle if file donesnt' exist
			
			connect_redirect(red_type, red_fd, red_filepath);
			
			if (red_type == LLDIR)
				free(red_filepath);
		}

		last_token = cur_token;
		cur_token = cur_token->next;
	}

	

}