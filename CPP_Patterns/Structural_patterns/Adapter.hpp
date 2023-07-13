/* Паттерн Адаптер (Adapter) */
/* Источник - https://digestcpp.com/designpattern/structural/adapter/ и др. */
/* https://radioprog.ru/post/1472 */

/* Паттерн Адаптер (Adapter) предназначен для преобразования интерфейса одного класса в
 * интерфейс другого. Благодаря реализации данного паттерна мы можем использовать вместе
 * классы с несовместимыми интерфейсами.

 - Когда надо использовать Адаптер?
 - Когда необходимо использовать имеющийся класс, но его интерфейс не соответствует потребностям
 - Когда надо использовать уже существующий класс совместно с другими классами,
 - интерфейсы которых не совместимы
 */

#pragma once
#include <iostream>
#include <string>

 // Концепция паттерна "Адаптер"
namespace Сonception {

    // Целевой класс объявляет интерфейс, с которым может работать клиентский код.
    class Target {
    public:
        virtual ~Target() = default;
        virtual std::string Request() const {
            return "Target: The default target's behavior.";
        }
    };

    // Адаптируемый класс содержит некоторое полезное поведение, но его интерфейс несовместим
    // с существующим клиентским кодом. Адаптируемый класс нуждается в некоторой доработке,
    // прежде чем клиентский код сможет его использовать.
    class Adaptee {
    public:
        std::string SpecificRequest() const {
            return ".eetpadA eht fo roivaheb laicepS";
        }
    };

    // Адаптер делает интерфейс Адаптируемого класса совместимым с целевым интерфейсом.
    class Adapter : public Target {
    private:
        Adaptee* adaptee_;
    public:
        Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}
        std::string Request() const override {
            std::string to_reverse = this->adaptee_->SpecificRequest();
            std::reverse(to_reverse.begin(), to_reverse.end());
            return "Adapter: (TRANSLATED) " + to_reverse;
        }
    };

    // Клиентский код поддерживает все классы, использующие целевой интерфейс.
    void ClientCode(const Target* target) {
        std::cout << target->Request();
    }

    void run_adapter() {
        std::cout << "Client: I can work just fine with the Target objects:\n";
        Target* target = new Target;
        ClientCode(target);
        std::cout << "\n\n";
        Adaptee* adaptee = new Adaptee;
        std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
        std::cout << "Adaptee: " << adaptee->SpecificRequest();
        std::cout << "\n\n";
        std::cout << "Client: But I can work with it via the Adapter:\n";
        Adapter* adapter = new Adapter(adaptee);
        ClientCode(adapter);
        std::cout << "\n";

        delete target;
        delete adaptee;
        delete adapter;
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Адаптер"
//--------------------------------------------------------------
namespace Structural {

    class ITarget {
    public:
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual void SetMotorType(std::string) = 0;
    };

    //Motor Interface
    class IMotor {
    public:
        virtual void StartMotor() = 0;
        virtual void StopMotor() = 0;
    };

    //Actual Motor Class
    class ActualMotor :public IMotor {
        void StartMotor() {
            std::cout << "Actual Motor Start, call driver app" << std::endl;
        }
        void StopMotor() {
            std::cout << "Actual Motor Stop, call driver app" << std::endl;
        }
    };

    // Motor Simulator Class
    class MotorSimulator :public IMotor {
        void StartMotor() {
            std::cout << "Motor Simulator  Start for testing" << std::endl;
        }
        void StopMotor() {
            std::cout << "Motor Simulator Stop for testing" << std::endl;
        }
    };

    //Adapter Class
    class Adapter :public ITarget  {
        IMotor* mp;
        Adapter(const Adapter& other) = delete;  // Disallow copying
        void operator=(const Adapter&) = delete; // Disallow copying
    public:
        Adapter();
        ~Adapter();
        void Start(); //Get interface from Base class
        void Stop();  //Get interface from Base class
        void SetMotorType(std::string str);
    };

    //Adapter definition
    Adapter::Adapter() : mp(nullptr) { }
    
    Adapter::~Adapter() {
        if (mp) delete mp;
    }

    void Adapter::Start() {
        if (mp)
            mp->StartMotor();
        else
            std::cout << "Motor is not set" << std::endl;
    }

    void Adapter::Stop() {
        if (mp)
            mp->StopMotor();
        else
            std::cout << "Motor is not set" << std::endl;
    }

    void Adapter::SetMotorType(std::string str) {
        if (str == "ActualMotor") {
            if (mp)
                delete mp;
            mp = new ActualMotor;
        }
        else if (str == "SimulatorMotor") {
            if (mp)
                delete mp;
            mp = new MotorSimulator;
        }
        else {
            std::cout << "Motor type is not available" << std::endl;
            if (mp)
                delete mp;
        }
    }

    // Client
    void test_adapter() {
        std::cout << "In Main" << std::endl;
        //Create the Target
        ITarget* tar = new Adapter;
        //Set the Actual Motor
        tar->SetMotorType("ActualMotor");
        tar->Start();
        tar->Stop();
        //Set the Simulator Motor
        tar->SetMotorType("SimulatorMotor");
        tar->Start();
        tar->Stop();
        delete tar;
    }
}