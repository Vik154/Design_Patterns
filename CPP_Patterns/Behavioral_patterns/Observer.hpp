/* Паттерн "Наблюдатель" (Observer) */
/* Наблюдатель – это поведенческий паттерн, который позволяет объектам оповещать 
 * другие объекты об изменениях своего состояния. 
 * При этом наблюдатели могут свободно подписываться и отписываться от этих оповещений.
 * Источник - https://radioprog.ru/post/1501
 * Источник - https://www.youtube.com/watch?v=zWznlNFmczk&list=PLKP3l9fd3KUFONuybgV1kZpY76jwHRdkM&index=19
*/

#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>

// Концепция паттерна "Наблюдатель"
namespace Сonception {

    class IObserver {
    public:
        virtual ~IObserver() {};
        virtual void Update(const std::string& message_from_subject) = 0;
    };

    class ISubject {
    public:
        virtual ~ISubject() {};
        virtual void Attach(IObserver* observer) = 0;
        virtual void Detach(IObserver* observer) = 0;
        virtual void Notify() = 0;
    };

    class Subject : public ISubject {
    public:
        virtual ~Subject() {
            std::cout << "Goodbye, I was the Subject.\n";
        }
        /* Методы управления подпиской. */
        void Attach(IObserver* observer) override {
            list_observer_.push_back(observer);
        }
        void Detach(IObserver* observer) override {
            list_observer_.remove(observer);
        }
        void Notify() override {
            std::list<IObserver*>::iterator iterator = list_observer_.begin();
            HowManyObserver();
            while (iterator != list_observer_.end()) {
                (*iterator)->Update(message_);
                ++iterator;
            }
        }
        void CreateMessage(std::string message = "Empty") {
            this->message_ = message;
            Notify();
        }
        void HowManyObserver() {
            std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
        }
        void SomeBusinessLogic() {
            this->message_ = "change message message";
            Notify();
            std::cout << "I'm about to do some thing important\n";
        }
    private:
        std::list<IObserver*> list_observer_;
        std::string message_;
    };

    class Observer : public IObserver {
    public:
        Observer(Subject& subject) : subject_(subject) {
            this->subject_.Attach(this);
            std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
            this->number_ = Observer::static_number_;
        }
        virtual ~Observer() {
            std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
        }

        void Update(const std::string& message_from_subject) override {
            message_from_subject_ = message_from_subject;
            PrintInfo();
        }
        void RemoveMeFromTheList() {
            subject_.Detach(this);
            std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
        }
        void PrintInfo() {
            std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
        }

    private:
        std::string message_from_subject_;
        Subject& subject_;
        static int static_number_;
        int number_;
    };

    int Observer::static_number_ = 0;

    void ClientCode() {
        Subject* subject = new Subject;
        Observer* observer1 = new Observer(*subject);
        Observer* observer2 = new Observer(*subject);
        Observer* observer3 = new Observer(*subject);
        Observer* observer4;
        Observer* observer5;

        subject->CreateMessage("Hello World! :D");
        observer3->RemoveMeFromTheList();

        subject->CreateMessage("The weather is hot today! :p");
        observer4 = new Observer(*subject);

        observer2->RemoveMeFromTheList();
        observer5 = new Observer(*subject);

        subject->CreateMessage("My new car is great! ;)");
        observer5->RemoveMeFromTheList();

        observer4->RemoveMeFromTheList();
        observer1->RemoveMeFromTheList();

        delete observer5;
        delete observer4;
        delete observer3;
        delete observer2;
        delete observer1;
        delete subject;
    }

    void run2() {
        ClientCode();
    }
}

//-----------------------------------------------------------
// Реализация паттерна "Наблюдатель"
//-----------------------------------------------------------
namespace Behavioral {

    using std::vector;
    using std::string;
    using std::cout;

    class IObserver abstract {
    public:
        virtual ~IObserver() {};
        virtual void update(double p) = 0;
    };

    class IObservable abstract {
    public:
        virtual ~IObservable() {};
        virtual void add_observer(IObserver* observer) = 0;
        virtual void remove_observer(IObserver* observer) = 0;
        virtual void notify() = 0;
    };

    class Product final : public IObservable {
    private:
        vector<IObserver*> observers;
        double price;
    public:
        Product(const double& pr) : price(pr) {};

        void change_price(double pr) {
            price = pr;
            notify();
        }
        void add_observer(IObserver* observer) override {
            observers.push_back(observer);
        }
        void remove_observer(IObserver* observer) override {
            observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
        }
        void notify() override {
            for (auto obs : observers)
                obs->update(price);
        }
    };

    class Wholesaler final : public IObserver {
    private:
        IObservable* product;
    public:
        Wholesaler(IObservable* obj) : product(obj) {
            obj->add_observer(this);
        }
        void update(double price) override{
            if (price < 300) {
                cout << "Оптовый покупатель закупил товар по цене: " << price << '\n';
                product->remove_observer(this);
            }
        }
    };

    class Buyer final : public IObserver {
    private:
        IObservable* product;
    public:
        Buyer(IObservable* obj) : product(obj) {
            obj->add_observer(this);
        }
        void update(double price) override {
            if (price < 350) {
                cout << "Розничный покупатель закупил товар по цене: " << price << '\n';
                product->remove_observer(this);
            }
        }
    };

    void test_observer() {
        Product*    product   = new Product(500);
        Wholesaler* wholeaser = new Wholesaler(product);
        Buyer*      buyer     = new Buyer(product);

        product->change_price(320);
        product->change_price(280);
    }
}