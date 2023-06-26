#include<iostream>
#include<fstream>
#include<string>
#include<assert.h>
using namespace std;
int LINE=1;   //���ڼ�¼���������? 
bool flag=false;   //���ڱ�ʾ��ǰע���Ƿ����? 
bool dComment = false; //˫б��ע��
//�ؼ��ʣ������?
enum Types{
    ENDFILE,ERROR,
    IF,ELSE,INT,RETURN,VOID,WHILE,FLOAT,CONST,BREAK,CONTINUE,CHAR,   //�ؼ��� 
    ID,NUM,   //��ʶ��������
    ADD,SUB,MUL,DIV,L,LE,G,GE,EQ,NEQ,NOT,ASS,DELIMI,COMMA,LP,RP,LBR,RBR,LB,RB,LC,RC,
    // + - * / < <= > >= == != ! =             ; , ( ) [ ] { } /* */
    //addtion subtract divide less less_equal great great_equal equal, not_equal,assign delimiter comma left/right parenthsis,bracket,brace,left and right comment
    CH,//�ַ�
    MOD,MODE,//% %=
    ADDE,SUBE,MULE,DIVE,//+=,-=,*=,/=    
    CHARERROR,//�ַ�'��ƥ��
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
	//��ʼ�����֡��ַ���С�ڵ��ڡ����ڵ��ڡ���ֵ����ڡ��?�Ϳ�ʼ��ע�����ݿ�ʼ��ע�����ݽ�������ɺ͵����ַ�ֱ����� 
    CHARS,CHARE, //�ַ���ʼ���ַ��У��ַ����� char start, char end
    INADD,INSUB,INMUL,INDIV,INMOD,//��ʼ����Ӽ��˳��?  
    INDCOM,//˫б�ܵ�ע�� double comment
    READTOUT,//׼����ע��
    INAND,INOR//&& ||
};

bool isNum(char a)  //��⵱ǰ�ַ��Ƿ��?���� 
{
	if(a>='0'&&a<='9')
	return true;
	return false;
}
 
bool isAlpha(char a)   //��⵱ǰ�ַ��Ƿ��?��ĸ 
{
	if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a=='_'))
	return true;
	return false;
}
 
bool isChar(char a) //��⵱ǰ�Ƿ��?һ���Ϸ��ַ� ASCII
{
    if(' '<=a&&a<='~')
    {
        return true;
    }
    return false;
}

void PrintToken(Types type, string TokenString)   //����ÿһ��״̬���ÿһ���Ĵʷ�������? 
{
	if(TokenString!="\0")   //����ǿ��У���ô���������ָ��? 
	cout<<"\t"<<LINE<<": ";
	switch(type)   //���ݵ�ǰ״̬���Ӧ��ƥ��Ķ��� 
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
        cout<<"<KEYWORD,"<<TokenString<<">"<<endl;   //Ԥ���ʶ��ǵ�����״̬ 
		break;
        case ADD: printf("< ADD,+ >\n");  break;
        case SUB: printf("< SUB,- >\n");  break;
        case MUL: printf("< MUL,* >\n");  break;
        case DIV: printf("< DIV,/>\n");  break;
        case L:   printf("< L,< >\n");  break;
        case LE:  printf("< LE,<= >\n"); break;//    ADD,SUB,MUL,DIV,L,LE,G,GE,ISE,NT,NTE,FZ,FH,DH,LXK,RXK,LZK,RZK,LDK,RDK,LZS,RZS   
                                                    // + - * / < <= > >= == != = ; , ( ) [ ] { } /* */
        case MOD: printf("< MOD,% >\n"); break;
        case G:   printf("< G,> >\n");  break;
        case GE:  printf("< GE,>= >\n"); break;
        case EQ: printf("< EQ,== >\n"); break;
        case NEQ:  printf("< NEQ,!= >\n");  break;
        case NOT: printf("< NOT,! >\n"); break;   // ADD,SUB,MUL,DIV,L,LE,G,GE,EQ,NEQ,NOT,ASS,DELIMI,COMMA,LP,RP,LBR,RBR,LB,RB,LC,RC,
                                                // + - * / < <= > >= == != ! =  ; , ( ) [ ] { } /* */
        case ASS:  printf("< ASS,= >\n");  break;
        case DELIMI: printf("< DELIMITER,; >\n");  break;
        case COMMA:  printf("< COMMA,, >\n");  break;
        case LP: printf("< LP,( >\n");  break;
        case RP: printf("< RP,) >\n");  break;
        case LBR: printf("< LBR,[ >\n");  break;
        case RBR: printf("< RBR,]>\n");  break;
        case LB: printf("< LB,{ >\n");  break;
        case RB: printf("< RB,} >\n");  break;
        case ADDE: printf("< ADDE,+=>");break;
        case SUBE: printf("< SUBE,-= >");break;
        case MULE: printf("< MULE,*= >");break;
        case DIVE: printf("< DIVE,/= >");break;
        case MODE: printf("< MODE,%= >");break;
        case ENDFILE: if(TokenString!="\0") cout<<"COMMENT"<<TokenString<<endl;break;   //ENDFILE��Ϊע�ͽ����������ֱ����������ַ��� 
		case NUM:
	        cout<<"< NUM,"<<TokenString<<" >"<<endl; break;
        case ID:
	        cout<<"< ID,"<<TokenString<<" >"<<endl; break;
        case ERROR:   
            //�����������ķ�����ô�����������״�? 
	        cout<<"ERROR"<<TokenString<<endl; break;
        case CH: 
            cout<<"< CHAR,"<<TokenString<<" >"<<endl; break;
        case IILEGAL_ID: 
            cout<<"< ILEGAL_ID,"<<TokenString<<" >"<<endl;
            break;
        case CHARERROR:
            cout<<"< CHARERROR,"<<TokenString<<" >"<<endl; break;
        case IILEGAL_NUM:
            cout<<"< IILEGAL_NUM,"<<TokenString<<" >"<<endl; break;
        case COMMENT_ERROR:
            cout<<"< COMMENT_ERROR,"<<TokenString<<" >"<<endl; break;
        case DADD:
            cout<<"< DADD,++ >"<<endl;break;
        case DSUB:
            cout<<"< DSUB,-- >"<<endl; break;
	}
}

