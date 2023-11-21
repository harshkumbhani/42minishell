#include "minishell.h"

void	free_redir_list(t_redir **redir)
{
	t_redir	*tail;

	tail = NULL;
	while (*redir != NULL)
	{
		tail = (*redir);
		free((*redir)->file_name);
		(*redir) = (*redir)->next;
		free(tail);
	}
	return ;
}

void	free_heredoc(t_heredoc **heredoc)
{
	t_heredoc	*tmp;

	tmp = NULL;
	while (*heredoc != NULL)
	{
		tmp = (*heredoc);
		free((*heredoc)->str);
		(*heredoc) = (*heredoc)->next;
		free(tmp);
	}
	return ;
}

void	free_cmd_table(t_cmd **cmd_table)
{
	int	i;

	i = -1;
	while (cmd_table[++i] != NULL)
	{
		if (cmd_table[i] == NULL)
			return ;
		if (cmd_table[i]->cmd != NULL)
			free_arr(cmd_table[i]->cmd);
		if (cmd_table[i]->heredoc != NULL)
			free_heredoc(&cmd_table[i]->heredoc);
		if (cmd_table[i]->files != NULL)
			free_redir_list(&cmd_table[i]->files);
		free(cmd_table[i]);
		cmd_table[i] = NULL;
	}
	free(cmd_table);
}
