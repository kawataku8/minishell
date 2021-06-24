
#include "../../include/parse.h"
#include "../../include/validator.h"


void parse_redirect(t_cmd_node *cmd_node)
{
	t_list *cur_token;
	t_list *tmp_token;

	cur_token = cmd_node->token_list;
	while(cur_token != NULL)
	{
		if (((t_token*)cur_token->content)->type == RDIR || ((t_token*)cur_token->content)->type == LDIR)
		{
			tmp_token = cur_token;
			// TODO: redirect opの後にSTRが存在しない場合->エラー
			// maybe above case is already validated at the validator()
			while (tmp_token != NULL)
			{
				if (((t_token*)tmp_token->content)->type == STR)
					cmd_node->red_out_filepath = ((t_token*)tmp_token->content)->word;
				tmp_token = tmp_token->next;
			}
		}
		cur_token = cur_token->next;
	}

}