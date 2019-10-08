#include "../includes/woody.h"

int					open_file(char *name, t_info *info)
{
	int 			fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "%s : %s", strerror(errno), name);
		clean_exit(info);
		exit(EXIT_FAILURE);	
	}
	return (fd);
}

void				*memory_protect(char *ptr, t_info *info)
{
	printf("start : %p | check : %p | end : %p\n",info->file, ptr, info->end_file);
	if (ptr >= info->end_file)
	{
		ft_putstr_fd("corrupted binary, we exit", 2);
		clean_exit(info);
		exit(EXIT_FAILURE);
	}
	return (ptr);

}

static size_t		get_file_size(int fd, t_info *info)
{
	struct stat 	stat;

	if (syscall(SYS_fstat, fd, &stat) == -1)
	{
		fprintf(stderr, "%s ", strerror(errno));
		clean_exit(info);
		exit(EXIT_FAILURE);
	}
	return (stat.st_size);
}

int					create_file(t_info *info)
{
	int 			fd;

	fd = open("woody", O_RDWR | O_CREAT | O_TRUNC, (mode_t)0766);
	if (fd == -1)
	{
		fprintf(stderr, "%s : %s", strerror(errno), "woody");
		clean_exit(info);
		exit(EXIT_FAILURE);	
	}
	return (fd);
}

void				map_file(char *file_name, t_info *info)
{
	void 			*file;
	
	info->file_size = get_file_size(info->fd, info);
	printf("File size : %lu\n", info->file_size);
	if ((file = mmap(0, info->file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, info->fd, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "%s : %s", strerror(errno), file_name);
		clean_exit(info);
		exit(EXIT_FAILURE);
	}
	info->file = file;
	info->end_file = info->file + info->file_size;
}

void				init(t_info *info, char **argv)
{
	char 			*keystream;
	
	keystream = ft_memalloc(sizeof(char) * 256);
	if (keystream == NULL)
		exit(EXIT_FAILURE);

	ft_memset(info, 0, sizeof(t_info));

	info->key = manage_key(info, argv[2]);
	info->fd = open_file(argv[1], info);
	info->new_fd = create_file(info);
	info->exploit_size = (char *)&print_woody_end - (char *)&print_woody;
	info->exploit_size += (char *)&end_decipher - (char *)&decipher;
	info->keystream = keystream;
	map_file(argv[1], info);
}

void				clean_exit(t_info *info)
{
	if (info->file)
		munmap(info->file, info->file_size);
	if (info->fd)
		close(info->fd);
	if (info->new_fd)
		close(info->new_fd);
	if (info->keystream)
		free(info->keystream);
	if (info->key)
		free(info->key);
}