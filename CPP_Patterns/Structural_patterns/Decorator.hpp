/* Паттерн Декоратор (Decorator) */
/* Источник - https://metanit.com/sharp/patterns/4.1.php и др. */
/* http://cpp-reference.ru/patterns/structural-patterns/decorator/ */
/* https://radioprog.ru/post/1483 */

/* Декоратор – это структурный паттерн, который позволяет добавлять объектам новые 
 * поведения на лету, помещая их в объекты-обёртки.
 * Декоратор позволяет оборачивать объекты бесчисленное количество раз благодаря тому,
 * что и обёртки, и реальные оборачиваемые объекты имеют общий интерфейс.
 */

#pragma once
#include <iostream>
#include <string>

// Концепция паттерна "Декоратор"
namespace Сonception {
    
    // Базовый интерфейс Компонента определяет поведение, которое изменяется декораторами.
    class Component {
    public:
        virtual ~Component() {}
        virtual std::string Operation() const = 0;
    };
    
    // Конкретные Компоненты предоставляют реализации поведения по умолчанию. Может
    // быть несколько вариаций этих классов.
    class ConcreteComponent : public Component {
    public:
        std::string Operation() const override { return "ConcreteComponent"; }
    };

    // Базовый класс Декоратора следует тому же интерфейсу, что и другие компоненты.
    // Основная цель этого класса - определить интерфейс обёртки для всех конкретных
    // декораторов. Реализация кода обёртки по умолчанию может включать в себя поле
    // для хранения завёрнутого компонента и средства его инициализации.
    class Decorator : public Component {
    protected:
        Component* component_;
    public:
        Decorator(Component* component) : component_(component) { }
        
        /* Декоратор делегирует всю работу обёрнутому компоненту. */
        std::string Operation() const override { return component_->Operation(); }
    };

    // Конкретные Декораторы вызывают обёрнутый объект и изменяют его результат некоторым образом.
    //Декораторы могут вызывать родительскую реализацию операции, вместо того, чтобы вызвать
    // обёрнутый объект напрямую. Такой подход упрощает расширение классов декораторов.
    class ConcreteDecoratorA : public Decorator {
    public:
        ConcreteDecoratorA(Component* component) : Decorator(component) { }
        std::string Operation() const override {
            return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
        }
    };

    // Декораторы могут выполнять своё поведение до или после вызова обёрнутого объекта.
    class ConcreteDecoratorB : public Decorator {
    public:
        ConcreteDecoratorB(Component* component) : Decorator(component) { }
        std::string Operation() const override {
            return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
        }
    };

    // Клиентский код работает со всеми объектами, используя интерфейс Компонента.
    // Таким образом, он остаётся независимым от конкретных классов компонентов, с которыми работает.
    void ClientCode(Component* component) {
        // ...
        std::cout << "RESULT: " << component->Operation();
        // ...
    }

    void run_decorator() {
        Component* simple = new ConcreteComponent;
        std::cout << "Client: I've got a simple component:\n";
        ClientCode(simple);
        std::cout << "\n\n";
        Component* decorator1 = new ConcreteDecoratorA(simple);
        Component* decorator2 = new ConcreteDecoratorB(decorator1);
        std::cout << "Client: Now I've got a decorated component:\n";
        ClientCode(decorator2);
        std::cout << "\n";
        delete simple;
        delete decorator1;
        delete decorator2;
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Декоратор"
//--------------------------------------------------------------
namespace Structural {

    using std::cout;

    // 1. " Наименьший общий знаменатель"
    class Widget {
    public:
        virtual void draw() = 0;
    };

    // 3. Основной класс, использующий отношение "является"
    class TextField : public Widget {
        int width, height;
    public:
        TextField(int w, int h) : width(w), height(h) { }

        void draw() {
            cout << "TextField: " << width << ", " << height << '\n';
        }
    };

    // 2. Базовый класс второго уровня
    // 3. использует отношение "является"
    class Decorator : public Widget {
        Widget* wid; // 4. отношение "имеет"
    public:
        Decorator(Widget* w) : wid(w) { };

        /*virtual*/
        void draw() {
            wid->draw(); // 5. делегирование
        }
    };

    // 6. Дополнительное декорирование
    class BorderDecorator : public Decorator {
    public:
        BorderDecorator(Widget* w) : Decorator(w) {}

        /*virtual*/
        void draw() {
            Decorator::draw();                    // 7. Делегирование базовому классу и
            cout << "   BorderDecorator" << '\n'; // 7. реализация дополнительной функциональности
        }
    };

    // 6. Дополнительное декорирование
    class ScrollDecorator : public Decorator {
    public:
        ScrollDecorator(Widget* w) : Decorator(w) { }

        /*virtual*/
        void draw() {
            // 7. Delegate to base class and add extra stuff
            Decorator::draw();
            cout << "   ScrollDecorator" << '\n';
        }
    };

    // 8. Клиент ответственен за конфигурирование нужной функциональности
    void test_decorator() {
        Widget* aWidget = new BorderDecorator(
            new BorderDecorator(
                new ScrollDecorator
                (new TextField(80, 24))));
        aWidget->draw();
    }
}