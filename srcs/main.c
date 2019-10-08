#include "../includes/woody.h"

void			check_header(t_info info)
{
	Elf64_Ehdr 	*header;

	header = (Elf64_Ehdr *)info.file;
	if (*(int *)header->e_ident == *(int *)ELFMAG)
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
			debug("Arch non pris en charge\n");
	}
	else
		debug("Unknow file");
	clean_exit(info);
	exit (EXIT_FAILURE);
}

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
	check_header(info);

	// On essaie le segment text
	pheader = search_segment(info, PF_R + PF_X, 1);
	if (pheader != NULL)
	{
		// debug("We are in segment text\n");
		packer(info, pheader);
		return (0);
	}
	// debug("Trying another place\n");
	pheader = search_segment(info, 0, 1);
	if (pheader != NULL)
	{
		// debug("We are NOT in segment text\n");
		packer(info, pheader);
		return (0);
	}
	debug("Can't pack this binary");
	clean_exit(info);
	return (0);
}