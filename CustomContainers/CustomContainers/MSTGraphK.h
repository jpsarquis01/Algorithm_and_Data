#pragma once
#include "Vector.h"
#include "Globals.h"

class DisjointSetUnion
{
public:
	DisjointSetUnion(int numNodes)
	{
		mParent.Resize(numNodes);
		mRank.Resize(numNodes, 0);
		for (int i = 0; i < numNodes; ++i)
		{
			mParent[i] = i;
		}
	}
	int FindParentIndex(int nodeIndex)
	{
		if (mParent[nodeIndex] != nodeIndex)
		{
			mParent[nodeIndex] = FindParentIndex(mParent[nodeIndex]);
		}
		return mParent[nodeIndex];
	}
	bool UniteEdges(int from, int to)
	{
		int rootFrom = FindParentIndex(from);
		int rootTo = FindParentIndex(to);
		if (rootFrom == rootTo)
		{
			return false;
		}
		if (mRank[rootFrom] < mRank[rootTo])
		{
			mParent[rootFrom] = rootTo;
		}
		else if (mRank[rootFrom] > mRank[rootTo])
		{
			mParent[rootTo] = rootFrom;
		}
		else
		{
			mParent[rootTo] = rootFrom;
			++mRank[rootFrom];
		}
		return true;
	}
private:
	Vector<int> mParent;
	Vector<int> mRank;

};
template<typename W>
class MSTGraphK
{
public:
	struct Edge
	{
		int fromNode = -1;
		int toNode = -1;
		W weight;
	};
public:
	void Clear()
	{
		mEdges.Clear();
		mMSTGraph.Clear();
	}

	void AddEdge(int a, int b, W weight)
	{
		Edge newEdgeA = { a, b, weight };
		mEdges.PushBack(newEdgeA);
	}

	void GenerateMST()
	{
		int numNodes = mEdges.Size();
		mMSTGraph.Clear();

		DisjointSetUnion dsu(numNodes);
		Globals::IntroSort(mEdges.Begin(), mEdges.End(), [](const Edge& a, const Edge& b) { return a.weight < b.weight; });
		for (std::size_t i = 0; i < mEdges.Size(); ++i)
		{
			Edge& edge = mEdges[i];
			if (dsu.UniteEdges(edge.fromNode, edge.toNode))
			{
				mMSTGraph.PushBack(edge);
				if (mMSTGraph.Size() == numNodes - 1)
				{
					break;
				}
			}
		}
	}
	const Vector<Edge>& GetMST() const
	{
		return mMSTGraph;
	}
private:
	Vector<Edge> mEdges;
	Vector<Edge> mMSTGraph;
};