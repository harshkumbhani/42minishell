
#include "minishell.h"

static int	open_file(char *file, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(file, O_RDONLY);
	else if (i == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void    open_infile(t_cmd *cmd)
{
	cmd->infile_fd = open_file(cmd->infile, cmd->file_type);
	dup2(cmd->infile_fd, STDIN_FILENO);
	close(cmd->infile_fd);
	fprintf(stderr, "Opening in file :D\n");
}


void	open_outfile(t_cmd *cmd)
{
	cmd->outfile_fd = open_file(cmd->outfile, cmd->file_type);
	dup2(cmd->outfile_fd, STDOUT_FILENO);
	close(cmd->outfile_fd);
}
