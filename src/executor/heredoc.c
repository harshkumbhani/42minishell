
#include "minishell.h"

static void	execute_heredoc(t_cmd *cmd);
// static int	has_cmd(t_cmd *cmd_table);
static void	execute_heredoc_cmd(t_minishell *minishell, int index);

void	handle_heredoc(t_minishell *minishell, int index)
{
	int		pid;

	pipe(minishell->cmd_table[index]->fd);
	pid = fork();
	if (pid == 0)
		execute_heredoc(minishell->cmd_table[index]);
	else
	{
		close(minishell->cmd_table[index]->fd[1]);
		dup2(minishell->cmd_table[index]->fd[0], STDIN_FILENO);
		close(minishell->cmd_table[index]->fd[0]);
	}
	(void)execute_heredoc_cmd(minishell, index);
}

static void	execute_heredoc(t_cmd *cmd_table)
{
	char	*str;

	close(cmd_table->fd[0]);
	while (true)
	{
		str = readline("> ");
		if (ft_strcmp(cmd_table->deli, str) == EXIT_SUCCESS)
		{
			free(str);
			break ;
		}
		ft_fprintf(cmd_table->fd[1], "%s\n", str);
		free(str);
	}
	close(cmd_table->fd[1]);
	exit(EXIT_SUCCESS);
}

static void	execute_heredoc_cmd(t_minishell *minishell, int index)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(minishell->cmd_table[index]->fd[0], STDIN_FILENO);
		close(minishell->cmd_table[index]->fd[0]);
		// if (has_cmd(minishell->cmd_table[index]) == 0)
		// 	execute_cmd(minishell->cmd_table[index], minishell->head_env);
		// else if (has_cmd(minishell->cmd_table[index]) == 1)
		// 	echo(minishell->cmd_table[index]->cmd);
	}
	else
	{
		close(minishell->cmd_table[index]->fd[0]);
	}
}

// static int	has_cmd(t_cmd *cmd_table)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_table->cmd[i])
// 	{
// 		if (strcmp("cat", cmd_table->cmd[i]) == EXIT_SUCCESS)
// 			return (0);
// 		if (strcmp("echo", cmd_table->cmd[i]) == EXIT_SUCCESS)
// 			return (1);
// 		i++;
// 	}
// 	return (-1);
// }
