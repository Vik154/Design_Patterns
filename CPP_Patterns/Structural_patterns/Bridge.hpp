/* Паттерн Мост (Bridge) */
/* Источник - https://metanit.com/sharp/patterns/4.6.php и др. */
/* https://www.youtube.com/watch?v=1OmwPFqlXBY&list=PLKP3l9fd3KUFONuybgV1kZpY76jwHRdkM&index=8 */
/* https://radioprog.ru/post/1474 */

/* Мост (Bridge) - структурный шаблон проектирования, который позволяет отделить абстракцию
 * от реализации таким образом, чтобы и абстракцию, и реализацию можно было изменять независимо
 * друг от друга. Даже если мы отделим абстракцию от конкретных реализаций, то у нас все равно
 * все наследуемые классы будут жестко привязаны к интерфейсу, определяемому в базовом
 * абстрактном классе. Для преодоления жестких связей и служит паттерн Мост.

 - Когда использовать данный паттерн?
 - Когда надо избежать постоянной привязки абстракции к реализации
 - Когда наряду с реализацией надо изменять и абстракцию независимо друг от друга.
 - То есть изменения в абстракции не должно привести к изменениям в реализации
 */

#pragma once
#include <iostream>
#include <string>

 // Концепция паттерна "Мост"
namespace Сonception {
    
    // Реализация устанавливает интерфейс для всех классов реализации.Он не должен соответствовать
    // интерфейсу Абстракции.На практике оба интерфейса могут быть совершенно разными.Как правило,
    // интерфейс Реализации предоставляет только примитивные операции, в то время как Абстракция
    // определяет операции более высокого уровня, основанные на этих примитивах.
    class Implementation {
    public:
        virtual ~Implementation() {}
        virtual std::string OperationImplementation() const = 0;
    };

    // Каждая Конкретная Реализация соответствует определённой платформе и реализует
    // интерфейс Реализации с использованием API этой платформы.
    class ConcreteImplementationA : public Implementation {
    public:
        std::string OperationImplementation() const override {
            return "ConcreteImplementationA: Here's the result on the platform A.\n";
        }
    };

    class ConcreteImplementationB : public Implementation {
    public:
        std::string OperationImplementation() const override {
            return "ConcreteImplementationB: Here's the result on the platform B.\n";
        }
    };

    // Абстракция устанавливает интерфейс для «управляющей» части двух иерархий классов.
    // Она содержит ссылку на объект из иерархии Реализации и делегирует ему всю настоящую работу.
    class Abstraction {
        /** @var Implementation **/
    protected:
        Implementation* implementation_;
    public:
        Abstraction(Implementation* implementation) : implementation_(implementation) { }
        virtual ~Abstraction() { }
        virtual std::string Operation() const {
            return "Abstraction: Base operation with:\n" +
                this->implementation_->OperationImplementation();
        }
    };

    /* Можно расширить Абстракцию без изменения классов Реализации. */
    class ExtendedAbstraction : public Abstraction {
    public:
        ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation) { }
        std::string Operation() const override {
            return "ExtendedAbstraction: Extended operation with:\n" +
                this->implementation_->OperationImplementation();
        }
    };

    // За исключением этапа инициализации, когда объект Абстракции связывается с определённым
    // объектом Реализации, клиентский код должен зависеть только от класса Абстракции.
    // Таким образом, клиентский код может поддерживать любую комбинацию абстракции и реализации.
    void ClientCode(const Abstraction& abstraction) {
        // ...
        std::cout << abstraction.Operation();
        // ...
    }

    // Клиентский код должен работать с любой предварительно сконфигурированной
    // комбинацией абстракции и реализации.
    /*
    int main() {
        Implementation* implementation = new ConcreteImplementationA;
        Abstraction* abstraction = new Abstraction(implementation);
        ClientCode(*abstraction);
        std::cout << std::endl;
        delete implementation;
        delete abstraction;

        implementation = new ConcreteImplementationB;
        abstraction = new ExtendedAbstraction(implementation);
        ClientCode(*abstraction);

        delete implementation;
        delete abstraction;

        return 0;
    }
    */
}

//--------------------------------------------------------------
// Реализация паттерна "Мост"
//--------------------------------------------------------------
namespace Structural {
    using std::cout;

    class DataReader abstract {
    public:
        virtual void read() = 0;
    };

    class DataBaseReader : public DataReader {
    public:
        void read() override {
            cout << "Данные из базы данных\n";
        }
    };

    class FileReader : public DataReader {
        void read() override {
            cout << "Данные из файла\n";
        }
    };

    class Sender abstract {
    protected:
        DataReader* reader;
    public:
        Sender(DataReader* dr) : reader(dr) { }
        void set_data_reader(DataReader* dr) { reader = dr; }
        virtual void send() = 0;
    };

    class EmailSender : public Sender {
    public:
        EmailSender(DataReader* dr) : Sender(dr) { }
        void send() override {
            reader->read();
            cout << "Отправлены при помощи email\n";
        }
    };

    class TelegramBotSender : public Sender {
    public:
        TelegramBotSender(DataReader* dr) : Sender(dr) { }
        void send() override {
            reader->read();
            cout << "Отправлены при помощи Telegram бота\n";
        }
    };

    void test_bridge() {
        Sender* sender = new EmailSender(new DataBaseReader());
        sender->send();

        sender->set_data_reader(new FileReader());
        sender->send();

        sender = new TelegramBotSender(new DataBaseReader());
        sender->send();
    }
}