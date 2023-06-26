%{
#include<io.h>
//C����������һ������ȫ�ֱ����ͺ������Ḵ�ƽ�lex.yy.c��

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
CHAR '{letter}'
ERROR [^{ws}{identifier}{number}{KEYWORD}{operator}{comment}{comments}]
ID_ERROR {digit}+{letter}+

%%
{ws} {}
{ID_ERROR} {printf("<ID_ERROR,%s>\n",yytext);}
{number} {printf("<number,%s>\n",yytext);}
{comment} {printf("<comment,%s>\n",yytext);}
{comments} {printf("<comment,%s>\n",yytext);}
{CHAR} {printf("<CHAR,%s>\n",yytext);}
"int" {printf("<int,%s>\n",yytext);}
"float" {printf("<float,%s>\n",yytext);}
"void" {printf("<void,%s>\n",yytext);}
"main" {printf("<main,%s>\n",yytext);}
"if" {printf("<if,%s>\n",yytext);}
"else" {printf("<else,%s>\n",yytext);}
"while" {printf("<while,%s>\n",yytext);}
"break" {printf("<break,%s>\n",yytext);}
"continue" {printf("<continue,%s>\n",yytext);}
"return" {printf("<return,%s>\n",yytext);}
"const" {printf("<const,%s>\n",yytext);}
"(" {printf("< (,%s>\n",yytext);}
")" {printf("< ),%s>\n",yytext);}
"{" {printf("< {,%s>\n",yytext);}
"}" {printf("< },%s>\n",yytext);}
"[" {printf("< [,%s>\n",yytext);}
"]" {printf("< ],%s>\n",yytext);}
"+" {printf("< +,%s>\n",yytext);}
"-" {printf("< -,%s>\n",yytext);}
"*" {printf("< *,%s>\n",yytext);}
"/" {printf("< /,%s>\n",yytext);}
"%" {printf("< %,%s>\n",yytext);}
"+=" {printf("< +=,%s>\n",yytext);}
"-=" {printf("< -=,%s>\n",yytext);}
"*=" {printf("< *=,%s>\n",yytext);}
"/=" {printf("< /=,%s>\n",yytext);}
"%=" {printf("< %=,%s>\n",yytext);}
"!" {printf("< !,%s>\n",yytext);}
"=" {printf("< =,%s>\n",yytext);}
">" {printf("< >,%s>\n",yytext);}
"<" {printf("< <,%s>\n",yytext);}
"!=" {printf("< !=,%s>\n",yytext);}
"==" {printf("< ==,%s>\n",yytext);}
"<=" {printf("< <=,%s>\n",yytext);}
">=" {printf("< >=,%s>\n",yytext);}
"&&" {printf("<&&,%s>\n",yytext);}
"||" {printf("<||,%s>\n",yytext);}
"," {printf("< ,,%s>\n",yytext);}
";" {printf("< ;,%s>\n",yytext);}
":" {printf("< :,%s>\n",yytext);}
{identifier} {printf("< id,%s >\n",yytext);}
{ERROR} {printf("(ERROR,%s)\n",yytext);}
%%
//�û��Զ�����̣�ֱ�Ӹ��Ƶ�lex.yy.cĩβ

int main()
{
    //printf("���� 20���� 202065073276");
    yyin=fopen("test.txt","r");
    yylex();
    return 0;
}
int yywrap()
{
    return 1;
}