<<<<<<< Updated upstream
﻿// scientific-calculator.cpp: Definuje vstupní bod pro aplikaci.
//

#include "scientific-calculator.h"
//#include "variables.h"
#include <stdarg.h>
//#include <complex.h>


=======
﻿/*
*Kalkulačka která přepíše vstup pomocí shunting yard algoritmu(SYA) https://en.wikipedia.org/wiki/Shunting_yard_algorithm
*do Reverse Polish notation
*Umí i s komplexními čísly, ukládat a načítat hodnoty ze souborů
*/
#include "scientific-calculator.h"
>>>>>>> Stashed changes
using namespace std;
typedef struct complex {
	double real;
	double imaginary;
};

typedef struct t_token
{
	int type; //typ, 0 cislo, 1 operator, 2 (, 3 ), 4 other 
	char content; //obsah pro kontrolu
	struct complex value; //hodnota pro čísla
	int precedence; //přednost, pro SYA
	bool associativity; //vázání s tokeny,0 left, 1 right
}Token;
<<<<<<< Updated upstream

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
=======
struct t_result { //struct pro načítání hodnot ze souboru
	int id; //V zápisu výpočtu se píše ve formátu A00, A se ignoruje
	char result[256];
	struct t_result* next;
};
struct t_result* firstResult = NULL;

//funkce 
void solver(char u_input[128]); // "main" pro výpočet, řeší jednotlivé char z inputu
Token ConvertToToken(char input_c); // z předané hodnoty udělá token
void AssignStack(Token token); // předaný token dá do stacku dle SYA
void PostFixEvaluator(); // výpočet RPN
void PrintResult(double r, double i,char *result); // tisk hodnoty výsledku RPN
void SaveResult(char *result,char path[]); // uložení hodnoty do souboru
void LoadResults(bool silent,char path[]); // načtení hodnot ze souboru, má funkci silent
Token ResultPicker(int id); // vrátí token dle LoadResult ID
void Commands(char input); // příkazy
void FileSolver(char* inputPath, char* outputPath); // výpočet ze souboru a následné uložení do souboru
void ClearStacks(); // vyčištění proměnných


//stacky
Token token_Operator_Stack[256]; //stack
Token token_Output[256];		 //que
complex postFixStack[256];	 	 //stack
int OSlast;		//posledni free
int Olast;		//posledni free
int PFSlast;	//POSLEDNÍ S HODNOTOU
bool repeat = "az naprsi a uschne"; // pro opakování mainu
char savedPath[] = "saved"; // cesta k souboru s trvalým úložištěm výsledků

>>>>>>> Stashed changes


int main()
{
<<<<<<< Updated upstream
	// desetinny cisla add////////////////////////
	char u_input[128];
	for (int i = 0; i < 128; i++)
	{u_input[i] = '\0';}
	printf("Priklad zapisu:\n(12-(5+5i)-2^(1+1))/(0-2i^(2))\n"); // Dle casio classwiz = 1.5 - 2.5i
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
=======
	printf("?h pro manual\n");
	while (repeat == true)
	{
		ClearStacks();
		LoadResults(true,savedPath); // načte výsledky ze souboru
		char u_input[128]; char result[256];
		printf("max 126 znaku\n");
		scanf("%126s", u_input);
		solver(u_input);
		PrintResult(postFixStack[0].real, postFixStack[0].imaginary, result);
		if (result[0] != '0') {		// uložení nenulového výsledku
			char buffer=NULL;
			printf("%s", result);
			printf("\nUlozit? y/n \n");
			scanf(" %c", &buffer);
			if (buffer == 'y')
			{
				SaveResult(result, savedPath);
				printf("ulozeno\n");
			}
		}
	}
	printf("Uschlo");
	return 0;
}
void ClearStacks() { // vyčištění proměnných
	OSlast = 0; Olast = 0; PFSlast = -1;
	memset(postFixStack, NULL, sizeof(postFixStack));
	memset(token_Operator_Stack, NULL, sizeof(token_Operator_Stack));
	memset(token_Output, NULL, sizeof(token_Output));
}

