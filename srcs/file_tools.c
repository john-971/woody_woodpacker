#include "../includes/woody.h"

int		open_file(char *name)
{
	int fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "%s : %s", strerror(errno), name);
		exit(EXIT_FAILURE);	
	}
	return (fd);
}

size_t		get_file_size(int fd)
{
	struct stat stat;

	if (syscall(SYS_fstat, fd, &stat) == -1)
	{
		fprintf(stderr, "%s ", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (stat.st_size);
}

int		create_file(void)
{
	int fd;

	fd = open("woody", O_RDWR | O_CREAT, (mode_t)0766);
	if (fd == -1)
	{
		fprintf(stderr, "%s : %s", strerror(errno), "woody");
		exit(EXIT_FAILURE);	
	}
	return (fd);
}

t_info		map_file(char *file_name, t_info info)
{
	void *file;
	

	info.file_size = get_file_size(info.fd);
	printf("File size : %lu\n", info.file_size);
	if ((file = mmap(0, info.file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, info.fd, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "%s : %s", strerror(errno), file_name);
		exit(EXIT_FAILURE);
	}
	info.file = file;
	return (info);
}