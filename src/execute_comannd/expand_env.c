#include "../../include/cmd.h"

int my_strcmp(const char *s1, const char *s2)
{
	while((unsigned char)*s1 == (unsigned char)*s2)
	{
		if(*s1 == '\0' && *s2 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}


char *get_value_from_envlist(char *key, t_doubly_list *env_list)
{
	t_env_node *cur_envnode;
	char *value;	

	cur_envnode = env_list->head;
	value = NULL;
	while (cur_envnode != NULL)
	{
		if (my_strcmp(key,cur_envnode->key) == 0)
		{
			value = ft_strdup(cur_envnode->value);
			return (value);
		}
		cur_envnode = cur_envnode->next;
	}
	return (NULL);
}

//input: "$NAME"
//output:"takuya"
//環境変数をkeyで探して、valueを返す
//見つからなければ NULL を返す
//key取り出すときの区切り　[スペース、バックスラッシュ、EOL]
char *get_env_from_token(char *word, t_doubly_list *env_list, int *i, int *j)
{
	char *key;
	char *value;

	*i = 0;
	value = NULL;
	while (word[*i] != '\0')
	{
		if (word[*i] == '$')
		{
			*j = *i + 1;
			while (word[*j] != '\0' && word[*j] != ' ' && word[*j] != '$' && word[*j] != '\\' )
				(*j)++;
			if (*j > *i + 1)
			{
				key = ft_substr(word,*i+1,*j-*i+1);
				value = get_value_from_envlist(key, env_list);
				free(key);
				if (value != NULL)
					return (value);
			}
		}
		(*i)++;
	}
	return (value);
}

// //input: "$NAME"
// //output: "oda"->"joe"
// //受け取ったtokenはfree()
// t_list *envvar_tokens(t_list *token, int quote_flag)
// {
// 	t_list *new_token;
// 	if(quote_flag)
// 		new_token = env_in_dquote(token);
// 	else
// 		new_token = env_out_dquote(token);
// 	return (new_token);
// }

// //input: "echo"->" "->"hello"->"$NAME"->";"
// //output:"echo"->" "->"hello"->"takuya"->";"
// t_list *expand_env(t_list *token_list, t_doubly_list *env_list)
// {
// 	char *env_word;
// 	t_list *cur_token;
// 	t_list *next_token;
// 	t_list *last_token;

// 	while(cur_token)
// 	{
// 		last_token;
// 		next_token;

// 		//一つのトークンの中にいくつもの＄,もしくは＄のvalueが＄の場合が有るので、
// 		//next_tokenに一つ展開した後、next_tokenにlast_token入れて
// 		//同じところをもう一回見てくようにする
// 		if((env_word = get_env_fromtoken()) != NULL)
// 		{
// 			new_token = envvar_tokens();
// 			last_token->next = new_token;
// 			// new_tokenの最後のnext = next_token;
// 			// last_token = new_tokenの最後
// 		}

// 		cur_token = next_token;
// 	}

// }