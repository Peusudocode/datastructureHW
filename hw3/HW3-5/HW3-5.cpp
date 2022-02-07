#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include<bits/stdc++.h>
#define INF INT_MAX
using namespace std;
//  the shortest paths from v to the remaining vertices of t. Your function should have complexity O(n)
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // adjacency lists
public:
    Graph(int V);  // Constructor
    void addEdge(int v, int w, int weight); // adds an edge
  
    // finds shortest path from source vertex ．s・ to
    // destination vertex ．d・.
    int findShortestPath(int s, int d);
  
    // print shortest path from a source vertex ．s・ to
    // destination vertex ．d・.
    int printShortestPath(int parent[], int s, int d);
};
  
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[2*V];
}
  
void Graph::addEdge(int v, int w, int weight)
{
    // split all edges of weight 2 into two
    // edges of weight 1 each.  The intermediate
    // vertex number is maximum vertex number + 1,
    // that is V.
    if (weight==2)
    {
        adj[v].push_back(v+V);
        adj[v+V].push_back(w);
    }
    else // Weight is 1
        adj[v].push_back(w); // Add w to v・s list.
}
  
// To print the shortest path stored in parent[]
int Graph::printShortestPath(int parent[], int s, int d)
{
    static int level = 0;
  
    // If we reached root of shortest path tree
    if (parent[s] == -1)
    {
        cout << "Shortest Path between " << s << " and "
             << d << " is "  << s << " ";
        return level;
    }
  
    printShortestPath(parent, parent[s], d);
  
    level++;
    if (s < V)
        cout << s << " ";
  
    return level;
}
  
// This function mainly does BFS and prints the
// shortest path from src to dest. It is assumed
// that weight of every edge is 1
int Graph::findShortestPath(int src, int dest)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[2*V];
    int *parent = new int[2*V];
  
    // Initialize parent[] and visited[]
    for (int i = 0; i < 2*V; i++)
    {
        visited[i] = false;
        parent[i] = -1;
    }
  
    // Create a queue for BFS
    list<int> queue;
  
    // Mark the current node as visited and enqueue it
    visited[src] = true;
    queue.push_back(src);
  
    // 'i' will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;
  
    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        int s = queue.front();
  
        if (s == dest)
            return printShortestPath(parent, s, dest);
  
        queue.pop_front();
  
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it
        // visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
                parent[*i] = s;
            }
        }
    }
}


int main(){
	int order;
	while(true){
		cout<<"if you want to find the shortest paths from v to the remaining vertices of t. Enter 1"<<endl;
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
    		int v, s, i=0;
    		getline(input_file, line);
    		istringstream ( line ) >> v;
    		cout << "vertex number :" << v << endl;
    		int n = v, l, j, k;
    		v++;
    		Graph g(v);
    		string number;
			while(n > 1){
				i= 0;
				getline(input_file, line);
				cout << line <<endl;
				istringstream edge(line);
				while(getline(edge, number, ' ')) {
					if(i == 0){
						istringstream ( number ) >> j;
						i++;
					}
					else if(i == 1){
						istringstream ( number ) >> k;
						i++;
					}
					else if(i == 2){
						istringstream ( number ) >> l;
						i++;
					}
				}
				g.addEdge(j, k, l);
				g.addEdge(k, j, l);
				cout << "addEdge:" << j << "," << k << "," << l << endl;
				n--;	
			}
			getline(input_file, line);
    		istringstream ( line ) >> s;
    		cout << "the root of the tree: " << s << endl;
    		g.shortestPath(s);
    		ofs.close();
   			input_file.close();
    	}
    }
    return 0;
}
