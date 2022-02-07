#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
using namespace std;
struct Node{
	int data;
	struct Node* left;
	struct Node* right;
};
Node* newNode(int val){
	Node *temp = new Node();
	temp->data = val;
	temp->right = NULL;
	temp->left = NULL;
	return temp;
}
Node* insert(Node* root, int val){
	if(root == NULL){
		root = newNode(val); 
	}
	else if(val < root->data)
		root->left = insert(root->left,val);
	else
		root->right = insert(root->right,val);
	return root;	
}
void display(Node* root){
	//cout<<"Displaying the tree elements\n";
	if(root!=NULL){
		display(root->left);
		cout<<root->data<<" -> ";
		display(root->right);
	}
}
void preorder(Node* node){
	if(node != NULL){
		cout<<node->data<<" ";
		preorder(node->left);
		preorder(node->right);
	}
}
void postorder(Node* node){
	if(node!=NULL){
		postorder(node->left);
		postorder(node->right);
		cout<<node->data<<" ";
	}
}
void inorder(Node* node){
	if(node!=NULL){
		postorder(node->left);
		cout<<node->data<<" ";
		postorder(node->right);
	}
}
void levelorder(Node* node){
	if(node == NULL)
		return;
	queue<Node*> myqueue;
	myqueue.push(node);
	while(!myqueue.empty()){
		Node* frontNode = myqueue.front();
		cout<<frontNode->data<<" ->";
		if(frontNode->left != NULL)
			myqueue.push(frontNode->left);
		if(frontNode->right != NULL)
			myqueue.push(frontNode->right);
		myqueue.pop();
	}
}
bool search(Node* root,int item){
	if(root==NULL)
		return false;
	if(item == root->data){
			return true;
	}
	else if(item < root->data){
		search(root->left,item);		
	}
	else if(item > root->data){
		search(root->right,item);
	}
	else
	return false;
}
int main(){
	struct ListNode* head = NULL;
	int number;
	Node *root = NULL;
	char action;
	while(true){
		cout<<"(I)nsert a number."<<endl;
		cout<<"(D)elete a number."<<endl;
		cout<<"(S)earch a number."<<endl;
		cout<<"(P)int 4 kinds of orders."<<endl;
		cout<<"(R)eturn"<<endl;
		cin>>action;
		if (action == 'i'){
			cout<<"Enter numbers: ";
			while(true){
				cin>>number;
				if(number == -1){
					break;
				}
				else if (search(root, number)){
					cout<<"Error. Number "<<number<<" exists."<<endl;
				}
				else{
					root = insert(root, number);
					cout<<"Number "<<number<<" is inserted."<<endl;
				}
			}
		}
	}
	return 0;
}
