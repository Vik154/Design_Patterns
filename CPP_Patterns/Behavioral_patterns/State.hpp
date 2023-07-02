/* Паттерн Состояние (State) */
/* Состояние – это поведенческий паттерн, позволяющий динамически изменять поведение 
 * объекта при смене его состояния. Поведения, зависящие от состояния, переезжают 
 * в отдельные классы. Первоначальный класс хранит ссылку на один из таких объектов-состояний 
 * и делегирует ему работу.
 */

#pragma once
#include<string>
#include<iostream>

 // Концепция паттерна "Состояние"
namespace Сoncept {

    // State: определяет интерфейс состояния
    class State {
    public:
        virtual ~State() { /* ... */ }
        virtual void handle() = 0;
    };

    // Классы StateA и StateB - конкретные реализации состояний
    class ConcreteStateA : public State {
    public:
        ~ConcreteStateA() { /* ... */ }
        void handle() { std::cout << "State A handled." << std::endl; }
    };

    class ConcreteStateB : public State {
    public:
        ~ConcreteStateB() { /* ... */ }
        void handle() { std::cout << "State B handled." << std::endl; }
    };

    // Context: представляет объект, поведение которого должно динамически изменяться
    // в соответствии с состоянием. Выполнение конкретных действий делегируется объекту состояния
    class Context  {
    public:
        Context() : state() { /* ... */ }
        ~Context() { delete state; }

        void setState(State* const s) {
            if (state)
                delete state;
            state = s;
        }
        void request() {
            state->handle();
        }
    private:
        State* state;
    };

    void client_context_run() {
        Context* context = new Context();
        context->setState(new ConcreteStateA());
        context->request();
        context->setState(new ConcreteStateB());
        context->request();
        delete context;
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Состояние"
//--------------------------------------------------------------
namespace Behavioral {
    
    class State;
    class StateContext;
    class SolidState;
    class LiquidState;
    class GasState;

    class State abstract {
        std::string name;
    public:
        State(const std::string& name) : name(name) {}
        std::string GetName() { return name; }
        virtual void Freeze(StateContext*) = 0;
        virtual void Heat(StateContext*) = 0;
    };

    class StateContext {
    private:
        State* state;
    public:
        StateContext(State* state) : state(state) {}

        void Freeze() {
            std::cout << "Freezing " << state->GetName() << "..." << std::endl;
            state->Freeze(this);
        }
        void Heat() {
            std::cout << "Heating " << state->GetName() << "..." << std::endl;
            state->Heat(this);
        }
        void SetState(State* s) {
            std::cout << "Changing state from " << state->GetName()
                << " to " << s->GetName() << "..." << std::endl;
            delete state;
            state = s;
        }
        State* GetState() {
            return state;
        }
        ~StateContext() {
            delete state;
        }
    };

    class SolidState : public State {
    public:
        SolidState() : State("Solid") {}
        virtual void Freeze(StateContext* state);
        virtual void Heat(StateContext* state);
    };

    class LiquidState : public State {
    public:
        LiquidState() : State("Liquid") {}
        virtual void Freeze(StateContext* state);
        virtual void Heat(StateContext* state);
    };

    class GasState : public State {
    public:
        GasState() : State("Gas") {}
        virtual void Freeze(StateContext* state);
        virtual void Heat(StateContext* state);
    };

    void SolidState::Freeze(StateContext* state) {
        std::cout << "Nothing happens" << std::endl;
    }

    void SolidState::Heat(StateContext* state) {
        state->SetState(new LiquidState());
    }

    void LiquidState::Freeze(StateContext* state) {
        state->SetState(new SolidState());
    }

    void LiquidState::Heat(StateContext* state) {
        state->SetState(new GasState());
    }

    void GasState::Freeze(StateContext* state) {
        state->SetState(new LiquidState());
    }

    void GasState::Heat(StateContext* state) {
        std::cout << "Nothing happens" << std::endl;
    }

    void test_state() {
        StateContext* sc = new StateContext(new SolidState());
        sc->Heat();
        sc->Heat();
        sc->Heat();
        sc->Freeze();
        sc->Freeze();
        sc->Freeze();
        delete sc;
    }
}