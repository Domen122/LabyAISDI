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
public:

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
            std::cout<<"WTF"<<std::endl;

    /*for(auto ite=other.begin();ite!=other.end();++ite)
      {
        std::cout<<"WTF"<<std::endl;
        append(*ite);
      }*/
    (void)other;
    //throw std::runtime_error("TODO");
  }

  LinkedList(LinkedList&& other)
  {
    (void)other;
    throw std::runtime_error("TODO");
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
  {}

  LinkedList& operator=(const LinkedList& other)
  {
    (void)other;
    throw std::runtime_error("TODO");
  }

  LinkedList& operator=(LinkedList&& other)
  {
    (void)other;
    throw std::runtime_error("TODO");
  }

  bool isEmpty() const
  {
    return(First==nullptr);
    //throw std::runtime_error("TODO");
  }

  size_type getSize() const
  {
    throw std::runtime_error("TODO");
  }

  void append(const Type& item)
  {
    //std::cout<<length<<" ";


    Node* Newt= new Node(item);
     if(length==0)
     {
        //std::cout<<"Pierwszy ele "<<item<<std::endl;
        First= Newt;
        Last=Newt;
        //Newt->nextNode=nullptr;
       // Newt->prevNode=nullptr;
     }
     else
     {
        //std::cout<<"NiePierwszy ele "<<item<<std::endl;
        Last->nextNode=Newt;
        Newt->prevNode=Last;
        Newt->nextNode=nullptr;
        Last=Newt;
     }
     length++;
     if(First==nullptr)std::cout<<"Lul ferst jest nullptr"<<std::endl;
     //std::cout<<"Po appendzie "<<length<<std::endl;
    //(void)item;
    //throw std::runtime_error("TODO");
  }

  void prepend(const Type& item)
  {
    (void)item;
    throw std::runtime_error("TODO");
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
    (void)insertPosition;
    (void)item;
    throw std::runtime_error("TODO");
  }

  Type popFirst()
  {
    throw std::runtime_error("TODO");
  }

  Type popLast()
  {
    throw std::runtime_error("TODO");
  }

  void erase(const const_iterator& possition)
  {
    (void)possition;
    throw std::runtime_error("TODO");
  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {
    (void)firstIncluded;
    (void)lastExcluded;
    throw std::runtime_error("TODO");
  }

  iterator begin()
  {
    Iterator ite(*this,First);
    return ite;
    //throw std::runtime_error("TODO");
  }

  iterator end()
  {
    Iterator ite(*this, nullptr);
    return ite;
    //throw std::runtime_error("TODO");
  }

  const_iterator cbegin() const
  {
    ConstIterator ite(*this,First);
    return ite;
    //throw std::runtime_error("TODO");
  }

  const_iterator cend() const
  {
    ConstIterator ite(*this, nullptr);
    return ite;
    //throw std::runtime_error("TODO");
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
  public:
  const LinkedList<Type> Lyst;
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
  reference operator*() const
  {
    return point->Itemero;
    //throw std::runtime_error("TODO");
  }

  ConstIterator& operator++()
  {
    if(*this == Lyst.end())throw std::out_of_range("Cannot increment out of the List");
    point=point->nextNode;
    return *this;
    //throw std::runtime_error("TODO");
  }

  ConstIterator operator++(int)
  {
    if(*this == Lyst.end())throw std::out_of_range("Cannot increment out of the List");
    auto PreviousPosition = *this;
    point=point->nextNode;
    return PreviousPosition;
    //throw std::runtime_error("TODO");
  }

  ConstIterator& operator--()
  {
    //if(*this == Lyst.begin())throw std::out_of_range("Cannot decrement out of the List");
   /* else*/ if(*this == Lyst.end())
    {
        point=Lyst.Last;
    }
    else point=point->prevNode;
    return *this;
    //throw std::runtime_error("TODO");
  }

  ConstIterator operator--(int)
  {
    auto PreviousPosition = *this;
    if(*this == Lyst.begin())throw std::out_of_range("Cannot decrement out of the List");
    else if(*this == Lyst.end()) point=Lyst.Last;
    else point=point->prevNode;
    return PreviousPosition;
    //throw std::runtime_error("TODO");
  }

  ConstIterator operator+(difference_type d) const
  {
    (void)d;
    throw std::runtime_error("TODO");
  }

  ConstIterator operator-(difference_type d) const
  {
    (void)d;
    throw std::runtime_error("TODO");
  }

  bool operator==(const ConstIterator& other) const
  {
    if(Lyst!=other.Lyst)std::cout<<"lellelelelelelelelel"<<std::endl;
    return(point == other.point && Lyst == other.Lyst);
    //throw std::runtime_error("TODO");
  }

  bool operator!=(const ConstIterator& other) const
  {
     return(point!=other.point && Lyst==other.Lyst);
    //throw std::runtime_error("TODO");
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
