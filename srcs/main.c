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
	int 		entry_diff;
	

	
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
					entry_diff = new_entry - old_entry;
					memcpy(info.file + new_entry, (void *)&print_woody, info.exploit_size);
					
					int *test = memchr(info.file + new_entry, 'A', info.exploit_size);
					printf("%d\n %d\n %d\n", (void *)&test, (void *)&diff, entry_diff);
					*test = entry_diff;

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
	u_char	*tab;
	u_char *input;
	u_char *keystream;
	int len;

  	// input = strdup(" condimentum nonummy, tincidunt alias blandit tellus massa justo. Vestibulum proin donec, lectus donec ligula fusce dui ante. Donec sed placerat, pulvinar pharetra, et vestibulum laoreet eget elit vitae egestas. Feugiat in pede integer, vitae erat accumsan sed. Neque amet felis rutrum in ut, at est morbi. Lectus wisi mauris tempor tortor mi, in justo, etiam nisl scelerisque in massa, posuere pellentesque sodales odio bibendum.Mauris cum libero, id imperdiet nulla, eros ac arcu commodo at sapien, at perferendis congue sit. Nunc sem amet auctor id sit, fusce nisl, faucibus rutrum, eget quisque odio, dolor pulvinar mauris. Nam pede eu vitae nulla, vestibulum integer amet mauris. Penatibus vestibulum consectetur, lobortis torquent tincidunt accumsan pede urna suscipit, volutpat ac convallis, donec etiam, adipiscing sit sit ut. Risus magnis nulla at tristique sollicitudin fusce. In vehicula sit, in vivamus bibendum elit nonummy imperdiet arcu, turpis id, lorem luctus morbi potenti lobortis, massa felis adipiscing arcu enim varius. Sed sed nec nam praesent convallis, vehicula sed wisi amet. Aut cum nibh harum nunc a sed, inceptos ut tortor nisl lorem odio, ut porttitor, cras mauris in enim eros delectus. Maecenas lectus sit. Dolor pharetra phasellus id hendrerit, in nam proin in lorem ut.Leo per purus platea, aliquam pellentesque ultricies, ante quam arcu suspendisse varius sed morbi, felis sem et, parturient vivamus etiam nullam. Duis libero vestibulum ligula quis, pede lacinia fermentum tristique ut eget, at adipiscing magna sit torquent, eget augue a dolorem magna, erat purus. Vitae a amet vitae vitae, diam et phasellus. Sit porta eget velit est dolor, etiam mollis id wisi, dapibus aliquet nostra ligula nibh molestie nonummy, iaculis mi ultrices. Mollis penatibus tempus libero. Adipisicing ullamcorper lacinia duis magna volutpat vestibulum, ut libero cursus placerat, metus at consequat libero. Laoreet vel, at enim pretium, at eros dolor, est erat nec sem. Proin massa, aliquet pulvinar wisi lorem ut et sed, aliquam lectus fermentum a ornare, in nulla elit scelerisque, eu nibh. Mauris sollicitudin morbi ante lorem, laoreet eu quis, morbi pellentesque wisi, mauris neque, donec donec a. Purus lectus a mollis, velit vehicula eget tristique nibh consectetuer. Porttitor mauris vitae. Nunc blandit nunc congue et leo, elit in et et urna.");
	input = strdup("ABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMAAAAAAAAAAAAAAbbbbbQQQQQ");
	len = strlen(input);
	if (argc < 2)
	{
		print_usage(argv[0]);
		return (1);
	}
	// info.fd = open_file(argv[1]);
	// info.new_fd = create_file();
	// info.exploit_size = (char *)&print_woody_end - (char *)&print_woody;
	// printf("Exploit size : %lu\n", info.exploit_size);
	// info = map_file(argv[1], info);

	// detect_file_arch(info.file);
	// // section_d_assaut(info);
	// parse_pheader(info);
	
	
	// tab = init("ABCDEFGHIJKMLNOP");
	// keystream = generate_keystream(tab);
	// cipher_rc4(input, keystream);

	write(1, "\nTo Crypt :\n", 12);
	write(1, input, len);
	input = cipher(input, "ABCDEFGHIJKMLNOP", len);
	write(1, "\n\nCrypt\n", 9);
	write(1, input, len);
	input = decipher(input, "ABCDEFGHIJKMLNOP", len);
	write(1, "\n\nDecrypt\n", 11);
	write(1, input, len);

	// munmap(info.file, info.file_size);
	// close(info.fd);
	// close(info.new_fd);
	return (0);
}