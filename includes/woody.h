#ifndef WOODY_H
# define WOODY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <elf.h>
#include <sys/mman.h>
#include "../srcs/libft/includes/libft.h"


#define ALIGN 
#define PAGE_SIZE 4096


extern int *input_diff;
extern int input_len;
extern int woody_diff;

extern int diff;
extern int print_woody;
extern int print_woody_end;


extern u_char	*cipher(char *input, char *key, int input_len, u_char *keystream);
extern u_char	*decipher(char *input, char *key, int input_len);
extern int		end_decipher;

typedef struct 	s_info {

	char 		*file;
	size_t		file_size;
	uint32_t	exploit_size;
	int			fd;
	int			exploit_fd;
	int			new_fd;
	char		*keystream;
	char		*key;
	
}				t_info;

typedef unsigned char u_char;

/*
*	Debug.c
*/
void	debug(char *str);
void	print_key(char *key);
void 	print_usage(char *name);

/*
*	File_tools.c
*/

int			open_file(char *name, t_info info);
size_t		get_file_size(int fd, t_info info);
int			create_file(t_info info);
void		map_file(char *file_name, t_info *info);
void		init(t_info *info, char **argv);
void		clean_exit(t_info info);
char		*generate_random_key(t_info info);


/*
*	Packer.c
*/
Elf64_Phdr	*packer(t_info info, Elf64_Phdr *pheader);
Elf64_Phdr	*search_segment(t_info info, uint32_t perm, uint8_t check_size);

/*
*	Main.c
*/
Elf64_Shdr	*section_d_assaut(t_info info, Elf64_Addr addr);
void		clean_exit(t_info info);
char		*manage_key(t_info info, char *key);



#endif