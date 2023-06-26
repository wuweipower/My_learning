#include<iostream>
#include<stack>
#include<map>//<string,type>
#include<string>
#include<vector>
#include<assert.h>
#include<fstream>
using namespace std;

struct Token
{
    string val;
    string type;
    Token(){}
    Token(string val, string type)
    {
        this->val = val;
        this->type = type;
    }
   // map<string,string> attrs;
    
};
vector<Token> tokens;
int tp=-1;//token pointer
struct Quadruple
{
    int num;
    string op;
    string arg1;
    string arg2;
    string result;
    Quadruple(string op, string arg1, string arg2,string result)
    {
        this->op = op;
        this->arg1 = arg1;
        this->arg2 = arg2;
        this->result = result;
    }
    void print()
    {
        cout<<"("
        <<this->op<<", "<<this->arg1<<", "<<this->arg2<<", "<<this->result<<")"
        <<endl;
    }
};
vector<Quadruple> quadrups;

struct back_patch
{
	vector<int> true_chain;//待回填的真链
	vector<int> false_chain;//待回填的假链
	vector<int> else_if_chain;//有else的句子，if then之后要直接跳出到整个if else
	//如果有多个and后面跟着一个or，那么这个and布尔项的假出口不能加到假链里面，而是加到这个链上面
	//每次只要再次遇到一个or，那就进行回填，如果一直到布尔表达式结束都没有or，那就直接把and布尔项的假链都加到真正的假链里面
	vector<int> and_or_false_chain;

	int codebegin;//第一个四元式的序号
	int accept;//用来标识式子是不是算术表达式
	string op;//在<算术表达式><关系符><算术表达式>中生成四元式要用到
	bool is_swap;//用来记录语句中是否有not，又不要交换真假链
	back_patch() { accept = 0; is_swap = 0; }
	//如果bool表达式里面有or把多个布尔项连接起来呢，那么无论满足了那个bool项都能到达真假出口，因此他们的链需要连起来，最后一起回填
	void addTrueChain(back_patch &st)
	{
		if (st.is_swap == 0)	true_chain.insert(true_chain.end(), st.true_chain.begin(), st.true_chain.end());
		else true_chain.insert(true_chain.end(), st.false_chain.begin(), st.false_chain.end());
	}
	void addFalseChain(back_patch &st)//把这个位置的出口加到假链上
	{
		if (st.is_swap == 0)	false_chain.insert(false_chain.end(), st.false_chain.begin(), st.false_chain.end());
		else false_chain.insert(false_chain.end(), st.true_chain.begin(), st.true_chain.end());
	}
	void addAndOrFalseChain(back_patch &st)
	{
		and_or_false_chain.insert(and_or_false_chain.end(), st.and_or_false_chain.begin(), st.and_or_false_chain.end());
	}
};

struct var_val //储存变量以及值
{
    string var;
    string val;
    string type;
    var_val(string var, string type)
    {
        this->var = var;
        this->type = type;
    }
};

vector<var_val> var_vals;


/*******************************词法分析*******************************************/

int LINE=1;   //用于记录代码的行数 
bool flag=false;   //用于表示当前注释是否结束 
bool dComment = false; //双斜杠注释
//关键词，运算符
enum Types{
    ENDFILE,ERROR,
    IF,ELSE,INT,RETURN,VOID,WHILE,FLOAT,CONST,BREAK,CONTINUE,CHAR,   //关键字 
    ID,NUM,   //标识符和数字
    ADD,SUB,MUL,DIV,L,LE,G,GE,EQ,NEQ,NOT,ASS,DELIMI,COMMA,LP,RP,LBR,RBR,LB,RB,LC,RC,
    // + - * / < <= > >= == != ! =             ; , ( ) [ ] { } /* */
    //addtion subtract divide less less_equal great great_equal equal, not_equal,assign delimiter comma left/right parenthsis,bracket,brace,left and right comment
    CH,//字符
    MOD,MODE,//% %=
    ADDE,SUBE,MULE,DIVE,//+=,-=,*=,/=    
    CHARERROR,//字符'不匹配
    IILEGAL_ID,
    IILEGAL_NUM,
    COMMENT_ERROR,
    DADD,DSUB,//double add, double sub
    DCOM,
    AND,OR//&& ||
};
enum States
{
    START,DONE,
    INNUM,INID,INLT,INGT,INEQ,INNOT,INCOMMENT,INDELETE,READDELETE,
	//开始、数字、字符、小于等于、大于等于、赋值或等于、注释开始，注释内容开始，注释内容结束，完成和单个字符直接完成 
    CHARS,CHARE, //字符开始，字符中，字符结束 char start, char end
    INADD,INSUB,INMUL,INDIV,INMOD,//开始进入加减乘除模  
    INDCOM,//双斜杠的注释 double comment
    READTOUT,//准备出注释
    INAND,INOR//&& ||
};

bool isNum(char a)  //检测当前字符是否为数字 
{
	if(a>='0'&&a<='9')
	return true;
	return false;
}
 
bool isAlpha(char a)   //检测当前字符是否为字母 
{
	if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a=='_'))
	return true;
	return false;
}
 
