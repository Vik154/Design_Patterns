/* Паттерн "Шаблонный метод" (Template Method) */

/* Паттерн Template Method определяет основу алгоритма и позволяет подклассам 
 * изменить некоторые шаги этого алгоритма без изменения его общей структуры.
 * Базовый класс определяет шаги алгоритма с помощью абстрактных операций,
 * а производные классы их реализуют.
 */

#pragma once
#include <iostream>
#include <string>

 // Концепция паттерна "Шаблонный метод"
namespace Сonception {
    /* AbstractClass: определяет шаблонный метод TemplateMethod(), который реализует алгоритм.
     * Алгоритм может состоять из последовательности вызовов других методов, часть из которых
     * может быть абстрактными и должны быть переопределены в классах-наследниках.
     * При этом сам метод TemplateMethod(), представляющий структуру алгоритма,
     * переопределяться не должен.
    */
    class AbstractClass abstract {
    public:
        void TemplateMethod() {
            Operation1();
            Operation2();
        }
        virtual void Operation1() = 0;
        virtual void Operation2() = 0;
    };

    /* ConcreteClass: подкласс, который может переопределять различные методы родительского класса. */
    class ConcreteClass : public AbstractClass {
    public:
        void Operation1() override { }
        void Operation2() override { }
    };
}

//-----------------------------------------------------------
// Реализация паттерна "Шаблонный метод"
//-----------------------------------------------------------
namespace Behavioral {

    class Pizza {
    public:
        Pizza(std::string description) : m_description(description) {};
        virtual ~Pizza() {};
        /* Шаблонный метод */
        void Prepare() {
            std::cout << "Preparing a " << m_description << "...\n";
            PrepareDough();
            AddSauce();
            AddToppings();
            Bake();
            std::cout << "\n";
        }
    protected:
        virtual void PrepareDough() { std::cout << "preparing dough\n"; }
        virtual void AddSauce()     { std::cout << "adding sauce\n"; }
        virtual void Bake()         { std::cout << "bake pizza\n"; }
        virtual void AddToppings() = 0;
    private:
        std::string m_description;
    };

    class CheesePizza final : public Pizza {
    public:
        CheesePizza() : Pizza(std::string("Cheese Pizza")) {};
        ~CheesePizza() {};
    protected:
        virtual void AddToppings() { std::cout << "adding cheese topping\n"; }
    };

    class MeatPizza final: public Pizza {
    public:
        MeatPizza() : Pizza(std::string("Meat Lover's Pizza")) {};
        ~MeatPizza() {}
    protected:
        virtual void AddToppings() {
            std::cout << "adding cheese, pepperoni, sausage and bacon toppings\n";
        }
    };
 
    void test_template() {
        CheesePizza cheesePizza;
        MeatPizza meatLoversPizza;
        cheesePizza.Prepare();
        meatLoversPizza.Prepare();
    }   
}