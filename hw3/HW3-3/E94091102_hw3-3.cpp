#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;
// Breadth-First Search (BFS)
vector<vector<int> > adj;
queue<int> myqueue;
void addEdge(int x, int y)
{
    adj[x][y] = 1;
}
void bfs(int start)
{
    // Visited vector to so that
    // a vertex is not visited more than once
    // Initializing the vector to false as no
    // vertex is visited at the beginning
    vector<bool> visited(adj.size(), false);
    vector<int> q;
    q.push_back(start);
  
    // Set source as visited
    visited[start] = true;
  
    int vis;
    while (!q.empty()) {
        vis = q[0];
  
        // Print the current node
        cout << vis << " ";
        myqueue.push(vis);
        q.erase(q.begin());
  
        // For every adjacent vertex to the current vertex
        for (int i = 0; i < adj[vis].size(); i++) {
            if (adj[vis][i] == 1 && (!visited[i])) {
  
                // Push the adjacent node to the queue
                q.push_back(i);
  
                // Set
                visited[i] = true;
            }
        }
    }
}


int main(){
	int order;
	while(true){
		cout<<"if you want to do Breadth-First Search (BFS). Enter 1"<<endl;
		cout<<"exit. Enter 2"<<endl;
		cin>>order;
		if (order == 2){
			break;
		}
		else{
			char input_filename[20] = {};// only accept filename not over 20 character
			char output_filename[20] = {};// only accept filename not over 20 character
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
    		int n , m, t, i = 0;
			istringstream ( line ) >> n;
			cout << "n:" << n << endl;
			while(n > 0){
				getline(input_file, line);
				istringstream m_and_t(line);
    			string number;
				while(getline(m_and_t, number, ' ')) {
					if(i == 0){
						istringstream ( number ) >> m;
					}
      				else if(i == 1){
      					istringstream ( number ) >> t;
					}
					i++;
				}
				cout << "m: " << m << " t: " << t <<endl;
				int v = m;
				i=0;
				adj = vector<vector<int> >(v, vector<int>(v, t));
				int s=0, e=0;
				while(s < m){
					getline(input_file, line);
					cout << line <<endl;
					istringstream edge(line);
					int j = 0;
					int k = 0;
					while(getline(edge, number, ' ')) {
						istringstream ( number ) >> k;
						if(k == 1){
							addEdge(s, j);
							cout << "addEdge:" << s << "," << j << " ";
						}
						j++;
					}
					cout<<endl;
					s++;
				}
				cout<< "Breadth-First Search:" << endl;
				bfs(t);
				while(!myqueue.empty()){
						ofs <<myqueue.front()<<" ";
						myqueue.pop();
					}
				ofs<<"\n";
				cout <<endl;
				n--;
			}
			ofs.close();
   			input_file.close();
   		}
	}
	return 0;
}
