#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utility.h"
#include "packet_resolver.h"
#include "url_parser.h"

#define MAX_WORDS 10

void prepare_packet(char **packet, char *url, int *final_len)
{
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

	int fixed_part_len = 12;

	total_len += word_counter;
	// this literal 5 is for the type and the class
	*final_len = fixed_part_len + total_len + 5;

	*packet = (char *)malloc(sizeof(char) * (*final_len));

	// adding the header part
	// ID
	int start_counter = 0;
	(*packet)[start_counter] = 170;
	start_counter++;
	(*packet)[start_counter] = 170;
	start_counter++;

	// Query Params
	(*packet)[start_counter] = 1;
	start_counter++;
	(*packet)[start_counter] = 0;
	start_counter++;

	// Number of Questions
	(*packet)[start_counter] = 0;
	start_counter++;
	(*packet)[start_counter] = 1;
	start_counter++;

	// Number of Answers
	(*packet)[start_counter] = 0;
	start_counter++;
	(*packet)[start_counter] = 0;
	start_counter++;

	// Number of Authority Records
	(*packet)[start_counter] = 0;
	start_counter++;
	(*packet)[start_counter] = 0;
	start_counter++;

	// Number of Addtional Records
	(*packet)[start_counter] = 0;
	start_counter++;
	(*packet)[start_counter] = 0;
	start_counter++;

	int packet_counter = start_counter;

	for (int i = 0; i < MAX_WORDS; i++)
	{
		if (word_list[i] != NULL)
		{
			int word_len = strlen(word_list[i]);
			(*packet)[packet_counter] = word_len;
			packet_counter++;
			for (int j = 0; j < word_len; j++)
			{
				if (word_list[i][j] != '.')
				{
					// converting each character to an int (ascii code)
					(*packet)[packet_counter] = word_list[i][j];
					packet_counter++;
				}
			}
		}
	}

	// zero byte to end the QName
	(*packet)[packet_counter++] = 0;
	// QType
	(*packet)[packet_counter++] = 0;
	(*packet)[packet_counter++] = 1;
	// QClass
	(*packet)[packet_counter++] = 0;
	(*packet)[packet_counter] = 1;

	for (int i = 0; i < MAX_WORDS; i++)
	{
		if (word_list[i] != NULL)
		{
			free(word_list[i]);
		}
	}

	free(word_list);
	free(domain);
}

void resolve_packet(char *packet)
{
}