#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Vertex
{
public:
	Vertex() :
		data(0)
	{	}

	Vertex(const T& data) :
		data(data)
	{	}

	T get_data()
	{
		return data;
	}

private:
	T data;
};

class Edge
{
public:

	Edge() :
		from(0),
		to(0)
	{	}
	Edge(const int& from, const int& to) :
		from(from),
		to(to)
	{	}

	int get_from()
	{
		return from;
	}
	int get_to()
	{
		return to;
	}

	void set_from(const int& from)
	{
		this->from = from;
	}
	void set_to(const int& to)
	{
		this->to = to;
	}

private:
	int from, to;
};

template <typename T>
class Graph
{
public:
	Graph(void) {};
	~Graph(void) {};

	void add_vertex(const T& data);								
	int find_vertex(const T& data);	
	T find_vertex(const int& numb);                
	void delete_vertex(const T& data);
	void delete_vertex(const int& numb);	
	void add_edge(const int& from, const int& to);				
	void add_edge(const T& from, const T& to);					
	bool find_edge(const int& from, const int& to);				
	int find_edge(const T& from, const T& to);					
	void delete_edge(const int& from, const int& to);			
	void delete_edge(const T& from, const T& to);				
	void print_graph();											
	int get_vertexes_size();

	bool is_empty(void);										
	void clear_graph(void);										

private:
	vector<Vertex<T>> vertexes;
	vector<Edge> edges;
};


//addition
template<typename T>
inline void Graph<T>::add_vertex(const T& data)
{
	if (find_vertex(data) == -1)
		vertexes.push_back(Vertex<T>(data));
}

//search by value
template<typename T>
inline int Graph<T>::find_vertex(const T& data)
{
	for (int i = 0; i < vertexes.size(); ++i)
		if (vertexes[i].get_data() == data)
			return i;
	return -1;
}

//search by number
template<typename T>
inline T Graph<T>::find_vertex(const int& numb)
{
	if(vertexes.size()>numb)
	    return vertexes[numb];
}

//daletion by value
template<typename T>
inline void Graph<T>::delete_vertex(const T& data)
{
	int vertex_num = find_vertex(data);
	if (vertex_num != -1)
	{
		vertexes.erase(vertexes.begin() + vertex_num);
		for (int i = 0; i < edges.size(); ++i)
			if (find_edge(i, vertex_num))
				delete_edge(i, vertex_num);
	}
}

//daletion by number
template<typename T>
inline void Graph<T>::delete_vertex(const int& numb)
{
	if (numb < vertexes.size())
	{
		vertexes.erase(vertexes.begin() + numb);
		for (int i = numb; i < vertexes.size(); ++i)
			vertexes[i] = vertexes[i + 1];
		if (vertexes.size() != 0)
			vertexes.pop_back();
	}
}

//addition by number
template<typename T>
inline void Graph<T>::add_edge(const int& from, const int& to)
{
	if (find_edge(from, to) == false)
		edges.push_back(Edge(from, to));
}

//addition by value
template<typename T>
inline void Graph<T>::add_edge(const T& from, const T& to)
{
	int first = find_vertex(from), sec = find_vertex(to);
	if (first != -1 && sec != -1 && find_edge(first, sec) == false)
		edges.push_back(Edge(find_vertex(from), find_vertex(to)));

}

//search by number
template<typename T>
inline bool Graph<T>::find_edge(const int& from, const int& to)
{
	for (int i = 0; i < edges.size(); ++i)
		if (edges[i].get_from() == from && edges[i].get_to())
			return true;
	return false;
}

//search by value
template<typename T>
inline int Graph<T>::find_edge(const T& from, const T& to)
{
	for (int i = 0; i < edges.size(); ++i)
		if (vertexes[edges[i].get_from()].get_data() == from && vertexes[edges[i].get_to()].get_data() == to)
			return i;
	return -1;
}

//deletion by number
template<typename T>
inline void Graph<T>::delete_edge(const int& from, const int& to)
{
	for (int i = 0; i < edges.size(); ++i)
		if (find_edge(from, to) == true)
		{
			edges.erase(edges.begin() + i);
			for (int k = i; k < edges.size(); ++k)
				edges[k] = edges[k + 1];
			if (edges.size() != 0)
				edges.pop_back();
		}
}

//deletion by value
template<typename T>
inline void Graph<T>::delete_edge(const T& from, const T& to)
{
	for (int i = 0; i < edges.size(); ++i)
		if (find_edge(from, to) != -1)
			edges.erase(edges.begin() + i);
}

//show graph
template<typename T>
inline void Graph<T>::print_graph()
{
	for (int i = 0; i < edges.size(); ++i)
		cout << vertexes[edges[i].get_from()].get_data() << " ---> " << vertexes[edges[i].get_to()].get_data() << endl;
}

template<typename T>
inline int Graph<T>::get_vertexes_size()
{
	return vertexes.size();
}

//check for content
template<typename T>
inline bool Graph<T>::is_empty(void)
{
	if (vertexes.size() == 0)
		return true;
	return false;
}

//clear graph
template<typename T>
inline void Graph<T>::clear_graph(void)
{
	vertexes.clear();
	edges.clear();
}