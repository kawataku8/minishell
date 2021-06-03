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

//input: "hello $TEST"
//output: 1->exist, 0->nah
//description: 文字列に環境変数があるかをチェックする
//ある->i, j は環境変数の文字indexを示す
int envvar_exist(char *word, int *i, int *j)
{
	*i = 0;
	while (word[*i] != '\0')
	{
		if (word[*i] == '\\' && word[*i + 1] != '\0')
		{
			i += 2;
			continue;
		}
		if (word[*i] == '$')
		{
			*j = *i + 1;
			while (word[*j] != '\0' && word[*j] != ' ' && word[*j] != '$' && word[*j] != '\\')
				(*j)++;
			if (*j > *i + 1)
				return (1);
		}
		(*i)++;
	}
	return (0);
}

//input: "$NAME"
//output:"takuya"
//環境変数をkeyで探して、valueを返す
//見つからなければ NULL を返す
//key取り出すときの区切り　[スペース、バックスラッシュ、EOL]
char *get_env_value(char *word, t_doubly_list *env_list)
{
	int i;
	int j;
	char *key;
	char *value;

	value = NULL;
	if (envvar_exist(word,&i,&j))
	{
		key = ft_substr(word,i+1,j-(i+1));
		value = get_value_from_envlist(key, env_list);
		free(key);
		if (value != NULL)
			return (value);
	}
	return (value);
}

//input: "ABC $TEST 123"
//output:"ABC hello   world 123"
char *make_new_word(char *word, char *env_value)
{
	char *new_word;
	int env_i;
	int env_j;
	int new_word_len;
	
	envvar_exist(word,&env_i, &env_j);
	new_word_len = ft_strlen(word) + (ft_strlen(env_value) - (env_j-env_i));
	new_word = (char*)malloc(sizeof(char) * new_word_len + 1);
	ft_strlcpy(new_word, word, new_word_len + 1);
	ft_strlcpy(new_word + env_i, env_value, new_word_len + 1);
	ft_strlcpy(new_word + (env_i + ft_strlen(env_value)), word + env_j, new_word_len + 1);
	return (new_word);
}

void free_splitstr(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
}


//input	  	:word = "12$TEST$USER"; env_value = "hello world"
//output	:new_tokenlist = "12hello"->"world$USER"
//description: 
//normal fieldのwordにいる環境変数を展開する
//valueをスペースでスプリット
//$より前に文字がある場合は、スプリットされる前に先頭にくっつけてからスプリット
t_list *make_new_tokens(char *word, char *env_value)
{
	t_list *new_tokenlist;
	t_token *new_token;
	char *new_word;
	char **split_newword;
	int i;
	int j;
	int l;

	new_tokenlist = NULL;
	new_word = make_new_word(word, env_value);
	split_newword = ft_split(new_word, ' ');
	l = 0;
	while (split_newword[l] != NULL)
	{
		new_token = (t_token *)malloc(sizeof(t_token));
		new_token->type = STR;
		new_token->word = split_newword[l++];
		ft_lstadd_back(&new_tokenlist, ft_lstnew((void*)new_token));
	}
	free(new_word);
	return (new_tokenlist);
}

// //input: "$NAME"
// //output: "oda"->"joe"
// //受け取ったtokenはfree()
t_list *expand_env_in_token(t_list *token, char *env_value, int flag_dquote)
{
	t_list	*new_tokenlist;
	t_token	*new_token;
	char	*new_word;

	new_tokenlist = NULL;
	if (flag_dquote)
	{
		new_word = make_new_word(((t_token*)token->content)->word, env_value);
		new_token = (t_token *)malloc(sizeof(t_token));
		new_token->type = STR;
		new_token->word = new_word;
		ft_lstadd_back(&new_tokenlist, ft_lstnew((void*)new_token));
	}
	else
		new_tokenlist = make_new_tokens(((t_token*)token->content)->word, env_value);
	return (new_tokenlist);
}

void free_token(t_list *token)
{
	free(((t_token*)token->content)->word);
	free(token->content);
	free(token);
}

// //input: "echo"->" "->"hello"->"$NAME"->";"
// //output:"echo"->" "->"hello"->"takuya"->";"
// //t_list->content == t_token
void expand_env(t_list *token_list, t_doubly_list *env_list)
{
	int i;
	int j;
	int flag_dquote;
	char *env_value;
	t_list *cur_token;
	t_list *new_tokenlist;
	t_list *next_token;
	t_list *last_token;
	
	flag_dquote = 0;
	cur_token = token_list;
	while(cur_token != NULL)
	{
		if ((((t_token*)cur_token->content)->type) == DQUOTE)
			flag_dquote ^= 1;
		printf("hello\n");	
		//一つのトークンの中にいくつもの＄,もしくは＄のvalueが＄の場合が有るので、
		//next_tokenに一つ展開した後、next_tokenにlast_token入れて
		//同じところをもう一回見てくようにする
		if ((env_value = get_env_value(((t_token*)cur_token->content)->word, env_list)) != NULL)
		{
			printf("morning\n");
			new_tokenlist = expand_env_in_token(cur_token, env_value, flag_dquote);
			next_token = cur_token->next;
			//new_tokenlistの前後のつなぎ合わせ
			//TODO:cur_token->nextがNULLの時やばいかも
			ft_lstadd_back(&new_tokenlist,next_token);
			if (last_token != NULL)
				last_token->next = new_tokenlist;
			free(cur_token);
			cur_token = new_tokenlist;
			continue;
		}
		last_token = cur_token;
		cur_token = cur_token->next;
	}
}

void edit_env(t_list *cmd_list, t_doubly_list *env_list)
{
	t_list *cur_cmd_list;

	cur_cmd_list = cmd_list;
	while (cur_cmd_list != NULL)
	{
		expand_env(((t_cmd_node*)cur_cmd_list->content)->token_list, env_list);
		cur_cmd_list = cur_cmd_list->next;
	}
}