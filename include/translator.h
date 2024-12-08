// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
// 
// Носков И.А.


#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
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
        pMem = new T[capacity];     // Выделяем память 2 * sz + 1
        if (pMem == nullptr)        // Проверка выделения памяти
            throw runtime_error("failed_to_allocate_memory");
    }
    Mvector(T* arr, size_t size) : sz(size), capacity(2 * size + 1)
    {
        if (arr == nullptr)
            throw ("arr_is_null");
        pMem = new T[capacity];     // Выделяем память 2 * sz + 1
        if (pMem == nullptr)        // Проверка выделения памяти
            throw ("failed_to_allocate_memory");
        copy(arr, arr + size, pMem);
    }
    Mvector(const Mvector& v) {
        sz = v.sz;
        capacity = v.capacity;
        pMem = new T[capacity];     // Выделяем память 2 * sz + 1
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

enum types { numbers, operation, open_bracket, close_bracket, nun};
// Класс 
class Term {
private:
    types type;
public:
    Term(types type) : type(type) {};
    types get_type() const noexcept {
        return type;
    }
};
//Класс число
class Number : public Term {
private:
    double value;
public:
    Number(double value): value(value), Term(numbers) {};
    double get_value() const noexcept {
        return value;
    };
};
//Класс операция
class Operation : public Term {
private:
    int priority;
    char oper;
public:
    Operation(char op = ' ') : oper(op), Term(operation), priority(0) {
        if (op == '*') priority = 2;
        if (op == '/') priority = 2;
        if (op == '+') priority = 1;
        if (op == '-') priority = 1;
    };
    char get_operation() const noexcept {
        return oper;
    };
    int get_priority() const noexcept {
        return priority;
    };
};
//Класс открывающая скобка
class Open_Bracket : public Term {
private:
    char bracket;
public:
    Open_Bracket(): Term(open_bracket), bracket('(') {};
};
//Класс закрывающая скобка
class Close_Bracket : public Term {
private:
    char bracket;
public:
    Close_Bracket(): Term(close_bracket), bracket(')') {};
};

//Класс транслятор 
class translator {
private:
    string expression;          //Строка выражение 
    Mvector<Term*> terms;       //Вектор лексем
    Mvector<Term*> sort_terms;  //Вектор лексем в обратной польской записи
public:
    translator(string str) : expression(str) {};
    void sintaksis_analysis() {         //Перевод строки в набор лексем
        int number_status = 0;
        string n;
        for (int i = 0; i < expression.size(); i++) {
            if (number_status == 0) {
                if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
                    terms.push_back(new Open_Bracket);
                if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']')
                    terms.push_back(new Close_Bracket);
                if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
                    terms.push_back(new Operation(expression[i]));
                if (expression[i] == '0' || expression[i] == '1' || expression[i] == '2' || expression[i] == '3' || expression[i] == '4' || expression[i] == '5' || expression[i] == '6' || expression[i] == '7' || expression[i] == '8' || expression[i] == '9') {
                    number_status++;
                    n += expression[i];
                }
            }
            else {
                if (expression[i] == '.' || expression[i] == '0' || expression[i] == '1' || expression[i] == '2' || expression[i] == '3' || expression[i] == '4' || expression[i] == '5' || expression[i] == '6' || expression[i] == '7' || expression[i] == '8' || expression[i] == '9')
                    n += expression[i];
                if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']') {
                    number_status = 0;
                    terms.push_back(new Number(stod(n)));
                    terms.push_back(new Close_Bracket);
                    n.clear();
                }
                if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
                    number_status = 0;
                    terms.push_back(new Number(stod(n)));
                    terms.push_back(new Operation(expression[i]));
                    n.clear();
                }
                if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
                    throw ("sintax error");
            }
        }
        if(number_status)
            terms.push_back(new Number(stod(n)));
    };
    bool analisys() const {             //Анализ лексем на конечном автомате 
        types pos = nun;
        if (terms[0]->get_type() == operation)
            return 0;
        if (terms[0]->get_type() == numbers)
            pos = numbers;
        if (terms[0]->get_type() == open_bracket)
            pos = open_bracket;
        if (terms[0]->get_type() == close_bracket)
            return 0;
        for (int i = 1; i < terms.size(); i++) {
            switch (terms[i]->get_type()) {
            case operation:
                if (pos == operation || pos == open_bracket)
                    return 0;
                else
                    pos = operation;
                break;
            case numbers:
                if (pos == numbers || pos == close_bracket)
                    return 0;
                else
                    pos = numbers;
                break;
            case open_bracket:
                if (pos == numbers || pos == close_bracket)
                    return 0;
                else
                    pos = open_bracket;
                break;
            case close_bracket:
                if (pos == operation || pos == open_bracket)
                    return 0;
                else
                    pos = close_bracket;
                break;
            default:
                break;
            }
        }
        return true;
    };
    bool checking_brackets() const{             //Проверка скобок
        Mstack<char> stack;
        for (int i = 0; i < expression.length(); i++) {
            if ((expression[i] == '(') || (expression[i] == '[') || (expression[i] == '{'))
                stack.push(expression[i]);

            if (expression[i] == ')') {
                if (stack.empty()) return 0;
                if (stack.top() != '(')
                    return 0;
                stack.pop();
            }
            if (expression[i] == ']') {
                if (stack.empty()) return 0;
                if (stack.top() != '[')
                    return 0;
                stack.pop();
            }
            if (expression[i] == '}') {
                if (stack.empty()) return 0;
                if (stack.top() != '{')
                    return 0;
                stack.pop();
            }
        }
        if (stack.size()) return 0;
        return 1;
    };
    void sort_term() {              //Перевод в обратную польскую запись
        stack<Term*> stack;
        for (int i = 0; i < terms.size(); i++) {
            if (terms[i]->get_type() == numbers)
                sort_terms.push_back(terms[i]);
            if (terms[i]->get_type() == operation) {
                if (stack.empty()) 
                    stack.push(terms[i]);
                else {
                    while (!stack.empty() && (((Operation*)(stack.top()))->get_priority() >= ((Operation*)(terms[i]))->get_priority())) {
                        sort_terms.push_back(stack.top());
                        stack.pop();
                        if (stack.empty()) break;
                    }
                    stack.push(terms[i]);
                }
            }
            if (terms[i]->get_type() == open_bracket) {
                stack.push(terms[i]);
            }
            if (terms[i]->get_type() == close_bracket) {
                while (stack.top()->get_type() != open_bracket) {
                    sort_terms.push_back(stack.top());
                    stack.pop();
                }
                stack.pop();
            }
        }
        while (!stack.empty()) {
            sort_terms.push_back(stack.top());
            stack.pop();
        }
    };
    double computing() {            //Вычисление выражения 
        Mstack<Term*> stack;
        double left_op, right_op;
        for (int i = 0; i < sort_terms.size(); i++) {
            if (sort_terms[i]->get_type() == numbers)
                stack.push(sort_terms[i]);
            if (sort_terms[i]->get_type() == operation) {
                right_op = ((Number*)(stack.top()))->get_value();
                stack.pop();
                left_op = ((Number*)(stack.top()))->get_value();
                stack.pop();
                if (((Operation*)sort_terms[i])->get_operation() == '+')
                    stack.push(new Number(left_op + right_op));
                if (((Operation*)sort_terms[i])->get_operation() == '-')
                    stack.push(new Number(left_op - right_op));
                if (((Operation*)sort_terms[i])->get_operation() == '*')
                    stack.push(new Number(left_op * right_op));
                if (((Operation*)sort_terms[i])->get_operation() == '/')
                    if (right_op != 0)
                        stack.push(new Number(left_op / right_op));
                    else
                        throw ("div_on_zero");
            }
        }
        return ((Number*)stack[0])->get_value();
    };


    double translation() {              //Итоговая функция вычисления ариф. выражения
        sintaksis_analysis();
	    if (!analisys() || !checking_brackets())
		    throw ("syntax_error");
        sort_term();
        return computing();
    }
    ~translator() {};
};


