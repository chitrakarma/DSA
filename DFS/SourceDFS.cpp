//{ Driver Code Starts
// Initial Template for C++

#include <iostream>
#include <map>
#include <vector>
#include <list>
using namespace std;


// } Driver Code Ends
// User function Template for C++

class Graph {
public:
    map<pair<int, int>, bool> visited;
    map<pair<int, int>, list<pair<int, int> > > adj_nodes;
    list<pair<int, int> > main_nodes;
    list<pair<int, int> > path_nodes;

    // function to add an edge to the graph
    void addEdge(pair<int, int> node, pair<int, int> adj_node);

    // DFS traversal of the vertices reachable from node
    void DFS(pair<int, int> node, vector<vector<int>>& grid);

    // traverse the graph and identify main nodes
    void FindMainNodes(vector<vector<int>>& grid);

    vector<int> results;
};

void Graph::addEdge(pair<int, int> node, pair<int, int> adj_node) {
    adj_nodes[node].push_back(adj_node);
}

void Graph::DFS(pair<int, int> node, vector<vector<int>>& grid) {
    // mark current node as visited
    visited[node] = true;
    if (grid[node.first][node.second] == 1) {
        if (
            (
                (
                    (node.first != 0) && (node.first != (grid.size() - 1))
                    )
                )
            &&
            (
                (node.second != 0) && (node.second != (grid[0].size() - 1))
                )
            ) {
            cout << node.first << " " << node.second << " " << grid.size() - 1 << " " << grid[0].size() - 1 << "\n";
            path_nodes.push_back(node);
        }
    }

    /*if ((grid[node.first][node.second] == 1) && ((node.first != 0)&&(node.first != (grid.size() - 1))&&(node.second != 0)&&(node.second != (grid[0].size())))){
        count++;
    }
    else {
        count = (-1)*count;
    }*/
    //cout << "[(" << node.first << ", " << node.second << ") = " << grid[node.first][node.second] << "] --> ";

    list<pair<int, int> >::iterator i;
    for (i = adj_nodes[node].begin(); i != adj_nodes[node].end(); ++i) {
        //if ((!visited[*i]) && ((node.first != 0)&&(node.first != (grid.size() - 1))&&(node.second != 0)&&(node.second != (grid[0].size()))))
        if (!visited[*i])
            DFS(*i, grid);
    }
}

void Graph::FindMainNodes(vector<vector<int>>& grid) {
    for (int i = 1; i < grid.size() - 1; ++i) {
        for (int j = 1; j < grid[0].size() - 1; ++j) {
            if (grid[i][j] == 1) {
                pair<int, int> temp(i, j);
                main_nodes.push_back(temp);
                //cout << i << " " << j << "\n";
            }
        }
    }
}

class Solution {
public:

    int numberOfEnclaves(vector<vector<int>>& grid) {
        // Code here
        Graph g;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                pair<int, int> cur_node(i, j);

                if (!((i - 1) < 0)) {
                    // if there is a top node
                    pair<int, int> top_node(i - 1, j);
                    g.addEdge(cur_node, top_node);
                }

                if (!((i + i) > grid.size())) {
                    // if there is a bottom node 
                    pair<int, int> bottom_node(i + 1, j);
                    g.addEdge(cur_node, bottom_node);
                }

                if (!((j - 1) < 0)) {
                    // if there is a left node
                    pair<int, int> left_node(i, j - 1);
                    g.addEdge(cur_node, left_node);
                }


                if (!((j + 1) > grid[0].size())) {
                    // if there is a right node
                    pair<int, int> right_node(i, j + 1);
                    g.addEdge(cur_node, right_node);
                }
            }
        }

        g.FindMainNodes(grid);

        int counter = 0;
        for (auto i : g.main_nodes) {
            if (!g.visited[i]) {
                counter = 0;
                g.DFS(i, grid);
                //g.results.push_back(counter);
            }
        }

        for (auto n : g.path_nodes) {
            if (((n.first != 0) || (n.first != (grid.size() - 1))) || ((n.second != 0) || (n.second != (grid[0].size() - 1)))) {
                //cout << n.first << " " << n.second << " "<< grid.size() - 1 << " " << grid[0].size() - 1 << "\n";
                counter++;
            }
            else {
                cout << "BREAK\n";
                counter = 0;
                break;
            }
        }

        /*if (*max_element(g.results.begin(), g.results.end()) < 0) {
            return 0;
        }
        return *max_element(g.results.begin(), g.results.end());*/
        return counter;
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        Solution obj;
        cout << obj.numberOfEnclaves(grid) << endl;
    }
}
// } Driver Code Ends