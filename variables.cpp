#include "variables.h"


typedef struct t_token
{
	int type; // 0 cislo, 1 operator, 2 (, 3 ), 4 other 
	const char value;
	const int precedence;
	const bool associativity; //0 left, 1 right
}token_Output[64], token_Operator_Stack[64], Token;