#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;

};
struct stack{
     struct node *head;

};

int stack_empty(struct stack *h){
       return h->head == NULL ? -1 : 1;

}

struct node* createnode(int k){
      struct node *p;
      p =(struct node*)malloc(sizeof(struct node));
      p->data = k;
      p->next = NULL;
      return p;
}

void stack_push(struct stack *S,struct node *newnode){
      if(S->head == NULL){
           S->head = newnode;
           return;
      }
      newnode->next = S->head;
      S->head = newnode;
      return;     

}

void stack_pop(struct stack *S){
       if(stack_empty(S) == -1){
            printf("-1\n");
            return;
       }     
       struct node *p;
       p = S->head;
       S->head = p->next;
       printf("%d\n",p->data);
       free(p);     

}

int main(){
    int key;
    struct stack S;
    S.head = NULL;
    char choice;
    while(1){
        scanf("%c",&choice);
        switch(choice){
           case 'i':
                scanf("%d",&key);
                stack_push(&S,createnode(key));
                break;
           case 'd':
                 stack_pop(&S);
                 break;
           case 'e':
                 printf("%d\n",stack_empty(&S));
                 break;
           case 't':
                 exit(1);                 
        
        
        }
        
    
    }
    
    return 0;
}
