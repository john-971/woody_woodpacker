#include "../includes/woody.h"

/**
 * This function check the file magic number and the arch
 * we support only efl 64b
 **/
void			check_header(t_info *info)
{
	Elf64_Ehdr 	*header;

	if (info->file_size > sizeof(Elf64_Ehdr))
	{
		header = (Elf64_Ehdr *)info->file;
		if (*(int *)header->e_ident == *(int *)ELFMAG)
		{
			if (info->file_size > (header->e_phnum * header->e_shentsize))
			{
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
					ft_putstr_fd("Only support 64b, we exit", 2);
			}
			else
				ft_putstr_fd("corrupted binary, we exit", 2);
		}
		else
			ft_putstr_fd("Unknow file magic, we exit", 2);
	}
	else
		ft_putstr_fd("corrupted binary, we exit", 2);
	clean_exit(info);
	exit (EXIT_FAILURE);
}

/**
 * First, we try to inject our code into text segment
 * else, we put our code in whatever segment who had enough space
 **/
int 			main(int argc, char **argv)
{
	t_info 		info;
	Elf64_Phdr 	*pheader;
	
	if (argc < 2)
	{
		print_usage(argv[0]);
		return (1);
	}
	init(&info, argv);
	check_header(&info);

	pheader = search_segment(&info, PF_R + PF_X, 1);
	if (pheader != NULL)
	{
		packer(&info, pheader);
		return (0);
	}
	pheader = search_segment(&info, 0, 1);
	if (pheader != NULL)
	{
		packer(&info, pheader);
		return (0);
	}
	debug("Can't pack this binary");
	clean_exit(&info);
	return (0);
}