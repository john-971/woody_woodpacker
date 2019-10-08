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
	ft_putstr("The key : [\033[01;33m");
	while (i < 16)
	{
		if (is_print)
			printf("%c", key[i]);	
		else
			printf("%x", key[i] & 0xff);
		i++;
		
	}
	printf("\033[0m]\n");
}

void			print_pecker(void)
{
	char		woody[200];
	int			fd;
	int			count_read;
	
	fd = open("./srcs/woody.txt", O_RDONLY);
	if (fd != -1)
	{
		while ((count_read = read(fd, woody, 199)))
		{
			woody[count_read] = '\0';
			ft_putstr(woody);
		}		
	}
}