#include "../includes/woody.h"

void swap(u_char *i, u_char *j) {
	u_char temp;

	temp = *i;
	*i = *j;
	*j = temp;
}

u_char	*init(u_char *key)
{
	int i = -1;
	int j = -1;
	int key_len = strlen((char *)key);
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
	i = -1;
	while (i++ < 255)
	{
		j = (j +tab[i] + key[i % key_len]) % 256;
		swap(&tab[i], &tab[j]);
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
		i = (i + 1) % 256;
		j = (j + tab[i]) % 256;
		swap(&tab[i], &tab[j]);
		keystream[k] = tab[(tab[i] + tab[j]) % 256];
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