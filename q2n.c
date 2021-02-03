#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	struct node *left,*right,*p;
	int data;
};

struct tree{
	struct node* root;
};


struct queue{
	int *arr;
	int head,tail;
};

void enqueue(struct queue *Q,int node){
	Q->arr[Q->tail] = node;
	Q->tail += 1;
}

int dequeue(struct queue *Q){
	int temp;
	temp = Q->arr[Q->head];
	Q->head += 1;
	return temp;
}

int empty(struct queue *Q){
	if(Q->head == Q->tail){
		return -1;
	}
	return 1;
}

struct node* create_node(int data){
	struct node* newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->p = NULL;
	newnode->data = data;
	return newnode;
}

int find_matching_index(char *s,int start,int end){
    int level=0;
    for (int i=start;i<end;i++){
        if (s[i]=='('){
            level++;
        }
        if (s[i]==')'){
            level--;
        }
        if (level==0){
            return i;
        }
    }
    return -1;
}

int leveling(char *ch,int leveler){
	int level=0,count =0;
	for(int i=0;i<strlen(ch);i++){
		if(ch[i] == '('){
			level++;
		}
		else if(ch[i] == ')'){
			level--;
		}
		else if(leveler == level){
			if(count == 1){
			return i;
			}
			else{
				count = 1;
			}
		}
	}
}

struct node* create_tree(char *ch,int pos,int level){
	if(ch[pos] == '(' && ch[pos+1] == ')'){
		return NULL;
	}
	if(ch[pos] == '('){
		level++;
		create_tree(ch,pos+1,level);
	}
	else if(ch[pos] == ')'){
		level--;
		create_tree(ch,pos+1,level);
	}
	else{
		struct node* root;
		root = create_node(ch[pos] - '0');
		pos++;
		root->left = create_tree(ch,pos,level);
		if(root->left != NULL){
		(root->left)->p = root;
		}
		int temp = find_matching_index(ch,pos,strlen(ch));
		root->right = create_tree(ch,temp,strlen(ch));
		if(root->right != NULL){
			(root->right)->p = root;
		}
		return root;
	}
	
}

int find_level(struct node* root,int num,int level){
	if(root == NULL){
		return 0;
	}
	else if(root->data == num){
		return level;
	}
	else{
		int k = find_level(root->left,num,level+1);
		if(k == 0){
			return find_level(root->right,num,level+1);
		}
		else{
			return k;
		}
	}
}

void find_my_cousins(struct queue *Q,struct node* root,int level,int num){
	if(root == NULL){
		return;
	}
	if(level == 1){
		enqueue(Q,root->data);
	}
	else{
		find_my_cousins(Q,root->left,level-1,num);
		find_my_cousins(Q,root->right,level-1,num);
	}
}


void print(struct node* root){
	if(root == NULL){
		return;
	}
	print(root->left);
	printf("%d ",root->data);
	print(root->right);
}

int main(){
	struct tree *T;
	struct queue *Q;
	Q = (struct queue*)malloc(sizeof(struct queue));
	Q->arr =(int*)malloc(10*sizeof(int));
	Q->head = 0;
	Q->tail = 0;
	T =(struct tree*)malloc(sizeof(struct tree));
	T->root = NULL;
	char ch[50];
	scanf("%s",ch);
	T->root = create_tree(ch,0,0);
	int num;
	scanf("%d",&num);
	int level = find_level(T->root,num,0);
	find_my_cousins(Q,T->root,level,num);
	printf("I am here\n");
	while(empty(Q)){
		int temp = dequeue(Q);
		printf("%d ",temp);
		
	}
	printf("\n");
	return 0;
}
