#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

void Node::SetNext(Node* next)
{
	m_next = next;
}

Node* Node::GetNext() const
{
	return m_next;
}

void Node::SetDown(Node* down)
{
	m_down = down;
}

Node* Node::GetDown() const
{
	return m_down;
}

void Node::SetLocation(int location)
{
	m_location = location;
}

int Node::GetLocation() const
{
	return m_location;
}
