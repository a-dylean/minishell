/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:05:44 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/09 11:05:59 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
	ft_terminal();
	
    get_tokens("ls -l | 'cat -e $PATH'");
    return (0);
}