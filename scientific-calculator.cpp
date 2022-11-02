// scientific-calculator.cpp: Definuje vstupní bod pro aplikaci.
//

#include "scientific-calculator.h"
#include <stdarg.h>
//#include <complex.h>
#include <string.h>

using namespace std;

char solver(char u_input[128]);

int main()
{
	char u_input[128];
	printf("lmfao zadej priklad pro vypocet xd\n");
	printf("max 126 znaku\n");
	scanf("%126s", &u_input);
	//printf("%s\n", u_input);
	solver(u_input);
	getchar();
	return 0;
}

char solver(char u_input[128]) {	// Přepíše vstup pomocí shunting yard algoritmu
								    // 
									//https://en.wikipedia.org/wiki/Shunting_yard_algorithm
	string Output[64];
	int Operator_stack[64];
	char Texas_Holdem;

	char *p_u_input = u_input;
	for (int i = 0; i < strlen(u_input); i++)
	{
		if (isdigit(*p_u_input))
			printf("AYO");
		else if (isalpha)
			printf("SUSSY ALPHA");
		printf("%c \n", *p_u_input);
		p_u_input++;
	}
	char c_output = 'jep';
	return c_output;
}

