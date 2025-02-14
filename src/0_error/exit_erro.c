/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_erro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:34:52 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/14 14:39:19 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/cub3d.h"

int	error(const char *message, int use_perror, t_game *g, t_config *c)
{
	if (use_perror && message)
		perror(message);
	else if (message)
		fprintf(stderr, "Error: %s\n", message);
	if (g || c)
		cleanup_all(g, c);
	exit(EXIT_FAILURE);
}
