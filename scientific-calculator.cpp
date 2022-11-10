// scientific-calculator.cpp: Definuje vstupní bod pro aplikaci.
//

#include "scientific-calculator.h"
#include "variables.cpp"
#include <stdarg.h>

//#include <complex.h>

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

char solver(char u_input[128]) {	// Přepíše vstup pomocí shunting yard algoritmu    https://en.wikipedia.org/wiki/Shunting_yard_algorithm
	char Texas_Holdem;

	char *p_u_input = u_input;
	for (int i = 0; i < strlen(u_input); i++)
	{
		// Sjednocení char v jedno číslo
		if (isdigit(*p_u_input)) {	
			Texas_Holdem = Texas_Holdem + *p_u_input;
		}
		else
		{
			if (Texas_Holdem == NULL)
			{
				ConvertToToken(*p_u_input);
			}
			else {								
				ConvertToToken(Texas_Holdem);
				Texas_Holdem = NULL;	// Konec sjednocení char v číslo
			}
		}
		p_u_input++;
	}
	char c_output = 'jep'; // placeholder
	return c_output;
}

void ConvertToToken(char input_c) {	// Z charu udělá Token
	if (isdigit(input_c)) {
		printf("Numero %c \n", input_c);
		//token_Output[0].value = input_c;
		
	}
	else if (isalpha)
		printf("SUSSY ALPHA");
	printf("%c \n", input_c);






	// 1=
}

