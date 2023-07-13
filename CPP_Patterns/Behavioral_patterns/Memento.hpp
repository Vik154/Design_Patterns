/* Паттерн Хранитель (Memento) */
/* Источник - https://www.sourcecodeexamples.net/2020/09/c-memento-pattern-example.html */
/* */

/* Паттерн Хранитель (Memento) позволяет выносить внутреннее состояние объекта за его пределы
 * для последующего возможного восстановления объекта без нарушения принципа инкапсуляции.
 - Когда использовать Memento?
 - Когда нужно сохранить состояние объекта для возможного последующего восстановления
 - Когда сохранение состояния должно проходить без нарушения принципа инкапсуляции
 */

#pragma once
#include <string>
#include <iostream>

 // Концепция паттерна "Хранитель"
namespace Сonception {
    /*
    class Originator {
    private:
        int state;
    public:
        Originator() : state(0) {}

        int getState() { return state; }
        void setState(int state) { state = state; }

        Memento* saveToMemento() {
            return new Memento(state);
        }
        void restoreFromMemento(Memento* m) {
            state = m->getState();
        }
    };

    class Memento {
    private:
        int state;
    public:
        Memento(int state) : state(state) {}

        int getState() {
            return state;
        }
    };

    class Caretaker {
    private:
        Memento* memento;
    public:
        void saveMemento(Memento* m) {
            memento = m;
        }
        Memento* restoreMemento() {
            return memento;
        }
    };
    */
}


//--------------------------------------------------------------
// Реализация паттерна "Хранитель"
//--------------------------------------------------------------
namespace Behavioral {

    class Memento {
    private:
        friend class Originator;

        Memento(const int s) : state(s) {}

        void setState(const int s) {
            state = s;
        }
        int getState() {
            return state;
        }
    private:
        int state;
    };

    class Originator {
    public:
        void setState(const int s) {
            std::cout << "Set state to " << s << "." << std::endl;
            state = s;
        }
        int getState() {
            return state;
        }
        void setMemento(Memento* const m) {
            state = m->getState();
        }
        Memento* createMemento() {
            return new Memento(state);
        }
    private:
        int state;
    };

    class CareTaker {
    public:
        CareTaker(Originator* const o) : originator(o) {}

        ~CareTaker() {
            for (unsigned int i = 0; i < history.size(); i++) {
                delete history.at(i);
            }
            history.clear();
        }
        void save() {
            std::cout << "Save state." << std::endl;
            history.push_back(originator->createMemento());
        }
        void undo() {
            if (history.empty()) {
                std::cout << "Unable to undo state." << std::endl;
                return;
            }
            Memento* m = history.back();
            originator->setMemento(m);
            std::cout << "Undo state." << std::endl;
            history.pop_back();
            delete m;
        }
    private:
        Originator* originator;
        std::vector<Memento*> history;
    };


    void test_memento() {
        Originator* originator = new Originator();
        CareTaker* caretaker = new CareTaker(originator);

        originator->setState(1);
        caretaker->save();

        originator->setState(2);
        caretaker->save();

        originator->setState(3);
        caretaker->undo();

        std::cout << "Actual state is " << originator->getState() << "." << std::endl;

        delete originator;
        delete caretaker;
    }
}