#include <iostream>
#include <ctime>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
/***********边表***********/
class EdgeNode
{
public:
	int adjvex;
	int weight;
	EdgeNode *next;
	EdgeNode(long int adj, EdgeNode *n = NULL): adjvex(adj), next(n){}

};
/************顶点表*************/
class VertexNode 
{
public:
	long int data;
	EdgeNode *firstEdge;

};
/************图*************/
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
/******************加边**********************/
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
		distInit();		
		marked.push_back(s);//将原点加入集合X中
		distTo[s] = 0; //原点距离初始化为0
		/***当集合X点不包括图中的顶点时****/
		while(marked.size() < length)  
		{
			long int min = maxInt;
			int index1, index2, indexMin;
			/******marked:be added to set X，集合X中的点******/
			for(int i = 0; i < marked.size(); i++) 
			{
				EdgeNode *p = new EdgeNode(0,NULL);
				p = (graph.adjList+marked[i])->firstEdge;
				index1 = marked[i];//集合X中的点
				while(p)
				{
					//try to traversed edges whose head is not in set X, tail in set X.
					if(min > p->weight + distTo[index1] && !is_marked(p->adjvex))
					{
						indexMin = index1;//标记最小索引
						min = p->weight + distTo[index1];
						index2 = p->adjvex;//集合X之外的点
					}
					p = p->next;
				}
			}
			//如果找到了最小路径
			if(min < maxInt)
			{
				marked.push_back(index2);//将该点添加到集合X中
				distTo[index2] = min;//距离更新
				path[index2].insert(path[index2].begin(),path[indexMin].begin(),path[indexMin].end());//路径更新
				path[index2].push_back(index2);
			}
		}
		
	}
	//判断是否为集合X中的点
	bool is_marked(int index)
	{
		for(int i = 0; i < marked.size(); i++)
		{
			if(marked[i] == index)
			return true;
		}
		return false;
	}


	void distInit()
	{
		path.resize(length);
		for(int i = 0; i < length; i++)
		{
			distTo[i] = maxInt;
	//		marked[i] = false;
		}
	}

	void write()
	{
		ofstream fout;
		fout.open("out2.txt");
		for(int i = 0; i < length; i++)
		{
			fout << "vertex:" << i+1 << " distance:" << distTo[i] << "path[" << i+1 << "]:" ;
			for(int k = 0; k < path[i].size(); k++)
			{
				fout << path[i][k] + 1 << ",";	
			}
			fout << endl;
		}

	}


private:
	int length = 200;
	vector<int> marked;
	vector< vector<int> > path;
	int distTo[200];
	long int maxInt = 1000000;

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
	cout << "running time:" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}

