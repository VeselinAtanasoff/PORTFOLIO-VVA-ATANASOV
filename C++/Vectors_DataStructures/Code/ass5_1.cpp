#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
	int left;
	int right;
};

int main()
{
	int n;
	cin >> n;

	vector<Node> tree(n+1);

	for(int i=0;i<n;i++)
	{
		int nr, left, right;
		cin >> nr >> left >> right;
		tree[nr] = {left, right};
	}
	int depth = 0;
	/* implement your algorithm and store the tree depth in depth */
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int size = q.size();
		for(int i=0;i<size;i++)
		{
			int node = q.front();
			q.pop();
			if(tree[node].left != 0)
				q.push(tree[node].left);
			if(tree[node].right != 0)
				q.push(tree[node].right);
		}
		depth++;
	}
	cout << "depth is " << depth << endl;

	return 0;
}
