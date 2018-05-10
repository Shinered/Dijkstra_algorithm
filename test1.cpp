#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <queue>
using namespace std;

class EdgeNode
{
public:
	int adjvex;
	int weight;
	EdgeNode *next;
	EdgeNode(int adj, EdgeNode *n = NULL):adjvex(adj), next(n){}
};

class VertexNode
{
public:
	int data;
	EdgeNode *firstEdge;
};
class Graph 
{
public:
	void initGraph()
	{
		for(int i = 0; i < numVertexes; i++)				
		{
			(adjList+i)->data = i;
			(adjList+i)->firstEdge = NULL;
		}
		ifstream fin("dijkstraData.txt");
//		ifstream fin("dijkstraData.txt");
		string line;
		stringstream stream;
		while(getline(fin, line))
		{
			replace(line);
			int vertex, adjacent, weight;
			stream.clear();
			stream << line;
			stream >> vertex;
			while(stream >> adjacent)
			{
				stream >>  weight;
				addEdge(vertex-1, adjacent-1, weight);
			}
		}
	}
	void replace(string &str)
	{
		for(auto &c : str)
		{
			if(c == ',')	
			{
				c = ' ';
			}
		}
	}

	void addEdge(int a, int b, int c)
	{
		EdgeNode *enode = new EdgeNode(b,NULL);
		enode->next = (adjList+a)->firstEdge;
		enode->weight = c;
		(adjList+a)->firstEdge = enode;
	}

	void print()
	{
		for(int i = 0; i < numVertexes; i++)
		{
			cout << (adjList+i)->data << "adj: ";
			EdgeNode *temp = new EdgeNode(0,NULL);
			temp = (adjList+i)->firstEdge;
			while(temp)
			{
				cout << temp->adjvex << "weight: " << temp->weight << " ";
				temp = temp->next;
			}
			cout << endl;
		}
		
	}

public:
	int numVertexes = 200;
	VertexNode* adjList = new VertexNode[200];
	
};






class Dijkstra
{
public:
	Dijkstra(Graph graph, int s)
	{
		priority_queue<int, vector<int>, greater<int> > myQueue;//优先队列
		distInit();//距离初始化，原点距离为0其余各点距离初始化为无穷大
		myQueue.push(s);
		while(!myQueue.empty())
		{
			VertexNode *temp = new VertexNode;	
			EdgeNode *p = new EdgeNode(0,NULL);
			temp = (graph.adjList + myQueue.top());
			p = (graph.adjList + myQueue.top())->firstEdge;
			myQueue.pop(); //将该点弹出
			while(p)//遍历与该点相连的点
			{
				/*************找到能够更新的，压入队列******************/
				if(distTo[p->adjvex] > distTo[temp->data] + p->weight)
				{
					myQueue.push(p->adjvex);
					distTo[p->adjvex] = distTo[temp->data] + p->weight;
					//路径更新
					edgeTo[p->adjvex].clear();			
					edgeTo[p->adjvex].insert(edgeTo[p->adjvex].begin(),edgeTo[temp->data].begin(),edgeTo[temp->data].end());
					edgeTo[p->adjvex].push_back(p->adjvex);
				}
				p = p->next;
			}
		}
	}

	void distInit()
	{
		distTo.resize(length);
		edgeTo.resize(length);
		distTo[0] = 0;
		for(int i = 1; i < length; i++)
		{
			distTo[i] = 1000000;
		}		

	}
	
	void write()
	{
		ofstream fout;
		fout.open("output.txt");
		for(int i = 0; i < length; i++)
		{
			fout << "vertex:" << i+1 << " distance:" << distTo[i] << "path[" << i+1 << "]:";
			for(int k = 0; k < edgeTo[i].size(); k++)
			{
				fout << edgeTo[i][k] + 1 << ",";	
			}
			fout << endl;
		}
		
	}



public:
	vector<long int> distTo; // 存储s点到每个点的距离
	vector< vector<int> >edgeTo; //存储从s到某个点的路径
	int length = 200;
};

int main()
{
	clock_t start, end;
	start = clock();
	Graph graph;
	graph.initGraph();
	Dijkstra dijk(graph, 0);
	dijk.write();
	end = clock();
	cout << "running time:" << (double)(end-start)/CLOCKS_PER_SEC << "s" << endl;;
	return 0;
}






