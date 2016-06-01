#include "StringList.h"
#include <cassert>
#include <list>


using namespace std;

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::PushBack(const std::string & data)
{
	auto newNode = make_unique<Node>(data, m_lastNode, nullptr);
	Node *newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else // empty list
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

void CStringList::PushFront(const std::string & data)
{
	auto newNode = make_unique<Node>(data, nullptr, nullptr);
	if (!IsEmpty())
	{
		m_firstNode->prev = newNode.get();
		newNode->next = move(m_firstNode);
	}
	else
	{
		m_lastNode = newNode.get();
	}
	m_firstNode = move(newNode);
	++m_size;
}

bool CStringList::IsEmpty() const
{
	return m_firstNode == nullptr;
}

CStringList::CIterator CStringList::Insert(const std::string & data, CIterator & iter)
{
	if (iter.m_node == m_firstNode.get())
	{
		PushFront(data);
	}
	else if (iter == end())
	{
		PushBack(data);
	}
	else
	{
		if (!iter.m_node)
		{
			throw std::invalid_argument("Iterator is not valid");
		}
		auto node = make_unique<Node>(data, iter->prev, move(iter->prev->next));
		iter->prev = move(node.get());
		node->prev->next = move(node);
		++m_size;
	}
	return iter;
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::end()
{
	return CIterator(nullptr);
}

CStringList::CIterator const CStringList::cbegin() const
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator const CStringList::cend() const
{
	return CIterator(nullptr);
}

CStringList::CIterator CStringList::rbegin()
{
	return CIterator(m_lastNode, true);
}

CStringList::CIterator CStringList::rend()
{
	return CIterator(m_firstNode->prev, true);
}

CStringList::CIterator const CStringList::crbegin() const
{
	return CIterator(m_lastNode, true);
}

CStringList::CIterator const CStringList::crend() const
{
	return CIterator(m_firstNode->prev, true);
}

CStringList::CIterator CStringList::Erase(CIterator & iter)
{
	if (m_size == 1)
	{
		Clear();
		return this->end();
	}
	if (iter == begin())
	{
		iter->next->prev = nullptr;
		m_firstNode = move(iter->next);
	}
	else if (iter.m_node == m_lastNode)
	{
		iter->prev->next = nullptr;
		m_lastNode = move(iter->prev);
		iter = m_lastNode->next.get();
	}
	else
	{
		auto next = move(iter.m_node->next);
		auto prev = iter.m_node->prev;
		next->prev = prev;
		prev->next = move(next);
		iter = prev->next.get();
	}

	--m_size;

	return iter;
}

std::string & CStringList::GetBackElement()
{
	assert(m_lastNode);
	return m_lastNode->data;
}

std::string & CStringList::GetFrontElement()
{
	assert(m_firstNode);
	return m_firstNode->data;
}

std::string const & CStringList::GetBackElement() const
{
	assert(m_lastNode);
	return m_lastNode->data;
}

std::string const& CStringList::GetFrontElement()const
{
	assert(m_firstNode);
	return m_firstNode->data;
}

void CStringList::Clear()
{
	while (m_lastNode)
	{
		m_lastNode->next = nullptr;
		m_lastNode = m_lastNode->prev;
		--m_size;
	}
	if (m_size == 0)
	{
		m_firstNode = nullptr;
	}
}

//CStringList::CIterator::CIterator(CIterator const & it)
//	:m_node(node)
//{
//}

CStringList::CIterator::CIterator(Node * node, bool isReverse)
	: m_node(node)
	, m_isReverse(isReverse)
{
}

std::string & CStringList::CIterator::operator*() const
{
	return m_node->data;
}

bool CStringList::CIterator::operator==(CIterator const & other) const
{
	return m_node == other.m_node;
}

bool CStringList::CIterator::operator!=(CIterator const & other) const
{
	return m_node != other.m_node;
}

CStringList::CIterator CStringList::CIterator::operator+(unsigned shift)
{
	return CIterator();
}

CStringList::CIterator & CStringList::CIterator::operator++()
{
	m_node = (m_isReverse ? m_node->prev : m_node->next.get());
	return *this;
}

CStringList::CIterator & CStringList::CIterator::operator--()
{
	m_node = (m_isReverse ? m_node->next.get() : m_node->prev);
	return *this;
}

CStringList::Node * CStringList::CIterator::operator->() const
{
	return m_node;
}