bool isChar(char a) //检测当前是否为一个合法字符 ASCII
{
    if(' '<=a&&a<='~')
    {
        return true;
    }
    return false;
}

void PrintToken(Types type, string TokenString)   //对于每一种状态输出每一样的词法分类结果 
{
	if(TokenString!="\0")   //如果是空行，那么跳过，保持格式 
	cout<<"\t"<<LINE<<": ";
	switch(type)   //根据当前状态输出应当匹配的东西 
    {
	    case IF:
        case INT:
        case ELSE:
        case RETURN:
        case VOID:
        case WHILE:
        case FLOAT:
        case CONST:
        case BREAK:
        case CONTINUE:
        case CHAR:
        cout<<"<KEYWORD,"<<TokenString<<">"<<endl;   //预留词都是单独的状态 
        tokens.push_back(Token(TokenString,"KEYWORD"));
		break;
        case ADD: 
        printf("< ADD,+ >\n");  
        tokens.push_back(Token(TokenString,"ADD"));
        break;
        case SUB: 
        printf("< SUB,- >\n");  
        tokens.push_back(Token(TokenString,"SUB"));
        break;
        case MUL: 
        tokens.push_back(Token(TokenString,"MUL"));
        printf("< MUL,* >\n");  break;
        case DIV: 
        printf("< DIV,/>\n"); 
        tokens.push_back(Token("/","DIV"));
        break;
        case L:   
        printf("< L,< >\n");
        tokens.push_back(Token(TokenString,"L"));  
        break;
        case LE:  printf("< LE,<= >\n"); break;//    ADD,SUB,MUL,DIV,L,LE,G,GE,ISE,NT,NTE,FZ,FH,DH,LXK,RXK,LZK,RZK,LDK,RDK,LZS,RZS   
                                                    // + - * / < <= > >= == != = ; , ( ) [ ] { } /* */
        case MOD: printf("< MOD,% >\n"); break;
        case G:   printf("< G,> >\n");
        tokens.push_back(Token(TokenString,"G"));  
        break;
        case GE:  printf("< GE,>= >\n"); break;
        case EQ: printf("< EQ,== >\n");
        tokens.push_back(Token(TokenString,"EQ"));
        break;
        case NEQ:  printf("< NEQ,!= >\n");  break;
        case NOT: printf("< NOT,! >\n"); break;   // ADD,SUB,MUL,DIV,L,LE,G,GE,EQ,NEQ,NOT,ASS,DELIMI,COMMA,LP,RP,LBR,RBR,LB,RB,LC,RC,
                                                // + - * / < <= > >= == != ! =  ; , ( ) [ ] { } /* */
        case ASS:  printf("< ASS,= >\n");
        tokens.push_back(Token(TokenString,"ASSIGN"));
        break;
        case DELIMI: printf("< DELIMITER,; >\n");
        tokens.push_back(Token(TokenString,"DELIMETER"));
        break;
        case COMMA:  printf("< COMMA,, >\n");
        tokens.push_back(Token(TokenString,"COMMA"));  
        break;
        case LP: printf("< LP,( >\n");  
        tokens.push_back(Token(TokenString,"LP"));
        break;
        case RP: printf("< RP,) >\n");
        tokens.push_back(Token(TokenString,"RP"));
        break;
        case LBR: printf("< LBR,[ >\n");  break;
        case RBR: printf("< RBR,]>\n");  break;
        case LB: printf("< LB,{ >\n");  
        tokens.push_back(Token(TokenString,"LB"));
        break;
        case RB: printf("< RB,} >\n");  
        tokens.push_back(Token(TokenString,"RB"));
        break;
        case ADDE: printf("< ADDE,+=>");break;
        case SUBE: printf("< SUBE,-= >");break;
        case MULE: printf("< MULE,*= >");break;
        case DIVE: printf("< DIVE,/= >");break;
        case MODE: printf("< MODE,%= >");break;
        case ENDFILE: if(TokenString!="\0") cout<<"COMMENT："<<TokenString<<endl;break;   //ENDFILE作为注释结束的输出，直接输出整个字符串 
		case NUM:
	        cout<<"< NUM,"<<TokenString<<" >"<<endl; 
            tokens.push_back(Token(TokenString,"NUM"));
            break;
        case ID:
	        cout<<"< ID,"<<TokenString<<" >"<<endl; 
            tokens.push_back(Token(TokenString,"ID"));
            break;
        case ERROR:   
            //如果输入符合文法，那么不会出现这种状态 
	        cout<<"ERROR："<<TokenString<<endl; 
            exit(0);
            break;
        case CH: 
            cout<<"< CHAR,"<<TokenString<<" >"<<endl; 
            tokens.push_back(Token(TokenString,"CHAR"));
            break;
        case IILEGAL_ID: 
            cout<<"< ILEGAL_ID,"<<TokenString<<" >"<<endl;
            exit(0);
            break;
        case CHARERROR:
            cout<<"< CHARERROR,"<<TokenString<<" >"<<endl; 
            exit(0);
            break;
        case IILEGAL_NUM:
            cout<<"< IILEGAL_NUM,"<<TokenString<<" >"<<endl; 
            exit(0);
            break;
        case COMMENT_ERROR:
            cout<<"< COMMENT_ERROR,"<<TokenString<<" >"<<endl; 
            exit(0);
            break;
        case DADD:
            cout<<"< DADD,++ >"<<endl;break;
        case DSUB:
            cout<<"< DSUB,-- >"<<endl; break;
	}
}

