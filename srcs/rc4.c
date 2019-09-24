#include "../includes/woody.h"

void swap(u_char *i, u_char *j) {
	u_char temp;

	temp = *i;
	*i = *j;
	*j = temp;
	// if (*i != *j)
	// {
	// 	// printf("%c : %c\n", *i, *j);
	// 	*i = *i ^ *j;
	// 	*j = *j ^ *i;
	// 	*i = *i ^ *j;
	// 	// printf("%c : %c\n", *i, *j);
	// }
	
}

u_char	*init(u_char *key)
{
	int i = -1;
	int j = 0;
	u_char *tab = malloc(256 * sizeof(u_char));

	if (tab == NULL)
	{
		exit(EXIT_FAILURE);
	}
	while(i++ < 255)
	{
		tab[i] = i;
		write(1, &tab[i], 1);
	}
	// write(1,"\n", 1);
	i = -1;
	while (i++ < 255)
	{
		j = (j + tab[i] + key[i & 15]) & 255;		//65, 132, 201, 16
		// printf("%d \n", j);
		// printf("%d : %d\n", tab[i], tab[j]);
		// swap(&tab[i], &tab[j]);
		/*
		0 : 65
		65 : 0
		-----------
		1 : 132
		132 : 1
		*/
		tab[i] ^= tab[j];
		tab[j] ^= tab[i];
		tab[i] ^= tab[j];
		// printf("%d : %d\n", tab[i], tab[j]);
		// printf("-----------\n");
	}
	// i = -1;
	// while(i++ < 255)
	// {
	// 	// tab[i] = i;
	// 	write(1, &tab[i], 1);
	// }
	return (tab);
}

u_char *generate_keystream(u_char *tab)
{
	int i = 0;
	int j = 0;
	int k = -1;
	u_char *keystream;
	
  	keystream = (u_char *)malloc(sizeof(u_char) * 256);

	while (k++ < 255)
	{
		i = (i + 1) & 255;						// 1 
		// printf("I : %d\nTAB : %x\n", i, tab[i]);//tab [i] 3a
		j = (j + tab[i]) & 255;					
		// printf("J : %x\n", j);					//j = 3a
												//tab[j] = 84
		tab[i] ^= tab[j];
		tab[j] ^= tab[i];
		tab[i] ^= tab[j];						//tab[i] = 84
												//tab[j] = 3a
												//tab[and] BE
		// printf("TAB[I] : %x\nTAB[J] : %x\nAND : %x\nTAB[and]%x\n", tab[i], tab[j], (tab[i] + tab[j]) & 255, tab[(tab[i] + tab[j]) & 255]);
		keystream[k] = tab[(tab[i] + tab[j]) & 255];//ea
		// write(1, &keystream[k], 1);
	}
	write(1, keystream, 255);
	return (keystream);				//ea 6c 1c 7d cd ee c9 93
}

void	cipher_rc4(u_char *input, u_char *keystream)
{
	int i = -1;
	int len = strlen((char *)input);
	u_char *output = malloc(sizeof(u_char) * len);

	while (i++ < len)
	{
		input[i] = input[i] ^ keystream[i % 256];
		// printf("Encrypt : %x\n", output[i]);
	}

	write(1, "\n\nCrypt\n", 9);
	write(1, input, len);

	i = -1;
	while (i++ < len)
	{
		input[i] = input[i] ^ keystream[i % 256];
	}
	write(1, "\n\nDecrypt\n", 11);
	write(1, input, len);
	
}

/*
Encrypt : 2d
Encrypt : 5d
Encrypt : 3c
Encrypt : 8c
Encrypt : af
Encrypt : 88
Encrypt : d2
Encrypt : 40
Encrypt : d0
Encrypt : 19
*/