/*Паттерн Цепочка Обязанностей (Chain of responsibility) */
/* Источник - https://www.bestprog.net/ru/2021/09/25/patterns-the-chain-of-responsibility-pattern-implementation-in-c-ru/ и др. */

/* Цепочка Обязанностей (Chain of responsibility) - поведенческий шаблон проектирования,
 * который позволяет избежать жесткой привязки отправителя запроса к получателю.
 * Все возможные обработчики запроса образуют цепочку, а сам запрос перемещается по этой цепочке.
 * Каждый объект в этой цепочке при получении запроса выбирает, либо закончить обработку запроса,
 * либо передать запрос на обработку следующему по цепочке объекту.
 - Когда применяется цепочка обязанностей?
 - Когда имеется более одного объекта, который может обработать определенный запрос
 - Когда надо передать запрос на выполнение одному из нескольких объект, точно не определяя, какому именно объекту
 - Когда набор объектов задается динамически
 */

#pragma once
#include <iostream>
#include <vector>
#include <ctime>

 // Концепция паттерна "Цепочка Обязанностей"
namespace Behavioral {
    
    // Класс, который служит единым интерфейсом для всех объектов, обрабатывающих запрос.
    // В этом классе указываются общие для объектов методы.
    // Класс определяет:
    // - внутреннее поле successor - указатель на преемника;
    // - конструктор Handler();
    // - метод HandleRequest(), предназначенный для обработки запроса;
    // - метод DoRequest() - определяет, нужно ли выполнять запрос;
    // - метод SetHandler() - устанавливает возможность обработки конкретным обработчиком.
    class Handler {
    private:
        Handler* successor; // указатель на последователя (последователь)
        int numHandler;     // номер обработчика, который обрабатывает запрос (1..3)
    public:
        // Конструктор
        Handler(Handler* _successor = nullptr, int numHandler = -1) :
            successor(_successor), numHandler(numHandler)
        { }

        // Виртуальный метод, предназначеный для обработки запроса.
        virtual void HandleRequest() {
            if (successor)
                successor->HandleRequest();
        }

        // Метод, определящий, нужно ли выполнять запрос
        virtual bool DoRequest() {
            return numHandler != -1;
        }

        // Метод, устанавливающий обработчика и возможность обработки
        virtual void SetHandler(Handler* _successor, int _numHandler) {
            successor = _successor;
            numHandler = _numHandler;
        }
    };

    // Конкретный обработчик - 1
    class ConcreteHandler1 : Handler {
    public:
        // Конструктор - получает 2 параметра:
        // - указатель на базовый класс;
        // - значение, определяющее, можно ли обрабатывать запрос.
        ConcreteHandler1(Handler* handler, int numHandler = -1)
            : Handler(handler, numHandler)
        { }

        // Конкретный метод обработки
        virtual void HandleRequest() {
            // Проверка, обрабатывает ли данный обработчик запрос.
            // Если обрабатывает, то выполнить соответствующие действия
            if (DoRequest())
                std::cout << "ConcreteHandler1.HandleRequest\n";
            else
                // если не обрабатывает, то передать вызов следующему обработчику по цепочке
                Handler::HandleRequest();
        }
    };

    // Конкретный обработчик - 2
    class ConcreteHandler2 : Handler {
    public:
        ConcreteHandler2(Handler* handler, int numHandler = -1) :
            Handler(handler, numHandler)
        { }

        // Конкретный метод обработки
        virtual void HandleRequest() {
            // Проверка, обрабатывает ли данный обработчик запрос.
            if (DoRequest())
                std::cout << "ConcreteHandler2.HandleRequest\n";
            else
                Handler::HandleRequest();
        }
    };

    // Последний конкретный обработчик. Этот обработчик замыкает обработку.
    // Поэтому ему не нужно передавать ссылку на предыдущего обработчика
    class ConcreteHandler3 : Handler {
    public:
        ConcreteHandler3(int numHandler = -1) : Handler(nullptr, numHandler) { }

        // Конкретный метод обработки
        virtual void HandleRequest() {
            if (DoRequest())
                std::cout << "ConcreteHandler3.HandleRequest\n";
            else
                std::cout << "There is no corresponding handler in the chain.\n";
        }
    };

    void test_chain() {
        // Код клиента.
        // 1. Создать цепочку из трех обработчиков, задать им соответствующий номер обработки
        // 1.1. Первым создается последний обработчик в цепи
        ConcreteHandler3* h3 = new ConcreteHandler3(3); // 3 - номер обработчика в цепи
        // 1.2. Следующий номер 2, получает ссылку на предыдущего обработчика h3
        ConcreteHandler2* h2 = new ConcreteHandler2((Handler*)h3, 2);
        // 1.3. Последний обработчик в цепочке - обработчик номер 1
        ConcreteHandler1* h1 = new ConcreteHandler1((Handler*)h2, 1);

        // 2. Создать клиента.
        // Клиент указывает на цепочку объектов-обработчиков client -> h1-> h2 -> h3.
        Handler* client = new Handler((Handler*)h1);

        // 3. Ввести с клавиатуры номер обработчика
        int numObject;
        for (numObject = 1; numObject < 5; ++numObject) {
            // 4. В зависимости от numObject реализовать диспетчеризацию
            switch (numObject) {
            case 1:
                // Установить обработчика для клиента
                client->SetHandler((Handler*)h1, 1); // обработчик 1
                client->HandleRequest(); // вызвать обработчика 1
                break;
            case 2:
                // Установить обработчика для клиента
                client->SetHandler((Handler*)h2, 2); // обработчик 2
                client->HandleRequest(); // вызвать обработчика 2
                break;
            case 3:
                // Установить обработчика для клиента
                client->SetHandler((Handler*)h3, 3); // обработчик 3
                client->HandleRequest(); // вызвать обработчика 3
                break;
            default:
                std::cout << "Incorrect handler\n";
                break;
            }
        }
    }
}