#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{

template <typename Type>
class Vector
{
private:
  Type *ItemContainer;
  size_t Size;
  size_t Capacity;
   void reallocate()
  {
    Type *tempo=new Type[Capacity];
    size_t oldC =Capacity;
    for(unsigned int i=0;i<Capacity;++i)
    {
        tempo[i]=ItemContainer[i];
    }
    delete[]ItemContainer;
    if(Capacity==0)Capacity=10;
    else Capacity*=1.8;
    ItemContainer=new Type[Capacity];
    for(unsigned int i=0;i<oldC;++i)
    {
        ItemContainer[i]=tempo[i];
    }
    delete[] tempo;
  }
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

  Type& operator[](int Position) const
  {
    return ItemContainer[Position];
  }
  Vector():Size(0),Capacity(10)
  {
    ItemContainer = new Type[Capacity];
  }

  Vector(std::initializer_list<Type> l):Size(l.size()),Capacity(2*l.size())
  {
    ItemContainer=new Type[Capacity];
    int i =0;
    for(auto ite=l.begin(); ite!=l.end();++ite)
    ItemContainer[i++]=*ite;
  }

  Vector(const Vector& other):Size(other.Size), Capacity(other.Capacity)
  {
     ItemContainer= new Type[Capacity];
     for(unsigned int i=0;i<Size;++i)
     {
        ItemContainer[i]=other.ItemContainer[i];
     }
  }

  Vector(Vector&& other):Size(other.Size),Capacity(other.Capacity)
  {
    ItemContainer=new Type[Capacity];
    for(unsigned int i=0;i<Size;++i)
     {
        ItemContainer[i]=other.ItemContainer[i];
     }
     other.ItemContainer = nullptr;
     other.Size=0;
     other.Capacity=0;
  }
    bool operator==(const Vector &other) const
  {
    if(Size!=other.Size || Capacity!=other.Capacity)return false;
    for(unsigned int i =0; i<Size;++i)
    {
        if(ItemContainer[i]!=other.ItemContainer[i]) return false;
    }
    return true;
  }
  ~Vector()
  {
    delete[] ItemContainer;
  }

  Vector& operator=(const Vector& other)
  {
  if(*this==other)return *this;
    Size=other.Size;
    Capacity=other.Capacity;
    delete[] ItemContainer;
    ItemContainer=new Type[Size];
    for(unsigned int i=0;i<Size;++i)
     {
        ItemContainer[i]=other.ItemContainer[i];
     }
     return *this;
  }

  Vector& operator=(Vector&& other)
  {
    Size=other.Size;
    Capacity=other.Capacity;
    delete[] ItemContainer;
    ItemContainer=other.ItemContainer;
    other.ItemContainer=nullptr;
    other.Size=0;
    other.Capacity=0;
    return *this;
  }

  bool isEmpty() const
  {
        return(Size==0);
  }

  size_type getSize() const
  {
    return Size;
  }

  void append(const Type& item)
  {
    if(Size==Capacity)reallocate();
    ItemContainer[Size]=item;
    ++Size;
  }

  void prepend(const Type& item)
  {
    if(Size==Capacity)reallocate();
    for(unsigned int i = Size; i>0 ;--i)
    {
        ItemContainer[i]=ItemContainer[i-1];
    }
    ItemContainer[0]=item;
    ++Size;
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
    if(Size==Capacity)reallocate();
    if(insertPosition==begin())prepend(item);
    else if(insertPosition==end())append(item);
    else
    {
    ++Size;
    auto ite=end()-1;
    while(ite!=insertPosition) *ite=*(--ite);
    *ite=item;
    }
  }

  Type popFirst()
  {
    if(isEmpty()) throw std::logic_error("The Collection is empty!");
    Type Result=ItemContainer[0];
    for(unsigned int i=0;i<getSize()-1;++i)   ItemContainer[i]=ItemContainer[i+1];
    --Size;
    return Result;
  }

  Type popLast()
  {
    if(isEmpty()) throw std::logic_error("The Collection is empty!");
    Type Result=ItemContainer[getSize()-1];
    --Size;
    return Result;
  }

  void erase(const const_iterator& possition)
  {
    if(isEmpty()) throw std::out_of_range("Cannot erase from empty Collection!");
    for(Iterator ite=possition;ite!=end()-1;++ite)  *ite=*(ite+1);
    --Size;
  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {
    if(isEmpty()) throw std::out_of_range("Cannot erase from empty Collection!");
    size_t length= lastExcluded.getPos()-firstIncluded.getPos();
    for(Iterator ite=firstIncluded;ite!=end();++ite)
    {
        if(ite+length==end())break;
        else *(ite)=*(ite+length);
    }
    Size-=length;
  }

  iterator begin()
  {
    Iterator ite(*this, 0);
    return ite;
  }

  iterator end()
  {
    Iterator ite(*this, Size);
    return ite;
  }

  const_iterator cbegin() const
  {
    ConstIterator ite(*this, 0);
    return ite;
  }

  const_iterator cend() const
  {
    ConstIterator ite(*this, Size);
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
class Vector<Type>::ConstIterator
{
protected:
const Vector<Type>& Viktor;
size_t Position;
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename Vector::value_type;
  using difference_type = typename Vector::difference_type;
  using pointer = typename Vector::const_pointer;
  using reference = typename Vector::const_reference;

  explicit ConstIterator(const Vector &Vektor=nullptr, const int position_arg=nullptr):Viktor(Vektor),Position(position_arg)
  {}
  size_t getPos() const
  {
    return Position;
  }
  reference operator*() const
  {
    if(*this==Viktor.end()) throw std::out_of_range("You are out of the Collection");
    return Viktor[Position];
  }
  ConstIterator(const ConstIterator& other):Viktor(other.Viktor),Position(other.Position)
  {
  }
  ConstIterator& operator++()
  {
    if(*this == Viktor.end())throw std::out_of_range("Cannot increment out of the List");
    ++Position;
    return *this;
  }

  ConstIterator operator++(int)
  {
    if(*this == Viktor.end())throw std::out_of_range("Cannot increment out of the List");
    auto Previous= *this;
    ++Position;
    return Previous;
  }

  ConstIterator& operator--()
  {
    if(*this == Viktor.begin())throw std::out_of_range("Cannot decrement out of the List");
    --Position;
    return *this;
  }

  ConstIterator operator--(int)
  {
    if(*this == Viktor.begin())throw std::out_of_range("Cannot decrement out of the List");
    auto Previous= *this;
    --Position;
    return Previous;  }

  ConstIterator operator+(difference_type d) const
  {
    auto result=*this;
    if(Position+d>Viktor.getSize())throw std::out_of_range("Cannot move to the outside the Collection");
    result.Position+=d;
    return result;
  }

  ConstIterator operator-(difference_type d) const
  {
    auto result= *this;
    if(Position-d<0)throw std::out_of_range("Cannot move to the outside of the Collection");
    result.Position-=d;
    return result;
  }

  bool operator==(const ConstIterator& other) const
  {
        if(Viktor==other.Viktor && Position==other.Position) return true;
        return false;
  }

  bool operator!=(const ConstIterator& other) const
  {
    if(Viktor==other.Viktor && Position==other.Position) return false;
    return true;
  }
};

template <typename Type>
class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
{
public:
  using pointer = typename Vector::pointer;
  using reference = typename Vector::reference;

  explicit Iterator(const Vector& Vektor, const int Position_arg): ConstIterator(Vektor,Position_arg)
  {

  }

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

#endif // AISDI_LINEAR_VECTOR_H