//�ж��ַ������������ͣ��ǹؼ��ֻ��Ǳ�ʶ��
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

//״̬ת�ƺ��������������Զ����ķ���
void getToken(string tmp)
{
    bool save = true;//�Ƿ񽫵�ǰ�ַ�����ƥ�䵥���ַ�
    Types curr;//��ǰ�ַ�
    States state;//��ǰ״̬
    string tokenString="";
    if(flag==false)//�����ǰ�������?���ڲ� 
    state=START;
    else
    state = INCOMMENT;//��ô��������ע��״̬ 
    string s="//";
	for(int i=0;i<=tmp.length();i++)   //������Ϊ��λ���� 
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
                else if(ch==' '||ch=='\t'||ch=='\n')//�ָ�
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
                        case '\0'://��ȡע�͵��������Ȼû�н�������ʱ���������״̬
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

            case INDIV: //�ս���ע��
                if(ch=='=')
                {
                    save=true;   
                    state=DONE;
                    curr=DIVE;
                    flag = true;                  
                }
                else if(ch=='/')
                {
                    state = INDCOM;//����ע�Ͳ���
                    flag = false;
                }
                else if(ch=='*')
                {
                    state = INCOMMENT;//����ע�Ͳ��� 
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
                state = READTOUT;//׼����ע��
                if(ch=='\0')
                {
	                state=DONE;
                    curr=ENDFILE;   //�����ǰ�����ж��Ѿ���������ôֱ�Ӱ����е��ַ������?��                    
                }
                break;

            case READTOUT: //��Ҫ�˳�ע�� ��ʱ�������һ��?/���˳�ע�ͣ����򷵻���ʽע��״̬ 
                if(ch=='/')
                {
                    state = DONE;
                    flag = false;
                    curr = ENDFILE;
                }
                else
                {
                    i--;
                    state = INCOMMENT;//����/��������ע��״̬
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
                    i--;//�´�ѭ���ܴӵ�ǰ�ַ���ʼ
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
                    i--;//�´�ѭ���ܴӵ�ǰ�ַ���ʼ
                    curr=SUB;
                }
                break;
            case INMUL:
                state=DONE;
                if(tmp[i]=='=')
                curr=MULE;
                else{
                    save=false;
                    i--;//�´�ѭ���ܴӵ�ǰ�ַ���ʼ
                    curr=MUL;
                }
                break;

            case INMOD:
                state=DONE;
                if(tmp[i]=='=')
                curr=MODE;
                else{
                    save=false;
                    i--;//�´�ѭ���ܴӵ�ǰ�ַ���ʼ
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
                
                break;//��Ϊ��������ֵĻ���ÿ���?��save����true������дelse

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
		tokenString+=tmp[i];   //����õ�ǰ���ַ�������ƥ���ַ���? 
		if(curr==ID)   //�����ID���ͣ���ô��һ����û�п��ܻ���Ԥ���� 
		curr=getType(tokenString);
		if(state==DONE)   //���ƥ����� 
		{
			PrintToken(curr,tokenString);   //�����? 
			tokenString="";   //ƥ���ַ������㣬��ʼ��һ�� 
			if(flag==false)   //flag��ʾ�Ƿ���ע���ڣ������ǰ�?�ͻ�û��������Ҫ�˻ص�ע���ڲ�״̬ 
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
    }

}

void read()
{
	fstream ff("test1.txt",ios::in);
	assert(ff.is_open());
    string tmp;
    cout<<"20计联黄鑫202065073276"<<endl;
    cout<<"20计创艾乐君202030430011"<<endl;
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

int main()
{
    read();
    return 0;
}