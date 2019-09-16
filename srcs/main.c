#include "../includes/woody.h"

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
		debug("Type : EFL file\n");
		if (header->e_ident[EI_CLASS] == ELFCLASS64)
		{
			debug("Arch : 64b\n");
			return (0);
		}
		else
			debug("Arch non pris en charge\n");
	}
	else
		debug("Unknow file");
	exit (1);

}

void	section_d_assaut(t_info info)
{
	Elf64_Ehdr 	*header;
	Elf64_Shdr  *section;
	Elf64_Shdr  *str_tab;
	int 		i = -1;

	header = (Elf64_Ehdr *)info.file;
	printf("Number of sections : %d\n", header->e_shnum);
	section = (Elf64_Shdr *)((uint8_t *)info.file + header->e_shoff);
	str_tab = &section[header->e_shstrndx];
	// section = (Elf64_Shdr *)((uint8_t *)section + header->e_shentsize);
	

	while (i++ < header->e_shnum - 1)
	{
		printf("Section: [%i] %s\n", i, (char *)((uint8_t *)info.file + (str_tab->sh_offset + section[i].sh_name)));
		if (&section[i + 1])
		{
			if (section[i].sh_flags & SHF_EXECINSTR)
			{
				// printf("Exec : true\n");
				if (((section[i + 1].sh_addr - section[i].sh_addr) - section[i].sh_size) > 3000)
				{
					((Elf64_Ehdr *)info.file)->e_entry = section[i].sh_addr + section[i].sh_size + 3;
					// header->e_entry = section[i].sh_addr + section[i].sh_size + ALIGN;
					
					
					// memcpy(info.file, header, sizeof(Elf64_Ehdr));

					printf( "%lx\n", ((Elf64_Ehdr *)info.file)->e_entry);
					printf( "%lx\n", header->e_entry);

					//SIZE OF SECTION

					// section[i].sh_size = section[i].sh_size + 50;

					// char *payload[500];
					// memset(payload, 0, 500);
					// read(fd_payload, info.file + (section[i].sh_addr + section[i].sh_size ), 500);


					// write(info.new_fd, info.file, info.file_size);



				
					// printf( "%ld\n", syscall(SYS_msync, info.file, info.size, MS_SYNC | MS_INVALIDATE));
					// fprintf(stderr, "%s \n", strerror(errno));
				}
			}
			// printf("cave size : %ld\n", (section[i + 1].sh_addr - section[i].sh_addr) - section[i].sh_size);
		}
		else
		{
			printf("\n");
		}
	}
}


void	parse_pheader(t_info info)
{
	Elf64_Ehdr 	*header;
	Elf64_Phdr	*pheader;
	int			i = -1;
	uint32_t	cave_size;
	uint32_t	old_entry;
	uint32_t	new_entry;
	

	
	header = (Elf64_Ehdr *)info.file;
	pheader = (Elf64_Phdr *)(info.file + header->e_phoff); 
	while(i++ < header->e_phnum)
	{
		if (pheader[i].p_type == PT_LOAD && pheader[i].p_flags == (PF_R + PF_X))
		{
			debug("Found load and execute segment\n");
			if (i + 1 < header->e_phnum)
			{
				cave_size = pheader[i + 1].p_vaddr - (pheader[i].p_vaddr + pheader[i].p_memsz);
				if (cave_size > info.exploit_size)
				{
					debug("Found cave with enough space:");	
					printf("%u\n", cave_size);
					
					new_entry = pheader[i].p_vaddr + pheader[i].p_memsz;
					printf("New Entry %i\n %i\n", new_entry, new_entry % 16);
					if (new_entry % 16 != 0)
					{
						new_entry += 16 - (new_entry % 16);
					}
					printf("New Entry Aligned %x\n", new_entry);

					old_entry = header->e_entry;
					header->e_entry = new_entry;

					//T'es sure ???
					//JSAIS PAS GROS
					pheader[i].p_memsz += info.exploit_size;
					pheader[i].p_filesz += info.exploit_size;
					int diff = new_entry - old_entry;
					read(info.exploit_fd, info.file + new_entry, info.exploit_size);

					int *test = memchr(info.file + new_entry, 'A', info.exploit_size);
					
					printf("\n DIFF : %i\n", diff);
					*test = diff;


					write(info.new_fd, info.file, info.file_size);
				}
				
			}
			
		}
		// printf("%d\n", pheader[i].p_type);

		// section = (Elf64_Shdr *)((uint8_t *)info.file + pheader.p_offset);
	}
	
}


int 	main(int argc, char **argv)
{
	t_info info;

	if (argc < 2)
	{
		print_usage(argv[0]);
		return (1);
	}
	info.fd = open_file(argv[1]);
	info.new_fd = create_file();
	info = map_file(argv[1], info);

	info.exploit_fd = open_file("./print.bin");
	info.exploit_size = get_file_size(info.exploit_fd);

	printf("Exploit size : %lu\n", info.exploit_size);

	detect_file_arch(info.file);
	// section_d_assaut(info);
	parse_pheader(info);

	munmap(info.file, info.file_size);
	close(info.fd);
	close(info.new_fd);
	return (0);
}