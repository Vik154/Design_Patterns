/* Паттерн Посредник (Mediator) */
/* Источник - https://ru.wikipedia.org/wiki/%D0%9F%D0%BE%D1%81%D1%80%D0%B5%D0%B4%D0%BD%D0%B8%D0%BA_(%D1%88%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD_%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)#%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D1%80_%D0%BD%D0%B0_C++и др. */

/* Посредник – это поведенческий паттерн, который упрощает коммуникацию между компонентами системы.
 * Посредник убирает прямые связи между отдельными компонентами, заставляя их общаться друг
 * с другом через себя.
 */

#pragma once
#include <iostream>
#include <string>

//--------------------------------------------------------------
// Концепция и Реализация паттерна "Посредник"
//--------------------------------------------------------------
namespace Behavioral {

    class Colleague;
    class Mediator;
    class ConcreteMediator;
    class ConcreteColleague1;
    class ConcreteColleague2;

    class Mediator abstract {
    public:
        virtual void Send(std::string const& message, Colleague* colleague) const = 0;
    };

    class Colleague {
    protected:
        Mediator* mediator_;
    public:
        explicit Colleague(Mediator* mediator) :mediator_(mediator) { }
    };

    class ConcreteColleague1 :public Colleague {
    public:
        explicit ConcreteColleague1(Mediator* mediator) : Colleague(mediator) { }

        void Send(std::string const& message) {
            mediator_->Send(message, this);
        }
        void Notify(std::string const& message) {
            std::cout << "Colleague1 gets message '" << message << "'" << std::endl;
        }
    };

    class ConcreteColleague2 :public Colleague {
    public:
        explicit ConcreteColleague2(Mediator* mediator) : Colleague(mediator) { }

        void Send(std::string const& message) {
            mediator_->Send(message, this);
        }
        void Notify(std::string const& message) {
            std::cout << "Colleague2 gets message '" << message << "'" << std::endl;
        }
    };

    class ConcreteMediator : public Mediator {
    protected:
        ConcreteColleague1* m_Colleague1;
        ConcreteColleague2* m_Colleague2;
    public:
        void SetColleague1(ConcreteColleague1* c) {
            m_Colleague1 = c;
        }
        void SetColleague2(ConcreteColleague2* c) {
            m_Colleague2 = c;
        }
        virtual void Send(std::string const& message, Colleague* colleague) const {
            if (colleague == m_Colleague1) {
                m_Colleague2->Notify(message);
            }
            else if (colleague == m_Colleague2) {
                m_Colleague1->Notify(message);
            }
        }
    };

    void test_mediator() {
        ConcreteMediator m;
        ConcreteColleague1 c1(&m);
        ConcreteColleague2 c2(&m);
        m.SetColleague1(&c1);
        m.SetColleague2(&c2);
        c1.Send("How are you?");
        c2.Send("Fine, thanks");
    }
}