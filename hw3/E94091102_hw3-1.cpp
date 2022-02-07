#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;
//construct the binary tree
queue<int> myqueue;
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
void preorder(Node* node){
	if(node != NULL){
		cout<<node->data<<" ";
		myqueue.push(node->data);
		preorder(node->left);
		preorder(node->right);
	}
}
void postorder(Node* node){
	if(node!=NULL){
		postorder(node->left);
		postorder(node->right);
		cout<<node->data<<" ";
		myqueue.push(node->data);
	}
}
int search(int arr[], int strt, int end, int value)
{
    int i;
    for (i = strt; i <= end; i++)
    {
        if (arr[i] == value)
            return i;
    }
}
Node* buildTree_preorder_inorder(int in[], int pre[], int inStrt, int inEnd)
{
    static int preIndex = 0;
 
    if (inStrt > inEnd)
        return NULL;
 
    Node* tNode = newNode(pre[preIndex++]);
 
    /* If this node has no children then return */
    if (inStrt == inEnd)
        return tNode;
 
    /* Else find the index of this node in Inorder traversal */
    int inIndex = search(in, inStrt, inEnd, tNode->data);
 
    /* Using index in Inorder traversal, construct left and
    right subtress */
    tNode->left = buildTree_preorder_inorder(in, pre, inStrt, inIndex - 1);
    tNode->right = buildTree_preorder_inorder(in, pre, inIndex + 1, inEnd);
 
    return tNode;
}

Node* buildUtil(int in[], int post[], int inStrt, int inEnd, int* pIndex)
{
    // Base case
    if (inStrt > inEnd)
        return NULL;
 
    /* Pick current node from Postorder traversal using
       postIndex and decrement postIndex */
    Node* node = newNode(post[*pIndex]);
    (*pIndex)--;
 
    /* If this node has no children then return */
    if (inStrt == inEnd)
        return node;
 
    /* Else find the index of this node in Inorder
       traversal */
    int iIndex = search(in, inStrt, inEnd, node->data);
 
    /* Using index in Inorder traversal, construct left and
       right subtress */
    node->right = buildUtil(in, post, iIndex + 1, inEnd, pIndex);
    node->left = buildUtil(in, post, inStrt, iIndex - 1, pIndex);
 
    return node;
}
Node* buildTree(int in[], int post[], int n)
{
    int pIndex = n - 1;
    return buildUtil(in, post, 0, n - 1, &pIndex);
}


int main(){
	int order;
	while(true){
		cout<<"if you want to build binary tree. Enter 1"<<endl;
		cout<<"exit. Enter 2"<<endl;
		cin>>order;
		if (order == 2){
			break;
		}
		else{
			char input_filename[20];// only accept filename not over 20 character
			char output_filename[20];// only accept filename not over 20 character
    		string line;
			cout<<"Please type the input filename: ";
			cin>>input_filename;
			cout<<"output filename: ";
			for(int i = 0; i < 20; i++){
				
				if(i ==0){
					output_filename[i] = 'o';
				}
				else if (i == 1){
					output_filename[i] = 'u';
				}
				else if (i == 2){
					output_filename[i] = 't';
				}
				else{
					output_filename[i] = input_filename[i-1];
				}
				cout<<output_filename[i];
			}
			cout<<endl;
			ifstream input_file(input_filename);
			if (!input_file.is_open()) {
  		  		cout << "Could not open the file :'"<< input_filename << "'" << endl;
  			}
  			ofstream ofs;
   			ofs.open(output_filename);
   			if (!ofs.is_open()) {
       		 cout << "Failed to open file.\n";
    		}
    		getline(input_file, line);
    		int m , n;
			istringstream ( line ) >> m;
			cout << m << endl;
			while(m > 0){
				getline(input_file, line);
				if (line.compare("preorder-inorder") == 0){
					cout << "preorder-inorder" << endl;
					getline(input_file, line);
					istringstream ( line ) >> n;
					cout <<"nodes: "<< n << endl;
					int preorder_array[n];
					int inorder_array[n];
					int k, i = 0;
					getline(input_file, line);
					cout<< line << endl;
					istringstream preorder(line);
    				string number;
					while(getline(preorder, number, ' ')) {
      					istringstream ( number ) >> k;
      					preorder_array[i] = k;
      					i++;
					}
					i = 0;
					getline(input_file, line);
					cout<< line << endl;
					istringstream inorder(line);
					while(getline(inorder, number, ' ')) {
      					istringstream ( number ) >> k;
      					inorder_array[i] = k;
      					i++;
					}
					Node *root = buildTree_preorder_inorder(inorder_array, preorder_array, 0, n-1);
					cout << "postorder sequence of the reconstructed binary tree" << endl;
					postorder(root);
					cout<<endl;
					while(!myqueue.empty()){
						ofs <<myqueue.front()<<" ";
						myqueue.pop();
					}
					ofs<<"\n";
					cout<<endl;
					m--;
				}
				else if(line.compare("postorder-inorder") == 0){
					cout << "postorder-inorder" << endl;
					getline(input_file, line);
					istringstream ( line ) >> n;
					cout <<"nodes: "<< n << endl;
					int postorder_array[n];
					int inorder_array[n];
					int k, i = 0;
					getline(input_file, line);
					cout<< line << endl;
					istringstream postorder(line);
    				string number;
					while(getline(postorder, number, ' ')) {
      					istringstream ( number ) >> k;
      					postorder_array[i] = k;
      					i++;
					}
					i = 0;
					getline(input_file, line);
					cout<< line << endl;
					istringstream inorder(line);
					while(getline(inorder, number, ' ')) {
      					istringstream ( number ) >> k;
      					inorder_array[i] = k;
      					i++;
					}
					Node* root = buildTree(inorder_array, postorder_array, n);
					cout << "preorder sequence of the reconstructed binary tree" << endl;
					preorder(root);
					cout << endl;
					while(!myqueue.empty()){
						ofs <<myqueue.front()<<" ";
						myqueue.pop();
					}
					ofs<<"\n";
					m--;
				}
			}
			ofs.close();
   			input_file.close();
				}
			}
    return 0;
}

