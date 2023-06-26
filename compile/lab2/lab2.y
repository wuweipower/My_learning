 %{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define BOOL int
#define true 1
#define false 2

#define MAXSTR 20
#define MAXMEMBER 100

#define INTTYPE  0
#define CHARTYPE 1

extern int yylex();
extern FILE* yyin;
extern char str[20];
int VarCount=0;
FILE* fp;
int NXQ=0; 

int Entry(char *name);                       
int AddType(int first,int type);             
int NewTemp();                                
int Merge(int p,int q);                      
void BackPatch(int p,int t);          
int GEN(char* op,int a1,int a2,int re);               
void OutQuadruple();                      
void OutList();     
int yyparse();
int yyerror(char *errstr);

struct QUATERLIST{
	char op[6];
	int arg1;
	int arg2;
	int result;
} QuaterList[MAXMEMBER];
struct VARLIST{
	char name[20];
	int type;
	int addr;
} VarList[MAXMEMBER];

%}
%start    CompUnit
%union 
{
    int  Iv;
    int CH;
    int NO;
    struct { int TC,FC;} _BExp;
    struct { int QUAD,CH;} _WBD;
    struct { int type,place;} _Exp;
    char   _Rop[5];
    int First;
    char   str[20];
}

%token	  	Int 	100
%token	  	Char	101
%token  	Void	102
%token  	Main	103
%token		If		104
%token		Else	105
%token	  	While	106
%token		Const	107
%token		And		108
%token	  	Equal	109
%token		Or		110
%token    	Ident	111
%token    	Num		112
%token	    String  113

%nonassoc '<' '>' '='
%left '+' '-'
%left '*' '/' 

%type <CH> CompUnit
%type <CH> SubComp
%type <CH> VarDef
%type <CH> VarDefList
%type <Iv> Type   
%type <First> VarList                  
%type <CH> Statement
%type <CH> StateList
%type <CH> StateLists
%type <CH> ComplexState       
%type <_WBD> AsignState        
%type <CH> IfElse
%type <CH> IfNoElse                       
%type <_WBD> Wd                    
%type <_Rop> RelationOp        
%type <_Exp> Exp 
%type <CH> W                       
%type <NO> Variable               
%type <NO> AVariable    
%type <_Exp> Data               
%type <_BExp>	BoolExp 

%%
CompUnit:SubComp{$$=0;}
		;

SubComp	:VarDef StateList{GEN("Stop",0,0,0);}
VarDef	:VarDef VarDefList {$$=0;}
		| VarDefList {$$=0;}

VarDefList	:VarDefList VarList ';'{$$=0;}
			|VarList ';'{$$=0;}
			;
VarList	:VarList ',' Variable{AddType($3,$1);}
		|Type Variable{$$=$1;AddType($2,$$);}
		|VarList ',' AVariable '=' Exp  {
		AddType($3,$1);
		if(VarList[$3].type==$5.type)
			   GEN("=",$5.place,0,$3);
		else if($5.type==INTTYPE && VarList[$3].type==CHARTYPE)
		{
			   int T=NewTemp();
			   GEN("INT->CHAR",$5.place,0,T);
			   GEN("=",T,0,$3);
		}
		else if($5.type==CHARTYPE && VarList[$3].type==INTTYPE)
		{
			 int T=NewTemp();
			 GEN("CHAR->INT",$5.place,0,T);
			 GEN("=",T,0,$3);
		}
	}
		|Type  AVariable '=' Exp
		{
			$$=$1;
			AddType($2,$$);
			if(VarList[$2].type==$4.type)
				GEN("=",$4.place,0,$2);
			else if($4.type==INTTYPE && VarList[$2].type==CHARTYPE)
			{
			   	int T=NewTemp();
			   	GEN("INT->CHAR",$4.place,0,T);
			   	GEN("=",T,0,$2);
			}
			else if($4.type==CHARTYPE && VarList[$2].type==INTTYPE)
			{
				int T=NewTemp();
				GEN("CHAR->I",$4.place,0,T);
				GEN("=",T,0,$2);
			}
		}
		|Const Type  AVariable '=' Exp 
		{
			$$=$2;
			AddType($3,$$);
			if(VarList[$3].type==$5.type)
				GEN("=",$5.place,0,$3);
			else if($5.type==INTTYPE && VarList[$3].type==CHARTYPE)
			{
			   	int T=NewTemp();
			   	GEN("INT->CHAR",$5.place,0,T);
			   	GEN("=",T,0,$3);
			}
			else if($5.type==CHARTYPE && VarList[$3].type==INTTYPE)
			{
				int T=NewTemp();
				GEN("CHAR->I",$5.place,0,T);
				GEN("=",T,0,$3);
			}
		}
		;

