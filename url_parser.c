
#include <stdlib.h>
#include <stdio.h>

#include "url_parser.h"

char *create_string(char *str, int start, int end)
{
	printf("from create string: recievied str is %s\n", str);
	char *new_str = (char *)malloc(sizeof(char) * (end - start));
	int j = 0;
	for (int i = start; i <= end; i++)
	{
		new_str[j] = str[i];
		j++;
	}
	return new_str;
}

char *parse_url(char *url)
{
	printf("from parse url: url has the value of %s\n", url);
	int len = strlen(url);
	for (int i = 0; i < len; i++)
	{
		if (url[i] == '/')
		{
			// current char is the first /
			// moving 2 chars forward
			if (url[i + 3] == 'w')
			{
				int start = i + 6;
				int stop = 0;
				for (int j = start; j < len; j++)
				{
					if (url[j] == '?' || url[j] == '/')
					{
						stop = j - 1;
						break;
					}
				}

				if (stop == 0)
					stop = strlen(url) - 1;

				char *domain_name = create_string(url, start, stop);
				return domain_name;
			}
			else
			{
				int start = i + 2;
				int stop = 0;
				for (int j = start; j < len; j++)
				{
					if (url[j] == '?' || url[j] == '/')
					{
						stop = j - 1;
						break;
					}
				}

				if (stop == 0)
					stop = strlen(url) - 1;

				char *domain_name = create_string(url, start, stop);
				return domain_name;
			}
		}
	}

	return url;
}