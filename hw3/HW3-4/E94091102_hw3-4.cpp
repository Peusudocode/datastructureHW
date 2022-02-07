#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include<bits/stdc++.h>
using namespace std;
//  finds a minimum cost spanning tree using Kruskal¡¦s algorithm.
// Creating shortcut for an integer pair
typedef  pair<int, int> iPair;
// Structure to represent a graph
struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges;
  
    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }
  
    // Utility function to add an edge
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }
  
    // Function to find MST using Kruskal's
    // MST algorithm
    int kruskalMST();
};
  
// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;
  
    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
  
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
  
            //every element is parent of itself
            parent[i] = i;
        }
    }
  
    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
  
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
  
        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
  
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};
  
 /* Functions returns weight of the MST*/ 
  
int Graph::kruskalMST()
{
    int mst_wt = 0; // Initialize result
  
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
  
    // Create disjoint sets
    DisjointSets ds(V);
  
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
  
        int set_u = ds.find(u);
        int set_v = ds.find(v);
  
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            cout << u << " - " << v << endl;
  
            // Update MST weight
            mst_wt += it->first;
  
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
  
    return mst_wt;
}


int main(){
	int order;
	while(true){
		cout<<"if you want to finds a minimum cost spanning tree using Kruskal¡¦s algorithm. Enter 1"<<endl;
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
    		int v, e, i=0;
    		getline(input_file, line);
			istringstream v_and_e(line);
    		string number;
			while(getline(v_and_e, number, ' ')) {
				if(i == 0){
					istringstream ( number ) >> v;
				}
      			else if(i == 1){
      				istringstream ( number ) >> e;
				}
				i++;
			}
			cout << "v: " << v << " e: " << e <<endl;
			Graph g(v, e);
			int n = e, l, j, k;
			while(n > 0){
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
				cout << "addEdge:" << j << "," << k << "," << l << endl;
				n--;	
			}
			cout << "Edges of MST are \n";
			int mst_wt = g.kruskalMST();
			cout << "\nWeight of MST is " << mst_wt << endl;
			ofs<<mst_wt;
    		ofs.close();
   			input_file.close();	
    	}
    }
    return 0;
}