//判断字符串所属的类型，是关键字还是标识符
Types getType(string str)
{
	if(str=="if")     return IF;
	else if(str=="else")   return ELSE;
	else if(str=="int")    return INT;
	else if(str=="return") return RETURN;
	else if(str=="void")   return VOID;
	else if(str=="while")  return WHILE;
    else if(str=="float")  return FLOAT;
    else if(str=="const") return CONST;
    else if(str=="continue") return CONTINUE;
    else if(str=="break") return BREAK;
    else if(str=="char") return CHAR;
	for(int i=0; i<str.length(); i++)
    {
        if((!isNum(str[i]))&&(!isAlpha(str[i])))
        {
            return IILEGAL_ID;
        }
    }
    return ID;
}

//状态转移函数，进行有穷自动机的分析
void getToken(string tmp)
{
    bool save = true;//是否将当前字符存入匹配单词字符
    Types curr;//当前字符
    States state;//当前状态
    string tokenString="";
    if(flag==false)//如果当前还处在注释内部 
    state=START;
    else
    state = INCOMMENT;//那么继续返回注释状态 
    string s="//";
	for(int i=0;i<=tmp.length();i++)   //按照行为单位读入 
    {
        save = true;
        char ch = tmp[i];
        switch(state)
        {
            //DFA
            case START:
                if(isNum(ch))
                state = INNUM;
                else if(isAlpha(ch))
                state = INID;
                else if(ch=='<')
                state=INLT;
                else if(ch=='>')
                state=INGT;
                else if(ch=='=')
                state=INEQ;
                else if(ch=='+')
                state=INADD;
                else if(ch=='-')
                state=INSUB;
                else if(ch=='*')
                state=INMUL;
                else if(ch=='/')
                state=INDIV;
                else if(ch=='%')
                state=INMOD;
                else if(ch=='!')
                state=INNOT;
                else if(ch==' '||ch=='\t'||ch=='\n')//分隔
                save = false;
                else if(ch=='\'')
                state = CHARS;
                else if(ch=='&')
                state = INAND;
                else if(ch=='|')
                state = INOR;
                else
                {
                    state=DONE;
                    switch(ch)
                    {
                        case '\0'://读取注释到了最后，仍然没有结束，此时返回特殊的状态
                            save= false;
                            curr = ENDFILE;
                            break;
                        case '(':
                            curr=LP;
                            break;
                        case ')':
                            curr=RP;
                            break;
                        case '[':
                            curr=LBR;
                            break;
                        case ']':
                            curr=RBR;
                            break;
                        case '{':
                            curr=LB;
                            break;
                        case '}':
                            curr=RB;
                            break;
                        case ';':
                            curr=DELIMI;
                            break;
                        case ',':
                            curr=COMMA;
                            break;
                        default:
						    curr=ERROR;
							break; 
                    }

                }
                break;

            case INDIV: //刚进入注释
                if(ch=='=')
                {
                    save=true;   
                    state=DONE;
                    curr=DIVE;
                    flag = true;                  
                }
                else if(ch=='/')
                {
                    state = INDCOM;//进入注释部分
                    flag = false;
                }
                else if(ch=='*')
                {
                    state = INCOMMENT;//进入注释部分 
                    flag = true;
                }
                else
                {
                    save = true;
                    state = DONE;
                    i--;
                    curr = DIV;
                }
                break;
            case INCOMMENT:
                save=true;
                if(ch=='*')
                state = READTOUT;//准备出注释
                if(ch=='\0')
                {
	                state=DONE;
                    curr=ENDFILE;   //如果当前行所有都已经结束，那么直接把所有的字符给到注释                    
                }
                break;

            case READTOUT: //快要退出注释 此时如果再来一个/，退出注释，否则返回正式注释状态 
                if(ch=='/')
                {
                    state = DONE;
                    flag = false;
                    curr = ENDFILE;
                }
                else
                {
                    i--;
                    state = INCOMMENT;//不是/继续进入注释状态
                    save = false;
                }
                break;

            case INDCOM: //

                s+=tmp.substr(i,tmp.length());
                cout<<"\t"<<LINE<<":"<<"< COMMENT,"<<s<<" >"<<endl;
                s="//";
                goto OUT;
                break;

            case INLT:
                state = DONE;
                if(ch=='=')
                curr = LE;
                else
                {
                    save = false;
                    i--;
                    curr = L;
                }
                break;
            
                case INGT:
                state = DONE;
                if(ch=='=')
                curr = GE;
                else
                {
                    save = false;
                    i--;
                    curr = G;
                }
                break;
            
                case INEQ:
                state = DONE;
                if(ch=='=')
                curr = EQ;
                else
                {
                    save = false;
                    i--;
                    curr = ASS;
                }
                break;

                case INNOT:
                state = DONE;
                if(ch=='=')
                curr = NEQ;
                else
                {
                    save = false;
                    i--;
                    curr = NOT;
                }
                break;

            case INADD:
                state=DONE;
                if(ch=='=')
                curr=ADDE;
                else if(ch=='+')
                curr = DADD;
                else{
                    save=false;
                    i--;//下次循环能从当前字符开始
                    curr=ADD;
                }
                break;
            case INSUB:
                state=DONE;
                if(ch=='=')
                curr=SUBE;
                else if(ch=='-')
                curr = DSUB;
                else{
                    save=false;
                    i--;//下次循环能从当前字符开始
                    curr=SUB;
                }
                break;
            case INMUL:
                state=DONE;
                if(tmp[i]=='=')
                curr=MULE;
                else{
                    save=false;
                    i--;//下次循环能从当前字符开始
                    curr=MUL;
                }
                break;

            case INMOD:
                state=DONE;
                if(tmp[i]=='=')
                curr=MODE;
                else{
                    save=false;
                    i--;//下次循环能从当前字符开始
                    curr=MOD;
                }
                break;

            case INNUM:
                if(!isNum(ch))
                {
                    if(isAlpha(ch))
                    {
                        state=DONE;
                        curr = IILEGAL_NUM;
                        break;
                    }
                    i--;
                    save = false;
                    state = DONE;
                    curr = NUM;
                }
                
                break;//因为如果是数字的话，每次循环save都是true不用再写else

            case INID:
                if(!isAlpha(ch))
                {
                    i--;
                    save = false;
                    state = DONE;
                    curr = ID;
                }
                break;
            
            case CHARS:
                if(isChar(ch))
                {
                    state=CHARE;
                }
                else
                {
                    state = DONE;
                    curr = ERROR;
                }
                break;

            case CHARE:
                if(tmp[i]=='\'')
                {
                    state=DONE;
                    curr=CH;
                    break;
                }
                else
                {
                    state = DONE;;
                    curr = CHARERROR;
                    break;
                }
            case INAND:
                if(ch=='&')
                {
                    curr = ADD;
                    state = DONE;
                    break;
                }
                else
                {
                    state = DONE;
                    curr = ERROR;
                    break;
                }
            
            case INOR:
                if(ch=='|')
                {
                    curr = OR;
                    state = DONE;
                }
                else
                {
                    state = DONE;
                    curr = ERROR;
                }
                break;

			case DONE:
                break;   

			default:
				state=DONE;
				curr=ERROR;
				break;            
        
        }
        if(save && tmp[i]!='\0')
		tokenString+=tmp[i];   //保存好当前的字符，加入匹配字符串 
		if(curr==ID)   //如果是ID类型，那么找一找有没有可能会是预留类 
		curr=getType(tokenString);
		if(state==DONE)   //如果匹配完毕 
		{
			PrintToken(curr,tokenString);   //输出！ 
			tokenString="";   //匹配字符串归零，开始下一轮 
			if(flag==false)   //flag表示是否在注释内，如果当前注释还没结束，需要退回到注释内部状态 
			state=START;
			else
			state=INCOMMENT;
		}
    }
    OUT:
    LINE++;
    if(flag==true) //flag
    {
        state = START;
        cout<<"error: no */"<<endl;
        exit(0);
    }

}

