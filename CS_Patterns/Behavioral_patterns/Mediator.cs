/* Паттерн Посредник (Mediator) */
/* Источник - https://metanit.com/sharp/patterns/3.9.php и др. */

/* Паттерн Посредник (Mediator) представляет такой шаблон проектирования, который обеспечивает
 * взаимодействие множества объектов без необходимости ссылаться друг на друга. 
 * Тем самым достигается слабосвязанность взаимодействующих объектов.
 - Когда используется паттерн Посредник?
 - Когда имеется множество взаимосвязаных объектов, связи между которыми сложны и запутаны.
 - Когда необходимо повторно использовать объект, однако повторное использование затруднено 
 - в силу сильных связей с другими объектами.
 */

// Концепция паттерна "Посредник"
namespace Сonception {

    // Mediator: представляет интерфейс для взаимодействия с объектами Colleague
    abstract class Mediator {
        public abstract void Send(string msg, Colleague colleague);
    }

    // Colleague: представляет интерфейс для взаимодействия с объектом Mediator
    abstract class Colleague {
        protected Mediator mediator;

        public Colleague(Mediator mediator) {
            this.mediator = mediator;
        }
    }

    // ConcreteColleague1 и ConcreteColleague2: конкретные классы коллег,
    // которые обмениваются друг с другом через объект Mediator
    class ConcreteColleague1 : Colleague {
        public ConcreteColleague1(Mediator mediator) : base(mediator) { }

        public void Send(string message) {
            mediator.Send(message, this);
        }
        public void Notify(string message) { }
    }

    class ConcreteColleague2 : Colleague {
        public ConcreteColleague2(Mediator mediator) : base(mediator) { }

        public void Send(string message) {
            mediator.Send(message, this);
        }
        public void Notify(string message) { }
    }

    // ConcreteMediator: конкретный посредник, реализующий интерфейс типа Mediator
    class ConcreteMediator : Mediator {
        public ConcreteColleague1 Colleague1 { get; set; }
        public ConcreteColleague2 Colleague2 { get; set; }
        public override void Send(string msg, Colleague colleague) {
            if (Colleague1 == colleague)
                Colleague2.Notify(msg);
            else
                Colleague1.Notify(msg);
        }
    }
}


//--------------------------------------------------------------
// Реализация паттерна "Посредник"
//--------------------------------------------------------------
namespace Patterns.Behavioral {

    internal abstract class Mediator {
        public abstract void Send(string msg, Colleague colleague);
    }

    internal abstract class Colleague {
        protected Mediator mediator;

        public Colleague(Mediator mediator) {
            this.mediator = mediator;
        }
        public virtual void Send(string message) {
            mediator.Send(message, this);
        }
        public abstract void Notify(string message);
    }

    // класс заказчика
    internal class CustomerColleague : Colleague {
        public CustomerColleague(Mediator mediator) : base(mediator) { }

        public override void Notify(string message) {
            Console.WriteLine("Сообщение заказчику: " + message);
        }
    }

    // класс программиста
    internal class ProgrammerColleague : Colleague {
        public ProgrammerColleague(Mediator mediator) : base(mediator) { }

        public override void Notify(string message) {
            Console.WriteLine("Сообщение программисту: " + message);
        }
    }

    // класс тестера
    internal class TesterColleague : Colleague {
        public TesterColleague(Mediator mediator) : base(mediator) { }

        public override void Notify(string message) {
            Console.WriteLine("Сообщение тестеру: " + message);
        }
    }

    internal class ManagerMediator : Mediator {
        public Colleague Customer { get; set; }
        public Colleague Programmer { get; set; }
        public Colleague Tester { get; set; }
        public override void Send(string msg, Colleague colleague) {
            // если отправитель - заказчик, значит есть новый заказ
            // отправляем сообщение программисту - выполнить заказ
            if (Customer == colleague)
                Programmer.Notify(msg);
            // если отправитель - программист, то можно приступать к тестированию
            // отправляем сообщение тестеру
            else if (Programmer == colleague)
                Tester.Notify(msg);
            // если отправитель - тест, значит продукт готов
            // отправляем сообщение заказчику
            else if (Tester == colleague)
                Customer.Notify(msg);
        }
    }

    internal static class TestMediator {
        
        public static void ShowResult() {
            ManagerMediator mediator = new ManagerMediator();
            Colleague customer = new CustomerColleague(mediator);
            Colleague programmer = new ProgrammerColleague(mediator);
            Colleague tester = new TesterColleague(mediator);
            mediator.Customer = customer;
            mediator.Programmer = programmer;
            mediator.Tester = tester;
            customer.Send("Есть заказ, надо сделать программу");
            programmer.Send("Программа готова, надо протестировать");
            tester.Send("Программа протестирована и готова к продаже");
        }
    }
}