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

typedef struct 	s_info {

	char 		*file;
	size_t		file_size;
	size_t		exploit_size;
	int			fd;
	int			exploit_fd;
	int			new_fd;
	
}				t_info;


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