#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <limits.h>
#include <algorithm>

template<class T>
class Container
{
    private:
        class Node
        {
            public:
                T item;
                Node * next;
                Node(const T&, Node* = nullptr);
                ~Node();
        };

        Node * Front, * Back;
        unsigned int ItemsCounter;

        // Funzioni per la gestione dei nodi della lista

        Node * Clone(Node *);
        static void Erase(Node *);
        Node * Jump(unsigned int) const;
        static bool Equals(Node *, Node *);

        // Gestione del contatore

        void IncreaseCounter(); // O(1)
        void DecreaseCounter(); // O(1)


    public:

        // Costruttori

        Container();
        Container(const Container& list); // Copia profonda
        ~Container();

        // Funzionalità di base per la lista

        T getFront() const;
        T getBack() const;
        T push_front(const T&); // O(1)
        T push_back(const T&); // O(1)
        bool popFront(); // O(1)
        bool popBack(); // O(n)
        bool Remove(const T&); // O(n)
        bool RemoveFromPos(unsigned int); // O(n)
        void Insert(const T&, unsigned int = 0); // O(n)

        // Controlli e Operazioni

        bool isEmpty() const; // O(1)
        unsigned int getCounter() const; // O(1)
        unsigned int lastPos() const; // O(1)
        void ReverseList(); // O(n)
        bool Search(const T&) const; // O(n)
        int SearchPos(const T&) const; // O(n)
        void Swapper(unsigned int, unsigned int); // O(n)
        T Select(unsigned int) const; // O(n)


        // Overloading operatori

        bool operator ==(const Container&) const;
        bool operator !=(const Container&) const;
        Container<T> operator =(const Container&);
        T& operator [](unsigned int) const; // O(n)


        // Classe annidata iteratore costante

        class ConstIterator
        {
            friend class Container<T>;

            private:
                const Node * Ptr;
                unsigned int Pos;
                bool End;
                ConstIterator(Node *, unsigned int =0, bool =false);
            public:
                ConstIterator();
                ~ConstIterator() = default;
                ConstIterator& operator++(); // O(1)
                const T& operator *() const;
                const T* operator ->() const;
                bool operator ==(const ConstIterator &) const;
                bool operator !=(const ConstIterator &) const;
                unsigned int getPos() const; // O(1)
                bool hasEnded() const; // O(1)
        };


        // Metodi di supporto per l'iteratore

        ConstIterator begin() const; // O(1)
        ConstIterator iBeginFrom(unsigned int) const; // O(n)
        ConstIterator end() const; // O(n)

};




// Costruttori e Distruttore di Plist

template<class T>
Container<T>::Container()
    : Front(nullptr), Back(nullptr), ItemsCounter(0)
{ }


template<class T>
Container<T>::Container(const Container& list)
     : Front(Clone(list.Front)),
        ItemsCounter(list.ItemsCounter)
{
    // Front = Clone(list.Front);
    // ItemsCounter = list.ItemsCounter;
}

template<class T>
Container<T>::~Container()
{
    if(Front)
        delete Front;
}

template<class T>
Container<T> Container<T>::operator =(const Container& list)
{
    if(this != &list) // Controllo di sanità
    {
        if(Front)
            delete Front;

        Front = Clone(list.Front);
        ItemsCounter = list.ItemsCounter;
    }

    return *this;
}


// Classe interna - Node

template<class T>
Container<T>::Node::Node(const T& t, Node* n) : item(t), next(n) {}


template<class T>
Container<T>::Node::~Node()
{
    if(next)
        delete next;
}


// Metodi privati per la classe interna

template<class T>
typename Container<T>::Node* Container<T>::Clone(Container<T>::Node* n)
{
    if(!n)
        return nullptr;

    // Caso base 1: lista vuota

    if(!n->next)
        return Back = new Node(n->item);

    // Caso base 2: fine della lista, assegno Back e riporto l'ultimo nodo

    return new Node(n->item, Clone(n->next));

    // Induzione: Creo un nuovo nodo copiando le informazioni dalla lista iniziale
}

template<class T>
void Container<T>::Erase(Container<T>::Node* n)
{
    if(n)
    {
        Erase(n->next);
        delete n;
    }
}


template<class T>
typename Container<T>::Node * Container<T>::Jump(unsigned int i) const
{
    if(isEmpty())
        return nullptr;

    if(i == lastPos())
        return Back;

    Node * curr = Front;
    while(i-- && curr != nullptr)
        curr = curr->next;
    return curr;
}

