%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define	  	Int 	100
#define	  	Char	101
#define	  	Void	102
#define	  	Main	103
#define		If	104
#define		Else	105
#define	  	While	106
#define		Const	107
#define		And	108
#define	  	Equal	109
#define		Or	110
#define		Ident	111
#define	  	Num	112
#define	    String	113
#define		ERROR 114

char str[20]; 

%}

delim [ \n\t]
ws {delim}+
letter [A-Za-z]
digit [0-9]
digits [1-9]{digit}*
number {digits}(\.{digits})?(E[+-]?{digits})?
identifier (_|{letter})(_|{letter}|{digit})*
KEYWORD int|float|main|void|if|else|break|while|continue|return|const
operator [{}|]
comment \/\/{letter}*
comments \/\*.*\*\/
CHAR 'letter'
ERROR [^{ws}{identifier}{number}{KEYWORD}{operator}{comment}{comments}]


%%
{ws} {}
{number} {ECHO;strcpy(str,yytext);return Num;}

{CHAR} {ECHO;strcpy(str,yytext); String;}

"int" {return Int;}
"char" {return Char;}
"void" {return Void;}
"main" {return Main;}
"if" {return If;}
"else" {return Else;}
"while" {return While;}
"const" {return Const;}
"("			{ECHO;return '(';}
")"			{ECHO;return ')';}
"{"			{ECHO;return '{';}
"}"			{ECHO;return '}';}
">"			{ECHO;return '>';}
"<"			{ECHO;return '<';}
"="			{ECHO;return '=';}
"+"			{ECHO;return '+';}
"-"			{ECHO;return '-';}
"/"			{ECHO;return '/';}
"%"			{ECHO;return '%';}
","			{ECHO;return ',';} 
";"			{ECHO;return ';';}

"==" {ECHO;return Equal;}
"&&" {ECHO;return And;}
"||" {ECHO;return Or;}

{identifier} {ECHO;strcpy(str,yytext);return Ident;}
{ERROR} {ECHO;return ERROR;}
%%


int yywrap()
{
    return 1;
}