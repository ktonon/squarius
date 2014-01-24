/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef MEMORY_H
#define MEMORY_H

template<class T> void SafeDelete(T*& pVal)
{
    if (pVal)
    {
        delete pVal;
        pVal = NULL;
    }
}

template<class T> void SafeDeleteArray(T*& pVal)
{
    if (pVal)
    {
        delete[] pVal;
        pVal = NULL;
    }
}

template <class T> void SafeDeleteLater(T*& pVal)
{
    if (pVal)
    {
        pVal->deleteLater();
        pVal = NULL;
    }
}

#endif // MEMORY_H
