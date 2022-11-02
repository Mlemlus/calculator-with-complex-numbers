class Token {
	enum type { Number, Operator, Function, Other };
	const char value;
	const int precedence;
	const char associativity;
};
