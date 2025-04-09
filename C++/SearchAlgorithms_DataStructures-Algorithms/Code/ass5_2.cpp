#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int t; 
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int n, m; 
        cin >> n >> m;

        
        vector<vector<int>> adj(n + 1);

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a); 
        }

        // BFS to find the shortest path from node 1 to node n
        vector<bool> visited(n + 1, false); // To track visited nodes
        queue<pair<int, int>> q;           // (node, depth)

        visited[1] = true; // Start from node 1
        q.push({1, 0});    // Push (node, depth)

        int route_count = -1; // Default value for no path

        // Iterate over the queue until it is empty
        while (!q.empty())
        {
            int curr = q.front().first;  // Get the current node
            int depth = q.front().second; // Get the depth (number of edges from node 1)
            q.pop(); // Dequeue the current node

            // If we reach the destination node (node n), store the result
            if (curr == n)
            {
                route_count = depth; // The number of connections in the shortest path
                break;
            }

            // Get all adjacent vertices of the dequeued vertex 'curr'
            // If an adjacent has not been visited, mark it as visited and enqueue it
            for (int neighbor : adj[curr])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true; // Mark neighbor as visited
                    q.push({neighbor, depth + 1}); // Enqueue the neighbor with an updated depth
                }
            }
        }

        cout << route_count << endl;
    }

    return 0;
}

