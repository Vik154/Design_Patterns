/* Паттерн Посетитель (Visitor) */
/* Источник - https://www.sourcecodeexamples.net/2020/09/c-visitor-pattern-example.html и др. */

/* Паттерн Посетитель (Visitor) позволяет определить операцию для объектов других классов
 * без изменения этих классов. При использовании паттерна Посетитель определяются две иерархии
 * классов: одна для элементов, для которых надо определить новую операцию, и вторая иерархия
 * для посетителей, описывающих данную операцию.
 - Когда использовать данный паттерн?
 - Когда имеется много объектов разнородных классов с разными интерфейсами, и требуется выполнить
 - ряд операций над каждым из этих объектов
 - Когда классам необходимо добавить одинаковый набор операций без изменения этих классов
 - Когда часто добавляются новые операции к классам, при этом общая структура классов стабильна
 - и практически не изменяется
 */

#pragma once
#include <iostream>

 // Концепция паттерна "Посетитель"
namespace Сonception {

    class Element;
    class ConcreteElementA;
    class ConcreteElementB;

    class Visitor {
    public:
        virtual ~Visitor() {}
        virtual void visitElementA(ConcreteElementA* const element) = 0;
        virtual void visitElementB(ConcreteElementB* const element) = 0;
    };

    class ConcreteVisitor1 : public Visitor {
    public:
        ~ConcreteVisitor1() {}
        void visitElementA(ConcreteElementA* const) {
            std::cout << "Concrete Visitor 1: Element A visited." << std::endl;
        }
        void visitElementB(ConcreteElementB* const) {
            std::cout << "Concrete Visitor 1: Element B visited." << std::endl;
        }
    };

    class ConcreteVisitor2 : public Visitor {
    public:
        ~ConcreteVisitor2() {}
        void visitElementA(ConcreteElementA* const) {
            std::cout << "Concrete Visitor 2: Element A visited." << std::endl;
        }
        void visitElementB(ConcreteElementB* const) {
            std::cout << "Concrete Visitor 2: Element B visited." << std::endl;
        }
    };

    class Element {
    public:
        virtual ~Element() {}
        virtual void accept(Visitor& visitor) = 0;
    };

    class ConcreteElementA : public Element {
    public:
        ~ConcreteElementA() {}
        void accept(Visitor& visitor) {
            visitor.visitElementA(this);
        }
    };

    class ConcreteElementB : public Element {
    public:
        ~ConcreteElementB() {}
        void accept(Visitor& visitor) {
            visitor.visitElementB(this);
        }
    };

    void run_visitor() {
        ConcreteElementA elementA;
        ConcreteElementB elementB;
        ConcreteVisitor1 visitor1;
        ConcreteVisitor2 visitor2;
        elementA.accept(visitor1);
        elementA.accept(visitor2);
        elementB.accept(visitor1);
        elementB.accept(visitor2);
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Посетитель"
//--------------------------------------------------------------
namespace Behavioral {

    class Color {
    public:
        virtual void accept(class Visitor*) = 0;
    };

    class Red : public Color {
    public:
        /*virtual*/void accept(Visitor*);
        void eye() {
            cout << "Red::eye\n";
        }
    };

    class Blu : public Color {
    public:
        /*virtual*/void accept(Visitor*);
        void sky() {
            cout << "Blu::sky\n";
        }
    };

    class Visitor {
    public:
        virtual void visit(Red*) = 0;
        virtual void visit(Blu*) = 0;
    };

    class CountVisitor : public Visitor {
    public:
        CountVisitor() {
            m_num_red = m_num_blu = 0;
        }
        /*virtual*/void visit(Red*) {
            ++m_num_red;
        }
        /*virtual*/void visit(Blu*) {
            ++m_num_blu;
        }
        void report_num() {
            cout << "Reds " << m_num_red << ", Blus " << m_num_blu << '\n';
        }
    private:
        int m_num_red, m_num_blu;
    };

    class CallVisitor : public Visitor {
    public:
        /*virtual*/void visit(Red* r) {
            r->eye();
        }
        /*virtual*/void visit(Blu* b) {
            b->sky();
        }
    };

    void Red::accept(Visitor* v) {
        v->visit(this);
    }

    void Blu::accept(Visitor* v) {
        v->visit(this);
    }

    void test_visitor() {
        Color* set[] = {
          new Red, new Blu, new Blu, new Red, new Red, 0
        };

        CountVisitor count_operation;
        CallVisitor call_operation;

        for (int i = 0; set[i]; i++) {
            set[i]->accept(&count_operation);
            set[i]->accept(&call_operation);
        }
        count_operation.report_num();
    }
}