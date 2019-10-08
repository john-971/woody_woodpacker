#include "../includes/woody.h"

/**
 * Generate a pseudo random key based on /dev/urandom output
 **/
static char			*generate_random_key(t_info info)
{
	int			    fd;
	char 		    *key;

	fd = open_file("/dev/urandom", info);
	key = malloc(17 * sizeof(char));
	if (key == NULL)
	{
		fprintf(stderr, "%s : %s", strerror(errno), "woody");
		clean_exit(info);
		exit(EXIT_FAILURE);
	}
	read(fd, key, 16);
	key[16] = '\0';
	return (key);
}

/**
 * Check if user had give a key param, otherwise we create our own key
 **/
char			    *manage_key(t_info info, char *key)
{
	char 		    *new_key;

	if (key != NULL)
	{
		new_key = ft_strdup(key);
		if (new_key == NULL)
		{
			fprintf(stderr, "%s : %s", strerror(errno), "woody");
			clean_exit(info);
			exit(EXIT_FAILURE);
		}
		else if (ft_strlen(new_key) != 16)
		{
			ft_putstr_fd("The key must be exactly 16 bytes len\n", 2);
			free(new_key);
			clean_exit(info);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		new_key = generate_random_key(info);
	}
	return (new_key);
}