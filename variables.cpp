#include "variables.h"


struct t_token
{
	int type; // 0 cislo, 1 operator, 2 (, 3 ), 4 ?funkce?, 5 other 
	const char value;
	const int precedence;
	const bool associativity; //0 left, 1 right
}token_Output[64], token_Operator_Stack[64];
	
	
/*
class Token {
public:
	//enum type { Number, Operator, Function, Other };
	int type;
	const char value;
	const int precedence;
	const bool associativity; //0 left, 1 right

	//Token(enum type, char value, int precedence, bool associativity);
	Token(int type, char value, int precedence, bool associativity);
};
*/