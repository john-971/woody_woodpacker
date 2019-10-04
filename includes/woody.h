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

// extern char *print_woody;
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
	
}				t_info;

typedef unsigned char u_char;

/*
*	Debug.c
*/

void	debug(char *str);

/*
*	File_tools.c
*/

int		open_file(char *name);
size_t		get_file_size(int fd);
int		create_file(void);
t_info		map_file(char *file_name, t_info info);


/*
*	Packer.c
*/
Elf64_Phdr	*parse_pheader(t_info info, Elf64_Phdr *pheader);
Elf64_Phdr	*search_segment(t_info info, uint32_t perm, uint8_t check_size);

/*
*	Main.c
*/
Elf64_Shdr	*section_d_assaut(t_info info, Elf64_Addr addr);

/*
*	rc4.c
*/
u_char	*init(u_char *key);
u_char *generate_keystream(u_char *tab);
void	cipher_rc4(u_char *input, u_char *keystream);

#endif