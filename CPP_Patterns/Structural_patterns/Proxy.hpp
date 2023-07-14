/* Паттерн Заместитель (Proxy) */
/* Источник - https://metanit.com/sharp/patterns/4.5.php и др. */
/* https://radioprog.ru/post/1489 */
/* https://www.youtube.com/watch?v=_erx1di25t0 */

/* Заместитель – это объект, который выступает прослойкой между клиентом и реальным сервисным
 * объектом. Заместитель получает вызовы от клиента, выполняет свою функцию (контроль доступа,
 * кеширование, изменение запроса и прочее), а затем передаёт вызов сервисному объекту.
 * Заместитель имеет тот же интерфейс, что и реальный объект, поэтому для клиента нет разницы 
 * – работать через заместителя или напрямую
 */

#pragma once
#include <iostream>
#include <string>
#include <map>

 // Концепция паттерна "Заместитель"
namespace Сoncept {
    /**
    * Интерфейс Субъекта объявляет общие операции как для Реального Субъекта, так и
    * для Заместителя. Пока клиент работает с Реальным Субъектом, используя этот
    * интерфейс, вы сможете передать ему заместителя вместо реального субъекта.
    */
    class Subject {
    public:
        virtual void Request() const = 0;
    };

    /* Реальный Субъект содержит некоторую базовую бизнес-логику. Как правило,
     * Реальные Субъекты способны выполнять некоторую полезную работу, которая к
     * тому же может быть очень медленной или точной – например, коррекция входных
     * данных. Заместитель может решить эти задачи без каких-либо изменений в коде
     * Реального Субъекта. */
    class RealSubject : public Subject {
    public:
        void Request() const override {
            std::cout << "RealSubject: Handling request.\n";
        }
    };

    /* Интерфейс Заместителя идентичен интерфейсу Реального Субъекта. */
    class Proxy : public Subject {
        /** @var RealSubject **/
    private:
        RealSubject* real_subject_;

        bool CheckAccess() const {
            // Некоторые реальные проверки должны проходить здесь.
            std::cout << "Proxy: Checking access prior to firing a real request.\n";
            return true;
        }
        void LogAccess() const {
            std::cout << "Proxy: Logging the time of request.\n";
        }

        /* Заместитель хранит ссылку на объект класса РеальныйСубъект. Клиент может
         * либо лениво загрузить его, либо передать Заместителю.
         */
    public:
        Proxy(RealSubject* real_subject) : real_subject_(new RealSubject(*real_subject)) { }

        ~Proxy() { delete real_subject_; }
        
        /* Наиболее распространёнными областями применения паттерна Заместитель
         * являются ленивая загрузка, кэширование, контроль доступа, ведение журнала и
         * т.д. Заместитель может выполнить одну из этих задач, а затем, в зависимости
         * от результата, передать выполнение одноимённому методу в связанном объекте
         * класса Реального Субъект.
         */
        void Request() const override {
            if (this->CheckAccess()) {
                this->real_subject_->Request();
                this->LogAccess();
            }
        }
    };
    /**
     * Клиентский код должен работать со всеми объектами (как с реальными, так и
     * заместителями) через интерфейс Субъекта, чтобы поддерживать как реальные
     * субъекты, так и заместителей. В реальной жизни, однако, клиенты в основном
     * работают с реальными субъектами напрямую. В этом случае, для более простой
     * реализации паттерна, можно расширить заместителя из класса реального
     * субъекта.
     */
    void ClientCode(const Subject& subject) {
        // ...
        subject.Request();
        // ...
    }

    /*
    int main() {
        std::cout << "Client: Executing the client code with a real subject:\n";
        RealSubject* real_subject = new RealSubject;
        ClientCode(*real_subject);
        std::cout << "\n";
        std::cout << "Client: Executing the same client code with a proxy:\n";
        Proxy* proxy = new Proxy(real_subject);
        ClientCode(*proxy);

        delete real_subject;
        delete proxy;
        return 0;
    }
    */
}

//--------------------------------------------------------------
// Реализация паттерна "Заместитель"
//--------------------------------------------------------------
namespace Structural {
    using std::string;
    using std::map;
    using std::cout;

    class ISite abstract {
    public:
        virtual string get_page(const int&) = 0;
        virtual ~ISite() {}
    };

    class Site : public ISite {
    public:
        string get_page(const int& num) override {
            string page = "Страница номер: " + std::to_string(num);
            return page;
        }
    };

    class SiteProxy : public ISite {
    private:
        ISite* site;
        map<int, string> cache;
    public:
        SiteProxy(ISite* site) : site(site) { }
        ~SiteProxy() { delete site; }

        string get_page(const int& num) override {
            string page;
            if (cache.find(num) == cache.end()) {
                page = site->get_page(num);
                cache[num] = page;
            }
            else {
                page = cache[num];
                page.insert(0, "из кеша ");
            }
            return page;
        }
    };

    void test_proxy() {
        ISite* site = new SiteProxy(new Site());

        cout << site->get_page(1) << std::endl;
        cout << site->get_page(2) << std::endl;
        cout << site->get_page(3) << std::endl;
        cout << site->get_page(1) << std::endl;
    }
}