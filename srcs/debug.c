#include "../includes/woody.h"

void print_usage(char *name)
{
	printf("usage : %s <filename> <key> (key is optional)\n", name);
}

void	debug(char *str)
{
	printf("\033[01;33m%s\033[0m", str);
}

void	print_key(char *key)
{
	int		i = 0;
	uint8_t	is_print = 1;
	
	while (i < 16)
	{
		if (ft_isprint(key[i++]) == 0)
		{
			is_print = 0;
			break ;
		}
	}
	i = 0;
	ft_putstr("The key : [");
	while (i < 16)
	{
		if (is_print)
			printf("%c", key[i]);	
		else
			printf("%x", key[i] & 0xff);
		i++;
		
	}
	printf("]\n");
}