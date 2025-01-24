#include "../../include/cub3d.h"

void exit_with_error(const char *message, int use_perror)
{
	if (use_perror)
		perror(message);
	else
		fprintf(stderr, "Error\n%s\n", message);
	exit(EXIT_FAILURE);
}
