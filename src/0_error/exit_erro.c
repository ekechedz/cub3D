#include "../../include/cub3d.h"

int error(const char *message, int use_perror)
{
	if (use_perror)
		perror(message);
	else
		fprintf(stderr, "Error: %s\n", message);
	exit(EXIT_FAILURE);
}