template<class T>
bool Container<T>::Equals(Container<T>::Node * a, Container<T>::Node * b)
{
    if(!a && !b) return true;
    if(!a || !b) return false;

    return a->item == b->item && Equals(a->next,b->next);
}


// Metodi pubblici di Plist

template<class T>
bool Container<T>::isEmpty() const
{
    return ItemsCounter == 0;
}


template<class T>
unsigned int Container<T>::getCounter() const
{
    return ItemsCounter;
}

template<class T>
unsigned int Container<T>::lastPos() const
{
    return ItemsCounter-1;
}

template<class T>
void Container<T>::IncreaseCounter()
{
    ItemsCounter++;
}

template<class T>
void Container<T>::DecreaseCounter()
{
    if(!this->isEmpty())
        ItemsCounter--;
}

template<class T>
T Container<T>::getFront() const
{
    return Front->item;
}

template<class T>
T Container<T>::getBack() const
{
    return Back->item;
}

template<class T>
T Container<T>::push_front(const T & item) // Problema
{
    if(this->isEmpty())
    {
        Front = Back = new Node(item);
    }
    else
    {
        Front = new Node(item, Front);
    }

    IncreaseCounter();
    return item;
}

template<class T>
T Container<T>::push_back(const T & item)
{
    if(this->isEmpty())
    {
        Front = Back = new Node(item);
    }
    else
    {
        Back->next = new Node(item);
        Back = Back->next;
    }

    IncreaseCounter();
    return item;
}


template<class T>
void Container<T>::Insert(const T& elem, unsigned int i)
{
    if(i > ItemsCounter)
        return;

    if(i == 0)
    {
        pushFront(elem);
        return;
    }

    if(i == ItemsCounter)
    {
        pushBack(elem);
        return;
    }

    Node * prev = this->Jump(i-1);
    prev->next = new Node(elem, prev->next);

    IncreaseCounter();

}


template<class T>
bool Container<T>::Remove(const T& elem)
{
    if(this->isEmpty())
        return false;

    // La lista non è vuota

    if (Front->item == elem)
        return popFront();

    Node * prev = Front;

    // La lista ha più di un elemento

    while(prev->next != Back && prev->next->item != elem)
         prev = prev->next;

    // Prev è l'elemento precedente a quello da cancellare e prima della fine della lista

    if(prev->next == Back)
    {
        delete prev->next;
        Back = prev;
        Back->next = nullptr;
    }
    else
    {
        // Prev non è il penultimo elemento di tutta la lista

        Node * succ = prev->next->next;

        // Succ è l'elemento successivo a quello da cancellare

        prev->next->next = nullptr;
        delete prev->next;

        // Prev-next è l'elemento che è stato cancellato

        prev->next = succ;

        // La lista viene riagganciata meno l'elemento elem ricercato
    }

    DecreaseCounter();
    return true;
}

template<class T>
bool Container<T>::RemoveFromPos(unsigned int i)
{
    if(this->isEmpty() || this->lastPos() < i)
        return false;

    if(i == 0)
        return popFront();

    if(i == lastPos())
        return popBack();

    return Remove(Select(i));
}


template<class T>
bool Container<T>::popFront()
{
    if(!this->isEmpty())
    {
        if(Front == Back)
        {
            delete Front;
            Front = Back = nullptr;
        }
        else
        {
            Node * TempHead = Front;
            Front = TempHead->next;
            TempHead->next = nullptr;
            delete TempHead;
        }
        DecreaseCounter();
        return true;
    }
    return false;
}


template<class T>
bool Container<T>::popBack()
{
    if(!this->isEmpty())
    {
        if(Front == Back)
        {
            delete Front;
            Front = Back = nullptr;
            DecreaseCounter();
            return true;
        }
        else
        {
            return this->Remove(Back->item);
        }
    }
    return false;
}


template<class T>
bool Container<T>::Search(const T& elem) const
{
    if(this->isEmpty())
        return false;

    if(Front->item == elem || Back->item == elem)
        return true;

    // Caso migliore O(1): lo trovo come primo / ultimo elemento o la lista è vuota

    Node * curr = Front->next;

    while(curr->next != nullptr && curr->item != elem)
         curr = curr->next;

    if(curr->item == elem)
        return true;
    else
        return false;

    // Caso peggiore O(n): sono arrivato alla fine della lista, senza risultati oppure ho trovato il risultato
}

