// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
// 
// Носков И.А.

#ifndef __TRANSLATOR_H__
#define __TRANSLATOR_H__

#include <iostream>
using namespace std;

//Вектор
template<typename T>
class Mvector {
protected:
    size_t sz;
    size_t capacity;
    T* pMem;
public:
    Mvector(size_t size = 0) : sz(size), capacity(2 * size + 1)
    {
        pMem = new T[capacity];     //Выделяем память 2 * sz + 1
        if (pMem == nullptr)        // Проверка выделения памяти
            throw ("failed_to_allocate_memory");
    }
    Mvector(T* arr, size_t size) : sz(size), capacity(2 * size + 1)
    {
        if (arr == nullptr)
            throw ("arr_is_null");
        pMem = new T[capacity];     //Выделяем память 2 * sz + 1
        if (pMem == nullptr)        // Проверка выделения памяти
            throw ("failed_to_allocate_memory");
        copy(arr, arr + size, pMem);
    }
    Mvector(const Mvector& v) {
        sz = v.sz;
        capacity = v.capacity;
        pMem = new T[capacity];     //Выделяем память 2 * sz + 1
        if (pMem == nullptr)        // Проверка выделения памяти
            throw ("failed_to_allocate_memory");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = v.pMem[i];
    }
    Mvector(Mvector&& v) noexcept {
        sz = 0;
        pMem = nullptr;
        swap(*this, v);
    }
    ~Mvector() {
        delete[] pMem;
        pMem = nullptr;
    }
    Mvector& operator=(const Mvector& v) {
        if (this == &v) return *this;
        if (sz == v.sz) {
            copy(v.pMem, v.pMem + sz, pMem);
            capacity = v.capacity;
        }
        else {
            sz = v.sz;
            capacity = v.capacity;
            delete[] pMem;
            pMem = new T[capacity];
            if (pMem == nullptr)        // Проверка выделения памяти
                throw ("failed_to_allocate_memory");
            copy(v.pMem, v.pMem + sz, pMem);
        }
        return *this;
    }

    size_t size() const noexcept {
        return sz;
    }

    // индексация
    T& operator[](size_t ind) {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const {
        return pMem[ind];
    }

    // сравнение
    bool operator==(const Mvector& v) const noexcept {
        if (sz != v.sz) return 0;
        for (size_t i = 0; i < sz; i++)
            if (pMem[i] != v.pMem[i]) return 0;
        return 1;
    }
    bool operator!=(const Mvector& v) const noexcept {
        return !(*this == v);
    }
    // операции вектора
    T back() const {
        if (empty())        //Проверка на пустоту
            throw ("null_of_size_vector");
        return pMem[sz - 1];
    }
    size_t _size() const noexcept {
        return sz;
    }
    size_t _capacity() const noexcept {
        return capacity;
    }
    bool full() const {
        if (sz == capacity) return 1;
        else return 0;
    }
    bool empty() const {
        if (sz == 0) return 1;
        else return 0;
    }
    void pop_back() {
        if (!empty())       //Проверка на пустоту
            pMem[sz - 1] = T(0);
        else
            throw ("null_of_size_vector");
        sz--;
    }
    void push_back(T elem) {
        if (!full())        //Проверка на полноту 
            ;
        else
            resize(sz * 2);
        pMem[sz] = elem;
        sz++;
    }
    // Перепаковка
    void resize(size_t size) {
        T* pMem_new = new T[2 * size + 1];
        if (pMem_new != nullptr) {      // Проверка выделения памяти
            copy(pMem, pMem + sz, pMem_new);
            capacity = size * 2 + 1;
            delete[] pMem;
            pMem = pMem_new;
            pMem_new = nullptr;
        }
        else
            throw ("failed_to_allocate_memory");
    }
    void swap(Mvector& left_v, Mvector& right_v) {
        swap(left_v.pMem, right_v.pMem);
        swap(left_v.sz, right_v.sz);
        swap(left_v.capacity, right_v.capacity);
    }
    void erase(size_t index) {
        if (index >= sz)        //Проверка на выход за границу
            throw ("out_of_bounds_index");
        if (!empty()) {         //Проверка на пустоту
            for (int i = index; i < sz - 1; i++)
                pMem[i] = pMem[i + 1];
            pMem[sz - 1] = 0;
            sz--;
        }
        else
            throw ("vector_is_empty!");
    }
};

//Стек
template<typename T>
class Mstack : public Mvector<T> {
private:
    using Mvector<T>::sz;
    using Mvector<T>::capacity;
    using Mvector<T>::pMem;
    using Mvector<T>::pop_back;
    using Mvector<T>::push_back;
    using Mvector<T>::resize;
public:
    Mstack() : Mvector<T>(0) {}
    using Mvector<T>::full;
    using Mvector<T>::empty;
    using Mvector<T>::size;
    using Mvector<T>::_capacity;
    using Mvector<T>::operator[];
    using Mvector<T>::back;

    void pop() {
        pop_back();
    }
    void push(T elem) {
        push_back(elem);
    }
    T top() {
        return back();
    }
};


class translator {
private:
    Mvector<Term> terms;
public:
    translator() {};
    Mvector<Term> fexical_analysis(string str) {};
    bool sintaksis_analysis() {};
    double computing() {};

};

enum types { numbers, operation, open_bracket, close_bracket};
class Term {
private:
    types type;
public:
    types get_type() {};
};
class Number : public Term {
private:
    double value;
public:
    Number(double value) {};
    double get_value() {};
};
class Operation : public Term {
private:
    int priority;
    char oper;
public:
    char get_operation() {};
    int get_priority() {};
};
class Open_Bracket : public Term {
private:
    char bracket;
public:
    Open_Bracket() {};
};
class Close_Bracket : public Term {
    Close_Bracket() {};
};
