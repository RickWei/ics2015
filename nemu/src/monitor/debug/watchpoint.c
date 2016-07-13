#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_list[NR_WP];
static WP *head, *free_;

void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_list[i].NO = i;
		wp_list[i].next = &wp_list[i + 1];		
		wp_list[i].USE=0;
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp(char* my_expr){
	if(free_){
		WP *p=free_;
		free_=free_->next;
		WP *temph=head;
		if(temph==NULL){
			head=p;
			p->next=NULL;
			p->USE=1;
			strcpy(p->expr,my_expr);
			bool* my_test=(bool*)malloc(sizeof(bool));
			my_test=false;
			p->value=expr(p->expr,my_test);
		}		
		else{
			WP* q=head;
			while(q->next)
				q=q->next;
			q->next=p;
			p->next=NULL;
			p->USE=1;
			strcpy(p->expr,my_expr);
			bool* my_test=(bool*)malloc(sizeof(bool));		
			my_test=false;
			p->value=expr(p->expr,my_test);
		}
		printf("succeed to set a watchpoint\n");
	}
	else{
		printf("no free watchpoint!\n");
		assert(0);	
	}
	return 0;
}

void free_wp(int my_NO){
	if(head){
		WP* p=head;
		if(p->NO==my_NO){
			head=p->next;
			p->USE=0;
			p->next=free_;
			free_=p;
		}
		else{
			while(p->next->NO!=my_NO){
				if(p->NO!=my_NO&&p->next==NULL){
					printf("the NO%d is not existed\n",my_NO);
					assert(0);
				}
				p=p->next;
			}
			WP* current=p->next;
			p->next=current->next;
			current->USE=0;
			current->next=free_;
			free_=current;
		}
		printf("succeed to delete\n");
	}
		else{
			printf("no free watchpoint!\n");		
		}
		assert(0);
	return;
}

void print_point(){
	if(head==NULL)
	{
		printf("no watchpoint\n");
	};
	WP* p=head;
	printf("NO\tvalue\taddress\t\n");
	while(p){		
		printf("%d\t%d\t%s\t\n",p->NO,p->value,p->expr);
		p=p->next;
	}
	return;
}