template<class T>
int Container<T>::SearchPos(const T& elem) const
{
    if(this->isEmpty())
        return -1;

    if(Front->item == elem)
        return 0;

    if(Back->item == elem)
        return ItemsCounter-1;

    // Caso migliore O(1): lo trovo come primo od ultimo elemento o la lista è vuota

    unsigned int i = 0;
    Node * curr = Front->next;

    for( ; curr->next != nullptr && curr->item != elem; i++)
         curr = curr->next;

    if(curr->item == elem)
        return i;
    else
        return -1;

    // Caso peggiore O(n): sono arrivato alla fine della lista, senza risultati oppure ho trovato il risultato
}


template<class T>
void Container<T>::Swapper(unsigned int i, unsigned int j)
{
    if(i == j)
        return;

    if(i > ItemsCounter || j > ItemsCounter)
        return;

    Node * a = Jump(i);
    Node * b = Jump(j);
    T it = a->item;
    a->item = b->item;
    b->item = it;
}

template<class T>
T Container<T>::Select(unsigned int i) const
{
    return Jump(i)->item;
}


template<class T>
void Container<T>::ReverseList()
{
    Node * curr = Front;
    Node * prev = nullptr, * succ = nullptr;

    // prev, curr e succ sono 3 puntatori che si sposteranno lungo la lista

    Back = Front;

    // Sistemo subito il puntatore Back che punterà a Front

    while (curr != nullptr)
    {
        succ = curr->next;

        // Succ punterà all'elemento successivo di curr

        curr->next = prev;

        // L'elemento successivo a curr diventa quello che lo precede

        prev = curr;
        curr = succ;

        // Muovo prev e curr avanti di uno
    }

    // Ottengo una lista riordinata al contrario

    Front = prev;
    Back->next = nullptr;

    // Riassegno Front all'ultimo elemento della lista e sistemo il Back
}


template<class T>
bool Container<T>::operator ==(const Container & list) const
{
    return Equals(Front, list.Front) && ItemsCounter == list.ItemsCounter;
}

template<class T>
bool Container<T>::operator !=(const Container & list) const
{
    return !(*this == list);
}

template<class T>
T& Container<T>::operator [](unsigned int i) const
{
    return Jump(i)->item;
}


// Implementazione classe annidata iteratore costante

template<class T>
Container<T>::ConstIterator::ConstIterator(Node * n, unsigned int p, bool e)
    : Ptr(n), Pos(p), End(e) { }

template<class T>
Container<T>::ConstIterator::ConstIterator()
    : Ptr(nullptr), Pos(0), End(false) { }


template<class T>
unsigned int Container<T>::ConstIterator::getPos() const
{
    return Pos;
}

template<class T>
bool Container<T>::ConstIterator::hasEnded() const
{
    return End;
}

template<class T>
typename Container<T>::ConstIterator& Container<T>::ConstIterator::operator ++()
{
    if(!End)
    {
        if(Ptr->next == nullptr)
        {
            End = true;
        }
        else
        {
            Ptr = Ptr->next;
        }

        Pos++;
    }

    return *this;
}

template<class T>
const T& Container<T>::ConstIterator::operator *() const
{
    return Ptr->item;
}


template<class T>
const T* Container<T>::ConstIterator::operator ->() const
{
    return &(Ptr->item);
}


template<class T>
bool Container<T>::ConstIterator::operator ==(const ConstIterator& ptd) const
{
    return Ptr == ptd.Ptr;
}

template<class T>
bool Container<T>::ConstIterator::operator !=(const ConstIterator& ptd) const
{
    return Ptr != ptd.Ptr;
}


// Implementazione dei metodi di supporto all'iteratore

template<class T>
typename Container<T>::ConstIterator Container<T>::begin() const
{
    return ConstIterator(Jump(0), 0, isEmpty());
}

template<class T>
typename Container<T>::ConstIterator Container<T>::iBeginFrom(unsigned int i) const
{
    if(i > lastPos())
       i = lastPos();

    return ConstIterator(Jump(i), i, i == lastPos() ? true : false);
}

template<class T>
typename Container<T>::ConstIterator Container<T>::end() const
{
    return ConstIterator(Jump(lastPos()), lastPos(), true);
}


#endif /* CONTAINER_H */
