#pragma once

class Node
{
private:
	Node* m_next{nullptr};
	Node* m_down{nullptr};

	int m_location{};

public:
	Node();
	virtual ~Node();

	void SetNext(Node* next);
	Node* GetNext() const;

	void SetDown(Node* down);
	Node* GetDown() const;

	void SetLocation(int location);
	int GetLocation() const;
};

