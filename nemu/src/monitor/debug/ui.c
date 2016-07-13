#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

WP* new_wp();
void free_wp(WP *wp);
void print_point();
extern int find_funaddr(int my_addr);
extern char* find_funname(int my_addr);
typedef struct{
	swaddr_t prev_ebp;
	swaddr_t ret_addr;
	uint32_t args[4];
}PartOfStackFrame;

void cpu_exec(uint32_t);
uint32_t swaddr_read(swaddr_t,size_t,uint8_t);
/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args);

static int cmd_info(char *args);

static int cmd_x(char *args);

static int cmd_w(char *args);

static int cmd_d(char *args);

static int cmd_p(char *args);

static int cmd_bt(char *args);

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },

	/* TODO: Add more commands */
	{"si","execute the program in n steps",cmd_si},
	{"info","print the state of computer when program is running",cmd_info},
	{"x","scanning memory",cmd_x},
	{"w","set a watchpoint",cmd_w},
	{"d","delete a watchpoint",cmd_d},
	{ "p"," calculate expr", cmd_p},
	{"bt","print the chain of stack frame",cmd_bt}
};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}
static int cmd_si(char *args){
	char *arg=args;
	if(arg==NULL)
		printf("you should input the num of the commands that need to be excute\n");
 	else
	{
		int my_len=strlen(arg);
		volatile uint32_t num=0;
		int j;
		for (j=0;j<my_len;j++)
		{
			if(arg[j]>'9'||arg[j]<'0'){
				printf("you should input a number");
				return 0;
			}
			if(j==0)
				num+=arg[j]-'0';
			else{
				num*=10;
				num+=arg[j]-'0';
			}
		}
		cpu_exec(num);
	}
	return 0;
}
static int cmd_info(char *args){
	char* arg=strtok(NULL,"");
	if((arg==NULL)||(strlen(arg)>1)){
		printf("you should input r for register,w for watchpoint\n");
		}
	else {
		if(arg[0]=='r'){
			printf("eax:0x%x\n",cpu.eax);
			printf("ecx:0x%x\n",cpu.ecx);
			printf("edx:0x%x\n",cpu.edx);
			printf("ebx:0x%x\n",cpu.ebx);
			printf("esp:0x%x\n",cpu.esp);
			printf("ebp:0x%x\n",cpu.ebp);
			printf("esi:0x%x\n",cpu.esi);
			printf("edi:0x%x\n",cpu.edi);
			printf("eip:0x%x\n",cpu.eip);
		}
		else if(arg[0]=='w'){
			print_point();
		}
		else if(arg[0]=='f'){
			printf("cf:%x\n",cpu.CF);
			printf("of:%x\n",cpu.OF);
			printf("sf:%x\n",cpu.SF);
			printf("zf:%x\n",cpu.ZF);
			printf("if:%x\n",cpu.IF);
		}
		else
			printf("wrong args\n");
	}
	return 0;
}
static int cmd_x(char *args){
	char* arg_num=strtok(args," ");
	char* arg_addr=strtok(NULL," ");
	printf("%s\n%s\n",arg_num,arg_addr);
	if(arg_num==NULL)
		printf("wrong num\n");
	else{
		uint32_t my_num=0,my_addr=0;
		bool* my_test=(bool*)malloc(sizeof(bool));
		my_test=false;
		my_num=expr(arg_num,my_test);
		printf("my_num=%d",my_num);
		if(arg_addr==NULL)
			printf("wrong adder");
		else{
			my_test=false;
			my_addr=expr(arg_addr,my_test);
			printf("my_addr=%d\n",my_addr);
			free(my_test);
		}
		int temp;
		for(temp=0;temp<my_num;temp++)
			printf("0x%x\n",swaddr_read(my_addr+temp*4,4,S_DS));
	}	
	return 0;
}

static int cmd_w(char* args){
	char* arg=args;
	new_wp(arg);
	return 0;
}

static int cmd_d(char* args){
	char* arg=args;
	if(arg==NULL){
		printf("please enter the address!\n");
		return 0;
	}
	WP* my_NO=(WP*)atoi(arg);
	free_wp(my_NO);
	return 0;
}
static int cmd_p(char* args){
	char* arg=args;
	bool* my_test=(bool*)malloc(sizeof(bool));
	my_test=false;
	uint32_t i=expr(arg,my_test);
	printf("num is %8x\n",i);
	free(my_test);
	return 0;
}

static int cmd_bt(char* args){
	PartOfStackFrame my_stackframe;
	my_stackframe.prev_ebp=cpu.ebp;
	my_stackframe.ret_addr=cpu.eip;
	printf("Address\tName\tparameter1\tparameter2\tparameter3\tparameter4\n");
	while(my_stackframe.prev_ebp!=0){
		printf("0x%x\t%s\t",find_funaddr(my_stackframe.ret_addr),find_funname(my_stackframe.ret_addr));
		my_stackframe.args[0]=swaddr_read(my_stackframe.prev_ebp+8,4,S_SS);
		my_stackframe.args[1]=swaddr_read(my_stackframe.prev_ebp+12,4,S_SS);
		my_stackframe.args[2]=swaddr_read(my_stackframe.prev_ebp+16,4,S_SS);
		my_stackframe.args[3]=swaddr_read(my_stackframe.prev_ebp+20,4,S_SS);
		printf("%d\t%d\t%d\t%d\n",my_stackframe.args[0],my_stackframe.args[1],my_stackframe.args[2],my_stackframe.args[3]);	
		my_stackframe.ret_addr=swaddr_read(my_stackframe.prev_ebp+4,4,S_SS);
		my_stackframe.prev_ebp=swaddr_read(my_stackframe.prev_ebp,4,S_SS);
	}
	return 0;
}	
	
	
void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
