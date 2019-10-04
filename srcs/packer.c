#include "../includes/woody.h"

uint32_t	align(uint32_t offset)
{
	if (offset % 16 != 0)
	{
		return (16 - (offset % 16));
	}
	return (0);
}

void	fill_asm_var(void *ptr, int value_tofill)
{
	int *match;
	
	match = (int *)((uint8_t *)ptr);
	// printf("MATCH !!!!!!!!! %x\n", *match);
	*match = value_tofill;
}

Elf64_Phdr	*search_segment(t_info info, uint32_t perm, uint8_t check_size)
{
	Elf64_Ehdr 	*header;
	Elf64_Phdr	*pheader;
	int			i = -1;
	uint32_t	cave_size;
	
	header = (Elf64_Ehdr *)info.file;
	pheader = (Elf64_Phdr *)(info.file + header->e_phoff);
	while(i++ < header->e_phnum)
	{
		if (pheader[i].p_type == PT_LOAD && i + 1 < header->e_phnum)
		{
			if (perm == pheader[i].p_flags || perm == 0)
			{
				if (check_size == 1)
				{
					cave_size = pheader[i + 1].p_offset - (pheader[i].p_offset + pheader[i].p_filesz);
					if ((int)cave_size > ((int)info.exploit_size + 256))
					{
						debug("Found segment with enough space\n");
						printf("Taille de la cave : %x (%d)\n", cave_size, cave_size);
						return (&pheader[i]);
					}
					else
					{
						debug("Pas assez de place dans le segment demandé\n");
					}
				}
				else
				{
					return (&pheader[i]);
				}
				
			}
		}
	}
	return (NULL);
}

Elf64_Phdr	*packer(t_info info, Elf64_Phdr *pheader)
{
	Elf64_Ehdr 	*header;
	Elf64_Phdr	*segment_txt;
	uint32_t	cave_size;
	uint32_t	woody_size = ((char *)&print_woody_end - (char *)&print_woody);
	uint32_t	decipher_size = (char *)&end_decipher - (char *)&decipher;
	uint32_t	alignement;
	int 		text_done = 0;
	uint32_t	woody_offset;
	uint32_t	decipher_offset;
	Elf64_Shdr	*section;
	
	
	header = (Elf64_Ehdr *)info.file;

	if (pheader->p_flags != (PF_R + PF_X) && pheader->p_flags != (PF_R + PF_X + PF_W))
	{
		segment_txt = search_segment(info, PF_R + PF_X, 0);
		if (segment_txt == NULL)
		{
			debug("Wtf pas de segment executable ?, on exit");
			clean_exit(info);
			exit(EXIT_FAILURE);
		}
		segment_txt->p_flags = (PF_R + PF_X + PF_W);
	}
	printf("Offset : %x\nVaddr : %x\nSize : %x\n", pheader->p_offset, pheader->p_vaddr, pheader->p_filesz);

	pheader->p_flags = (PF_R + PF_X + PF_W);
	
	woody_offset = pheader->p_offset + pheader->p_filesz;
	alignement = align(woody_offset);
	woody_offset += align(woody_offset);

	printf("WOODY OFFSET : %x\nWOODY SIZE : %x\n", woody_offset, woody_size);
	ft_memcpy(info.file + woody_offset, (void *)&print_woody, woody_size);
	
	printf("OLD ENTRY : %x\n", header->e_entry);

	fill_asm_var(info.file + woody_offset + ((void *)&diff - (void *)&print_woody), (pheader->p_vaddr + pheader->p_memsz + alignement) - header->e_entry);

	section = section_d_assaut(info, header->e_entry);
	printf("offset : %x\naddr : %x\nsize : %x\n", section->sh_offset, section->sh_addr, section->sh_size);
	printf("START CIPHER : %x\n", section->sh_offset + (header->e_entry - section->sh_addr));
	cipher((void *)info.file + section->sh_offset + (header->e_entry - section->sh_addr), info.key, section->sh_size - (header->e_entry - section->sh_addr), info.keystream);
	
	int diff = header->e_entry - section->sh_addr;
	printf("Diff decipher to start section : %x\n", diff);
	decipher_offset = woody_offset + woody_size;
	alignement += align(decipher_offset);
	decipher_offset += align(decipher_offset);
	
	ft_memcpy(info.file + decipher_offset, (void *)&decipher, decipher_size);
	ft_memcpy(info.file + decipher_offset + decipher_size, info.keystream, 256);

	printf("input diff : %x (%d)\n", (pheader->p_vaddr + pheader->p_memsz + alignement + woody_size) - header->e_entry, (pheader->p_vaddr + pheader->p_memsz + alignement + woody_size) - header->e_entry);
	fill_asm_var(info.file + decipher_offset + ((void *)&input_diff - (void *)&decipher), (pheader->p_vaddr + pheader->p_memsz + alignement + woody_size) - header->e_entry);
	fill_asm_var(info.file + decipher_offset + ((void *)&input_len - (void *)&decipher), section->sh_size - (header->e_entry - section->sh_addr));
	fill_asm_var(info.file + decipher_offset + ((void *)&woody_diff - (void *)&decipher), decipher_offset - woody_offset);
	

	header->e_version = 42;
	header->e_entry = pheader->p_vaddr + pheader->p_memsz + woody_size + alignement;
	printf("Final Entry point (decipher) : %x\n", header->e_entry);
	pheader->p_memsz += info.exploit_size + align(woody_size) + 256; //exploit size + alignement
	pheader->p_filesz += info.exploit_size + align(woody_size) + 256;
	// printf("Total size of segment text : %x\n", pheader->p_filesz);

	write(info.new_fd, info.file, info.file_size);
	print_key(info.key);
	return (pheader);
}