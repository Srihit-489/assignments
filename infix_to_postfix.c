#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stack{
        int *arr;
        int size;
        int top;

};

void stack_push(struct stack *s,char n){
        s->arr[++s->top] = n;
}

char stack_pop(struct stack *s){
        int pop = s->arr[s->top];
        s->top = s->top - 1;
        return pop;
}

int operand(char ch){
   
    return (ch >= 'a' && ch <= 'z') ||  
           (ch >= 'A' && ch <= 'Z'); 
}

int precedence(char ch){
    switch(ch){
    case '+':
         return 1;
    case '-':
         return 1;
    case '*':
         return 2;
    case '/':
         return 2;
    case '^':
         return 3;
    default :
         return -1;                         
    }
}

char peak(struct stack *s){
     return s->arr[s->top];
}

void INFIXTOPOSTFIX(char* string){
    char ch[20],gar;
    int i,k=-1;
    struct stack *stack;
    stack = (struct stack*)malloc(sizeof(struct stack));
    stack->size = 20;
    stack->arr = (int*)malloc(stack->size*sizeof(int));
    stack->top = -1;
    for(i=0;i<strlen(string);i++){
         if(operand(string[i]))
                 ch[++k] = string[i];
         else if(string[i] == '('){
                 stack_push(stack,string[i]);
         }
         else if(string[i] == ')'){
                 while(stack->top != -1 && peak(stack) != '('){
                           ch[++k] = stack_pop(stack);
                 }
                 gar = stack_pop(stack);
         }  
         else{
                  
                  while(stack->top != -1 && precedence(string[i])<=precedence(peak(stack))){
                           if(peak(stack) == '(')
                           break;
                           ch[++k] = stack_pop(stack);
                  }
                   stack_push(stack,string[i]);
                
         }       
       
    }
    while(stack->top != -1){
        if(stack->arr[stack->top] == '(')
                    gar = stack_pop(stack);
        else
          ch[++k] = stack_pop(stack);
    }
    ch[++k] = '\0';
    printf("%s\n",ch);
}

int main(){
   char string[20];
   scanf("%s",string);
   INFIXTOPOSTFIX(string);
   return 0;
}
