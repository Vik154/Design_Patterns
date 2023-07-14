/* Паттерн Приспособленец (Flyweight) */
/* Источник - https://metanit.com/sharp/patterns/4.7.php и др. */
/* https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D0%B8%D1%81%D0%BF%D0%BE%D1%81%D0%BE%D0%B1%D0%BB%D0%B5%D0%BD%D0%B5%D1%86_(%D1%88%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD_%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)#%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D1%80_%D0%BD%D0%B0_C++ */

/* Паттерн Приспособленец (Flyweight) - структурный шаблон проектирования, который позволяет
 * использовать разделяемые объекты сразу в нескольких контекстах. Данный паттерн используется
 * преимущественно для оптимизации работы с памятью
 - Паттерн Приспособленец следует применять при соблюдении всех следующих условий:
 - Когда приложение использует большое количество однообразных объектов,
 - из-за чего происходит выделение большого количества памяти
 - Когда часть состояния объекта, которое является изменяемым, можно вынести во вне.
 - Вынесение внешнего состояния позволяет заменить множество объектов небольшой группой
 - общих разделяемых объектов.
 */

#pragma once
#include <map>
#include <iostream>
#include <memory>
#include <unordered_map>

 // Концепция паттерна "Приспособленец"
namespace Сonception {
    
    // Паттерн Приспособленец позволяет вместить бóльшее количество объектов в отведённую 
    // оперативную память, экономит память, разделяя общее состояние объектов между собой,
    // вместо хранения одинаковых данных в каждом объекте.
    struct SharedState {
        std::string brand_;
        std::string model_;
        std::string color_;

        SharedState(const std::string& brand, const std::string& model, const std::string& color)
            : brand_(brand), model_(model), color_(color)
        { }

        friend std::ostream& operator<<(std::ostream& os, const SharedState& ss) {
            return os << "[ " << ss.brand_ << " , " << ss.model_ << " , " << ss.color_ << " ]";
        }
    };

    struct UniqueState {
        std::string owner_;
        std::string plates_;

        UniqueState(const std::string& owner, const std::string& plates)
            : owner_(owner), plates_(plates)
        { }

        friend std::ostream& operator<<(std::ostream& os, const UniqueState& us) {
            return os << "[ " << us.owner_ << " , " << us.plates_ << " ]";
        }
    };

    // Приспособленец хранит общую часть состояния (также называемую внутренним состоянием),
    // которая принадлежит нескольким реальным бизнес-объектам. Приспособленец принимает оставшуюся
    // часть состояния (внешнее состояние, уникальное для каждого объекта) через его параметры метода.
    class Flyweight {
    private:
        SharedState* shared_state_;
    public:
        Flyweight(const SharedState* shared_state) : shared_state_(new SharedState(*shared_state)) { }
        Flyweight(const Flyweight& other) : shared_state_(new SharedState(*other.shared_state_))   { }
        ~Flyweight() {
            delete shared_state_;
        }
        SharedState* shared_state() const {
            return shared_state_;
        }
        void Operation(const UniqueState& unique_state) const {
            std::cout << "Flyweight: Displaying shared (" << *shared_state_ << ") and unique (" << unique_state << ") state.\n";
        }
    };

    // Фабрика Приспособленцев создает объекты-Приспособленцы и управляет ими. Она обеспечивает
    // правильное разделение Приспособленцев. Когда клиент запрашивает Приспособленца, фабрика
    // либо возвращает существующий экземпляр, либо создает новый, если он ещё не существует.
    class FlyweightFactory {
        /** @var Flyweight[] **/
    private:
        std::unordered_map<std::string, Flyweight> flyweights_;

        std::string GetKey(const SharedState& ss) const {
            return ss.brand_ + "_" + ss.model_ + "_" + ss.color_;
        }
    public:
        FlyweightFactory(std::initializer_list<SharedState> share_states) {
            for (const SharedState& ss : share_states) {
                this->flyweights_.insert(std::make_pair<std::string, Flyweight>(this->GetKey(ss), Flyweight(&ss)));
            }
        }
        Flyweight GetFlyweight(const SharedState& shared_state) {
            std::string key = this->GetKey(shared_state);
            if (this->flyweights_.find(key) == this->flyweights_.end()) {
                std::cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
                this->flyweights_.insert(std::make_pair(key, Flyweight(&shared_state)));
            }
            else {
                std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
            }
            return this->flyweights_.at(key);
        }

        void ListFlyweights() const {
            size_t count = this->flyweights_.size();
            std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
            for (std::pair<std::string, Flyweight> pair : this->flyweights_) {
                std::cout << pair.first << "\n";
            }
        }
    };

    // ...
    void AddCarToPoliceDatabase(
        FlyweightFactory& ff, const std::string& plates, const std::string& owner,
        const std::string& brand, const std::string& model, const std::string& color)
    {
        std::cout << "\nClient: Adding a car to database.\n";
        const Flyweight& flyweight = ff.GetFlyweight({ brand, model, color });
        flyweight.Operation({ owner, plates });
    }

    int run_flyweight() {
        FlyweightFactory* factory = new FlyweightFactory({ {"Chevrolet", "Camaro2018", "pink"}, {"Mercedes Benz", "C300", "black"}, {"Mercedes Benz", "C500", "red"}, {"BMW", "M5", "red"}, {"BMW", "X6", "white"} });
        factory->ListFlyweights();

        AddCarToPoliceDatabase(*factory,
            "CL234IR",
            "James Doe",
            "BMW",
            "M5",
            "red");

        AddCarToPoliceDatabase(*factory,
            "CL234IR",
            "James Doe",
            "BMW",
            "X1",
            "red");
        factory->ListFlyweights();
        delete factory;

        return 0;
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Приспособленец"
//--------------------------------------------------------------
namespace Structural {

    // "Flyweight"
    class Character {
    public:
        virtual ~Character() = default;
        virtual void display() const = 0;
    protected:
        char mSymbol;
        int  mWidth;
        int  mHeight;
        int  mAscent;
        int  mDescent;
        int  mPointSize;
    };

    // "ConcreteFlyweight"
    class ConcreteCharacter : public Character {
    public:
        // Constructor
        ConcreteCharacter(char aSymbol, int aPointSize) {
            mSymbol = aSymbol;
            mWidth = 120;
            mHeight = 100;
            mAscent = 70;
            mDescent = 0;
            mPointSize = aPointSize;
        }
        // from Character
        virtual void display() const {
            std::cout << mSymbol << " ( PointSize " << mPointSize << " )\n";
        }
    };

    // "FlyweightFactory"
    template < const int POINT_SIZE >
    class CharacterFactory {
    public:
        const Character& getCharacter(char aKey) {
            // Uses "lazy initialization"
            Characters::const_iterator it = mCharacters.find(aKey);
            if (mCharacters.end() == it) {
                mCharacters[aKey] = std::make_unique<const ConcreteCharacter>(aKey, POINT_SIZE);
                return *mCharacters[aKey];
            }
            else {
                return *it->second;
            }
        }

    private:
        using Characters = std::map < char, std::unique_ptr<const Character> >;
        Characters mCharacters;
    };

    void test_flyweight() {
        std::string document = "AAZZBBZB";

        CharacterFactory<12> characterFactory;
        for (auto it : document) {
            auto&& character = characterFactory.getCharacter(it);
            character.display();
        }
    }
}