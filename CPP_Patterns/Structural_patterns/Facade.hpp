/* Паттерн Фасад (Facade) */
/* Источник - https://radioprog.ru/post/1485 и др. */
/* https://ru.wikipedia.org/wiki/%D0%A4%D0%B0%D1%81%D0%B0%D0%B4_(%D1%88%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD_%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)#C++ */

/* Фасад – это структурный паттерн, который предоставляет простой (но урезанный) интерфейс 
 * к сложной системе объектов, библиотеке или фреймворку. 
 * Кроме того, что Фасад позволяет снизить общую сложность программы, он также помогает
 * вынести код, зависимый от внешней системы в единственное место.
 */

#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <string_view>

 // Концепция паттерна "Фасад"
namespace Сonception {
    
    // Подсистема может принимать запросы либо от фасада, либо от клиента напрямую.
    // В любом случае для Подсистемы Фасад – это еще один клиент, и он не является частью Подсистемы.
    class Subsystem1 {
    public:
        std::string Operation1() const {
            return "Subsystem1: Ready!\n";
        }
        // ...
        std::string OperationN() const {
            return "Subsystem1: Go!\n";
        }
    };

    // Некоторые фасады могут работать с разными подсистемами одновременно.
    class Subsystem2 {
    public:
        std::string Operation1() const {
            return "Subsystem2: Get ready!\n";
        }
        // ...
        std::string OperationZ() const {
            return "Subsystem2: Fire!\n";
        }
    };

    /**
     * Класс Фасада предоставляет простой интерфейс для сложной логики одной или
     * нескольких подсистем. Фасад делегирует запросы клиентов соответствующим
     * объектам внутри подсистемы. Фасад также отвечает за управление их жизненным
     * циклом. Все это защищает клиента от нежелательной сложности подсистемы.
     */
    class Facade {
    protected:
        Subsystem1* subsystem1_;
        Subsystem2* subsystem2_;
    public:
        Facade(Subsystem1* subsystem1 = nullptr, Subsystem2* subsystem2 = nullptr) {
            subsystem1_ = subsystem1 ? subsystem1 : new Subsystem1;
            subsystem2_ = subsystem2 ? subsystem2 : new Subsystem2;
        }
        ~Facade() {
            delete subsystem1_;
            delete subsystem2_;
        }
        std::string Operation() {
            std::string result = "Facade initializes subsystems:\n";
            result += this->subsystem1_->Operation1();
            result += this->subsystem2_->Operation1();
            result += "Facade orders subsystems to perform the action:\n";
            result += this->subsystem1_->OperationN();
            result += this->subsystem2_->OperationZ();
            return result;
        }
    };

    /**
     * Клиентский код работает со сложными подсистемами через простой интерфейс,
     * предоставляемый Фасадом. Когда фасад управляет жизненным циклом подсистемы,
     * клиент может даже не знать о существовании подсистемы. Такой подход позволяет
     * держать сложность под контролем.
     */
    void ClientCode(Facade* facade) {
        // ...
        std::cout << facade->Operation();
        // ...
    }

    /**
     * В клиентском коде могут быть уже созданы некоторые объекты подсистемы. В этом
     * случае может оказаться целесообразным инициализировать Фасад с этими
     * объектами вместо того, чтобы позволить Фасаду создавать новые экземпляры.
     */

    int run_facade() {
        Subsystem1* subsystem1 = new Subsystem1;
        Subsystem2* subsystem2 = new Subsystem2;
        Facade* facade = new Facade(subsystem1, subsystem2);
        ClientCode(facade);
        delete facade;
        return 0;
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Фасад"
//--------------------------------------------------------------
namespace Structural {

    /* Абстрактный музыкант - не является обязательной составляющей паттерна, введен для упрощения кода */
    class Musician {
        const char* name;
    public:
        Musician(std::string_view name) : name(name.data()) { }
        virtual ~Musician() = default;
    protected:
        void output(std::string_view text) {
            std::cout << name << " " << text << "." << std::endl;
        }
    };

    /** Конкретные музыканты */
    class Vocalist : public Musician {
    public:
        Vocalist(std::string_view name) : Musician(name) {}

        void singCouplet(int coupletNumber) {
            std::string text = "спел куплет №";
            text += std::to_string(coupletNumber);
            output(text);
        }
        void singChorus() {
            output("спел припев");
        }
    };

    class Guitarist : public Musician {
    public:
        Guitarist(std::string_view name) : Musician(name) {}
        void playCoolOpening()        { output("начинает с крутого вступления"); }
        void playCoolRiffs()          { output("играет крутые риффы"); }
        void playAnotherCoolRiffs()   { output("играет другие крутые риффы"); }
        void playIncrediblyCoolSolo() { output("выдает невероятно крутое соло"); }
        void playFinalAccord()        { output("заканчивает песню мощным аккордом"); }
    };

    class Bassist : public Musician {
    public:
        Bassist(std::string_view name) : Musician(name) {}
        void followTheDrums() { output("следует за барабанами"); }
        void changeRhythm(std::string_view type) {
            std::string text = ("перешел на ритм ");
            text += type;
            text += "a";
            output(text);
        }
        void stopPlaying() { output("заканчивает играть"); }
    };

    class Drummer : public Musician {
    public:
        Drummer(std::string_view name) : Musician(name) {}
        void startPlaying() { output("начинает играть"); }
        void stopPlaying()  { output("заканчивает играть"); }
    };

    /** Фасад, в данном случае - знаменитая рок-группа */
    class BlackSabbath {
        std::unique_ptr<Vocalist> vocalist;
        std::unique_ptr<Guitarist> guitarist;
        std::unique_ptr<Bassist> bassist;
        std::unique_ptr<Drummer> drummer;
    public:
        BlackSabbath() {
            vocalist = std::make_unique<Vocalist>("Оззи Осборн");
            guitarist = std::make_unique<Guitarist>("Тони Айомми");
            bassist = std::make_unique<Bassist>("Гизер Батлер");
            drummer = std::make_unique<Drummer>("Билл Уорд");
        }
        void playCoolSong() {
            guitarist->playCoolOpening();
            drummer->startPlaying();
            bassist->followTheDrums();
            guitarist->playCoolRiffs();
            vocalist->singCouplet(1);
            bassist->changeRhythm("припев");
            guitarist->playAnotherCoolRiffs();
            vocalist->singChorus();
            bassist->changeRhythm("куплет");
            guitarist->playCoolRiffs();
            vocalist->singCouplet(2);
            bassist->changeRhythm("припев");
            guitarist->playAnotherCoolRiffs();
            vocalist->singChorus();
            bassist->changeRhythm("куплет");
            guitarist->playIncrediblyCoolSolo();
            guitarist->playCoolRiffs();
            vocalist->singCouplet(3);
            bassist->changeRhythm("припев");
            guitarist->playAnotherCoolRiffs();
            vocalist->singChorus();
            bassist->changeRhythm("куплет");
            guitarist->playCoolRiffs();
            bassist->stopPlaying();
            drummer->stopPlaying();
            guitarist->playFinalAccord();
        }
    };

    void test_facade() {
        std::cout << "OUTPUT:" << std::endl;
        BlackSabbath band;
        band.playCoolSong();
    }
}