void solver(char u_input[128]) { // "main" pro výpočet, řeší jednotlivé char z inputu	
	char numUnify[1024];
	int numCount = 0;
	char *ptr = u_input;
	if (*ptr == '?') { // pro commandy
		ptr++;
		Commands(*ptr);
		ClearStacks();
		return;
	}
	while(*ptr != '\0' || numCount != 0) {		// Sjednocení char v jedno číslo
		if (*ptr != '\0') {
			if (*ptr == 'A') { // nacte vysledek dle kodu(ID)
				ptr++; char buffer[128]; int ibuff = 0;
				while (isdigit(*ptr)) {
					buffer[ibuff] = *ptr;
					ibuff++; ptr++;
				}
				buffer[ibuff] = '\0';
				AssignStack(ResultPicker(atoi(buffer)));
			}
			if (isdigit(*ptr) || *ptr == ',' || *ptr == '.') { //přidá číslo či čárku do bufferu, uživatel může napsat jak , tak .
				*ptr == ',' ? numUnify[numCount] = '.' : numUnify[numCount] = *ptr;
>>>>>>> Stashed changes
				ptr++; numCount++;
				continue;
			}
		}
		if (numCount == 0) {
			AssignStack(ConvertToToken(*ptr));
		}
<<<<<<< Updated upstream
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
=======
		else {								 //pro cisla
			numUnify[numCount] = '\0';
			Token tukTuk{ 0,'n',complex{0,0},0,NULL };
			if (*ptr == 'i') {	//nereálné číslo
				numCount == 0 ? tukTuk.value.imaginary = 1: tukTuk.value.imaginary = atof(numUnify);
				tukTuk.value.imaginary = atof(numUnify);
				AssignStack(tukTuk); // assign num do outputu dle SYA
			}else{ //reálné
				tukTuk.value.real = atof(numUnify);
				AssignStack(tukTuk);	// assign num do outputu dle SYA
>>>>>>> Stashed changes
				if (*ptr != '\0') {
					AssignStack(ConvertToToken(*ptr));  // assign aktualniho (neco jiného než num)
				}
			}
			numCount = 0;
		}
		ptr++;
	}


	while (OSlast != 0) {	// dosazení zbylích operátorů do outputu -> postfix v outputu
		token_Output[Olast] = token_Operator_Stack[OSlast - 1];
		token_Operator_Stack[OSlast - 1].content = '\0';
		Olast++;
		OSlast--;
	}

	StacksPrint(); //vibe check

	PostFixEvaluator();

	return 0;
}