Type	:Int{$$=INTTYPE;}
		|Char{$$=CHARTYPE;}
		;
AsignState	:AVariable '=' Exp  {
	$$.QUAD=$1;
	$$.CH=NXQ-1;
	if(VarList[$1].type==$3.type)  GEN("=",$3.place,0,$1);
}
	;

AVariable	:  Variable {$$=$1;} 
			;
	
Exp	:   Exp'+'Exp 
	{
		int T=NewTemp();
		if($1.type== INTTYPE && $3.type==INTTYPE)  
		{
			GEN("INT+",$1.place,$3.place,T);
		  	VarList[T].type=$$.type=INTTYPE;
		}
		else if($1.type== CHARTYPE && $3.type==CHARTYPE)  
		{
		  	GEN("CHAR+",$1.place,$3.place,T);
		  	VarList[T].type=$$.type=CHARTYPE;
		}
		}
	|Exp'-'Exp  // 减法
    {
		int T=NewTemp();
		if($1.type== INTTYPE && $3.type==INTTYPE)
		{
			GEN("INT-",$1.place,$3.place,T);
			VarList[T].type=$$.type=INTTYPE;
		}
		else if($1.type== CHARTYPE && $3.type==CHARTYPE)	
		{
			GEN("CHAR-",$1.place,$3.place,T);
			VarList[T].type=$$.type=CHARTYPE;
		}
		$$.place=T;
	}

	|Exp'*'Exp //乘法
    {
		int T=NewTemp();
		if($1.type== INTTYPE && $3.type==INTTYPE)
		{
		  	GEN("INT*",$1.place,$3.place,T);
		  	VarList[T].type=$$.type=INTTYPE;
		}
		else if($1.type== CHARTYPE && $3.type==CHARTYPE)	
		{
			GEN("CHAR*",$1.place,$3.place,T);
		  	VarList[T].type=$$.type=CHARTYPE;
		}
		$$.place=T;
		}
	|Exp'/'Exp //除法
    {
		int T=NewTemp();
		if($1.type== INTTYPE && $3.type==INTTYPE)
		{
		  	GEN("INT/",$1.place,$3.place,T);
		  	VarList[T].type=$$.type=INTTYPE;
		}
		else if($1.type== CHARTYPE && $3.type==CHARTYPE)
		{
		  	GEN("CHAR/",$1.place,$3.place,T);
		  	VarList[T].type=$$.type=CHARTYPE;
		}
		$$.place=T;
	}
	|'(' Exp ')'{$$=$2;}
	|Variable
    {
		 $$.place=$1;
		 $$.type=VarList[$1].type;
	}
	|Data{$$=$1;}
	;

Variable	:Ident{ $$=Entry(str); }
			;
StateLists	:StateList{BackPatch($1,NXQ);}
			;

StateList	:Statement{$$=$1;BackPatch($1,NXQ);}
			|Statement StateList{$$=$1;BackPatch($1,NXQ);}
			;
Statement	:AsignState ';' {$$=0;}
		|IfElse ComplexState {$$=Merge($1,$2);}
		|IfNoElse   ComplexState {$$=Merge($1,$2);}
		|Wd ComplexState   { 
			GEN("j",0,0,$1.QUAD);
			BackPatch($2,$1.QUAD);
			$$=$1.CH;
		}
		;

IfElse	:IfNoElse ComplexState Else  {int q=NXQ;GEN("j",0,0,0);BackPatch($1,NXQ);$$=Merge($2,q);}
	;

IfNoElse	:If '(' BoolExp ')' {BackPatch($3.TC,NXQ);$$=$3.FC;}
	;

Wd	:W '(' BoolExp ')' {BackPatch($3.TC,NXQ);$$.QUAD=$1;$$.CH=$3.FC;}
	;

W	:While{$$=NXQ;}
	;

ComplexState	:'{' StateList '}' {	$$=$2;	}
				;

