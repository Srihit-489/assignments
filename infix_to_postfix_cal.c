#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack{
        int *arr;
        int size;
        int top;

};

void stack_push(struct stack *s,int n){
        s->arr[++(s->top)] = n;
}

int stack_pop(struct stack *s){
        int pop = s->arr[s->top];
        s->top = s->top - 1;
        return pop;
}

int operand(char ch){
   
    return (ch >= '0' && ch <= '9');  
         
}


int POSTFIX_EVALUATION(char *string){
     char ch[100];
     struct stack *stack;
     stack = (struct stack*)malloc(sizeof(struct stack));
     stack->top = -1;
     stack->size = 100;
     stack->arr =(int*)malloc(stack->size*sizeof(int));
     int i,op1,op2;
     for(i=0;i<string[i] != '\0';i++){
              
              if(string[i] == ' ')
                  continue;
                  
              else if(operand(string[i]))
              {
                   int num = 0;
                   while(operand(string[i])){
                      
                       num = num*10 + (int)string[i]-'0';
                       
                       i++;
                   }
                   
                   stack_push(stack,num);
              }
                    
              else{
                      op1 = stack_pop(stack);
                      op2 = stack_pop(stack);
                     
              
                   switch(string[i]){
                         case '+':
                                  stack_push(stack,op1+op2);
                                  break;
                         case '-':
                                  stack_push(stack,op2-op1);
                                  break;
                         case '*':
                                  stack_push(stack,op1*op2);
                                  break;
                         case '/':
                                  stack_push(stack,op2/op1);
                                  break;                           
                   }
              }      
     }
     return stack->arr[stack->top];
}


int main(){
   char string[100];
   scanf("%[^\n]s",string);
   printf("%d\n",POSTFIX_EVALUATION(string));
   return 0;
}
