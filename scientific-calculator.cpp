// scientific-calculator.cpp: Definuje vstupní bod pro aplikaci.
//

#include "scientific-calculator.h"
//#include "variables.h"
#include <stdarg.h>
//#include <complex.h>


using namespace std;
typedef struct complex {
	double real;
	double imaginary;
};

typedef struct t_token
{
	int type; // 0 cislo, 1 operator, 2 (, 3 ), 4 other 
	char content;
	struct complex value;
	int precedence;
	bool associativity; //0 left, 1 right
}Token;

//funkce ci metody nebo jak se tomu nadava 
char solver(char u_input[128]);
Token ConvertToToken(char input_c);
void AssignStack(Token token);
void StacksPrint();
void PostFixEvaluator();



//stacky
Token token_Operator_Stack[64]; //stack
Token token_Output[64];			//que
complex postFixStack[64];				//stack
int OSlast = 0;		//posledni free
int Olast = 0;		//posledni free
int PFSlast = - 1;	//POSLEDNÍ S HODNOTOU


int main()
{
	char u_input[128];
	for (int i = 0; i < 128; i++)
	{u_input[i] = '\0';}
	printf("Priklad zapisu:\n12-(5*5-2^(1+1))/(2^2)\n");
	printf("max 126 znaku\n");
	scanf("%126s", &u_input);
	//printf("%s\n", u_input);
	solver(u_input);

	getchar();
	return 0;
}

char solver(char u_input[128]) {	// Přepíše vstup pomocí shunting yard algoritmu    https://en.wikipedia.org/wiki/Shunting_yard_algorithm
	char numUnify[128];
	int numCount = 0;
	char *ptr = u_input;
	while(*ptr != '\0' || numCount != 0) {
		// Sjednocení char v jedno číslo
		if (*ptr != '\0') {
			if (isdigit(*ptr)) {
				numUnify[numCount] = *ptr;
				ptr++; numCount++;
				continue;
			}
		}
		if (numCount == 0) {
			AssignStack(ConvertToToken(*ptr));
		}
		else {
			numUnify[numCount] = '\0';
			Token tukTuk{ 0,'n',complex{0,0},0,NULL };
			if (*ptr == 'i') {
				tukTuk.value.imaginary = atof(numUnify);
				AssignStack(tukTuk);
				printf("NUMR %c \n", tukTuk.content); //vibe check

			}else{
				tukTuk.value.real = atof(numUnify);
				AssignStack(tukTuk);				// assign num do outputu
				printf("NUMR %c \n", tukTuk.content); //vibe check
				if (*ptr != '\0') {
					AssignStack(ConvertToToken(*ptr));  // assign aktualniho (neco jiného než num)
				}
			}
			numCount = 0;
		}
		ptr++;
	}


	while (OSlast != 0) {	// dosazení zbylích operátorů do outputu -> postfix v output
		token_Output[Olast] = token_Operator_Stack[OSlast - 1];
		token_Operator_Stack[OSlast - 1].content = '\0';
		Olast++;
		OSlast--;
	}

	StacksPrint(); //vibe check

	PostFixEvaluator();

	return 0;
}

Token ConvertToToken(char input_c) {	// Z charu udělá Token
	if (isalpha) {
		printf("CHAD %c \n", input_c); //vibe check
		if (input_c == '^')
			return Token{ 1,input_c,complex{},4,1};
		if (input_c == '*')
			return Token{ 1,input_c,complex{},3,0};
		if (input_c == '/' || input_c == ':')
			return Token{ 1,input_c,complex{},3,0};
		if (input_c == '+')
			return Token{ 1,input_c,complex{},2,0};
		if (input_c == '-')
			return Token{ 1,input_c,complex{},2,0};
		if (input_c == '(')
			return Token{ 2,input_c,complex{},0,1};
		if (input_c == ')')
			return Token{ 3,input_c,complex{},0,0};
	}
	else {
		printf("Něco nefachá: %c \n", input_c); //vibe check
		return Token{ 4, input_c,0,0 };
	}
}

