#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

namespace aisdi
{

template <typename Type>
class LinkedList
{
private:

    struct Node
    {
        Type Itemero;
        Node* prevNode;
        Node* nextNode;
        Node(const Type& Item) :Itemero(Item), prevNode(nullptr), nextNode(nullptr){}
    };
    Node* First;
    Node* Last;
    size_t length;

public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using value_type = Type;
  using pointer = Type*;
  using reference = Type&;
  using const_pointer = const Type*;
  using const_reference = const Type&;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  LinkedList():First(nullptr),Last(nullptr),length(0)
  {}
  Iterator Getnodlast() const
  {return Iterator(*this,Last);}
  void getLast()
  {
    std::cout<<Last->Itemero<<std::endl;
  }
  void getFirst()
  {
    std::cout<<First->Itemero<<std::endl;
  }
  LinkedList(std::initializer_list<Type> l):First(nullptr), Last(nullptr), length(0)
  {
      for(auto ite=l.begin();ite!=l.end();++ite)
      {
        append(*(ite));
      }
  }
  size_t getSize()
  {
    return length;
  }
  LinkedList(const LinkedList& other):First(nullptr), Last(nullptr), length(0)
  {
    for(auto ite=other.begin();ite!=other.end();++ite)
      {
        append(*ite);
      }
  }

  LinkedList(LinkedList&& other): First(other.First),Last(other.Last), length(other.length)
  {
    other.First=nullptr;
    other.Last=nullptr;
    other.length=0;
  }
  bool operator==(const LinkedList& other) const
  {
    if(length!=other.length)return false;
    Node *one, *two;
    one=First;
    two=other.First;
    for(;one!=nullptr && two!=nullptr;one=one->nextNode,two=two->nextNode)
    {
        if(one->Itemero!=two->Itemero)return false;
    }

    return true;
  }
  bool operator!=(const LinkedList& other) const
  {
    if(length!=other.length)return true;
    Node *one, *two;
    one=First;
    two=other.First;
    for(;one!=nullptr && two!=nullptr;one=one->nextNode,two=two->nextNode)

        if(one->Itemero!=two->Itemero)return true;

    return false;
  }
  ~LinkedList()
  {
    Node *act=First;
    Node *tempo;
    while(act!=nullptr)
    {
        tempo=act;
        act=act->nextNode;
        delete tempo;
    }
    First=nullptr;
    Last=nullptr;
  }

  LinkedList& operator=(const LinkedList& other)
  {
        Node *Actual = First;
        Node *Tempo;
        while(Actual!=nullptr)
        {
             Tempo = Actual;
             Actual=Actual->nextNode;
             delete Tempo;
        }
        First=nullptr;
        Last=nullptr;
        length=0;
        for(auto it= other.begin();it!=other.end();++it)
        {
            append(*it);
        }
        return *this;
  }

  LinkedList& operator=(LinkedList&& other)
  {
    Node *Actual = First;
        Node *Tempo;
        while(Actual!=nullptr)
        {
             Tempo = Actual;
             Actual=Actual->nextNode;
             delete Tempo;
        }
        First=other.First;
        Last=other.Last;
        length=other.length;
        other.First=nullptr;
        other.Last=nullptr;
        other.length=0;
        return *this;
  }

  bool isEmpty() const
  {
    return(First==nullptr);
  }

  size_type getSize() const
  {
    return length;
  }

  void append(const Type& item)
  {
    Node* Newt= new Node(item);
     if(length==0)
     {
        First= Newt;
        Last=Newt;
        Newt->nextNode=nullptr;
        Newt->prevNode=nullptr;
     }
     else
     {
        Last->nextNode=Newt;
        Newt->prevNode=Last;
        Newt->nextNode=nullptr;
        Last=Newt;
     }
     length++;
     if(First==nullptr)std::cout<<"Lul ferst jest nullptr"<<std::endl;
  }

  void prepend(const Type& item)
  {
    Node *Newt = new Node(item);
    if(length==0)
    {
        First=Newt;
        Last=Newt;
    }
    else
    {
        First->prevNode=Newt;
        Newt->nextNode=First;
        First=Newt;
    }
    ++length;
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
    if(insertPosition==begin()) prepend(item);
    else if(insertPosition==end()) append(item);
    else
    {
        Node *Newt = new Node(item);
        Node *Tempo = insertPosition.GetNode();
        Newt->nextNode=Tempo;
        Newt->prevNode=Tempo->prevNode;
        Tempo->prevNode->nextNode=Newt;
        Tempo->prevNode=Newt;
        ++length;
    }
  }

  Type popFirst()
  {
        if(length==0) throw std::logic_error("Cannot pop from empty Collection");
        Type Popped = First->Itemero;
        Node *Tempo = First;
        if(length==1)
        {
            First=nullptr;
            Last=nullptr;
        }
        else
        {
            First=First->nextNode;
            First->prevNode=nullptr;
        }
        --length;
        delete Tempo;
        return Popped;
  }

  Type popLast()
  {
        if(length==0) throw std::logic_error("Cannot pop from empty Collection");
        Type Popped = Last->Itemero;
        Node *Tempo = Last;
        if(length==1)
        {
            First=nullptr;
            Last=nullptr;
        }
        else
        {
            Last=Last->prevNode;
            Last->nextNode=nullptr;
        }
        --length;
        delete Tempo;
        return Popped;
  }

