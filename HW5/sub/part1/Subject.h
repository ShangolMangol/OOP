#ifndef HW5_SUBJECTS_H
#define HW5_SUBJECTS_H

#include <vector>
#include "Observer.h"
#include "OOP5EventException.h"

template<typename T>
class Subject
{
public:
    Subject() = default;

    void notify(const T& value)
    {
        for(int i = 0; i < mObservers.size(); i++)
        {
            mObservers[i]->handleEvent(value);
        }
    }

    void addObserver(Observer<T>& item)
    {
        if(isContain(item))
            throw ObserverAlreadyKnownToSubject();

        mObservers.push_back(&item);
    }
    void removeObserver(Observer<T>& item)
    {
        int index = getIndex(item);
        if(index == NOT_FOUND)
            throw ObserverUnknownToSubject();

        mObservers.erase(mObservers.begin() + index);
    }

    Subject<T>& operator+=(Observer<T>& item)
    {
        addObserver(item);
        return *this;
    }

    Subject<T>& operator-=(Observer<T>& item)
    {
        removeObserver(item);
        return *this;
    }

    Subject<T>& operator()(const T& item)
    {
        notify(item);
        return *this;
    }

private:
    static const int NOT_FOUND = -1;

    std::vector<Observer<T>*> mObservers;

    int getIndex(Observer<T>& item)
    {

        for(int i = 0; i < mObservers.size(); i++)
        {
            if(mObservers[i] == &item)
                return i;
        }

        return NOT_FOUND;
    }

    bool isContain(Observer<T>& item)
    {
        return getIndex(item) != NOT_FOUND;
    }
};


#endif //HW5_SUBJECTS_H