BoolExp	:Exp RelationOp Exp
	{
		$$.TC=NXQ;$$.FC=NXQ+1;
		GEN($2,$1.place,$3.place,0);
		GEN("j",0,0,0);                      
	}
	| BoolExp And  {BackPatch($1.TC,NXQ);}   BoolExp{$$.TC=$4.TC;$$.FC=Merge($1.FC,$4.FC);}
	| BoolExp Or    {BackPatch($1.FC,NXQ);}   BoolExp{$$.FC=$4.FC;$$.TC=Merge($1.TC,$4.TC);}	
	|'(' BoolExp ')'{$$=$2;}
	;

Data	: Num
	{ 
		int i=Entry(str);
		$$.type=VarList[i].type=INTTYPE;
	  	$$.place=i;
	}
	|String
	{
		int i=Entry(str);
		$$.type=VarList[i].type=CHARTYPE;
		$$.place=i;
	}
	;

RelationOp:	'<'{strcpy($$,"j<");}
	|	'>'{strcpy($$,"j>");}
	|	Equal {strcpy($$,"j=");}
	;
%%


void OutQuadruple(void)
{
    int i;
	printf("------------------------------------------------------\n");
    printf("\nQuarters :\n");
    for(i=0;i<NXQ;i++)
    {
        printf("NO.%4d ( %8s, ",i,QuaterList[i].op);
        if(QuaterList[i].arg1)
	        printf("%6s, ",VarList[QuaterList[i].arg1].name);
   		else printf("      , ");
        if(QuaterList[i].arg2)
	        printf("%6s, ",VarList[QuaterList[i].arg2].name);
		else printf("      , ");
        if((QuaterList[i].op[0]=='j')||(QuaterList[i].op[0]=='S')) 
			printf("%6d )\n",QuaterList[i].result);
        else if(QuaterList[i].result)
	        printf("%6s )\n",VarList[QuaterList[i].result].name);
		else printf("-\t )\n");
    }
    return;
}

int yyerror(char *errstr)
{
    printf(" %s\n",errstr);
    return 0;
}

int Entry(char *name)
{
    int i;
    for(i=1;i<=VarCount;i++) 
        if(!strcmp(name,VarList[i].name)) 
            return i;
    if(++VarCount>MAXMEMBER) 
    {
        printf("Too many Variables!\n");exit(-1);
    }
    strcpy(VarList[VarCount].name,name);
    return VarCount;
}

int AddType(int first,int type)
{ 
    int i;
    for(i=first;i<=VarCount;i++) VarList[i].type=type;
    return i-1;
}

int Merge(int p,int q)
{
   int r;
   if(!q) return p;
   else
   {
       r=q;
       while(QuaterList[r].result)
        r=QuaterList[r].result;
       QuaterList[r].result=p;
   }
   return q;
}

void BackPatch(int p,int t)
{
    int q=p;
    while(q)
    { 
        int q1=QuaterList[q].result;
        QuaterList[q].result=t;
        q=q1;
    } 
    return;
}

int GEN(char* op,int a1,int a2,int re)
{
    strcpy(QuaterList[NXQ].op,op);
    QuaterList[NXQ].arg1=a1;
    QuaterList[NXQ].arg2=a2;
    QuaterList[NXQ].result=re;
    NXQ++;
    return NXQ;
}

int NewTemp()
{
    static int no=0;
    char Tempname[10];
    sprintf(Tempname,"T%o",no++);
    return Entry(Tempname);
}

void OutList(void)
{
    int i;
	printf("\n------------------------------------------------------\n");
	printf("\nAddress allocation : \n");
    printf(" Address\tName\tType\n");
    for(i=1;i<VarCount;i++)
    {
        printf("%4d\t%6s\t\t",i,VarList[i].name);
        if(VarList[i].type) 	
			printf(" CHAR   \n");
        else printf(" INT \n"); 
    }
	printf("------------------------------------------------------\n");
    return;
}

int main(int argc, char *argv[])
{
    yyin=NULL;
    if(argc>1)
    {
        if((yyin=fopen(argv[1],"r"))==NULL)
        {
            printf("Can't open file %s\n",argv[1]);exit(0);
        }
    } 
    yyin=fopen("test.txt","r");
    if(yyin==NULL)
    {
        printf("Can't open file test.txt\n");
        return -1;
    }	
	printf("\n Ai Lejun with 202030430011   ");
	printf("\n Huangxin with 202065073276   \n");
    yyparse();
    printf("\n");
    OutQuadruple();
    OutList();
    getchar();
    return;
}