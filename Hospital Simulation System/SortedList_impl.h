#ifndef SORTED_LIST_IMPL_H
#define SORTED_LIST_IMPL_H

template<class T>
SortedListNode<T>::SortedListNode(T* itemIn,
                                  SortedListNode* nextNodeIn,
                                  SortedListNode* prevNodeIn)
    : item(itemIn)
    , next(nextNodeIn)
    , prev(prevNodeIn)
{}

template<class T>
SortedList<T>::SortedList()
    : head(NULL)
    , back(NULL)
{}

template<class T>
SortedList<T>::SortedList(const SortedList& other)
    : head(NULL)
    , back(NULL)
{
     
}

template<class T>
SortedList<T>& SortedList<T>::operator=(const SortedList& other)
{
     
    return *this;
}

template<class T>
SortedList<T>::~SortedList()
{
     
}

template<class T>
void SortedList<T>::InsertItem(T* i)
{
     
}

template<class T>
void SortedList<T>::InsertItemPrior(T* i)
{
     
}

template<class T>
T* SortedList<T>::RemoveFirstItem()
{
     
    return NULL;
}

template<class T>
T* SortedList<T>::RemoveFirstItem(int priority)
{
     
    return NULL;
}

template<class T>
T* SortedList<T>::RemoveLastItem(int priority)
{
     
    return NULL;
}

template<class T>
const T* SortedList<T>::FirstItem() const
{
    return (head) ? head->item : NULL;
}

template<class T>
const T* SortedList<T>::LastItem() const
{
    return (back) ? back->item : NULL;
}

template<class T>
bool SortedList<T>::IsEmpty() const
{
    return head == NULL;
}

template<class T>
void SortedList<T>::ChangePriorityOf(int priority, int newPriority)
{
     
}

template<class T>
void SortedList<T>::Split(SortedList& listLeft,
                          SortedList& listRight,
                          int priority)
{
    assert(listLeft.head == NULL);
    assert(listRight.head == NULL);

     
}

template<class T>
SortedList<T> SortedList<T>::Merge(const SortedList& list0,
                                   const SortedList& list1)
{
    
   return SortedList<T>();
}

#endif