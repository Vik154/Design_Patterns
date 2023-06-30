/* Паттерн "Строитель" (Builder) */
// Строитель – это порождающий паттерн проектирования, который позволяет создавать объекты пошагово.
// Строитель позволяет производить различные продукты, используя один и тот же процесс строительства.

#pragma once
#include <iostream>
#include <memory>
#include <string>

// Концепция паттерна "Строитель"
namespace Сonception {
    
    // Класс - продукт
    class Product {
    public:
        int part1; // часть 1
        int part2; // часть 2
    };

    // Класс Builder определяет интерфейс конструирования продукта по частям;
    class Builder {
    public:
        virtual void CreateProduct() { }
        virtual void BuildPart1(int part1) { }
        virtual void BuildPart2(int part2) { }
        virtual Product* GetResult() { return nullptr; }
    };

    // Конкретный строитель, который создает только известный ему объект класса Product
    class ConcreteBuilder : public Builder {
    private:
        Product* currentBuilder;
    public:
        ConcreteBuilder() {
            currentBuilder = nullptr;
        }
        /* Реализация виртуальных методов */
        virtual void CreateProduct() { currentBuilder = new Product(); }
        
        // Построить часть 1
        virtual void BuildPart1(int part1) { currentBuilder->part1 = part1; }

        // Построить часть 2
        virtual void BuildPart2(int part2) { currentBuilder->part2 = part2; }

        // Метод, возвращающий продукт
        virtual Product* GetResult() { return currentBuilder; }

        ~ConcreteBuilder() {
            if (currentBuilder != nullptr)
                delete currentBuilder;
        }
    };

    // Класс - распорядитель
    class Director {
    public:
        // Метод, конструирующий части
        void Construct(Builder& builder) {
            builder.CreateProduct();       // 1. Создать продукт
            builder.BuildPart1(25);        // 2. Построить часть 1
            builder.BuildPart2(777);       // 3. Построить часть 2
        }
    };
}



/* Реализация паттерна */
namespace Creational {

    using std::unique_ptr;
    using std::make_unique;
    using std::string;
    using std::cout;

    // Класс - продукт
    class Pizza {
    public:
        void setDough(const string& dough) {
            m_dough = dough;
        }
        void setSauce(const string& sauce) {
            m_sauce = sauce;
        }
        void setTopping(const string& topping) {
            m_topping = topping;
        }
        void open() const {
            cout << "The Pizza have " 
                 << m_dough   << " dough, "
                 << m_sauce   << " sauce, " 
                 << m_topping << " topping.\n";
        }
    private:
        string m_dough, m_sauce, m_topping;
    };

    // Интерфейс строителя
    class PizzaBuilder {
    public:
        virtual ~PizzaBuilder() = default;
        void createNewPizza() { m_pizza = make_unique<Pizza>(); }
        Pizza* getPizza()     { return m_pizza.release(); }
        virtual void buildDough() = 0;
        virtual void buildSauce() = 0;
        virtual void buildTopping() = 0;
    protected:
        unique_ptr<Pizza> m_pizza;
    };

    // Конкретный строитель
    class HawaiianPizzaBuilder : public PizzaBuilder {
    public:
        ~HawaiianPizzaBuilder() override = default;
        void buildDough() override {
            m_pizza->setDough("Hawaiian dough");
        }
        void buildSauce() override {
            m_pizza->setSauce("Hawaiian sauce");
        }
        void buildTopping() override {
            m_pizza->setTopping("Hawaiian topping");
        }
    };

    // Конкретный строитель
    class SpicyPizzaBuilder : public PizzaBuilder {
    public:
        ~SpicyPizzaBuilder() override = default;
        void buildDough() override {
            m_pizza->setDough("Spicy dough");
        }
        void buildSauce() override {
            m_pizza->setSauce("Spicy sauce");
        }
        void buildTopping() override {
            m_pizza->setTopping("Spicy topping");
        }
    };

    // Класс - Директор
    class Cook {
    public:
        void openPizza() const {
            m_pizzaBuilder->getPizza()->open();
        }
        void createPizza(PizzaBuilder* pizzaBuilder) {
            m_pizzaBuilder = pizzaBuilder;
            m_pizzaBuilder->createNewPizza();
            m_pizzaBuilder->buildDough();
            m_pizzaBuilder->buildSauce();
            m_pizzaBuilder->buildTopping();
        }
    private:
        PizzaBuilder* m_pizzaBuilder;
    };

    void test_builder() {
        Cook cook{};
        HawaiianPizzaBuilder hawaiianPizzaBuilder;
        cook.createPizza(&hawaiianPizzaBuilder);
        cook.openPizza();

        SpicyPizzaBuilder spicyPizzaBuilder;
        cook.createPizza(&spicyPizzaBuilder);
        cook.openPizza();
    }
}