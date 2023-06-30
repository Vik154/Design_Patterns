/* Паттерн "Стратегия" (Strategy) */

#pragma once
#include <memory>
#include <iostream>
#include <algorithm>
#include <string>

// Стратегия – это поведенческий паттерн, выносит набор алгоритмов
// в собственные классы и делает их взаимозаменимыми.

namespace Сonception {

    class Strategy {
    public:
        virtual ~Strategy() { /* ... */ }
        virtual void algorithmInterface() = 0;
    };

    class ConcreteStrategyA : public Strategy {
    public:
        ~ConcreteStrategyA() { /* ... */ }
        void algorithmInterface() {
            std::cout << "Concrete Strategy A \n";
        }
    };

    class ConcreteStrategyB : public Strategy {
    public:
        ~ConcreteStrategyB() { /* ... */ }
        void algorithmInterface() {
            std::cout << "Concrete Strategy B \n";
        }
    };

    class ConcreteStrategyC : public Strategy {
    public:
        ~ConcreteStrategyC() { /* ... */ }
        void algorithmInterface() {
            std::cout << "Concrete Strategy C \n";
        }
    };

    class Context {
    public:
        Context(Strategy* const s) : strategy(s) {}

        ~Context() {
            delete strategy;
        }
        void contextInterface() {
            strategy->algorithmInterface();
        }
    private:
        Strategy* strategy;
    };

    void run() {
        Context context(new ConcreteStrategyA());
        context.contextInterface();

        Context context1(new ConcreteStrategyB());
        context1.contextInterface();

        Context context2(new ConcreteStrategyC());
        context2.contextInterface();
    }
}

//-----------------------------------------------------------
// Реализация паттерна "Стратегия"
//-----------------------------------------------------------
namespace Behavioral {

    using std::string;
    using std::sort;
    using std::sort_heap;
    using std::make_heap;
    using std::cout;
    using std::unique_ptr;
    using std::make_unique;
    
    class ISorting abstract {
    public:
        virtual ~ISorting() {}
        virtual void isort(string& str) = 0;
        virtual void ishow(string& str) = 0;
        virtual const string& get_name() = 0;
    };

    class QuickSort : public ISorting {
    public:
        void isort(string& str) override {
            sort(str.begin(), str.end());
        }
        void ishow(string& str) override {
            cout << "Result: " << str << '\n';
        }
        const string& get_name() override { return name; }
    private:
        const string name = "QuickSort\n";
    };

    class HeapSort : public ISorting {
    public:
        void isort(string& str) override {
            make_heap(str.begin(), str.end());
            sort_heap(str.begin(), str.end());
        }
        void ishow(string& str) override {
            cout << "Result: " << str << '\n';
        }
        const string& get_name() override { return name; }
    private:
        const string name = "HeapSort\n";
    };

    class SortContext final {
    public:
        SortContext(ISorting* typesort) : type_sort(typesort), str("HelloWorld") { }
        void run() {
            cout << "Sort name: " << type_sort->get_name();
            type_sort->isort(str);
            type_sort->ishow(str);
            cout << "----------------------\n";
        }
    private:
        string str;
        ISorting *type_sort;
    };

    void test_strategey() {
        unique_ptr<QuickSort> quick = make_unique<QuickSort>();
        unique_ptr<HeapSort>   heap = make_unique<HeapSort>();
        unique_ptr<SortContext> scontext1 = make_unique<SortContext>(quick.get());
        unique_ptr<SortContext> scontext2 = make_unique<SortContext>(heap.get());
        scontext1->run();
        scontext2->run();
    }
}