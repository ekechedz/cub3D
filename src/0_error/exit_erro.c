/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_erro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:34:52 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 14:34:54 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	error(const char *message, int use_perror)
{
	if (use_perror)
		perror(message);
	else
		fprintf(stderr, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}
