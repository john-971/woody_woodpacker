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
	i = -1;
	while(i++ < 255)
	{
		// tab[i] = i;
		write(1, &tab[i], 1);
	}
	return (tab);
}

u_char *generate_keystream(u_char *tab, u_char *input)
{
	int i = 0;
	int j = 0;
	int k = -1;
	int len = strlen((char *)input);
	u_char *keystream;
	
  	keystream = (u_char *)malloc(sizeof(u_char) * 256);

	while (k++ < len)
	{
		i = (i + 1) & 255;
		j = (j + tab[i]) & 255;
		swap(&tab[i], &tab[j]);
		keystream[k] = tab[(tab[i] + tab[j]) & 255];
	}
	return (keystream);
}

void	cipher_rc4(u_char *input, u_char *keystream)
{
	int i = -1;
	int len = strlen((char *)input);
	u_char *output = malloc(sizeof(u_char) * len);

	while (i++ < len)
	{
		output[i] = input[i] ^ keystream[i % 256];
	}

	printf("\nEncrypt : %s", (char *)output);

	i = -1;
	while (i++ < len)
	{
		output[i] = output[i] ^ keystream[i];
	}

	printf("\nEncrypt : %s", (char *)output);
}