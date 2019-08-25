#ifndef DEEPPTR_H
#define DEEPPTR_H


// Template ausiliario per la gerarchia con distruzione e copia profonda

template<class T>
class DeepPtr
{
    private:
        T* pointed;

    public:

        // Costruttori e distruttore

        DeepPtr(T * = nullptr);
        DeepPtr(const DeepPtr&); // Copia profonda
        ~DeepPtr();

        T* target() const; // alias di operator->

        // Overloading degli operatori

        T& operator *() const;
        T* operator ->() const;

        DeepPtr& operator =(const DeepPtr&);
        bool operator ==(const DeepPtr&) const;
        bool operator !=(const DeepPtr&) const;
};


template<class T>
DeepPtr<T>::DeepPtr(T * item)
    : pointed(item)
{ }


template<class T>
DeepPtr<T>::DeepPtr(const DeepPtr& copy)
    : pointed(copy.pointed == nullptr ? nullptr : (copy.pointed)->clone())
{ }


template<class T>
DeepPtr<T>::~DeepPtr()
{
    if(pointed)
    {
        delete pointed;
    }
}


template<class T>
T* DeepPtr<T>::target() const
{
    return pointed;
}


template<class T>
T* DeepPtr<T>::operator->() const
{
    return pointed;
}


template <class T>
T& DeepPtr<T>::operator*() const
{
    return *pointed;
}


template <class T>
DeepPtr<T>& DeepPtr<T>::operator= (const DeepPtr& deep)
{
    if(this != &deep)
    {
        if(pointed)
        {
            delete pointed;
        }

        pointed = deep.pointed == nullptr ? nullptr : (deep.pointed)->deepClone();
    }

    return *this;
}


template <class T>
bool DeepPtr<T>::operator==(const DeepPtr& deep) const
{
    return *pointed == *(deep.pointed);
}


template <class T>
bool DeepPtr<T>::operator!=(const DeepPtr& deep) const
{
    return *pointed != *(deep.pointed);
}

#endif // DEEPPTR_HPP











/*
template <class T>
class DeepPtr{
private:
    T* p;
public:
    DeepPtr(T* = nullptr);
    DeepPtr(const DeepPtr&);
    DeepPtr& operator=(const DeepPtr&);
    T* operator->() const;
    T& operator*() const;
    ~DeepPtr();                         //distruzione polimorfa
};


template<class T>
DeepPtr<T>::DeepPtr(T* q): p(q){}

template<class T>
DeepPtr<T>::DeepPtr(const DeepPtr& dp): p(dp.p!=nullptr?dp.p->clone():nullptr){}

template<class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& dp){
    if(this!=&dp){
        if(p) delete p;
        p = (dp.p!=nullptr?(dp.p)->clone():nullptr);
    }
    return *this;
}

template<class T>
T* DeepPtr<T>::operator->() const{
    return p;
}

template<class T>
T& DeepPtr<T>::operator*() const{
    return *p;
}

template<class T>
DeepPtr<T>::~DeepPtr(){ if(p) delete p; }

#endif // DEEPPTR_H
*/
