#include "nemu.h"
#include <stdlib.h>
#include <elf.h>


extern int find_obj(char* my_obj);
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, NEQ,

	/* TODO: Add more token types */
	NUMBER,NEGANUM,HEX, EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, EIP, DEREF, NOT, OR, AND,OBJECT
};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"\\+", '+'},					// plus
	{"==", EQ},						// equal
	{"!=", NEQ},					//not equal
	{"-",'-'},						//subtract
	{"\\*",'*'},					//multiple
	{"/",'/'},						//divide
	{"\\(",'('},					//left bracket
	{"\\)",')'},					//right bracket
	{"0x[0-9a-fA-F]+",HEX},			// hexadecimal
	{"[0-9]+",NUMBER},				//number
	{"\\$eax",EAX},{"\\$ecx",ECX},{"\\$edx",EDX},{"\\$ebx",EBX},{"\\$esp",ESP},{"\\$ebp",EBP},{"\\$esi",ESI},{"\\$edi",EDI},{"\\$eip",EIP},				//register
	{"!", NOT},						//not
	{"\\|\\|", OR},					//or
	{"&&", AND},						//and
	{"[a-zA-z]|[a-zA-Z][a-zA-Z0-9_]+", OBJECT}	//object
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.s
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */
				
				switch(rules[i].token_type) {
					case NOTYPE:break;
					case '+':
						tokens[nr_token].type='+';
						nr_token++;
						break;
					case '-':
						if(nr_token==0||((tokens[nr_token-1].type!=NUMBER)&&(tokens[nr_token-1].type!=')')))
							tokens[nr_token].type=NEGANUM;
						else
							tokens[nr_token].type='-';
						nr_token++;
						break;
					case '*':
						if(nr_token==0||tokens[nr_token-1].type=='+'||tokens[nr_token-1].type=='-'||tokens[nr_token-1].type=='*'||tokens[nr_token-1].type=='/'||tokens[nr_token-1].type=='('||tokens[nr_token-1].type==NEGANUM||tokens[nr_token-1].type==NOT||tokens[nr_token-1].type==EQ||tokens[nr_token-1].type==AND||tokens[nr_token-1].type==OR||tokens[nr_token-1].type==DEREF||tokens[nr_token-1].type==NEQ){
						 tokens[nr_token].type=DEREF;
						 nr_token++;
						 break;
						}
						else{
							tokens[nr_token].type='*';
							nr_token++;
							break;
						}
					case '/':
						tokens[nr_token].type='/';
						nr_token++;
						break;
					case '(':
						tokens[nr_token].type='(';
						nr_token++;
						break;
					case ')':
						tokens[nr_token].type=')';
						nr_token++;
						break;
					case NUMBER:
						tokens[nr_token].type=NUMBER;
						strncpy(tokens[nr_token].str,substr_start,substr_len);
						tokens[nr_token].str[substr_len]='\0';
						nr_token++;
						break;
					case HEX:
						tokens[nr_token].type=HEX;
						strncpy(tokens[nr_token].str,substr_start,substr_len);
						tokens[nr_token].str[substr_len]='\0';
						nr_token++;
						break;
					case NOT:
						tokens[nr_token].type=NOT; 
						nr_token++; break;
					case OR: 
						tokens[nr_token].type=OR; 
						nr_token++; break;			
					case AND:
						tokens[nr_token].type=AND;
						nr_token++; break;
					case EAX:
						tokens[nr_token].type=EAX; 
						nr_token++; break;
					case ECX:
						tokens[nr_token].type=ECX; 
						nr_token++; break;
					case EDX:
						tokens[nr_token].type=EDX;
					   	nr_token++; break;
					case EBX:
						tokens[nr_token].type=EBX;
						nr_token++; break;
					case ESP:
						tokens[nr_token].type=ESP; 
						nr_token++; break;
					case EBP:
						tokens[nr_token].type=EBP; 
						nr_token++; break;
					case ESI:
						tokens[nr_token].type=ESI; 
						nr_token++; break;
					case EDI:
						tokens[nr_token].type=EDI; 
						nr_token++; break;
					case EIP:
						tokens[nr_token].type=EIP; 
						nr_token++; break;
					case EQ:
						tokens[nr_token].type=EQ; 
						nr_token++; break;
					case NEQ:
						tokens[nr_token].type=NEQ;
						nr_token++;break; 
					case OBJECT:
						tokens[nr_token].type=OBJECT;
						strncpy(tokens[nr_token].str,substr_start,substr_len);
						tokens[nr_token].str[substr_len]='\0';
						nr_token++;
						break;
					default: panic("please implement me");
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

bool check_parentheses(int p,int q){
	if(tokens[p].type!='('||tokens[q].type!=')')
		return false;
	else{
		int num_check=0;
		int temp;
		for(temp=p;temp<q-1;temp++)
		{	
			if(tokens[temp].type=='(')
				num_check++;
			if(tokens[temp].type==')')
				num_check--;
			if(num_check<1)
				return false;
		}
		return true;
	}
}

int dominant_op(int p,int q){
	int check;
	int op=p;         //temp dominant
	for(check=p;check<q;check++){
		if(tokens[check].type=='('){
			int i=check;
			while(1){
				if(check_parentheses(i,check))
					break;
				else
					check++;
			}
			continue;
		}
		else if(tokens[check].type==EQ||tokens[check].type==OR||tokens[check].type==AND||tokens[check].type==NEQ)
			op=check;
		else if(tokens[check].type=='+'||tokens[check].type=='-')
		{
			if(tokens[op].type!=EQ&&tokens[op].type!=OR&&tokens[op].type!=AND&&tokens[op].type!=NEQ)
				op=check;
		}
		else if(tokens[check].type=='*'||tokens[check].type=='/')
		{
			if(tokens[op].type=='*'||tokens[check].type=='/'||tokens[check].type==NEGANUM||op==p)
			op=check;
		}
		else continue;
	}
	return op;
}

uint32_t eval(int p,int q){
	if(p>q){
		printf("bad expression\n");
		return(-1);
	}
	else if(p==q){
		switch(tokens[p].type){
		case EAX:return cpu.eax;
		case ECX:return cpu.ecx;
		case EDX:return cpu.edx;
		case EBX:return cpu.ebx;
		case ESP:return cpu.esp;
		case EBP:return cpu.ebp;
		case ESI:return cpu.esi;
		case EDI:return cpu.edi;
		case EIP:return cpu.eip;
		case NUMBER:return atoi(tokens[p].str);break;
		case HEX:return strtol(tokens[p].str,NULL,16);
		case OBJECT:return find_obj(tokens[p].str);
		default:assert(0);
		}
	}
	else if(check_parentheses(p,q)==true){
		return eval(p+1,q-1);
	}
	else{
		int op=dominant_op(p,q);
		uint32_t val1=0,val2=0;			
		if(p!=op)
			val1=eval(p,op-1);
		val2=eval(op+1,q);
		switch(tokens[op].type){
			case EQ:return val1==val2;break;		
			case NEQ:return val1!=val2;break;
			case OR:return val1||val2;break;
			case AND:return val1&&val2;break;
			case '+':return val1+val2;break;
			case '-':return val1-val2;break;
			case '*':return val1*val2;break;
			case '/':return val1/val2;break;
			case NEGANUM:return -val2;break;
			case DEREF:return swaddr_read(val2,1,S_DS);break;
			case NOT:return !val2;break;
			default:assert(0);
			}
	}
}
uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}

	/* TODO: Insert codes to evaluate the expression. */

	return eval(0, nr_token-1);
}


