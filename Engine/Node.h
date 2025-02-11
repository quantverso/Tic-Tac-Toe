#ifndef QUANTVERSO_NODE_H
#define QUANTVERSO_NODE_H

//--------------------------------------------------------------------------------------------------

#include <vector>
#include <memory>
#include <unordered_set>
#include <cassert>

class Node;
using NodePtr = std::shared_ptr<Node>;

//--------------------------------------------------------------------------------------------------

class Node
{
public:
	enum Status
	{
		Unvisited,
		Visited
	};

	Node(size_t size);

	void SetStatus(Status status) const;
	void SetDistance(unsigned distance);
	void SetParent(NodePtr parent);
	void Move(size_t index);

	constexpr size_t Size() const;
	Status GetStatus() const;
	const unsigned& GetDistance() const;
	NodePtr GetParent();
	void GetAdjacent(std::vector<NodePtr>& adjacent);

	static unsigned VisitedNodes();
	static void Reset();

	Node& operator=(const Node& other);
	bool operator==(const Node& other) const;

private:
	class Reference
	{
	public:
		Reference(Node& node, size_t index) :
			node{ node },
			index{ index }
		{
		}

		Reference& operator=(unsigned value)
		{
			if (value == 0)
				node.indexOfZero = index;

			// Limpa os bits existentas na posição
			node.data &= ~(uint64_t(0b1111) << (index * 4));

			// Define os novos bits
			node.data |= (uint64_t(value) << (index * 4));

			return *this;
		}

		operator int() const
		{
			return (node.data >> (index * 4)) & 0b1111;
		}

	private:
		Node&	     node;
		const size_t index;
	};
	
	inline static std::unordered_set<uint64_t> visited;

	uint64_t data;
	size_t	 size;
	int		 columns;
	size_t	 indexOfZero;
	unsigned distance;
	NodePtr	 parent;

public:
	Reference operator[](size_t index);
};

//--------------------------------------------------------------------------------------------------

inline void Node::SetStatus(Status status) const
{
	if (status == Visited)
		visited.insert(data);
	else
		visited.erase(data);
}

//--------------------------------------------------------------------------------------------------

inline void Node::SetDistance(unsigned distance)
{
	this->distance = distance;
}

//--------------------------------------------------------------------------------------------------

inline void Node::SetParent(NodePtr parent)
{
	this->parent = parent;
}

//--------------------------------------------------------------------------------------------------

inline constexpr size_t Node::Size() const
{
	return size;
}

//--------------------------------------------------------------------------------------------------

inline Node::Status Node::GetStatus() const
{
	return visited.find(data) == visited.end() ? Unvisited : Visited;
}

//--------------------------------------------------------------------------------------------------

inline const unsigned& Node::GetDistance() const
{
	return distance;
}

//--------------------------------------------------------------------------------------------------

inline NodePtr Node::GetParent()
{
	return parent;
}

//--------------------------------------------------------------------------------------------------

inline unsigned Node::VisitedNodes()
{
	return unsigned(visited.size());
}

//--------------------------------------------------------------------------------------------------

inline void Node::Reset()
{
	visited.clear();
}

//--------------------------------------------------------------------------------------------------

inline Node& Node::operator=(const Node& other)
{
	if (this != &other)
	{
		data = other.data;
		size = other.size;
		columns = other.columns;
		indexOfZero = other.indexOfZero;
	}

	return *this;
}

//--------------------------------------------------------------------------------------------------

inline bool Node::operator==(const Node& other) const
{
	return this->data == other.data;
}

//--------------------------------------------------------------------------------------------------

inline Node::Reference Node::operator[](size_t index)
{
	assert(index < size && "Index fora dos limites do nodo!");
	return Reference(*this, index);
}

//--------------------------------------------------------------------------------------------------

#endif
