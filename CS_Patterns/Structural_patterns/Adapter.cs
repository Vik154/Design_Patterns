/* Паттерн Адаптер (Adapter) */
/* Источник - https://metanit.com/sharp/patterns/4.2.php и др. */

/* Паттерн Адаптер (Adapter) предназначен для преобразования интерфейса одного класса в 
 * интерфейс другого. Благодаря реализации данного паттерна мы можем использовать вместе 
 * классы с несовместимыми интерфейсами.

 - Когда надо использовать Адаптер?
 - Когда необходимо использовать имеющийся класс, но его интерфейс не соответствует потребностям
 - Когда надо использовать уже существующий класс совместно с другими классами, 
 - интерфейсы которых не совместимы
 */

// Концепция паттерна "Адаптер"
namespace Сonception {

    // Target: представляет объекты, которые используются клиентом
    // класс, к которому надо адаптировать другой класс   
    class Target {
        public virtual void Request() { }
    }

    // Адаптер
    class Adapter : Target {
        private Adaptee adaptee = new Adaptee();

        public override void Request() {
            adaptee.SpecificRequest();
        }
    }

    // Адаптируемый класс
    class Adaptee {
        public void SpecificRequest() { }
    }

    /*
    class Client {
        public void Request(Target target) {
            target.Request();
        }
    }
    */
}

//--------------------------------------------------------------
// Реализация паттерна "Адаптер"
//--------------------------------------------------------------
namespace Patterns.Structural {

    internal interface ITransport {
        void Drive();
    }

    // класс машины
    internal class Auto : ITransport {
        public void Drive() {
            Console.WriteLine("Машина едет по дороге");
        }
    }

    internal class Driver {
        public void Travel(ITransport transport) {
            transport.Drive();
        }
    }

    // интерфейс животного
    internal interface IAnimal {
        void Move();
    }

    // класс верблюда
    internal class Camel : IAnimal {
        public void Move() {
            Console.WriteLine("Верблюд идет по пескам пустыни");
        }
    }

    // Адаптер от Camel к ITransport
    internal class CamelToTransportAdapter : ITransport {
        Camel camel;
        public CamelToTransportAdapter(Camel c) {
            camel = c;
        }
        public void Drive() {
            camel.Move();
        }
    }

    internal static class TestAdapter {
        public static void ShowResult() {
            Driver driver = new Driver();   // путешественник
            Auto auto = new Auto();         // машина
            driver.Travel(auto);            // отправляемся в путешествие
            Camel camel = new Camel();      // встретились пески, надо использовать верблюда
            // используем адаптер
            ITransport camelTransport = new CamelToTransportAdapter(camel);

            driver.Travel(camelTransport);  // продолжаем путь по пескам пустыни
        }
    }
}