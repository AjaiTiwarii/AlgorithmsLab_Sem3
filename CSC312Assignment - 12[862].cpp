#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
#include<list>
#include<queue>
#include<stack>
using namespace std;


class graph{

    public:
    unordered_map<int, list<int>> adj;

    void addEdge(int u, int v, bool direction){
        //direction = 0  -> undirected graph
        //direction = 1  -> directed graph

        //create an edge from u to v
        adj[u].push_back(v);

        if(direction == 0){
            adj[v].push_back(u);
        }
    }

    void printAdjList(){
        for(auto i: adj){
            cout << i.first << "-> ";
            for(auto j: i.second){
                cout << j << ", ";
            }
            cout << endl;
        }
    }

    // BFS traversal
    void BFS(int start){
        unordered_map<int, bool> visited;
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while(!q.empty()){
            int node = q.front();
            cout << node << " ";
            q.pop();

            for(int neighbour: adj[node]){
                if(!visited[neighbour]){
                    q.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }
    }

    // DFS traversal
    void DFS(int start){
        unordered_map<int, bool> visited;
        stack<int> s;
        s.push(start);

        while(!s.empty()){
            int node = s.top();
            s.pop();

            if(!visited[node]){
                cout << node << " ";
                visited[node] = true;
            }

            for(int neighbour: adj[node]){
                if(!visited[neighbour]){
                    s.push(neighbour);
                }
            }
        }
    }



    bool cycledetection(int v, bool visited[], int parent) 
    { 
        // Mark the current node as visited 
        visited[v] = true; 
    
        // Recur for all the vertices adjacent to this vertex 
        list<int>::iterator i; 
        for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        { 
            // If an adjacent is not visited, then recur for that adjacent 
            if (!visited[*i]) 
            { 
                if (cycledetection(*i, visited, v)) 
                    return true; 
            } 
    
            // If an adjacent is visited and not parent of current vertex, then there is a cycle. 
            else if (*i != parent) 
                return true; 
        } 
        return false; 
    } 
    
    // Returns true if the graph contains a cycle, else false. 
    bool isCyclic() 
    {
        int V = adj.size();
        // Mark all the vertices as not visited and not part of recursion stack
        bool *visited = new bool[V]; 
        for (int i = 0; i < V; i++) 
            visited[i] = false; 
    
        // Call the recursive helper function to detect cycle in different DFS trees
        for (int u = 0; u < V; u++) 
            if (!visited[u]) // Don't recur for u if it is already visited
            if (cycledetection(u, visited, -1)) 
                return true; 
    
        return false; 
    } 


};



int main(){

    int n;
    cout << "enter no. of nodes = ";
    cin >> n;

    int m;
    cout << "enter no. of edges = ";
    cin>> m;

    graph g;

    for(int i=0; i<m; i++){
        int u,v;
        cin>>u>>v;

        //creating undirected graph
        // g.addEdge(u,v,0);

        g.addEdge(u,v,1);
    }

    //printing graph
    g.printAdjList();

    // BFS traversal
    cout << "BFS traversal: ";
    g.BFS(1); // replace 1 with your starting node
    cout << endl;

    // DFS traversal
    cout << "DFS traversal: ";
    g.DFS(1); // replace 1 with your starting node
    cout << endl;

    if(g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";


    return 0;
}