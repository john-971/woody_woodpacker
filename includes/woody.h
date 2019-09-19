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


#define ALIGN 
#define PAGE_SIZE 4096

// extern char *print_woody;
extern int diff;
extern int print_woody;
extern int	print_woody_end;
extern void	cipher(char *input, char *key, int input_len);

typedef struct 	s_info {

	char 		*file;
	size_t		file_size;
	size_t		exploit_size;
	int			fd;
	int			exploit_fd;
	int			new_fd;
	
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
*	rc4.c
*/
u_char	*init(u_char *key);
u_char *generate_keystream(u_char *tab, u_char *input);
void	cipher_rc4(u_char *input, u_char *keystream);