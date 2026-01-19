/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:25:49 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:26:45 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	write_heredoc_loop(int fd, const char *delim,
                           int expand_vars, t_line *line, t_hdctx *ctx)
{
	char	*input;
	char	*expanded;

	input = readline("> ");
	while (input)
	{
		if (ctx->interrupted)
		{
			free(input);
			return ;
		}
		if (ft_strcmp(input, delim) == 0)
		{
			free(input);
			return ;
		}
		expanded = expand_vars
			? expand_heredoc_line(input, 0, line)
				: ft_strdup(input);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
		free(input);
		input = readline("> ");
		if (!input)
			ctx->interrupted = SIGINT;
	}
}*/

static char	*hd_expand_line(const char *input, t_hdctx *ctx)
{
	if (ctx->expand_vars)
		return (expand_heredoc_line(input, 0, ctx->line));
	return (ft_strdup(input));
}

void	write_heredoc_loop(int fd, t_hdctx *ctx)
{
	char	*input;
	char	*expanded;

	input = readline("> ");
	while (input)
	{
		if (ctx->interrupted)
		{
			free(input);
			return ;
		}
		if (ft_strcmp(input, ctx->delim) == 0)
		{
			free(input);
			return ;
		}
		expanded = hd_expand_line(input, ctx);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
		free(input);
		input = readline("> ");
		if (!input)
			ctx->interrupted = SIGINT;
	}
}

/*void	child_heredoc(const char *file, const char *delim,
			int expand_vars, t_line *line)
{
	int		fd;
	t_hdctx	ctx;

	ctx.interrupted = 0;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		_exit(1);
	hd_setup_signals();
	write_heredoc_loop(fd, delim, expand_vars, line, &ctx);
	close(fd);
	if (ctx.interrupted == SIGINT)
		_exit(130);
	_exit(0);
}*/

void	child_heredoc(const char *file, const char *delim,
			int expand_vars, t_line *line)
{
	int		fd;
	t_hdctx	ctx;

	ctx.interrupted = 0;
	ctx.expand_vars = expand_vars;
	ctx.delim = (char *)delim;
	ctx.line = line;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		_exit(1);
	hd_setup_signals();
	disable_echoctl();
	write_heredoc_loop(fd, &ctx);
	close(fd);
	if (ctx.interrupted == SIGINT)
		_exit(130);
	_exit(0);
}