void read()
{
	fstream ff("test2.txt",ios::in);
	assert(ff.is_open());
    string tmp;
    cout<<"20JiLian HUANG XIN 202065073276"<<endl;
	while(!ff.eof())
	{
		getline(ff,tmp);
		{
			cout<<endl;
		    cout<<"LINE"<<LINE<<":"<<tmp;
		    if(!ff.eof())
		    cout<<endl;
		}
		if(ff.eof())
		cout<<"EOF"<<endl;
		getToken(tmp);
	}  
}


enum Error{ID_ERROR,ASSIGN_ERROR,DELIMITER_ERROR,TYPE_ERROR,BRACE_ERROR,PARENTHSIS_ERROR,};

//以下为递归下降

//错误
void error(Error e)
{
    switch(e)
    {
        case ID_ERROR:
        cout<<"NO Identifier here"<<endl;
        break;

        case ASSIGN_ERROR:
        cout<<"ASSIGN_ERROR"<<endl;
        break;

        case DELIMITER_ERROR:
        cout<<"NOT FIND DELIMETER"<<endl;
        break;

        case TYPE_ERROR:
        cout<<"TYPE_ERROR"<<endl;
        break;

        case BRACE_ERROR:
        cout<<"BRACE_ERROR"<<endl;
        break;

        case PARENTHSIS_ERROR:
        cout<<"PARENTHSIS_ERROR"<<endl;
        break;

        default:
        cout<<"ERROR"<<endl;
        break;
    }
}
//下一个token
Token getNext()
{
    return tokens[++tp];
}
//当前的token
Token now;

int lookupTable(string var)
{
    for(int i=0;i<var_vals.size();i++)
    {
        if(var_vals[i].var==var)
        return i;
    }
    return -1;
}

