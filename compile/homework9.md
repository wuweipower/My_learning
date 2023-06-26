# yacc-bison

| L->E     | L.val = E.val                                 |
| -------- | --------------------------------------------- |
| E->E1+T  | E.val = E1.val+T.val; E1.t=int  and T.t = int |
| E->T     | E.val = T.val                                 |
| T->T1*F  | T.val = T1.val*F.val; T1.t=int  and F.t = int |
| T->F     | T.val = F.val                                 |
| F->(E)   | F.val = E.val                                 |
| F->digit | F.val = digit.lexval                          |
| digit->0 | digit.val =0                                  |
| ...      |                                               |
| digit->9 | digit.val=9                                   |

```c
说明：直接对1.y和1.l进行编译
bison --yacc -dv 1.y
flex 1.l
gcc -o test y.tab.c lex.yy.c
使用方法：直接输名字运行该文件
```







```
%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#ifndef YYSTYPE
#define YYSTYPE double
#endif

int yylex();
extern int yyparse();
FILE* yyin;
void yyerror(const char* s);
%}

%token DIGIT

%%

line : expr '\n'      {printf("%d\n",$1);}
     ;

expr : expr '+' term  {$$ = $1 + $3;}
     | term
     ;

term : term '*' factor {$$ = $1 * $3;}
     | factor
     ;
    
factor : '(' expr ')'   {$$ = $2;}
       | DIGIT
       ;
%%

int yylex()
{
	int c;
    c = getchar();
    if(isdigit(c))
    {
		yylval = c-'0';
        return DIGIT;
    }
    return c;
}

void yyerror(const char* s){
	fprintf(stderr, "Parse erro: %s\n", s);
	exit(1);
}

int main(void)
{
	yyin = stdin;
	do{
		yyparse();
	}while(!feof(yyin));

	return 0;
}
```

```
%{
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
%}
%token DIGIT
%%
line    :expr '\n' { printf("%d\n",$1);return;}
        ;
expr    : expr '+' term { $$=$1+$3;}
		| expr '-' term { $$=$1-$3;}
		| term
		;
term	: term '*' factor {$$=$1*$3;}
		| factor
		;
factor	: '(' expr ')' {$$=$2;}
        | DIGIT
        ;
%%

int yylex(){
    int c;
    while ((c=getchar())==' ');
    if(isdigit(c)){
        yylval=c-'0';
        return DIGIT;
    }
    return c;
}
int yyerror(char *s){
    fprintf(stderr,"%s\n",s);
    return 1;
}

int main(){
    return yyparse();
}


```











## 只用.y文件

```
%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#ifndef YYSTYPE
#define YYSTYPE double
#endif

int yylex();
extern int yyparse();
FILE* yyin;
void yyerror(const char* s);

struct id_struct
{
    char id_name[50];
    double id_value;
}id;
%}

%token NUMBER
%token ADD
%token MUL
%token DIV
%token LB RB
%token SUB
%token ID
%token EQUAL
%token ADD_ADD SUB_SUB

%right EQUAL
%left ADD MUS
%left MUL DIV
%right ADD_ADD SUB_SUB
%right UMINUS
%%

lines :  lines expr ';' {printf("result: %f\n", $2);}
		| lines ';'
		|
		;

expr :   expr ADD expr   {$$ = $1 + $3;}
		| expr SUB expr  {$$ = $1 - $3;}
		| expr MUL expr  {$$ = $1 * $3;}
		| expr DIV expr  {
					if ($3==0.0)
						yyerror("divide by zero!");
					else
						$$ = $1 / $3;
						}
		| LB expr RB {$$ = $2;}
        | ID {$$ = id.id_value;}
        | ID EQUAL expr {
                        $$ = $3;
                        id.id_value = $3;
                        }
        | ADD_ADD ID    { $$ = id.id_value + 1; id.id_value += 1; } // (++a)
		| SUB_SUB ID    { $$ = id.id_value - 1; id.id_value -= 1; } // (--a)
		| ID ADD_ADD    { $$ = id.id_value; id.id_value += 1; } //  (a++)
		| ID SUB_SUB    { $$ = id.id_value; id.id_value -= 1; }  // (a--)
		//可以用%prec强制定义产生式的优先级和结合性
		| SUB expr %prec UMINUS {$$=-$2;}
		| NUMBER
	    ; 
%%

int yylex()
{
	char t,t_temp;
    
	while (1){
		t = getchar();
		if (t == ' ' || t == '\t'||t=='\n')
		{}
        else if (t == '+'){
            t = getchar();
			if (t == '+')
				return ADD_ADD;
			else {
				ungetc(t, stdin);
				return ADD;
                }
        }
        else if (t == '-'){
            t = getchar();

			if (t == '-')
				return SUB_SUB;
			else {
				ungetc(t, stdin);
				return SUB;
                }
        }
        else if (t == '*')
            return MUL;
        else if (t == '/')
            return DIV;
		else if (t == '(')
			return LB;
		else if (t == ')')
			return RB;
        else if (t == '=')
            return EQUAL;
		else if (isdigit(t)) {
            yylval = 0;
            while(isdigit(t)){
			yylval = yylval * 10 + t - '0';
            t = getchar();
            }
            ungetc(t, stdin);
			return NUMBER;
		}
        else if ((t >= 'a' && t <= 'z' ) || (t >= 'A' && t <= 'Z') || (t == '_')) {
            int ti=0;
            while(('a'<=t&&t<='z')||('A'<=t&&'Z'>=t)||(t=='_')||(t>='0'&&t<='9')){
                id.id_name[ti] = t;
                ti++;
                t=getchar(); 
            }
            id.id_name[ti] = '\0';
            ungetc(t,stdin);
            return ID; 
        }
		else {return t; }
	}
}

void yyerror(const char* s){
	fprintf(stderr, "Parse erro: %s\n", s);
	exit(1);
}

int main(void)
{
	yyin = stdin;
	do{
		yyparse();
	}while(!feof(yyin));

	return 0;
}
```

```
bison -d myyacc2.1.y
gcc -o myyacc2.1.out myyacc2.1.tab.c
./myyacc2.1.out
```

