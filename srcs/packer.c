#include "../includes/woody.h"

uint32_t	align(uint32_t offset)
{
	if (offset % 16 != 0)
	{
		return (16 - (offset % 16));
	}
	return (0);
}

void	fill_asm_var(void *ptr, char tofind, uint32_t len, int value_tofill)
{
	int *match;
	
	match = memchr(ptr, tofind, len);
	if (match == NULL)
	{
		printf("Error in fill asm variable %c, we exit", tofind);
		exit(EXIT_FAILURE);
	}
	*match = value_tofill;
}

void	parse_pheader(t_info info)
{
	Elf64_Ehdr 	*header;
	Elf64_Phdr	*pheader;
	int			i = -1;
	uint32_t	cave_size;
	uint32_t	new_entry;
	uint32_t	woody_size = ((char *)&print_woody_end - (char *)&print_woody);
	uint32_t	decipher_size = (char *)&end_decipher - (char *)&decipher;
	uint32_t	alignement;
	int 		text_done = 0;
	

	
	header = (Elf64_Ehdr *)info.file;
	pheader = (Elf64_Phdr *)(info.file + header->e_phoff); 
	// printf("TAMERE %d\n %d\n", woody_size, decipher_size);
	while(i++ < header->e_phnum)
	{
		if (pheader[i].p_type == PT_LOAD && pheader[i].p_vaddr != 0)
		{
			debug("Found load and execute segment\n");
			debug("V ADDR != 0\n");
			if (i + 1 < header->e_phnum)
			{
				if (pheader[i].p_flags != (PF_R + PF_X) && text_done == 0)
				{
					continue ;
				}
				text_done = 1;

				printf("Vaddr : %x | Size : %x\n", pheader[i].p_vaddr, pheader[i].p_filesz);
				cave_size = pheader[i + 1].p_vaddr - (pheader[i].p_vaddr + pheader[i].p_filesz);
				printf("Taille de la cave : %x (%d)\n", cave_size, cave_size);
				if ((int)cave_size > ((int)info.exploit_size + 256))
				{

					pheader[i].p_flags = (PF_R + PF_X + PF_W);
					new_entry = pheader[i].p_vaddr + pheader[i].p_memsz;
					alignement = align(new_entry);
					new_entry += align(new_entry);

					pheader[i].p_memsz += info.exploit_size + align(woody_size); //exploit size + alignement
					pheader[i].p_filesz += info.exploit_size + align(woody_size);
					
					printf("Total size of segment text : %x\n", pheader[i].p_memsz);

					printf("WOODY OFFSET : %x\n", new_entry);
					memcpy(info.file + new_entry, (void *)&print_woody, woody_size);
					
					fill_asm_var(info.file + new_entry, 'A', woody_size, new_entry - header->e_entry);
					cipher((void *)info.file + pheader[i].p_vaddr, "ABCDEFGHIJKMLNOP", pheader[i].p_memsz, info.keystream);
					
					new_entry += woody_size;
					new_entry += align(new_entry);
					printf("Final Entry point (decipher) : %x\n", new_entry);
					memcpy(info.file + new_entry, (void *)&decipher, decipher_size);
					memcpy(info.file + new_entry + decipher_size, info.keystream, 256);

					printf("Exploit size : %x (%d)\n", info.exploit_size + 255, info.exploit_size + 255);
					header->e_entry = new_entry;
					
					fill_asm_var(info.file + new_entry, 'C', decipher_size, new_entry - pheader[i].p_vaddr);
					fill_asm_var(info.file + new_entry, 'Z', decipher_size, woody_size + align(new_entry) + align(woody_size));
					
					write(info.new_fd, info.file, info.file_size);
					return ;
				}
				else
				{
					printf("Pas assez de place\n");
				}
			}
			else
			{
				printf("Dernier block\n");
			}
		}
		else if (pheader[i].p_type == PT_LOAD && pheader[i].p_vaddr == 0)
		{
			debug("Found load and execute segment\n");
			debug("V ADDR == 0\n");
			if (i + 1 < header->e_phnum)
			{
				if (pheader[i].p_flags != (PF_R + PF_X) && text_done == 0)
				{
					continue ;
				}
				text_done = 1;
				printf("Vaddr : %x | Size : %x\n", pheader[i].p_vaddr, pheader[i].p_filesz);
				cave_size = pheader[i + 1].p_offset - pheader[i].p_filesz;
				printf("Taille de la cave : %x (%d)\n", cave_size, cave_size);
				if ((int)cave_size > ((int)info.exploit_size + 256))
				{

					pheader[i].p_flags = (PF_R + PF_X + PF_W);
					new_entry = pheader[i].p_memsz;
					alignement = align(new_entry);
					new_entry += align(new_entry);

					// pheader[i].p_memsz += info.exploit_size + align(woody_size); //exploit size + alignement
					// pheader[i].p_filesz += info.exploit_size + align(woody_size);
					
					printf("Total size of segment text : %x\n", pheader[i].p_memsz);

					printf("WOODY OFFSET : %x\n", new_entry);
					memcpy(info.file + new_entry, (void *)&print_woody, woody_size);
					
					printf("OLD ENTRY : %x\n", header->e_entry);
					fill_asm_var(info.file + new_entry, 'A', woody_size, new_entry - header->e_entry);
					cipher((void *)info.file + header->e_entry, "ABCDEFGHIJKMLNOP", (new_entry - header->e_entry) + woody_size, info.keystream);
					
					new_entry += woody_size;
					alignement += align(new_entry);
					new_entry += align(new_entry);
					printf("Final Entry point (decipher) : %x\n", new_entry);
					memcpy(info.file + new_entry, (void *)&decipher, decipher_size);
					memcpy(info.file + new_entry + decipher_size, info.keystream, 256);

					printf("Exploit size : %x (%d)\n", info.exploit_size + 255, info.exploit_size + 255);
					
					
					fill_asm_var(info.file + new_entry, 'C', decipher_size, new_entry - header->e_entry);
					fill_asm_var(info.file + new_entry, 'Z', decipher_size, woody_size + align(new_entry) + align(woody_size));
					
					header->e_entry = new_entry;
					write(info.new_fd, info.file, info.file_size);
					return ;
				}
				else
				{
					printf("Pas assez de place\n");
				}
			}
			else
			{
				printf("Dernier block\n");
			}
		}
	}
	
}