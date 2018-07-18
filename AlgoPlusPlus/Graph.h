#pragma once
#include <iostream>
#include <set>
#include <list>
#include <map>
#include <memory>
#include <queue>

using namespace std;

template<typename T>
class Graph {
public:
	Graph(set<T> nodes) : m_Map()
	{
		for (auto node : nodes)
		{
			set<T> vec;
			m_Map.insert(pair<T, set<T>> (node, vec));
		}
	}

	~Graph() {}

	void AddEdge(T u, T v)
	{
		map<T, set<T>>::iterator it;
		it = m_Map.find(u);
		it->second.insert(v);
		it = m_Map.find(v);
		it->second.insert(u);
	}

	class BFSiterator
	{
	public:
		BFSiterator(const map<T, set<T>> &mapa, T node) :
			m_CurrentMap(mapa)
		{
			map<T, set<T>>::iterator it = m_CurrentMap.find(node);
			m_Queue.push(it->first);
		}
		BFSiterator(const BFSiterator& other) :
			m_CurrentMap(other.m_CurrentMap),
			m_Queue(other.m_Queue),
			m_Visited(other.m_Visited)

		{ }

		T getCurrent()
		{
			return m_Queue.front();
		}
		bool hasNext()
		{
			return !m_Queue.empty();
		}
		BFSiterator& next()
		{
			 // pop the element we should visit
			T current = m_Queue.front();
			m_Visited.insert(current);
			m_Queue.pop();

			map<T, set<T>>::iterator it = m_CurrentMap.find(current);
			for (auto neighbor : it->second)
			{
				if (m_Visited.find(neighbor) == m_Visited.end())
				{
					m_Queue.push(neighbor);
					m_Visited.insert(neighbor);
				}
			}
			return *this;
		}
	private:
		map<T, set<T>> m_CurrentMap;
		queue<T> m_Queue;
		set<T> m_Visited;
	};

	BFSiterator begin(T node)
	{
		return BFSiterator(m_Map, node);
	}

private:
	map<T, set<T>> m_Map;
};