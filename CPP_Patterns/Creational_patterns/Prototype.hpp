/* Паттерн "Прототип" (Prototype) */
// порождающий паттерн, который позволяет копировать объекты любой 
// сложности без привязки к их конкретным классам.

#pragma once
#include <memory>
#include <iostream>
 
//-----------------------------------------------------------
// Концепция паттерна "Прототип"
// https://riptutorial.com/design-patterns/example/20640/prototype-pattern--cplusplus-
//-----------------------------------------------------------
namespace Сonception {

    class IPrototype abstract {
    public:
        virtual ~IPrototype() = default;

        auto Clone() const { return std::unique_ptr<IPrototype>{ DoClone() }; }
        auto Create() const { return std::unique_ptr<IPrototype>{ DoCreate() }; }
    private:
        virtual IPrototype* DoClone() const = 0;
        virtual IPrototype* DoCreate() const = 0;
    };

    class A : public IPrototype {
    public:
        auto Clone() const { return std::unique_ptr<A>{DoClone()}; }
        auto Create() const { return std::unique_ptr<A>{DoCreate()}; }
    private:
        // Use covariant return type :)
        A* DoClone() const override { return new A(*this); }
        A* DoCreate() const override { return new A; }
    };

    class B : public IPrototype {
    public:
        auto Clone() const { return std::unique_ptr<B>{DoClone()}; }
        auto Create() const { return std::unique_ptr<B>{DoCreate()}; }
    private:
        // Use covariant return type :)
        B* DoClone() const override { return new B(*this); }
        B* DoCreate() const override { return new B; }
    };

    class ChildA : public A {
    public:
        auto Clone() const { return std::unique_ptr<ChildA>{ DoClone()}; }
        auto Create() const { return std::unique_ptr<ChildA>{ DoCreate()}; }
    private:
        // Use covariant return type :)
        ChildA* DoClone() const override { return new ChildA(*this); }
        ChildA* DoCreate() const override { return new ChildA; }
    };
}

//-----------------------------------------------------------
// Реализация паттерна "Прототип"
//-----------------------------------------------------------
namespace Creational {

    using std::unique_ptr;
    using std::make_unique;
    using std::string;
    using std::cout;

    class IAnimal abstract {
    public:
        virtual ~IAnimal() = default;
        virtual std::unique_ptr<IAnimal> create() = 0;
        virtual std::unique_ptr<IAnimal> clone() = 0;
        virtual const std::string& get_name() const noexcept = 0;
    };

    class Cat : public IAnimal {
    public:
        Cat(const string& name) : _name(name) {}
        unique_ptr<IAnimal> create() override { return make_unique<Cat>(_name); }
        unique_ptr<IAnimal> clone() override  { return make_unique<Cat>(_name); }
        const string& get_name() const noexcept override { return _name; }
    private:
        const string _name;
    };

    class Dog : public IAnimal {
    public:
        Dog(const string& name) : _name(name) {}
        unique_ptr<IAnimal> create() override { return make_unique<Dog>(_name); }
        unique_ptr<IAnimal> clone() override { return make_unique<Dog>(_name); }
        const string& get_name() const noexcept override { return _name; }
    private:
        const string _name;
    };

    // Для теста
    void who_i(unique_ptr<IAnimal>&& animal) {
        auto who1 = animal->create();
        auto who2 = animal->clone();
        cout << "Who1: " << who1->get_name() << '\n';
        cout << "Who2: " << who2->get_name() << '\n';
    }

    // Тест паттерна
    void test_prototype() {
        unique_ptr<Cat> cat = make_unique<Cat>("CAT");
        auto dog = make_unique<Dog>("DOG");
        who_i(std::move(cat));
        who_i(std::move(dog));
    }
}