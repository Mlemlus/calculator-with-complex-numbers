// scientific-calculator.cpp: Definuje vstupní bod pro aplikaci.
//

#include "scientific-calculator.h"
//#include "variables.h"
#include <stdarg.h>

//#include <complex.h>

using namespace std;

typedef struct t_token
{
	int type; // 0 cislo, 1 operator, 2 (, 3 ), 4 other 
	char value;
	int precedence;
	bool associativity; //0 left, 1 right
}Token;

//funkce ci metody nebo jak se tomu nadava 
char solver(char u_input[128]);
Token ConvertToToken(char input_c);
void AssignStack(Token token);

//stacky
Token token_Operator_Stack[64];
Token token_Output[64];

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
	char digitComplet;
	Token token = {};
	char *p_u_input = u_input;
	for (int i = 0; i < strlen(u_input); i++)
	{
		// Sjednocení char v jedno číslo
		// dodělat poznání komplexu
		if (isdigit(*p_u_input)) {	
			digitComplet = digitComplet + *p_u_input;
			p_u_input++;
			continue;
		}
		else
		{
			if (digitComplet == NULL)
			{
				AssignStack(ConvertToToken(*p_u_input));
			}
			else {
				AssignStack(ConvertToToken(digitComplet));
				digitComplet = NULL;	// Konec sjednocení char v číslo
			}
		}
		p_u_input++;
	}
	char c_output = 'jep'; // placeholder aka vibe check
	return c_output;
}

void AssignStack(Token token) { // magie


}

Token ConvertToToken(char input_c) {	// Z charu udělá Token
	if (isdigit(input_c)) {
		printf("Numero %c \n", input_c); // vibe check
		Token t = {0,input_c,0,NULL};
		return t;
	}
	else if (isalpha) {
		printf("CHAD %c \n", input_c); //vibe check
		if (input_c == '^')
			return Token{ 1,input_c,4,1 };
		if (input_c == '*')
			return Token{ 1,input_c,3,0 };
		if (input_c == '/')
			return Token{ 1,input_c,3,0 };
		if (input_c == '+')
			return Token{ 1,input_c,2,0 };
		if (input_c == '-')
			return Token{ 1,input_c,2,0 };
		if (input_c == '(')
			return Token{ 2,input_c,1,1 };
		if (input_c == ')')
			return Token{ 3,input_c,1,0 };
	}
	else {
		printf("Něco nefachá: %c \n", input_c); //vibe check
	}
}

