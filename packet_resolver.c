#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utility.h"
#include "packet_resolver.h"
#include "url_parser.h"

#define MAX_WORDS 10


void prepare_packet(int **packet, char *url, int* final_len)
{
	char *fixed_part = "\xAA\xAA\x01\x00\x00\x01\x00\x00\x00\x00\x00\x00";

	// run the url parser
	char *domain = parse_url(url);
	int domain_len = strlen(domain);
	char **word_list = (char **)malloc(sizeof(long long) * MAX_WORDS);

	// spliting the string based on '.'
	char *portion = strtok(domain, ".");
	int total_len = strlen(portion);
	int word_counter = 0;
	word_list[word_counter] = (char *)malloc(sizeof(char) * total_len);
	strncpy(word_list[word_counter], portion, sizeof(char) * total_len);
	word_counter++;

	while (portion != NULL)
	{
		portion = strtok(NULL, ".");
		if (portion != NULL)
		{
			int len = strlen(portion);
			word_list[word_counter] = (char *)malloc(sizeof(char) * len);
			strncpy(word_list[word_counter], portion, sizeof(char) * len);
			total_len += len;

			word_counter++;
		}
	}

	total_len += word_counter;
	*final_len = strlen(fixed_part) + total_len;
	*packet = (int *)malloc(sizeof(int) * (*final_len));
	int packet_counter = 0;

	for (int i = 0; i < MAX_WORDS; i++)
	{
		if (word_list[i] != NULL)
		{
			int word_len = strlen(word_list[i]);
			char len_hex[2];
			dec_to_hexa(word_len, len_hex);
			rev_string(len_hex);
			(*packet)[packet_counter] = atoi(len_hex);
			packet_counter++;
			for (int j = 0; j < word_len; j++)
			{
				if (word_list[i][j] != '.')
				{
					// converting each character to an int (ascii code)
					char hex_number[2];
					dec_to_hexa(word_list[i][j], hex_number);
					rev_string(hex_number);
					(*packet)[packet_counter] = atoi(hex_number);
					packet_counter++;
				}
			}
		}
	}

	for(int i = 0; i < MAX_WORDS; i++)
	{
		if(word_list[i] != NULL)
		{
			free(word_list[i]);
		}
	}

	free(word_list);
	free(domain);
}

void resolve_packet(char* packet)
{
    
}