//操作数
stack<string> operand;
//操作符
stack<string> op;

//以下的三个字符串是为了进行类型判断
//声明的类型
string declType;
//前一个数据类型，在一个表达式中，不允许不同类型进行操作
string preDataType="";
//目前的数据类型
string dataType;
bool priority(string a, string b)
{

    if((a=="*"||a=="/")&&(b=="+"||b=="-"))
    {
        return true;
    }
    else return false;
}

string temp="T";
int count = 0;

void Decls();
void Stmts();
void Decl();
void FuncDef();
void ConstDecl();
void VarDecl();
void BType();
void ConstDef();
void ConstInitVal();
void VarDef();
void InitVal();
void Block();
void BlockItem();
void Stmt();
void Exp(); 
void E();
void T();
void E_();
void F();
void T_();
void term();
void LVal();
void Cond();
void RelExp();
//CompUnit → [ CompUnit ] ( Decl | FuncDef ) 

//Decls()可以不断向后分析
void Decls()
{
    now = tokens[tp+1];
    if( now.val!="const" && now.val!="int" && now.val!="char")
    {
        return;
    }
    Decl();
    Decls();
}

//Decl → ConstDecl | VarDecl
void Decl()
{
    now = getNext();//预测一下
    if(now.val=="const")
    {
        cout<<"matching const"<<endl;
        ConstDecl();
    }
    else if(now.val=="int" && tokens[tp+1].val=="main")
    {
        tp--;//返回到当前的token，因为以上的尝试失败
        FuncDef();
    }
    else
    {
        tp--;//返回到当前的token，因为以上的尝试失败
        VarDecl();
    }

}
void FuncDef()
{
    BType();
    now = getNext();
    if(now.type=="ID")
    {
        cout<<"matching main"<<endl;
    }
    else
    {
        error(ID_ERROR);
        exit(0);
    }

    if(getNext().val=="(")
    {
        cout<<"matching ("<<endl;
        if(getNext().val==")")
        cout<<"matching )"<<endl;
    }
    else
    {
        exit(0);
        cout<<"Function define error "<<endl;
    }
    Block();
}

//ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';' 
void ConstDecl()
{
    //now = getNext();
    // if(now.val!="const")
    // error();

    BType();
    declType = now.val;

    string tempID  = tokens[tp+1].val;
    ConstDef();

    now = getNext();
    while(now.val==",")
    {
        ConstDef();
    }

    //now = getNext();
    //cout<<now.val<<endl;
    if(now.val==";")
    {
        cout<<"matching ;"<<endl;
        //处理操作数栈和操作符栈
        string arg1;
        string arg2;
        string res;
        while(!op.empty())
        {
            arg1 = operand.top();
            operand.pop();
            //cout<<arg1<<endl;
            arg2 = operand.top();
            operand.pop();
            //cout<<arg2<<endl;
            res = temp+to_string(++count);
            quadrups.push_back(Quadruple(op.top(),arg2,arg1,res));

            //cout<<op.top()<<endl;
            op.pop();
            operand.push(res);
            //cout<<res<<endl;
        }

        if((declType=="int"&&dataType=="NUM")||(declType=="char"&&dataType=="CHAR"))
        {
            quadrups.push_back(Quadruple("=",operand.top(),"_",tempID));
            preDataType = "";
            operand.pop();
        }
        else
        {
            cout<<"Type Error: The right size value can not assign to left hand size "<<endl;
            exit(0);
        }
        return;
    }
    else
    error(DELIMITER_ERROR);

}

//VarDecl → BType VarDef { ',' VarDef } ';'
void VarDecl()
{
    BType();
    declType = now.val;

    string tempID = tokens[tp+1].val;
    VarDef();

    now = getNext();
    while(now.val==",")
    {
        VarDef();
        now=getNext();
    }
    
    if(now.val!=";")
    error(DELIMITER_ERROR);
    else
    {
        cout<<"matching ;"<<endl;

        string arg1;
        string arg2;
        string res;
        while(!op.empty())
        {
            arg1 = operand.top();
            operand.pop();

            arg2 = operand.top();
            operand.pop();

            res = temp+to_string(++count);
            quadrups.push_back(Quadruple(op.top(),arg2,arg1,res));

            op.pop();
            operand.push(res);
        }
        if((declType=="int"&&dataType=="NUM")||(declType=="char"&&dataType=="CHAR"))
        {

            quadrups.push_back(Quadruple("=",operand.top(),"_",tempID));
            preDataType = "";
            operand.pop();
        }
        else
        {
            cout<<"Type Error: The right size value can not assign to left hand size "<<endl;
            exit(0);
        }
        return;
    }
}

//BType → 'int' | 'char'
void BType()
{
    now = getNext();

    //cout<<now.val<<endl;
    if(now.val=="int")
    {
        cout<<"matching int"<<endl;
        return;
    }
    else if(now.val=="char")
    {
        cout<<"matching char"<<endl;
        return;
    }
    else
    error(TYPE_ERROR);
}

