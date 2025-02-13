/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_erro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:34:52 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 18:26:25 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/cub3d.h"

int	error(const char *message, int use_perror, t_game *g, t_config *c)
{
	if (use_perror)
		perror(message);
	else
		fprintf(stderr, "Error: %s\n", message);
	if (g || c)
		cleanup_all(g, c);
	exit(EXIT_FAILURE);
}
