#include <vector> 
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

class Graph
{
public:
	void initGraph()
	{
		_storage.resize(length);
		ifstream fin("SCC.txt");
		string line;
		stringstream stream;
		while(getline(fin, line))
		{
			long int vertex, adjacent;
			stream.clear();
			stream << line;
			stream >> vertex;
			while(stream >> adjacent)
			{
				_storage[vertex-1].push_back(adjacent - 1);
	//			_inversed[adjacent-1].push_back(vertex - 1);
			}
		}
	}
	void print()
	{
		for(long int i = 0; i < 10; i++)
		{
			cout << i << " ";
			list<long int> :: iterator iter;
			for( iter = _storage[i].begin();  iter != _storage[i].end(); iter++)
			{
				cout << *iter << " ";
			}
			cout << endl;	
		}
	}
/*	void markInit()
	{
		marked.resize(length);
		for(int i = 0; i < marked; i++)
		{
			marked[i] = false;
		}
	}*/
	
	long int get_numbers()
	{
		return length;
	}

private:
	vector< list<long int> > _storage;
	vector< list<long int> > _inversed;
//	vector <bool> marked;
//	vector <long int> f;
	long int length = 875714;
//	long int t = 0;
//	long int s = 0;
};

class DepthFirstSearch
{
public:
	void mark_init()
	{
		marked.resize(length);
		leader.resize(length);
		for(int i = 0; i < length; i++)
		{	
			marked[i] = false;
		}
	}
	
	void DFS_Loop( Graph graph, int flag )
	{
		length = graph.get_numbers();
		mark_init();
		t = 0;
		s = 0;
		
		for(long int i = length; i >= 0; i--)
		{
			if(!marked[i])
			{
				s = i;
				DFS(graph, i, flag);
			}
		}
	}
	
	void DSF(Graph graph, long int i, int flag)
	{
		marked[i] = true;
		if(flag == 2) 
		{
			leader[i] = s;
		}
		for(int j = 0; i < graph._storage[i].size(); j++)
		{
			if(!marked[j])	
			{
				DFS(graph,j);
			}
		}
		if(flag == 1) 
		{
			t++;
			f[i] = t;
		}
	}
	
private:
	vector< long int > f;
	vector< long int > leader;
	vector< bool > marked;
	long int t;// keep track of the number of vertices that have been fully explored.
	long int s;//This keeps track of vertex from which the last DFS call was invoked.
	long int length;
};

int main()
{
	Graph graph;
	graph.initGraph();
	graph.print();
			
	return 0;
}


