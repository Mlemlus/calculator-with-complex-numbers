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
Token token_Operator_Stack[64]; //stack
Token token_Output[64];			//que
int OSlast = 0;
int Olast = 0;


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

	while (OSlast != 0) {	// dosazení zbylích operátorů do outputu -> postfix v output
		token_Output[Olast] = token_Operator_Stack[OSlast - 1];
		Olast++;
		OSlast--;
	}


	char c_output = 'jep'; // placeholder aka vibe check
	return c_output;
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

void AssignStack(Token token) { // dá token do stacku
	if (token.type == 0) { // číslo
		token_Output[Olast] = token;
		Olast++;
	}

	if (token.type == 1) { // operátor
		if (token_Operator_Stack[OSlast - 1].precedence > token.precedence) { // check priority předchozího operátoru
			token_Output[Olast] = token_Operator_Stack[OSlast - 1];
			Olast++;
			token_Operator_Stack[OSlast - 1] = token;
		}
		else {
			token_Operator_Stack[OSlast] = token;
			OSlast++;
		}
	}

	if (token.type == 2) { // (
		token_Operator_Stack[OSlast] = token;
		OSlast++;
	}

	if (token.type == 3) { // )
		for (int i = OSlast - 1; i <= 0; i--)
		{
			if (token_Operator_Stack[i].type != 2) { // přesun operátorů do output dokud nenajde (
				token_Output[Olast] = token_Operator_Stack[i];
				Olast++;
				OSlast--;
			}
			else {
				OSlast--;
				break;
			}
		}
	}
}

void PostFixEvaluator() { // oh yeah, it's all coming together

}