  void erase(const const_iterator& possition)
  {
      if(length==0) throw std::out_of_range("Cannot erase from empty Collection");
      if(possition==end()) throw std::out_of_range("Cannot erase nullptr");
      Node *Tempo = possition.GetNode();
      if(length==1)
      {
        First=nullptr;
        Last=nullptr;
      }
      else if(possition==begin())
      {
        First=First->nextNode;
        First->prevNode=nullptr;
      }
      else if(Tempo==Last)
      {
        Last=Last->prevNode;
        Last->nextNode=nullptr;
      }
      else
      {
        Tempo->prevNode->nextNode=Tempo->nextNode;
        Tempo->nextNode->prevNode=Tempo->prevNode;
      }
      delete Tempo;
      --length;

  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {
    if(firstIncluded==lastExcluded)return;
    for( auto it=firstIncluded+1;it!=lastExcluded;++it) erase(it-1);
    erase(lastExcluded-1);
  }

  iterator begin()
  {
    Iterator ite(*this,First);
    return ite;
  }

  iterator end()
  {
    Iterator ite(*this, nullptr);
    return ite;
  }

  const_iterator cbegin() const
  {
    ConstIterator ite(*this,First);
    return ite;
  }

  const_iterator cend() const
  {
    ConstIterator ite(*this, nullptr);
    return ite;
  }

  const_iterator begin() const
  {
    return cbegin();
  }

  const_iterator end() const
  {

    return cend();
  }
};

template <typename Type>
class LinkedList<Type>::ConstIterator
{
  protected:
  const LinkedList<Type> &Lyst;
  Node* point;


public:

  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename LinkedList::value_type;
  using difference_type = typename LinkedList::difference_type;
  using pointer = typename LinkedList::const_pointer;
  using reference = typename LinkedList::const_reference;

  explicit ConstIterator(const LinkedList &List=nullptr, Node *N=nullptr)
  : Lyst(List),point(N)
  {}
    ConstIterator(const ConstIterator& other): Lyst(other.Lyst), point(other.point)
    {}
    Node * GetNode() const
    {
        return point;
    }
  reference operator*() const
  {
    if(*this==Lyst.end())throw std::out_of_range("Iterator wskazuje na end()");
    return point->Itemero;
  }

  ConstIterator& operator++()
  {
    if(*this == Lyst.end())throw std::out_of_range("Cannot increment out of the List");
    point=point->nextNode;
    return *this;
  }

  ConstIterator operator++(int)
  {
    if(*this == Lyst.end())throw std::out_of_range("Cannot increment out of the List");
    auto PreviousPosition = *this;
    point=point->nextNode;
    return PreviousPosition;
  }

  ConstIterator& operator--()
  {
    if(*this == Lyst.begin())throw std::out_of_range("Cannot decrement out of the List");
    else if(*this == Lyst.end())
    {
        point=Lyst.Last;
    }
    else point=point->prevNode;
    return *this;
  }

  ConstIterator operator--(int)
  {
    auto PreviousPosition = *this;
    if(*this == Lyst.begin())throw std::out_of_range("Cannot decrement out of the List");
    else if(*this == Lyst.end()) point=Lyst.Last;
    else point=point->prevNode;
    return PreviousPosition;
  }

  ConstIterator operator+(difference_type d) const
  {
     auto result = *this;
     for(int i=0;i<d;++i)
     {
        result.point=result.point->nextNode;
     }
     return result;
  }

  ConstIterator operator-(difference_type d) const
  {
     auto result = *this;
     if(*this == Lyst.end())
     {
        result.point=result.Lyst.Last;
        --d;
     }
     for(int i=0;i<d;++i)
     {
        result.point=result.point->prevNode;
     }
     return result;
  }

  bool operator==(const ConstIterator& other) const
  {
    if(Lyst!=other.Lyst)std::cout<<"lellelelelelelelelel"<<std::endl;
    return(point == other.point && Lyst == other.Lyst);
  }

  bool operator!=(const ConstIterator& other) const
  {
     return(point!=other.point && Lyst==other.Lyst);
  }
};

template <typename Type>
class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
{
  private:
public:
  using pointer = typename LinkedList::pointer;
  using reference = typename LinkedList::reference;

  explicit Iterator(const LinkedList &Listero, Node* pointy):
  ConstIterator(Listero,pointy)
  {}

  Iterator(const ConstIterator& other)
    : ConstIterator(other)
  {}

  Iterator& operator++()
  {
    ConstIterator::operator++();
    return *this;
  }

  Iterator operator++(int)
  {
    auto result = *this;
    ConstIterator::operator++();
    return result;
  }

  Iterator& operator--()
  {
    ConstIterator::operator--();
    return *this;
  }

  Iterator operator--(int)
  {
    auto result = *this;
    ConstIterator::operator--();
    return result;
  }

  Iterator operator+(difference_type d) const
  {
    return ConstIterator::operator+(d);
  }

  Iterator operator-(difference_type d) const
  {
    return ConstIterator::operator-(d);
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif // AISDI_LINEAR_LINKEDLIST_H
