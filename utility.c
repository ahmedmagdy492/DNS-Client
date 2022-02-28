
#include "utility.h"

void dec_to_hexa(int n, char* hex_number)
{
	// counter for hexadecimal number array
	int i = 0;
	while (n != 0) {
		// temporary variable to store remainder
		int temp = 0;

		// storing remainder in temp variable.
		temp = n % 16;

		// check if temp < 10
		if (temp < 10) {
			hex_number[i] = temp + 48;
			i++;
		}
		else {
			hex_number[i] = temp + 55;
			i++;
		}

		n = n / 16;
	}
}

void rev_string(char* src)
{
    int len = strlen(src);
    int j = len-1;
    for(int i = 0; i < j; i++)
    {
        char temp = src[i];
        src[i] = src[j];
        src[j] = temp;
    }
}