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
	uint32_t	woody_offset;
	uint32_t	decipher_offset;
	

	
	header = (Elf64_Ehdr *)info.file;
	pheader = (Elf64_Phdr *)(info.file + header->e_phoff); 
	// printf("TAMERE %d\n %d\n", woody_size, decipher_size);
	while(i++ < header->e_phnum)
	{
		if (pheader[i].p_type == PT_LOAD)
		{
			debug("Found load and execute segment\n");
			debug("V ADDR == 0\n");
			if (i + 1 < header->e_phnum)
			{
				//MANIP SUR LE FICHIER, POFFSET + FILESZ
				//MANIP SUR LES ADDRESSES , P_VADDR + MEMSIZE
				if (pheader[i].p_flags != (PF_R + PF_X) && text_done == 0)
				{
					continue ;
				}
				text_done = 1;
				printf("Vaddr : %x | Size : %x\n", pheader[i].p_vaddr, pheader[i].p_filesz);
				// cave_size = pheader[i + 1].p_vaddr - pheader[i].p_filesz;
				cave_size = pheader[i + 1].p_offset - (pheader[i].p_offset + pheader[i].p_filesz);
				printf("Taille de la cave : %x (%d)\n", cave_size, cave_size);
				if ((int)cave_size > ((int)info.exploit_size + 256))
				{
					printf("Section text %s", pheader[i].p_flags == (PF_R + PF_X) ? "oui\n": "non");

					pheader[i].p_flags = (PF_R + PF_X + PF_W);
					woody_offset = pheader[i].p_offset + pheader[i].p_filesz;
					alignement = align(woody_offset);
					woody_offset += align(woody_offset);

					// pheader[i].p_memsz += info.exploit_size + align(woody_size); //exploit size + alignement
					// pheader[i].p_filesz += info.exploit_size + align(woody_size);
					
					// printf("Total size of segment text : %x\n", pheader[i].p_filesz);

					printf("WOODY OFFSET : %x\n", woody_offset);
					memcpy(info.file + woody_offset, (void *)&print_woody, woody_size);
					
					printf("OLD ENTRY : %x\n", header->e_entry);

					fill_asm_var(info.file + woody_offset, 'A', woody_size, (pheader[i].p_vaddr + pheader[i].p_memsz + alignement) - header->e_entry);
					printf("START CIPHER : %x\n", (woody_offset) - header->e_entry);
					// cipher((void *)info.file + header->e_entry, "ABCDEFGHIJKMLNOP", woody_offset + woody_size, info.keystream);
					

					decipher_offset = woody_offset + woody_size;
					alignement += align(decipher_offset);
					decipher_offset += align(decipher_offset);
					
					
					memcpy(info.file + decipher_offset, (void *)&decipher, decipher_size);
					memcpy(info.file + decipher_offset + decipher_size, info.keystream, 256);

					// printf("Exploit size : %x (%d)\n", info.exploit_size + 255, info.exploit_size + 255);
					
					
					fill_asm_var(info.file + decipher_offset, 'C', decipher_size, (woody_offset) - header->e_entry);
					fill_asm_var(info.file + decipher_offset, 'Z', decipher_size, decipher_offset - woody_offset);
					
					header->e_entry = pheader[i].p_vaddr + pheader[i].p_memsz + woody_size + alignement;
					printf("Final Entry point (decipher) : %x\n", header->e_entry);
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