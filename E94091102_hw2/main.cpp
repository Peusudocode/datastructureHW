#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <bits/stdc++.h>
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
Node* minValueNode(Node * node)
{
    Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
Node* findMaximum(Node * node){
	if(node == NULL)
		return node;
	if(node->right == NULL){
			return node;
	}
	else
		return findMaximum(node->right);
}
Node* deleteNode(Node* root, int val){
	if (root == NULL)
        return root;
    // If the val to be deleted is smaller than the root's val, then it lies in left subtree
    else if (val < root->data)
        root->left = deleteNode(root->left, val);
    // If the val to be deleted is greater than the root's val, then it lies in right subtree
    else if (val > root->data)
        root->right = deleteNode(root->right, val);
    // if val is same as root's val, then This is the node to be deleted
    else {
        // node has no child
        if (root->left==NULL and root->right==NULL)
            return NULL;
       
        // node with only one child or no child
        else if (root->left == NULL) {
            Node* temp = root->right;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            return temp;
        }
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        Node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->data = temp->data;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
void display(Node* root){
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
		inorder(node->left);
		cout<<node->data<<" ";
		inorder(node->right);
	}
}
void levelorder(Node* node){
	if(node == NULL)
		return;
	queue<Node*> myqueue;
	myqueue.push(node);
	while(!myqueue.empty()){
		Node* frontNode = myqueue.front();
		cout<<frontNode->data<<" ";
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
bool findpath(Node* root, stack<int>& path, int key){
	if (root == NULL) {
        return false;
    }
    path.push(root->data);
   	if (root->data == key)   
        return true;
    if (findpath(root->left, path, key) || findpath(root->right, path, key))
        return true;
    path.pop();
    return false;
}
void printpath(Node* root, int key){
	stack<int> path;
	stack<int> reverse_path;
	if (findpath(root, path, key))
    {
    	while(!path.empty()){
        	reverse_path.push(path.top());
        	path.pop();
		}
        while(!reverse_path.empty()){
        	cout<<reverse_path.top()<<"->";
        	reverse_path.pop();
		}
    }
    else
        cout << "No Path";
}
// Function to find the path between two nodes in binary tree
void pathBetweenNode(Node *root, int v1, int v2) {
  	stack<int> path1;
 	stack<int> path2;
  	vector<int> path1_vector;
  	vector<int> path2_vector;
  	findpath(root, path1, v1);
  	findpath(root, path2, v2);
  	path1.pop();
  	while(!path1.empty()){
  		path1_vector.push_back(path1.top());
  		path1.pop();
  	}
  	while(!path2.empty()){
  		path2_vector.push_back(path2.top());
  		path2.pop();
  	}
  	int i_intersection = path1_vector.size() - 1;
  	int j_intersection = path2_vector.size() - 1;
  	while(path1_vector[i_intersection] == path2_vector[j_intersection]){
  		i_intersection--;
  		j_intersection--;
	}
    for (int i = 0; i <= i_intersection + 1; i++)
        cout << path1_vector[i] <<"->";
    for (int i = j_intersection; i >0; i--)
        cout << path2_vector[i] <<"->";
    cout<<path2_vector[0]<<endl;
}

int main(){
	int number;
	char action;
	while(true){
		cout<<"(1)Binary searching Tree."<<endl;
		cout<<"(2)Finding Meaty."<<endl;
		cout<<"(0)Escape and face to music next year."<<endl;
		cin>>action;
		if(action == '1'){
			Node *root = NULL;
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
				else if(action == 'd'){
					cout<<"Enter numbers to deleted: ";
					while(true){
						cin>>number;
						if(number == -1){
							break;
						}
						else if (!search(root, number)){
							cout<<"Number "<<number<<" is not exist."<<endl;
						}
						else{
							root = deleteNode(root, number);
							cout<<"Number "<<number<<" is deleted."<<endl;
						}
					}
				}
				else if (action == 's'){
					cout<<"Enter elements to searching: ";
					while(true){
						cin>>number;
						if(number == -1){
							break;
						}
						else if (!search(root, number)){
							cout<<"SORRY.  "<<number<<" is not found."<<endl;
						}
						else{
							cout<<"Bingo! "<<number<<" is found."<<endl;
						}
					}
				}
				else if (action == 'p'){
					cout<<"The tree in prefix order : ";
					preorder(root);
					cout<<endl;
					cout<<"The tree in infix order : ";
					inorder(root);
					cout<<endl;
					cout<<"The tree in post order : ";
					postorder(root);
					cout<<endl;
					cout<<"The tree in level order : ";
					levelorder(root);
					cout<<endl;
				}
				else if (action == 'r'){
					break;
				}
			}
		}	
		else if(action == '2'){
			Node *bst = NULL;
			int sword, Meaty, broccoli;
			stack<int> path;
			char file_name[10]; // only accept filename not over 10 character
			cout<<"Please input the map file: ";
			cin>>file_name;
			ifstream bst_file(file_name);
			if (!bst_file.is_open()) {
        		cout << "Could not open the file - '"<< file_name << "'" << endl;
    		}
			while (bst_file >> number) {
       		 	bst = insert(bst, number);
   			}
   			cout<<"Load file sucess."<<endl;
   			cout<<"\n";
   			cout<<"Please input the sword location: ";
   			cin>>sword;
   			cout<<"Please input the Meaty's location: ";
   			cin>>Meaty;
   			cout<<"Please input the broccoli traps' index (0~9): ";
   			cin>>broccoli;
   			Node *max = findMaximum(bst);
   			cout<<endl;
   			int first_broccoli = broccoli;
   			while(broccoli <= max->data){
   				if(search(bst, broccoli)){
   					bst = deleteNode(bst, broccoli);
   					cout<<"Number "<<broccoli<<" is deleted"<<endl;
				}
				broccoli += 10;
				if (broccoli != 0 && broccoli > first_broccoli*10){
					if(search(bst, first_broccoli)){
   					bst = deleteNode(bst, first_broccoli);
   					cout<<"Number "<<broccoli<<" is deleted"<<endl;
					}
					first_broccoli *= 10;
				}
			}
			cout<<endl;
			cout<<"Capoo successfully found his favorite meaty<3."<<endl;
			cout<<endl;
			cout<<"shortest path to find the meaty :"<<endl;
			printpath(bst, sword);
			pathBetweenNode(bst, sword, Meaty);
			cout<<endl;	
		}
		else if(action == '0'){
			break;
		}
	}
	return 0;
}