//ConstDef → Ident  '=' ConstInitVal //这里我们不写数组
void ConstDef()
{
   now = getNext();
   if(now.type!="ID")
   {
        error(ID_ERROR);
        exit(0);
   }
   else
   {
       var_vals.push_back(var_val(now.val,
       tokens[tp-1].val=="int" ? "NUM":"CHAR"));
       cout<<"matching "<<now.val<<endl;
   }
   
   now = getNext();

   if(now.val!="=")
   {
       error(ASSIGN_ERROR);
   }
   else
   {
       cout<<"matching "<<now.val<<endl;
   }
   //cout<<now.val<<endl;
   ConstInitVal();
}
//ConstInitVal → ConstExp 这里不写用{}来初始化数组 因为不写数组
//原本的是ConstExp → AddExp 注：使用的 Ident 必须是常量
//现在改为ConstExp → char |Exp //要么是字符要么是表达式
void ConstInitVal()
{
    //now = getNext();
   // cout<<now.val<<endl;
    // if(now.type=="char")
    // {
    //     cout<<"matching char"<<endl;
    //     return ;
    // }
    
    Exp();
}

//VarDef → Ident  '=' InitVal //不写数组
void VarDef()
{
   now = getNext();
//    cout<<now.val<<endl;
//    cout<<now.type<<endl;
   if(now.type!="ID")
   error(ID_ERROR);
   else
   {
       var_vals.push_back(var_val(now.val,
       tokens[tp-1].val=="int" ? "NUM" : "CHAR"));
       cout<<"matching "<<now.val<<endl;
   }

   now = getNext();
   if(now.val!="=")
   error(ASSIGN_ERROR);
   else
   {
       cout<<"matching "<<now.val<<endl;
   }

   InitVal();
}

//原本InitVal → Exp 不写后面 '{' [ InitVal { ',' InitVal } ] '}' 这是数组的初始化
//自己改的 InitVal → char |Exp //要么是字符要么是表达式
void InitVal()
{
    now = getNext();
    if(now.type=="CHAR")
    {
        cout<<"matching "<<now.val<<endl;
        dataType = "CHAR";
        operand.push((now.val));
        return;
    }
    else
    {
        tp--;
        Exp();
    }

}

//Block → '{' { BlockItem } '}' 语句块
void Block()
{
    now = getNext();
    //cout<<now.val<<endl;
    if(now.val!="{")
    error(BRACE_ERROR);
    else
    {
        cout<<"matching "<<now.val<<endl;
    }
    now = getNext();
    if(now.val=="}")
    {
        cout<<"matching }"<<endl;
    }
    else
    {
        tp--;
        BlockItem();
    }
    now = getNext();
    if(now.val!="}")
    error(BRACE_ERROR);
    else
    {
        cout<<"matching "<<now.val<<endl;
    }

}

//BlockItem → Decl | Stmt
void BlockItem()
{
    Decls();
    Stmts();
}

void Stmts()
{
    now = tokens[tp+1];
    if(now.val!="if" && now.val!="while" && now.type!="ID")
    {
        return;
    }
    Stmt();
    Stmts();
}

