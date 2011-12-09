#include "calc3.h"

void push_type(int t){
	struct type_stack * new = (struct type_stack *)malloc(sizeof(struct type_stack));

	//fprintf(stderr,"Pushing type %d\n", t);

	new->type = t;
	if( top_of_stack == NULL ){
		top_of_stack = new;
	}else{
		new->previous = top_of_stack;
		top_of_stack = new;
	}
}

int pop_type(){
	if( top_of_stack == NULL ){
		printf("Stack error\n");
		exit(1);
	}

	struct type_stack * new_top = top_of_stack->previous;
	int ret = top_of_stack->type;
	free(top_of_stack);
	top_of_stack = new_top;

	//fprintf(stderr,"Popping type %d\n", ret);
	
	return ret;
}

void printTypeStack(){
	struct type_stack * current = top_of_stack;
	while(current != NULL){
		printf("\t%d\n",current->type);
		current = current->previous;
	}
}