void AssignStack(Token token) { // dá token do stacku
	if (token.type == 0) { // číslo
		token_Output[Olast] = token;
		Olast++;
	}

	if (token.type == 1) { // operátor
		// check precedence předchozího operátoru ve OperatorStacku
		while (token_Operator_Stack[OSlast - 1].precedence >= token.precedence && token.associativity != 1) {
			token_Output[Olast] = token_Operator_Stack[OSlast - 1];
			Olast++; OSlast--;
		}
		if (token_Operator_Stack[OSlast - 1].precedence < token.precedence || token.associativity == 1) {
			token_Operator_Stack[OSlast] = token;
			OSlast++;
		}
		else {
			printf("Precedance err %c", token.content);
		}
	}

	if (token.type == 2) { // (
		token_Operator_Stack[OSlast] = token;
		OSlast++;
	}

	if (token.type == 3) { // )
		for (int y = OSlast - 1; y >= 0; y--)
		{
			if (token_Operator_Stack[y].type != 2) { // přesun operátorů do output dokud nenajde (
				token_Output[Olast] = token_Operator_Stack[y];
				token_Operator_Stack[y] = Token{};
				Olast++;
				OSlast--;
			}
			else {
				token_Operator_Stack[y]= Token{};
				OSlast--;
				break;
			}
		}
	}
}

void StacksPrint() {
	
	printf("Operator Stack: ");
	for (int i = 0; i < 64; i++)
	{
		if (token_Operator_Stack[i].content != '\0') {
			if (token_Operator_Stack[i].type == 0)
			{
				printf("(%lf + %lf i)", token_Operator_Stack[i].value.real, token_Operator_Stack[i].value.imaginary);
			}else
				printf("%c", token_Operator_Stack[i].content);
		}
	}
	printf("\nToken Output:");	
	for (int i = 0; i < 64; i++)
	{
		if (token_Operator_Stack[i].content != '\0') {
			if (token_Output[i].type == 0)
			{
				printf("(%lf + %lf i)", token_Output[i].value.real, token_Output[i].value.imaginary);
			}
			else
				printf("%c", token_Output[i].content);
		}
	}
	printf("\n");
}

void PostFixEvaluator() { // oh yeah, it's all coming together
	for (int i = 0; i < 64; i++) {
		if(token_Output[i].content != '\0')
		{
			if (token_Output[i].type == 0) {
				postFixStack[PFSlast + 1] = (token_Output[i].value);
				PFSlast++;
			}
			if (token_Output[i].type == 1) {
				if (token_Output[i].content == '+') {
					postFixStack[PFSlast - 1].real = postFixStack[PFSlast - 1].real + postFixStack[PFSlast].real;
					postFixStack[PFSlast - 1].imaginary = postFixStack[PFSlast - 1].imaginary + postFixStack[PFSlast].imaginary;
				}
				if (token_Output[i].content == '-') {
					postFixStack[PFSlast - 1].real = postFixStack[PFSlast - 1].real - postFixStack[PFSlast].real;
					postFixStack[PFSlast - 1].imaginary = postFixStack[PFSlast - 1].imaginary - postFixStack[PFSlast].imaginary;
				}
				if (token_Output[i].content == '*') {
					postFixStack[PFSlast - 1].real = postFixStack[PFSlast - 1].real * postFixStack[PFSlast].real;
					postFixStack[PFSlast - 1].imaginary = postFixStack[PFSlast - 1].imaginary * postFixStack[PFSlast].imaginary;
				}
				if (token_Output[i].content == '/') {
					postFixStack[PFSlast - 1].real = postFixStack[PFSlast - 1].real / postFixStack[PFSlast].real;
					postFixStack[PFSlast - 1].imaginary = postFixStack[PFSlast - 1].imaginary / postFixStack[PFSlast].imaginary;
				}
				if (token_Output[i].content == '^') { //fix x^0=1, i^2=-i
					postFixStack[PFSlast - 1].real = pow(postFixStack[PFSlast - 1].real, postFixStack[PFSlast].real);
					postFixStack[PFSlast - 1].imaginary = pow(postFixStack[PFSlast - 1].imaginary,postFixStack[PFSlast].imaginary);
				}
				PFSlast--;
			}
		}
	}
	printf("(%4lf + %4lf i)", postFixStack[0].real, postFixStack[0].imaginary);

}