#include "database.h"
#include <stdio.h>
#include <stdint.h>


int main(int argc, char const *argv[])
{
	uint16_t a[]  = {0,1,2,3,4,5,6,7};
	uint16_t size = sizeof(a)/sizeof(*a); 
	printf("%d\n", size);
	printf("%d\n", *(a+size-1));

	return 0;
} 


