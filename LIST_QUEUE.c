#include<stdio.h>
#include<stdlib.h>

struct node{

   int data;
   
   struct node* next;

};

struct Queue{

    struct node *head;

};

struct node* create_node(int key){

     struct node *newnode;
     
     newnode = (struct node*)malloc(sizeof(struct node));
     
     newnode->next = NULL;
     
     newnode->data = key;
     
     return newnode;

}

void Enqueue(struct Queue *Q,struct node *newnode){

     newnode->next = Q->head;
     
     Q->head = newnode;


}

void Dequeue(struct Queue *Q){

     if(Q->head == NULL){
     
           printf("-1\n");
           
           return;
     
     }
     
     

     struct node *p,*q;
     
     p = Q->head;
     
     q = p;
     
     if(p->next == NULL){
     
          printf("%d\n",p->data);
     
          free(p);
          
          Q->head = NULL;
          
          return;
     
     }
     
     while(p->next){
     
     q = p;
     
     p = p->next;
     
     }
     
     q->next = NULL;
     
     printf("%d\n",p->data);
     
     free(p);
     
}

void Queue_empty(struct Queue *Q){

     if(Q->head){
     
           printf("1\n");
          
           return;
     
     }
     
     else{
     
            printf("-1\n");
            
            return;
     
     }
     

}

int main(){

    struct Queue Q;
    
    Q.head = NULL;
    
    int key;
    
    char choice;
    
    while(1){
    
         scanf("%c",&choice);
         
         switch(choice){
         
              case 'i':
              
                    scanf("%d",&key);
                    
                    Enqueue(&Q,create_node(key));
                    
                    break;
                    
              case 'd':
              
                    Dequeue(&Q);
                    
                    break;  
                    
              case 'e':
              
                    Queue_empty(&Q);   
                    
                    break;
                    
              case 't':
              
                    exit(1);               
                 
         
         }
       
    }
    
    return 0;   

}