Token ConvertToToken(char input_c) { // z předané hodnoty udělá token
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
<<<<<<< Updated upstream
	else {
		printf("Něco nefachá: %c \n", input_c); //vibe check
=======
	else { // nemělo by nastat, vytvoří se token na zahození
		printf("Něco nefachá: %c \n", input_c);
>>>>>>> Stashed changes
		return Token{ 4, input_c,0,0 };
	}
}

void AssignStack(Token token) { // předaný token dá do stacku dle SYA
	if (token.type == 0) { // číslo
		token_Output[Olast] = token;
		Olast++;
	}

	if (token.type == 1) { // operátor
		// check precedence předchozího operátoru ve OperatorStacku dle SYA
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
			if (token_Operator_Stack[y].type != 2) { // přesun operátorů do outputu dokud nenajde (
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

<<<<<<< Updated upstream
void StacksPrint() {
	/*
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
	*/
}

void PostFixEvaluator() { // oh yeah, it's all coming together
=======
void PostFixEvaluator() { // výpočet RPN
>>>>>>> Stashed changes
	for (int i = 0; i < 64; i++) {
		if(token_Output[i].content != '\0')
		{
			if (token_Output[i].type == 0) { // přidá token na konec que, využijeme již existující postFixStack
				postFixStack[PFSlast + 1] = (token_Output[i].value);
				PFSlast++;
			}
			if (token_Output[i].type == 1) { //provede operaci s každým číslem v pořadí: předposlední *operator* poslední
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
					if (postFixStack[PFSlast].real != 0) {
						postFixStack[PFSlast - 1].real = postFixStack[PFSlast - 1].real / postFixStack[PFSlast].real;
						postFixStack[PFSlast - 1].imaginary = postFixStack[PFSlast - 1].imaginary / postFixStack[PFSlast].real;
					}
<<<<<<< Updated upstream
				}
				if (token_Output[i].content == '^') { //THE SAUCE
=======
				} else
				if (token_Output[i].content == '^') { // absolutní magie
>>>>>>> Stashed changes
					if(postFixStack[PFSlast - 1].real != 0 && postFixStack[PFSlast].real != 0) // nelze 0^0 (v komplex)
						postFixStack[PFSlast - 1].real = pow(postFixStack[PFSlast - 1].real, postFixStack[PFSlast].real);

					int num2 = (int)(postFixStack[PFSlast].real);
					double podlaha = floor(10000 * postFixStack[PFSlast].real) / 10000;	//zbavení desetinných čísel
					if (podlaha / num2 == 1 || num2 == 0) //mocnit lze pouze celými čísly
					{
						while (num2 >= 4) {	// nepotřebujeme mocninu vetší než 3
							num2 -= 4;
						}
						switch (num2) {	// operace dle mocniny
							case 0: 
								postFixStack[PFSlast - 1].real += postFixStack[PFSlast - 1].imaginary;
								postFixStack[PFSlast - 1].imaginary = 0;
								break;	
							case 1:
								postFixStack[PFSlast - 1].imaginary = postFixStack[PFSlast - 1].imaginary;
								break;
							case 2: 
								postFixStack[PFSlast - 1].real -= postFixStack[PFSlast - 1].imaginary;
								postFixStack[PFSlast - 1].imaginary = 0;
								break;
							case 3:
								postFixStack[PFSlast - 1].imaginary = -postFixStack[PFSlast - 1].imaginary;
								break;
						}
					}else{
						printf("Imaginarni cisla lze mocnit pouze celymi cisly: %4lf ^ %4lf", postFixStack[PFSlast - 1].imaginary, num2);
					}
				}
				PFSlast--;
			}
		}
	}
<<<<<<< Updated upstream
	printf("(%4lf + %4lf i)", postFixStack[0].real, postFixStack[0].imaginary);
=======
}

void PrintResult(double r, double i,char *result) { // tisk hodnoty výsledku RPN
	while (false == false) {
		if ((int)(round(r)) == 0) {
			snprintf(result,sizeof(result),"%.4lfi\0", i); //realná část je nulová
			break;
		}
		if ((int)(round(i)) == 0) {
			snprintf(result, sizeof(result), "%.4lf\0", r); // nereálná část je nulová
			break;
		}
		i < 0 ? snprintf(result, 256, "%.4lf%.4lfi\0", r, i) : snprintf(result, 256, "%.4lf+%.4lfi\0", r, i); // pro správné znamínko mezi real a imag
		break;
	}
}

void SaveResult(char *result, char path[]) { // uložení hodnoty do souboru
	FILE* f;
	f = fopen(path, "a+");
	if (f == NULL) {
		printf("neexistujici soubor, bude vytvoren\n");
	}
	fprintf(f, "%s", result);
	fprintf(f, ";"); // delim
	fclose(f);
}

void LoadResults(bool silent,char path[]) { // načtení hodnot ze souboru, má funkci silent
	free(firstResult); // vyčistí paměť od předem načtených hodnot
	firstResult = NULL;
	struct t_result* newResult;
	struct t_result* aktResult;
	newResult = (struct t_result*)malloc(sizeof(struct t_result));
	aktResult = (struct t_result*)malloc(sizeof(struct t_result));

	FILE *f = fopen(path, "r");
	if (f == NULL) { // klasika
		if(silent==false)
			printf("Prazny soubor\n");
		return;
	}
	int id = 0 ,ibuff = 0;
	char buffer[256];
	int c = fgetc(f);
	while (c != EOF) { // nacita char dokud nenajde delim ';'
		if ((char)(c) == ';') {
			newResult = (struct t_result*)malloc(sizeof(struct t_result));
			buffer[ibuff] = '\0'; // dokonci string
			newResult->id = id;
			newResult->next = NULL;
			strcpy_s(newResult->result, 256, buffer); // kopie bufferu do result u pointru
			if (firstResult == NULL) {
				firstResult = newResult;
			}
			else {
				aktResult->next = newResult; 
			}
			aktResult = newResult;
			buffer[0] = '\0'; 
			ibuff = 0; id++;
			c = fgetc(f);
			continue;
		}
		buffer[ibuff] = (char)(c); // pridani do bufferu
		ibuff++;
		c = fgetc(f);
	}
	fclose(f);
	if(silent == false){ // vypíše kódy A(id) načtených hodnot
		aktResult = firstResult;
		printf("\nKod | vysledek\n");
		while (aktResult)
		{
			printf("A%d | %s\n", aktResult->id,aktResult->result);
			if (aktResult->next == NULL)
				break;
			aktResult = aktResult->next;
		}
		printf("\n");
	}
}

Token ResultPicker(int id) { // vrátí token dle LoadResult ID
	Token token{ 4,'n',complex{0,0},0,NULL };
	struct t_result* aktResult;
	if (firstResult == NULL) { // načte hodnoty ze souboru kdyby uživatel po zapnutí rovnou napsal kód výsledku
		LoadResults(true,savedPath);
	}if (firstResult == NULL) {
		printf("Zadne ulozene vysledky");
		return token;
	}
	aktResult = firstResult;
	while (aktResult) // projede resulty dokud nenajde správné id
	{
		if (id == aktResult->id) {
			char buffer[256]; int ibuff = 0;
			char* Rptr = aktResult->result; // pointer pro procházení char[]
			while (*Rptr != '\0') {
				if (isdigit(*Rptr) || *Rptr == ',' || *Rptr == '.') {
					*Rptr == ',' ? buffer[ibuff] = '.' : buffer[ibuff] = *Rptr;
					Rptr++; ibuff++;
					continue;
				}
				else {
					buffer[ibuff] = '\0';
					if (*Rptr == 'i') {
						token.value.imaginary = atof(buffer);
						ibuff = 0;
						buffer[0] = '\0';
					}
					else if (*Rptr == '+') {
						token.value.real = atof(buffer);
						ibuff = 0;
						buffer[0] = '\0';
					}
					else if (*Rptr == '-') {
						if (ibuff == 0) {
							buffer[ibuff] = '-';
							ibuff++;
						}
						else {
							token.value.real = atof(buffer);
							ibuff = 1;
							buffer[0] = '-';
						}
					}
					Rptr++;
				}
			}
			if (ibuff != 0) {
				token.value.real = atof(buffer);
			}
			token.type == 0; // aby SYA nepřeskočil token
			return token;
		}
		aktResult = aktResult->next;
	}
	printf("Vysledek A%d nenalezen", id);
	return token;
}

void Commands(char input) {// příkazy
	switch (input) {
		case 'h':
			printf("\nPredchozi vysledky se pisou v kodu primu do vypoctu, viz. ?e\n");
			printf("Prikazy se zadavaji otaznikem + prikazem napr. ?h\n");
			printf("?h - Vypsat manual\n");
			printf("?l - (L)Vypsat ulozene\n");
			printf("?e - Vypsat priklady zapisu \n");
			printf("?c - Vycisti ulozene vysledky \n");
			printf("?x - Vypocet ze souboru \n");
			printf("?q - ukonceni programu\n\n");
			break;
		case 'e':
			printf("Priklad zapisu:\n(12-(5+5i)-2^(1+1))/(0-2i^(2)) \n");// Dle casio classwiz = 1.5 - 2.5i
			printf("10i^25-300/5-i | ");								 // Dle casio classwiz = -60 + 9i
			printf("-i+2i | ");											 // Dle casio classwiz = 1i
			printf("i-2i+A2-A3 | ");
			printf("1-2-1i+1i | ");
			printf("2-1-1i+1i\n");
			break;
		case 'l':
			LoadResults(false,savedPath);
			break;
		case 'q':
			repeat = false;
			break;
		case 'x':
			char inputPath[256]; char outputPath[256];
			printf("priklad souborKVypoctu.txt:\n2i^40-(20i-1);1+1;i^2;\n");
			printf("Zadejte cesty k souborum ve tvaru: souborKVypoctu.txt souborKZapsaniVysledku.txt\n");
			scanf("%256s %256s", &inputPath, &outputPath);
			FileSolver(inputPath, outputPath);
			break;
		case 'c':
			fclose(fopen(savedPath,"w"));
			break;
	}
}

void FileSolver(char *inputPath, char *outputPath) {// výpočet ze souboru a následné uložení do souboru
	FILE* f = fopen(inputPath, "r");
	if (f == NULL) {
		printf("Prazny soubor\n");
		return;
	}
	int ibuff = 0; char buffer[256];
	int c = fgetc(f);
	while (c != EOF) { //vlastně main ale opakuje se dokud nedojte na konec souboru
		if ((char)(c) == ';') {
			ClearStacks();
			char result[256];
			buffer[ibuff] = '\0'; 
			solver(buffer);
			PrintResult(postFixStack[0].real, postFixStack[0].imaginary, result);
			SaveResult(result,outputPath);
			c = fgetc(f);
			ibuff = 0;
			continue;
		}
		buffer[ibuff] = (char)(c);
		ibuff++;
		c = fgetc(f);
	}
	fclose(f);
>>>>>>> Stashed changes
}