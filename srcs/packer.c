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

Elf64_Phdr	*search_segment(t_info info, uint32_t perm)
{
	Elf64_Ehdr 	*header;
	Elf64_Phdr	*pheader;
	int			i = -1;
	uint32_t	cave_size;
	
	header = (Elf64_Ehdr *)info.file;
	pheader = (Elf64_Phdr *)(info.file + header->e_phoff);
	while(i++ < header->e_phnum)
	{
		if (pheader[i].p_type == PT_LOAD)
		{
			if (i + 1 < header->e_phnum)
			{
				if (perm == pheader[i].p_flags || perm == 0)
				{
					// printf("Found load segment with right perm => v_addr : %x\n", pheader[i].p_vaddr);
					cave_size = pheader[i + 1].p_offset - (pheader[i].p_offset + pheader[i].p_filesz);
					// printf("Taille de la cave : %x (%d)\n", cave_size, cave_size);
					if ((int)cave_size > ((int)info.exploit_size + 256))
					{
						debug("Found segment with enough space\n");
						printf("Taille de la cave : %x (%d)\n", cave_size, cave_size);
						return (&pheader[i]);
					}
					else
					{
						debug("Pas assez de place\n");
					}
				}
			}
			else
			{
				debug("Dernier block\n");
			}
		}
	}
	return (NULL);
}

Elf64_Phdr	*parse_pheader(t_info info, Elf64_Phdr *pheader)
{
	Elf64_Ehdr 	*header;
	// Elf64_Phdr	*pheader;
	uint32_t	cave_size;
	uint32_t	new_entry;
	uint32_t	woody_size = ((char *)&print_woody_end - (char *)&print_woody);
	uint32_t	decipher_size = (char *)&end_decipher - (char *)&decipher;
	uint32_t	alignement;
	int 		text_done = 0;
	uint32_t	woody_offset;
	uint32_t	decipher_offset;
	Elf64_Shdr	*section;
	

	
	header = (Elf64_Ehdr *)info.file;

	//MANIP SUR LE FICHIER, POFFSET + FILESZ
	//MANIP SUR LES ADDRESSES , P_VADDR + MEMSIZE
	// if (pheader->p_flags != (PF_R + PF_X) && text_done == 0)
	// {
	// 	continue ;
	// }
	// text_done = 1;

	

	printf("Offset : %x\nVaddr : %x\nSize : %x\n", pheader->p_offset, pheader->p_vaddr, pheader->p_filesz);
	printf("Section text %s\n", pheader->p_flags == (PF_R + PF_X) ? "oui\n": "non");

	pheader->p_flags = (PF_R + PF_X + PF_W);
	woody_offset = pheader->p_offset + pheader->p_filesz;
	alignement = align(woody_offset);
	int woody_align = alignement;
	woody_offset += align(woody_offset);
	// section = section_d_assaut(info, woody_offset);



	printf("WOODY OFFSET : %x\nWOODY SIZE : %x\n", woody_offset, woody_size);
	memcpy(info.file + woody_offset, (void *)&print_woody, woody_size);
	
	printf("OLD ENTRY : %x\n", header->e_entry);

	fill_asm_var(info.file + woody_offset, 'A', woody_size, (pheader->p_vaddr + pheader->p_memsz + alignement) - header->e_entry);

	section = section_d_assaut(info, header->e_entry);
	printf("offset : %x\naddr : %x\nsize : %x\n", section->sh_offset, section->sh_addr, section->sh_size);
	printf("START CIPHER : %x\n", section->sh_offset + (header->e_entry - section->sh_addr));
	cipher((void *)info.file + section->sh_offset + (header->e_entry - section->sh_addr), "ABCDEFGHIJKMLNOP", section->sh_size - (header->e_entry - section->sh_addr), info.keystream);
	
	int diff = header->e_entry - section->sh_addr;
	printf("Diff decipher to start section : %x\n", diff);
	decipher_offset = woody_offset + woody_size;
	alignement += align(decipher_offset);
	decipher_offset += align(decipher_offset);
	
	memcpy(info.file + decipher_offset, (void *)&decipher, decipher_size);
	memcpy(info.file + decipher_offset + decipher_size, info.keystream, 256);

	// printf("Exploit size : %x (%d)\n", info.exploit_size + 255, info.exploit_size + 255);
	// fill_asm_var(info.file + decipher_offset, 'C', decipher_size, decipher_offset - header->e_entry);
	printf("input diff : %x (%d)\n", (pheader->p_vaddr + pheader->p_memsz + alignement + woody_size) - header->e_entry, (pheader->p_vaddr + pheader->p_memsz + alignement + woody_size) - header->e_entry);
	fill_asm_var(info.file + decipher_offset, 'C', decipher_size, (pheader->p_vaddr + pheader->p_memsz + alignement + woody_size) - header->e_entry);
	fill_asm_var(info.file + decipher_offset, 'Y', decipher_size, section->sh_size - (header->e_entry - section->sh_addr));
	fill_asm_var(info.file + decipher_offset, 'Z', decipher_size, decipher_offset - woody_offset);
	
	

	

	header->e_entry = pheader->p_vaddr + pheader->p_memsz + woody_size + alignement;
	printf("Final Entry point (decipher) : %x\n", header->e_entry);
	pheader->p_memsz += info.exploit_size + align(woody_size) + 256; //exploit size + alignement
	pheader->p_filesz += info.exploit_size + align(woody_size) + 256;
	// printf("Total size of segment text : %x\n", pheader->p_filesz);

	write(info.new_fd, info.file, info.file_size);
	return (pheader);
}