#include "../includes/woody.h"

void			check_header(t_info info)
{
	Elf64_Ehdr 	*header;

	header = (Elf64_Ehdr *)info.file;
	if (*(int *)header->e_ident == *(int *)ELFMAG)
	{
		debug("Type : EFL file\n");
		if (header->e_ident[EI_CLASS] == ELFCLASS64)
		{
			if (header->e_version == 0x2a)
			{
				debug("Binary already packed ¯\\(°_o)/¯ \n");
				clean_exit(info);
				exit(EXIT_SUCCESS);
			}
			return ;
		}
		else
			debug("Arch non pris en charge\n");
	}
	else
		debug("Unknow file");
	clean_exit(info);
	exit (EXIT_FAILURE);

}

char			*generate_random_key(t_info info)
{
	int			fd;
	char 		*key;

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

char			*manage_key(t_info info, char *key)
{
	char 		*new_key;

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
			fprintf(stderr, "The key must be exactly 16 bytes len\n");
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

Elf64_Shdr		*section_d_assaut(t_info info, Elf64_Addr addr)
{
	Elf64_Ehdr 	*header;
	Elf64_Shdr  *section;
	Elf64_Shdr  *str_tab;
	int 		i = -1;

	header = (Elf64_Ehdr *)info.file;
	printf("Number of sections : %d\n", header->e_shnum);
	section = (Elf64_Shdr *)((uint8_t *)info.file + header->e_shoff);
	str_tab = &section[header->e_shstrndx];

	while (i++ < header->e_shnum - 1)
	{
		if (&section[i + 1])
		{
			if (section[i].sh_addr <= addr && section[i + 1].sh_addr > addr)
			{
				printf("We try section: [%i] %s\n", i, (char *)((uint8_t *)info.file + (str_tab->sh_offset + section[i].sh_name)));
				return (&section[i]);
			}
		}
	}
	printf("WTF ? Section not found, we exit");
	clean_exit(info);
	exit(EXIT_FAILURE);
	return (NULL);
}



int 	main(int argc, char **argv)
{
	t_info info;
	Elf64_Phdr *pheader;
	
	if (argc < 2)
	{
		print_usage(argv[0]);
		return (1);
	}
	init(&info, argv);

	check_header(info);

	// On essaie le segment text
	pheader = search_segment(info, PF_R + PF_X, 1);
	if (pheader != NULL)
	{
		debug("We are in segment text\n");
		packer(info, pheader);
		return (0);
	}
	debug("Trying another place\n");
	pheader = search_segment(info, 0, 1);
	if (pheader != NULL)
	{
		debug("We are NOT in segment text\n");
		packer(info, pheader);
		return (0);
	}
	debug("Can't pack this binary");
	
	clean_exit(info);
	return (0);
}