// int if_begin=0;
// int else_begin=0;
// int while_begin=0;
vector<int>if_true_patch;
vector<int>if_false_patch;
vector<int>while_true_patch;
vector<int>while_false_patch;
/*
Stmt → LVal '=' Exp ';'

| [Exp] ';' | Block

| 'if' '( Cond ')' Stmt [ 'else' Stmt ]

| 'while' '(' Cond ')' Stmt 
*/
void Stmt()
{
    now = getNext();
    if(now.val=="if")
    {
        cout<<"matching if"<<endl;
        //if_begin = quadrups.size();

        now = getNext();
        if(now.val!="(")
        error(PARENTHSIS_ERROR);
        else
        {
            cout<<"matching "<<now.val<<endl;
        }

        Cond();

        if(now.val!=")")
        error(PARENTHSIS_ERROR);
        else
        {
            cout<<"matching "<<now.val<<endl;
        }
        

        now = getNext();
        if(now.val=="{")
        {
            cout<<"matching {"<<endl;
            int index = if_true_patch.back();
            if_true_patch.pop_back();
            quadrups[index].result = to_string(quadrups.size());

        }

        else
        {
            error(BRACE_ERROR);
        }

        Stmt();

        now = getNext();
        if(now.val=="}")
        {
            cout<<"matching "<<now.val<<endl;
            for(int i =0;i<if_false_patch.size();i++)
            {
                quadrups[if_false_patch[i]].result = to_string(quadrups.size());
            }
            if_false_patch.clear();
        }

        now = tokens[tp+1];
        if(now.val=="else")
        {
            cout<<"matching else"<<endl;
            tp++;
            now = getNext();
            if(now.val=="{")
            {
                cout<<"matching {"<<endl;
            }
            else
            {
                error(BRACE_ERROR);
                exit(0);
            }
            Stmt();
            now = getNext();
            if (now.val=="}")
            {
                cout<<"matching }"<<endl;
            }
            else
            {
                error(BRACE_ERROR);
                exit(0);
            }
            
        }
    }
    else if(now.val=="while")
    {
        cout<<"matching while"<<endl;
        now = getNext();
        if(now.val!="(")
        error(PARENTHSIS_ERROR);
        else
        {
            cout<<"matching "<<now.val<<endl;
        }
        int condBegin = quadrups.size();
        Cond();
        int condEnd = quadrups.size();

        if(now.val!=")")
        error(PARENTHSIS_ERROR);    
        else
        {
            cout<<"matching "<<now.val<<endl;
        }  
        now = getNext();
        if(now.val=="{")
        {
            cout<<"matching {"<<endl;
            //cout<<if_false_patch.empty()<<endl;
            int index = if_true_patch.back();
            if_true_patch.pop_back();
            quadrups[index].result = to_string(quadrups.size());
        }
        else
        {
            error(BRACE_ERROR);
        }
        int stmtBegin = quadrups.size();
        Stmt();
        now = getNext();
        if(now.val=="}")
        {
            cout<<"matching "<<now.val<<endl;

            // for(int i = condBegin;i<condEnd;i++)
            // {
            //     quadrups.push_back(quadrups[i]);
            // }
            // quadrups[quadrups.size()-2].result=to_string(stmtBegin);
            // quadrups[quadrups.size()-1].result=to_string(quadrups.size());
            quadrups.push_back(Quadruple("j","_","_",to_string(condBegin)));
            for(int i =0;i<if_false_patch.size();i++)
            {
                quadrups[if_false_patch[i]].result = to_string(quadrups.size());
            }
            if_false_patch.clear();

        }
    }
    else
    {
        LVal();//这个函数里已经将LVal压入栈了
        string tempID = now.val;
        now = getNext();
        if(now.val!="=")
        error(ASSIGN_ERROR);
        else
        {
            cout<<"matching "<<now.val<<endl;
        }
        //cout<<now.val<<endl;
        Exp();
        now = getNext();
        //cout<<now.val<<endl;
        if(now.val!=";")
        error(DELIMITER_ERROR);
        else
        {
            cout<<"matching "<<now.val<<endl;
            //处理操作数栈和操作符栈
            string arg1;
            string arg2;
            string res;
            while(!op.empty())
            {
                arg1 = operand.top();
                operand.pop();
                //cout<<arg1<<endl;
                arg2 = operand.top();
                operand.pop();
                //cout<<arg2<<endl;
                res = temp+to_string(++count);
                quadrups.push_back(Quadruple(op.top(),arg2,arg1,res));

                //cout<<op.top()<<endl;
                op.pop();
                operand.push(res);
                //cout<<res<<endl;
            }

            if((declType=="int"&&dataType=="NUM")||(declType=="char"&&dataType=="CHAR"))
            {
                quadrups.push_back(Quadruple("=",operand.top(),"_",tempID));
                preDataType = "";
                operand.pop();
            }
            else
            {
                cout<<"Type Error: The right size value can not assign to left hand size "<<endl;
                exit(0);
            }
            return;
        }
    }

}

//算数表达式
/*
1、语法分析所依据的文法；
G[E]：
E→E+T| E-T| T
T→T*F| T/F| F
F→(E)| i
2、给出消除左递归及提取左公因子的文法；
G’[E]：
E →  TE’
E’ → +TE’| -TE’|ε
T  →  FT’
T’→  *FT’|/FT’|ε
F  → (E)| i

i可以是变量或者数字 用term()表示
*/
void Exp()
{
    E();
    return;
}
void E()
{
    T();
    E_();
    return;
}
void T()
{
    F();
    T_();
    return;
}
void E_()
{
    now = getNext();
    //cout<<now.val<<endl;
    if(now.val=="+")
    {
        //cout<<op.top()<<endl;
        if(op.empty())
        {
            op.push("+");
        }
        else
        {
            while(!op.empty())
            {
                string arg1 = operand.top();
                operand.pop();
                string arg2 = operand.top();
                operand.pop();
                string res = temp+to_string(++count);
                quadrups.push_back(Quadruple(op.top(),arg2,arg1,res));

                //cout<<op.top()<<endl;
                op.pop();
                operand.push(res);
                //cout<<op.empty()<<endl;
                
            }
            op.push("+");
        }


        cout<<"matching +"<<endl;
        T();
        E_();
        return;
    }
    else if(now.val=="-")
    {
        if(op.empty())
        {
            op.push("-");
        }
        else
        {
            while(!op.empty())
            {
                string arg1 = operand.top();
                operand.pop();
                string arg2 = operand.top();
                operand.pop();
                string res = temp+to_string(++count);
                quadrups.push_back(Quadruple(op.top(),arg2,arg1,res));

                //cout<<op.top()<<endl;
                op.pop();
                operand.push(res);
                //cout<<op.empty()<<endl;
                
            }
            op.push("-");
        }
        cout<<"matching -"<<endl;
        T();
        E_();
        return;
    }
    tp--;
    return;
}
void F()
{
    term();
}

