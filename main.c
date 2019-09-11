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

void print_usage(char *name)
{
	printf("usage : %s [filename]", name);
}


int	detect_file_arch(void *file)
{
	Elf64_Ehdr *header;

	header = (Elf64_Ehdr *)file;
	if (*(int *)header->e_ident == *(int *)ELFMAG)
	{
		printf("Type : EFL file\n");
		if (header->e_ident[EI_CLASS] == ELFCLASS64)
		{
			printf("Arch : 64b\n");
			return (0);
		}
		else
			printf("Arch non pris en charge\n");
	}
	else
		printf("Unknow file");
	exit (1);

}

char *map_file(char *file_name)
{
	int fd;
	void *file;
	struct stat stat;

	fd = open(file_name, O_RDWR);
	if (fd == -1)
	{
		fprintf(stderr, "%s : %s", strerror(errno), file_name);
		exit(EXIT_FAILURE);	
	}
	if (syscall(SYS_fstat, fd, &stat) == -1)
	{
		fprintf(stderr, "%s ", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("File size : %u\n", stat.st_size);
	if ((file = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE,fd, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "%s : %s", strerror(errno), file_name);
		exit(EXIT_FAILURE);
	}
	return (file);
}

void	section_d_assaut(void *file)
{
	Elf64_Ehdr 	*header;
	Elf64_Shdr  *section;
	Elf64_Shdr  *str_tab;
	int 		i = -1;

	header = (Elf64_Ehdr *)file;
	printf("Number of sections : %d\n", header->e_shnum);
	section = (Elf64_Shdr *)((uint8_t *)file + header->e_shoff);
	// section = (Elf64_Shdr *)((uint8_t *)section + header->e_shentsize);
	str_tab = &section[header->e_shstrndx];
	// section = (Elf64_Shdr *)((uint8_t *)section + header->e_shentsize);
	
	while (i++ < header->e_shnum)
	{
		// printf("%x\n", section->sh_name);
		// printf("Section name : %x\n", header->e_shstrndx);
		printf("Section: [%i] %s\n", i, (char *)((uint8_t *)file + (str_tab->sh_offset + section[i].sh_name)));
		// section = (Elf64_Shdr *)((uint8_t *)section + header->e_shentsize);
	}

}

int 	main(int argc, char **argv)
{
	void *file;
	if (argc < 2)
	{
		print_usage(argv[0]);
		return (1);
	}
	file = map_file(argv[1]);
	detect_file_arch(file);
	section_d_assaut(file);


	return (0);
}