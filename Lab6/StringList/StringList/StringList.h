#pragma once
#include "stdafx.h"


class CStringList
{
	struct Node
	{
		Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node *prev;
		std::unique_ptr<Node> next;
	};
	
public:
	size_t GetSize()const;
	bool IsEmpty() const;

	void PushBack(const std::string& data);
	void PushFront(const std::string& data);

	class CIterator : public std::iterator<std::bidirectional_iterator_tag, Node>
	{
		friend CStringList;
		CIterator(Node *node, const CStringList * list, bool isReverse = false);
	public:
		CIterator() = default;
		std::string & operator*()const;
		bool operator==(CIterator const & other) const;
		bool operator!=(CIterator const & other) const;
		CIterator &operator++();
		CIterator &operator--();
		Node * operator->()const;
	private:
		const CStringList * m_list;
		Node *m_node = nullptr;
		bool m_isReverse = false;
	};

	CIterator Insert(const std::string& data, CIterator  & iter);

	CIterator begin();
	CIterator end();
	const CIterator cbegin() const;
	const CIterator cend() const;

	CIterator rbegin();
	CIterator rend();
	const CIterator crbegin() const;
	const CIterator crend() const;
	CIterator Erase(CIterator & iter);

	std::string & GetBackElement();
	std::string & GetFrontElement();
	std::string const& GetBackElement()const;
	std::string const& GetFrontElement()const;

	void Clear();
	~CStringList();
private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode = nullptr;
	Node * m_lastNode = nullptr;
};

