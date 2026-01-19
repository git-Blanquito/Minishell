/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/10/30 15:24:25 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_error(char *str)
{
	printf("%s", str);
	kill(0, SIGUSR1);
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	exit_malloc_error_tokens(t_token **head)
{
	printf("Error: malloc failed\n");
	free_token_list(*head);
	free_argv2((*head)->line->g_environ);
	exit(EXIT_FAILURE);
}

void	exit_malloc_error_tokens_input(t_token **head, char *input)
{
	printf("Error: malloc failed\n");
	free_token_list(*head);
	free(input);
	free_argv2((*head)->line->g_environ);
	exit(EXIT_FAILURE);
}

void	*error_malloc(void)
{
	printf("Error: malloc failed\n");
	return (NULL);
}