void T_()
{
    now = getNext();
    if(now.val=="*")
    {
        if(op.empty())
        {
            op.push("*");
            cout<<"matching *"<<endl;
            F();
            T_();
            return;
        }
        else
        {
            if(priority("*",op.top()))
            {
                op.push("*");
                cout<<"matching *"<<endl;
                F();
                T_();
                return;
            }
            else
            {
                while(!op.empty())
                {
                    string arg1 = operand.top();
                    operand.pop();
                    string arg2 = operand.top();
                    operand.pop();
                    string res = temp+to_string(++count);
                    quadrups.push_back(Quadruple(op.top(),arg2,arg1,res));

                    //cout<<op.top()<<endl;
                    op.pop();
                    operand.push(res);
                }
                op.push("*");
                cout<<"matching *"<<endl;
                F();
                T_();
                return;
            }
        }
        
    }
    else if(now.val=="/")
    {
        op.push("/");
        cout<<"matching /"<<endl;
        F();
        T_();
        return;
    }
    tp--;
    return;
}
void term()
{
    now = getNext();
    //cout<<now.val<<endl;
    if(now.type=="NUM")
    {
        if(preDataType=="")
        {
            preDataType = "NUM";   
            operand.push(now.val);
            cout<<"matching "<<now.val<<endl;
            //return;
        }
        else if(preDataType==now.type)
        {
            operand.push(now.val);
            cout<<"matching "<<now.val<<endl;
            //return;
        }
        else
        {
            cout<<"Error: operations on different types are not supported"<<endl;
            exit(0);
        }
        dataType = "NUM";
        return;

    }

    if(now.type=="ID")
    {
        int index = lookupTable(now.val);
        if(index!=-1)
        {
            if(preDataType=="")
            {
                preDataType = var_vals[index].type;
                operand.push(now.val);
                cout<<"matching "<<now.val<<endl;
                //dataType=preDataType;        
            }
            else if(preDataType==var_vals[index].type)
            {
                operand.push(now.val);
                cout<<"matching "<<now.val<<endl;
                //dataType = var_vals[index].type;    
            }
            else
            {
                cout<<index<<endl;
                cout<<preDataType<<" "<<var_vals[index].type<<endl;
                cout<<"Error: operations on different types are not supported"<<endl;
                exit(0);
            }
            dataType = var_vals[index].type;
            return;

        }
        else
        {
            cout<<"Error: "<<now.val<<" Dose not be declared before"<<endl;
        }

    }
    //cout<<now.type<<endl;
    if(now.type=="CHAR")
    {
        //operand.push(now.val);
        if(operand.size()==0)
        {
            cout<<"matching "<<now.val<<endl;
            operand.push(now.val);
            dataType = "CHAR";

           // cout<<"AAA"<<endl;
        }
        else
        {
            cout<<"Do not support operations on characters!"<<endl;
            exit(0);
        }

        
    }
    error(TYPE_ERROR);

}

void LVal()
{
    //now = getNext();
    if(now.type!="ID")
    error(ID_ERROR);
    else
    {
        int index = lookupTable(now.val);
        if(index!=-1)//是否存在该标识符
        {
            declType = var_vals[index].type=="NUM" ? "int":"char";
            cout<<"matching "<<now.val<<endl;
        }
        else
        {
            cout<<"Error: "<<now.val<<" Dose not be declared before"<<endl;
            exit(0);
        }
    }
}

/*
Cond->RelExp | RelExp {&& | ||} Cond
*/
void Cond()
{
    RelExp();
    
    now = getNext();
    if(now.val=="&&" || now.val=="||")
    {
        cout<<"matching "<<now.val<<endl;
        Cond();
    }
}
//RelExp->Exp {>|<|==} Exp
//这里写的很简单就只判断大小关系
void RelExp()
{
    if(now.val=="&&")
    {
        int now = quadrups.size();
        int index=if_true_patch.back();
        if_true_patch.pop_back();
        quadrups[index].result=to_string(now);


    }
    if(now.val=="||")
    {
        int index = if_false_patch.back();
        if_false_patch.pop_back();
        quadrups[index].result  =to_string(quadrups.size());
    }
    Exp();
    now = getNext();
    string temp = now.val;

    if(now.val=="<"|| now.val==">"||now.val=="==")
    {
        cout<<"matching "<<now.val<<endl;
        Exp();
        string arg1 = operand.top();
        operand.pop();
        string arg2 =  operand.top();
        operand.pop(); 
        quadrups.push_back(Quadruple("j"+temp,arg2,arg1,"true"));
        //待回填的
        if_true_patch.push_back(quadrups.size()-1);

        quadrups.push_back(Quadruple("j","_","_","false"));
        //待回填
        if_false_patch.push_back(quadrups.size()-1);
    }
    else
    {
        cout<<"Error: No relations operator here"<<endl;
        exit(0);
    }

}

int main()
{
    read();
    for(int i = 0; i <tokens.size(); i++)
    {
        cout<<tokens[i].val<<"  "<<tokens[i].type<<endl;
    }
    cout<<"--------------------------------"<<endl;
   // while(tp<tokens.size())
    //{
        Decls();
    //}

    //cout<<quadrups.size()<<endl;
    for(int i=0; i<quadrups.size(); i++)
    {
        cout<<i<<" ";
        quadrups[i].print();
    }
}