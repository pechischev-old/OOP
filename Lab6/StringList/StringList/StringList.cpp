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
		unique_ptr<Node> node = nullptr;
		try
		{
			auto node = make_unique<Node>(data, iter.m_node->prev, move(iter.m_node->prev->next));
			++m_size;
		}
		catch (...)
		{
			iter.m_node->prev = move(node.get());
			node->prev->next = move(node);
		}
	}
	
	return CIterator(iter.m_node->prev, this);
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get(), this);
}

CStringList::CIterator CStringList::end()
{
	return CIterator(nullptr, this);
}

const CStringList::CIterator  CStringList::cbegin() const
{
	return CIterator(m_firstNode.get(), this);
}

const CStringList::CIterator  CStringList::cend() const
{
	return CIterator(nullptr, this);
}

CStringList::CIterator CStringList::rbegin()
{
	return CIterator(m_lastNode, this, true);
}

CStringList::CIterator CStringList::rend()
{
	return CIterator(nullptr, this, true);
}

const CStringList::CIterator  CStringList::crbegin() const
{
	return CIterator(m_lastNode, this, true);
}

const CStringList::CIterator  CStringList::crend() const
{
	return CIterator(nullptr, this, true);
}

CStringList::CIterator CStringList::Erase(CIterator & it)
{
	if (m_size == 1)
	{
		Clear();
		return CIterator(nullptr, this);
	}

	if (it == begin())
	{
		it->next->prev = nullptr;
		m_firstNode = move(it->next);
	}
	else if (it->data == GetBackElement())
	{
		it->prev->next = nullptr;
		m_lastNode = move(it->prev);
	}
	else
	{
		it->next->prev = move(it->prev);
		it->prev->next = move(it->next);
	}

	m_size--;	
	return it;
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
	}
	m_firstNode = nullptr;
	m_size = 0;
}

CStringList::~CStringList()
{
	Clear();
}

CStringList::CIterator::CIterator(Node * node, const CStringList * list, bool isReverse)
	: m_node(node)
	, m_list(list)
	, m_isReverse(isReverse)
{
	if (!m_list)
	{
		throw std::invalid_argument("Pointer to list is nullptr");
	}
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

CStringList::CIterator & CStringList::CIterator::operator++()
{
	m_node = (m_isReverse ? m_node->prev : m_node->next.get());
	return *this;
}

CStringList::CIterator & CStringList::CIterator::operator--()
{
	if (!m_node)
	{
		m_node = (m_isReverse ? m_list->m_firstNode.get() : m_list->m_lastNode);
	}
	else
	{
		m_node = (m_isReverse ? m_node->next.get() : m_node->prev);
	}
	return *this;
}

CStringList::Node * CStringList::CIterator::operator->() const
{
	return m_node;
}
