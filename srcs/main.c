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



int 	main(int argc, char **argv)
{
	t_info info;
	u_char	*tab;
	u_char *input;
	char *keystream = malloc(sizeof(char) * 256);
	keystream = memset(keystream, 0, 256);
	memset(&info, 0, sizeof(info));
	if (keystream == NULL)
	{
		exit(EXIT_FAILURE);
	}
	int len;

  	// input = strdup("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas in eleifend enim. Nulla maximus, eros ac suscipit iaculis, justo turpis fringilla est, sed finibus orci velit nec sem. Cras quis nulla purus. Maecenas ante nisi, congue non nibh eget, gravida imperdiet lorem. Donec tellus ipsum, rutrum a metus non, laoreet molestie ligula. Fusce commodo finibus lorem, sit amet venenatis augue lobortis ac. Morbi auctor velit non magna condimentum, ac aliquam elit porttitor. Suspendisse nec elementum purus. Aliquam rhoncus tempus tempus. Phasellus nec dapibus ipsum. Morbi ornare augue quis dolor tempor finibus. Donec a scelerisque ante. Integer eget quam augue. Morbi at nunc fringilla, aliquam neque eget, elementum lectus. Proin dolor ipsum, pretium a gravida et, vehicula at lorem. Pellentesque vitae magna faucibus sem mattis consequat.Morbi dapibus laoreet nisl vitae sollicitudin. Suspendisse pharetra quis lorem faucibus vulputate. Etiam ac pulvinar nibh. Curabitur et nisi odio. Pellentesque ut felis sagittis, auctor ante at, commodo nisl. Ut dictum faucibus turpis sit amet eleifend. Cras ultrices purus nec dui tincidunt, at fringilla nunc facilisis. Fusce lobortis molestie iaculis. Nam volutpat justo quis diam ullamcorper rhoncus. Pellentesque et libero cursus nisi blandit mollis nec ac sapien. Aliquam elit justo, consectetur vulputate ante ut, mollis posuere velit. Nam id faucibus tellus. Proin augue leo, consectetur ac malesuada id, posuere non mauris. In scelerisque imperdiet nisl, consequat tristique sapien malesuada in. Suspendisse hendrerit imperdiet augue, quis semper diam auctor at.Ut ultricies neque massa, nec congue mi finibus quis. Maecenas a augue convallis, varius mi vitae, gravida lacus. Ut aliquam, erat ut accumsan efficitur, risus augue euismod metus, sed consectetur ante mi ac magna. Phasellus cursus, libero id sollicitudin suscipit, sapien risus tempus enim, nec sagittis tortor velit eu magna. Quisque cursus rutrum sem, pulvinar ultricies enim scelerisque eget. Nulla massa ante, viverra a odio sit amet, hendrerit tincidunt sapien. Aenean accumsan eget magna eu faucibus. Fusce in aliquam ex, et dignissim nisl. Nulla auctor eget neque non fringilla. Maecenas finibus aliquet porta. Donec molestie scelerisque sodales. Suspendisse potenti. Phasellus et tortor porta, mattis magna sed, pulvinar lorem. Ut ullamcorper ipsum a sapien pretium rutrum. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut et mattis orci.Ut gravida urna felis, id blandit nulla fermentum convallis. Praesent iaculis dolor et nisi aliquam vulputate. Phasellus ultricies tempor mauris, at tempor dolor dapibus sed. Integer ultrices erat quis leo blandit venenatis. Mauris lorem dolor, consequat et tellus sed, ultrices aliquet sem. Mauris sed ex id est elementum volutpat eu sed ex. Sed malesuada vel risus eu interdum. Etiam sit amet tellus et orci aliquam laoreet. Donec at tempor leo. Quisque dui ligula, pretium aliquam sollicitudin vel, placerat ut est. Sed tristique eros eu fermentum fermentum. Nulla et mi pharetra, porta elit in, condimentum diam. Nulla commodo justo eget egestas laoreet. Sed tempor, ipsum sed porttitor vulputate, neque urna commodo elit, non ultrices nisi tellus eget sapien. Sed auctor sagittis nisl sit amet elementum.Morbi mattis pulvinar erat, sed imperdiet tellus iaculis quis. Sed non efficitur odio, et luctus purus. Cras vehicula quam id lacinia malesuada. Aenean sed lorem ac mi suscipit posuere eget vitae justo. Nullam facilisis porta metus, a porttitor nisl finibus ac. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi varius augue quis rutrum ornare. Morbi blandit egestas varius. Proin tempus commodo elit ac imperdiet. In hac habitasse platea dictumst. Ut non velit orci.Suspendisse blandit, metus a pharetra consequat, nibh augue porta risus, id elementum lorem ipsum sed nisi. Suspendisse gravida tempor malesuada. Nullam imperdiet faucibus eros et rutrum. Duis in turpis aliquam magna suscipit tincidunt sit amet sed turpis. Aliquam nec libero sed neque ornare fringilla sit amet non metus. Nam vitae cursus libero, ac malesuada felis. Suspendisse egestas neque libero, eget suscipit lorem rutrum vitae. Duis aliquam, dolor eu finibus mollis, nibh odio mattis purus, in interdum purus nunc vel justo.Etiam imperdiet augue risus, eget aliquam neque sollicitudin eu. Cras vitae sem mattis, feugiat diam eu, ultrices urna. Morbi eget leo purus. Integer consectetur facilisis magna et varius. Vivamus placerat nunc in volutpat ultrices. Aenean varius eget augue id condimentum. Curabitur ipsum ante, vehicula ut rutrum et, fringilla eu dolor. Nam feugiat, nisl eget ultricies tincidunt, massa ante finibus dolor, eget euismod eros ante vel sapien. Vivamus neque risus, ullamcorper ac tincidunt scelerisque, venenatis lacinia neque. Nunc fermentum turpis non libero malesuada, eu sagittis magna facilisis. Morbi blandit laoreet tristique. Aliquam eleifend tortor eu vehicula porttitor. Praesent lectus sapien, auctor ac ullamcorper a, ultrices et leo. Phasellus gravida odio a facilisis mattis. In congue, mi at porttitor finibus, neque velit dignissim elit, eu rutrum orci dolor sit amet tellus.Fusce pretium, orci at dictum varius, arcu lorem mollis sem, ut molestie tortor felis eget neque. Ut vitae ante molestie, venenatis eros in, semper purus. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Phasellus ac sem ac ligula lacinia pharetra. Pellentesque ultrices augue vitae turpis tempor, et venenatis enim egestas. Nulla tincidunt semper dolor, sed feugiat mauris congue et. Mauris blandit euismod condimentum. Mauris fringilla ac sem sed fermentum. Mauris consequat metus non efficitur imperdiet.Aenean egestas ex ut lorem pharetra consequat. Vestibulum in ligula sit amet lacus eleifend dictum. Nullam in eleifend metus. Proin bibendum euismod accumsan. Proin vel arcu accumsan, consectetur felis sit amet, malesuada tortor. Mauris lacinia egestas massa. Proin ut egestas est. Vestibulum ut neque lorem. Cras quis ante eget nisi aliquet lacinia.In in aliquam tortor, in malesuada dolor. Suspendisse turpis orci, vulputate sed leo sit amet, euismod condimentum odio. Integer rutrum consectetur tristique. Mauris non rhoncus augue, a dapibus nunc. Vestibulum eu nibh rutrum justo porttitor dapibus. Integer eget sapien a nisi mollis hendrerit a sed purus. Praesent tincidunt facilisis erat, a feugiat erat congue quis. Sed sagittis diam et ornare convallis. Morbi id aliquet nisl. Aenean a ipsum ut augue dictum congue. Ut id ligula dictum, rhoncus eros in, fermentum turpis.Proin pharetra interdum tortor, ac pretium ante. Fusce volutpat nibh eu dui gravida fermentum. Donec placerat commodo purus sit amet cursus. Maecenas blandit mi vel orci imperdiet sodales. Quisque risus felis, ultrices nec bibendum et, cursus sit amet metus. Etiam ut mi at enim venenatis fermentum vel quis est. Integer dignissim condimentum feugiat. Nullam malesuada, nisi ac facilisis facilisis, neque nulla varius lectus, quis blandit elit sem et orci. Integer mi quam, tristique id dignissim eu, tincidunt sit amet sem. Nam ut mi tristique, rhoncus urna eget, finibus risus.Nullam consequat, eros eu mattis hendrerit, arcu ante malesuada sapien, a finibus libero massa et dui. Aliquam placerat congue urna, tempus dapibus justo facilisis et. Nullam ornare lacus in tortor aliquet, vitae sodales ante mollis. Donec commodo ex eros, at pulvinar lectus aliquam vel. Duis a pharetra mi. Suspendisse sagittis dolor lorem, eu sodales dolor hendrerit a. Vestibulum ac ligula volutpat, tempor metus et, rutrum arcu.Pellentesque vel erat vitae purus varius vulputate eget ut ex. Donec eleifend velit libero, quis porta ex lobortis ut. Vestibulum quis mollis augue, et tempus ligula. Phasellus varius ultrices purus viverra consectetur. Pellentesque vitae lectus sit amet velit pretium euismod. Cras euismod a nisi nec vehicula. Ut euismod magna nisl, non elementum tortor faucibus eu. Etiam sed. ");
	// input = strdup("ABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMLNOPABCDEFGHIJKMAAAAAAAAAAAAAAbbbbbQQQQQ");
	len = strlen(input);
	if (argc < 2)
	{
		print_usage(argv[0]);
		return (1);
	}
	info.fd = open_file(argv[1]);
	info.new_fd = create_file();
	info.exploit_size = (char *)&print_woody_end - (char *)&print_woody;
	info.exploit_size += (char *)&end_decipher - (char *)&decipher;
	info.keystream = keystream;
	
	info = map_file(argv[1], info);

	detect_file_arch(info.file);
	// section_d_assaut(info);
	parse_pheader(info);
	
	
	// tab = init("ABCDEFGHIJKMLNOP");
	// keystream = generate_keystream(tab);
	// cipher_rc4(input, keystream);

	// write(1, "\nTo Crypt :\n", 12);
	// write(1, input, len);
	// keystream = cipher(input, "ABCDEFGHIJKMLNOP", len, keystream);
	// // write(1, "\n\nCrypt\n", 9);
	// // write(1, input, len);
	// input = decipher(input, "ABCDEFGHIJKMLNOP", len);
	// write(1, "\n\nDecrypt\n", 11);
	// write(1, input, len);

	// write(1, "\nKeystream\n", 12);
	// write(1, keystream, 255);

	munmap(info.file, info.file_size);
	close(info.fd);
	close(info.new_fd);
	return (0);
}