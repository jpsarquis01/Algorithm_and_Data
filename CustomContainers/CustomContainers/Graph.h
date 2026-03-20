#pragma once

#include <iostream>
#include "Vector.h"

template<typename T>

class Graph
{
public:
    struct Node
    {
        //Data store in the graph
        const T* data = nullptr;

        //Used for graph traversal, reset after search complete
        bool isVisited = false;
        //If looking for the end node, can be used to obtain a path to the start
        Node* fromNode = nullptr;

        //Edges connected to the node
        Vector<int> edges;
    };

public:
    Graph()
    {
    }
    ~Graph()
    {
        Terminate();
    }

    int AddItem(const T* data)
    {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->isVisited = false;

        mNodes.PushBack(newNode);

        return mNodes.Size() - 1;
    }

    void AddLink(int a, int b)
    {
        if (a < 0 || a >= mNodes.Size() || b < 0 || b >= mNodes.Size())
        {
            return;
        }

        mNodes[a]->edges.PushBack(b);
        mNodes[b]->edges.PushBack(a);
    }

    void GetAllConnectionsDFS(int startIndex, Vector<const T*>& connections)
    {
        // uses a stack
        // LIFO
        Vector<bool> visited;
        visited.Resize(mNodes.Size(), false);

        Vector<Node*> stack;
        stack.PushBack(mNodes[startIndex]);
        while (stack.Size() > 0)
        {
            Node* node = stack[stack.Size() - 1];
            stack.PopBack();
            if (!node->isVisited)
            {
                node->isVisited = true;
                connections.PushBack(node->data);

                for (std::size_t i = 0; i < node->edges.Size(); ++i)
                {
                    int nodeIndex = node->edges[i];
                    Node* edgeNode = mNodes[nodeIndex];
                    if (!edgeNode->isVisited)
                    {
                        stack.PushBack(edgeNode);
                    }

                }
            }
        }
    }

    void GetAllConnectionsBFS(int startIndex, Vector<const T*>& connections)
    {
        // uses a queue
        // FIFO
        Reset();

        Vector<Node*> queue;
        queue.PushBack(mNodes[startIndex]);

        while (queue.Size() > 0)
        {
            Node* node = queue[0];
            queue.PopFront();

            if (!node->isVisited)
            {
                node->isVisited = true;
                connections.PushBack(node->data);

                for (std::size_t i = 0; i < node->edges.Size(); ++i)
                {
                    int nodeIndex = node->edges[i];
                    Node* edgeNode = mNodes[nodeIndex];
                    if (!edgeNode->isVisited)
                    {
                        queue.PushBack(edgeNode);
                    }
                }
            }
        }
    }

    bool GetPathDFS(int startIndex, int endIndex, Vector<const T*>& path)
    {
        // we just do the same as above
        // but we also set the "frontNode"
        // this can be used to obtain a path from start to finish
        bool pathFound = false;
        Node* startNode = mNodes[startIndex];
        Node* endNode = mNodes[endIndex];

        Reset();
        Vector<Node*> stack;
        stack.PushBack(mNodes[startIndex]);
        while (stack.Size() > 0)
        {
            Node* node = stack[stack.Size() - 1];
            stack.PopBack();

            if (!node->isVisited)
            {
                node->isVisited = true;
                if (node == endNode)
                {
                    pathFound = true;
                    break;
                }
                for (std::size_t i = 0; i < node->edges.Size(); ++i)
                {
                    int nodeIndex = node->edges[i];
                    Node* edgeNode = mNodes[nodeIndex];

                    if (!edgeNode->isVisited)
                    {
                        edgeNode->fromNode = node;
                        stack.PushBack(edgeNode);

                    }
                }
            }
        }
        if (pathFound)
        {
            Node* pathNodes = endNode;

            while (pathNodes != nullptr)
            {
                path.PushBack(pathNodes->data);
                pathNodes = pathNodes->fromNode;
            }
        }
        return pathFound;
    }

    bool GetPathBFS(int startIndex, int endIndex, Vector<const T*>& path)
    {
        bool pathFound = false;
        Node* startNode = mNodes[startIndex];
        Node* endNode = mNodes[endIndex];

        Reset();
        Vector<Node*> queue;
        queue.PushBack(startNode);
        while (queue.Size() > 0)
        {
            Node* node = queue[0];
            queue.PopFront();

            if (!node->isVisited)
            {
                node->isVisited = true;
                if (node == endNode)
                {
                    pathFound = true;
                    break;
                }
                for (std::size_t i = 0; i < node->edges.Size(); ++i)
                {
                    int nodeIndex = node->edges[i];
                    Node* edgeNode = mNodes[nodeIndex];
                    if (!edgeNode->isVisited)
                    {
                        edgeNode->fromNode = node;
                        queue.PushBack(edgeNode);
                    }
                }
            }
        }
        if (pathFound)
        {
            Node* pathNodes = endNode;

            while (pathNodes != nullptr)
            {
                path.PushBack(pathNodes->data);
                pathNodes = pathNodes->fromNode;
            }
        }
        return pathFound;
    }

    void PrintGraph()
    {
        std::cout << "Printing Adjacency List of Graph:\n";
        for (std::size_t i = 0; i < mNodes.Size(); ++i)
        {
            // * converts a pointer to a reference and gets the data
            // if we dont use the "*" we would print the address of the data
            std::cout << (*mNodes[i]->data) << ": ";
            for (std::size_t e = 0; e < mNodes[i]->edges.Size(); ++e)
            {
                int nodeIndex = mNodes[i]->edges[e];
                std::cout << (*mNodes[nodeIndex]->data) << " ";
            }
            std::cout << "\n";
        }
    }

    void Terminate()
    {
        for (std::size_t i = 0; i < mNodes.Size(); ++i)
        {
            delete mNodes[i];
            mNodes[i] = nullptr;
        }

        mNodes.Clear();
    }

private:
    void Reset()
    {
        for (std::size_t i = 0; i < mNodes.Size(); ++i)
        {
            mNodes[i]->isVisited = false;
            mNodes[i]->fromNode = nullptr;
        }
    }

    Vector<Node*> mNodes;
};