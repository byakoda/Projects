 #ifndef FCFS_LIST_IMPL_H
#define FCFS_LIST_IMPL_H

template<class T>
FCFSNode<T>:: FCFSNode(const T& t, FCFSNode* node)
    : item(t)
    , next(node)
{}

// ============================ //
template<class T>
FCFSList<T>::FCFSList()
    : head(NULL)
{
    // Using a dummy node
    head = new FCFSNode<T>(T());
}

template<class T>
FCFSList<T>::FCFSList(const FCFSList& other)
{
    head = new FCFSNode<T>(T());

    FCFSNode<T>* current = head;
    FCFSNode<T>* guard = other.head->next;

    while (guard) {
        current->next = new FCFSNode<T>(guard->item);
        guard = guard->next;
        current = current->next;
    }
}

template<class T>
FCFSList<T>& FCFSList<T>::operator=(const FCFSList& other)
{
    if (this == &other) return *this;

    FCFSNode<T>* to_delete = NULL;
    for (FCFSNode<T>* temp = head; temp != NULL; ) {
        to_delete = temp;
        temp = temp->next;
        delete to_delete;
    }

    head = new FCFSNode<T>(T());

    FCFSNode<T>* current = head;
    for (FCFSNode<T>* temp = other.head->next; temp != NULL; temp = temp->next) {
        current->next = new FCFSNode<T>(temp->item);
        current = current->next;
    }

    return *this;
}

template<class T>
FCFSList<T>::~FCFSList()
{
    while(head){
        FCFSNode<T> *guard = head;
        head = head -> next;
        delete guard;
    }
}

template<class T>
void FCFSList<T>::Enqueue(const T& item)
{
    FCFSNode<T> *new_node = new FCFSNode<T>(item);
    FCFSNode<T> *current = head;
    while(current -> next){
        current = current -> next;
    }
    current -> next = new_node;
}

template<class T>
T FCFSList<T>::Dequeue()
{
    if (head->next == NULL) {
        return T();
    }

    FCFSNode<T>* to_delete = head->next;
    T value = to_delete->item;

    if (head->next->next != NULL) {
        head->next = head->next->next;
    } 
    else {
        head->next = NULL;
    }

    delete to_delete;
    return value;
}

template<class T>
bool FCFSList<T>::IsEmpty(){
    bool gedson = false;
    if(head -> next == NULL){
        gedson = true;
    }
    return gedson;
}

#endif