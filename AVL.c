#include<stdio.h>
#include<stdlib.h>

struct node{
	struct node *right;
	struct node *left;
	int key;
	struct node* p;
};

struct AVL{
	struct node* root;
};

struct node* create_node(int data){
	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->p = NULL;
	newnode->key = data;
	return newnode;
};

int height(struct node* root){
	if(root == NULL)
		return 0;
	int h1 = 1 + height(root->left);
	int h2 = 1 + height(root->right);
	return h1 > h2? h1 : h2 ;	
}

int balance_factor(struct node* root){
	int ret =  height(root->left) - height(root->right);
	return ret;
}

void bst_insert(struct node* root,struct node* newnode){
	//printf("over here bro\n");
	if(root->key > newnode->key){
		if(root->left == NULL){
			root->left = newnode;
			newnode->p = root;
			return;
		}
		else{
			bst_insert(root->left,newnode);
			return;
		}
	}
	else{
		if(root->right == NULL){
			root->right = newnode;
			newnode->p = root;
			return;
		}
		else{
			bst_insert(root->right,newnode);
			return;
		}
	}
}

struct node* minimum(struct node *root){
       while(root->left != NULL)
              root = root->left;
       return root;       
}

struct node* succesor(struct node **root){
     struct node *pi = *root;
     if(pi == NULL){
     	return NULL;
     }
     if(pi->right != NULL)
               return minimum(pi->right);
     struct node *q = pi->p;
     while(q != NULL && pi == q->right){
               pi = q;
               q = q->p;
     }
     return q;       
                      
}



void print_tree(struct node *root){
	if(root == NULL){
		printf("( )");
		return;
	}
	printf("( ");
	printf("%d ",root->key);
	print_tree(root->left);
	printf(" ");
	print_tree(root->right);
	printf(" )");
}

struct node* delete(struct node* root,int data){
	if(root == NULL)
		return NULL;
	else if(root->key > data){
		root->left = delete(root->left,data);
	}	
	else if(root->key < data){
		root->right = delete(root->right,data);
	}
	else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
		}
		else if(root->left == NULL || root->right == NULL){
			struct node* temp = root->left?root->left:root->right;
			free(root);
			root = temp;
		}
		else{
			struct node* temp = minimum(root->right);
			root->key = root->key;
			root->right = delete(root->right,root->key);
		}
	}
	if(root == NULL){
		return NULL;
	}
		int bf = balance_factor(root);
	if(bf > 1 && data < root->left->key)
		return rightrotate(root);
	else if(bf < -1 && data > root->right->key)
		return leftrotate(root);
	else if(bf > 1 && data > root->left->key){
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}
	else if(bf < -1 && data < root->right->key){
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	return root;

}

struct node* leftrotate(struct node* root){
	struct node* temp1 = root->right;
	struct node* temp2 = temp1->left;
	temp1->left = root;
	root->right = temp2;
	return temp1;
}

struct node* rightrotate(struct node* root){
	struct node* temp1 = root->left;
	struct node* temp2 = temp1->right;
	temp1->right = root;
	root->left = temp2;
	return temp1;
}

struct node* insert(struct node* root,int data){
	if(root == NULL)
		return create_node(data);
	if(root->key > data)
		root->left = insert(root->left,data);
	else if(root->key < data)
		root->right = insert(root->right,data);
	else
		return root;
	int bf = balance_factor(root);
	if(bf > 1 && data < root->left->key)
		return rightrotate(root);
	else if(bf < -1 && data > root->right->key)
		return leftrotate(root);
	else if(bf > 1 && data > root->left->key){
		root->left = leftrotate(root->left);
		return rightrotate(root);
	}
	else if(bf < -1 && data < root->right->key){
		root->right = rightrotate(root->right);
		return leftrotate(root);
	}
	return root;
							
}



struct node* search(struct node* root,int data){
	if(root == NULL)
		return NULL;
	if(root->key == data)
		return root;
	else if(root->key > data)
		search(root->left,data);
	else if(root->key < data)
		search(root->right,data);		
}




int main(){
	struct AVL *T;
	T = (struct AVL*)malloc(sizeof(struct AVL));
	T->root = NULL;
	char ch;
	int key;
	struct node *temp;
	while(1){
		scanf("%c",&ch);
		switch(ch){
			case 'i':
				scanf("%d",&key);
				T->root = insert(T->root,key);
				break;
		    case 's':
		    	scanf("%d",&key);
		    	temp = search(T->root,key);
		    	if(temp)
		    		printf("TRUE\n");
		    	else
		    		printf("FALSE\n");
		    	break;
		    case 'p':
		    	print_tree(T->root);
		    	break;
		    case 'b':
		    	scanf("%d",&key);
		    	temp = search(T->root,key);
		    	if(temp)
		    		printf("%d\n",balance_factor(temp));
		    	else
		    		printf("FALSE\n");
		    	break;
		    case 'd':
		    	scanf("%d",&key);
		    	temp = search(T->root,key);
		    	DELETE(T,key);
		    	if(temp)
		    		printf("%d\n",key);
		    	
		        else
		    		printf("FALSE\n");
		    		break;
		    	

		    case 'e':
		    	exit(1);				
		    							
		}
	}
	return 0;
}
