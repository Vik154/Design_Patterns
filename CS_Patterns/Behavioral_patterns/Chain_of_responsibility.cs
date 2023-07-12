/*Паттерн Цепочка Обязанностей (Chain of responsibility) */
/* Источник - https://metanit.com/sharp/patterns/3.7.php и др. */

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

// Концепция паттерна "Цепочка Обязанностей"
namespace Сonception {

    // Client: отправляет запрос объекту Handler
    /* 
    class Client {
        void Main() {
            Handler h1 = new ConcreteHandler1();
            Handler h2 = new ConcreteHandler2();
            h1.Successor = h2;
            h1.HandleRequest(2);
        }
    }
    */

    // Handler: определяет интерфейс для обработки запроса.
    // Также может определять ссылку на следующий обработчик запроса
    abstract class Handler {
        public Handler Successor { get; set; }
        public abstract void HandleRequest(int condition);
    }

    // ConcreteHandler1 и ConcreteHandler2: конкретные обработчики, которые реализуют
    // функционал для обработки запроса. При невозможности обработки и наличия ссылки
    // на следующий обработчик, передают запрос этому обработчику
    class ConcreteHandler1 : Handler {
        public override void HandleRequest(int condition) {
            // некоторая обработка запроса
            if (condition == 1) {
                // завершение выполнения запроса;
            }
            // передача запроса дальше по цепи при наличии в ней обработчиков
            else if (Successor != null) {
                Successor.HandleRequest(condition);
            }
        }
    }

    class ConcreteHandler2 : Handler {
        public override void HandleRequest(int condition) {
            // некоторая обработка запроса

            if (condition == 2) {
                // завершение выполнения запроса;
            }
            // передача запроса дальше по цепи при наличии в ней обработчиков
            else if (Successor != null) {
                Successor.HandleRequest(condition);
            }
        }
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Цепочка Обязанностей"
//--------------------------------------------------------------
namespace Patterns.Behavioral {

    internal class Receiver {
        public bool BankTransfer { get; set; }      // банковские переводы
        public bool MoneyTransfer { get; set; }     // денежные переводы - WesternUnion, Unistream
        public bool PayPalTransfer { get; set; }    // перевод через PayPal
        public Receiver(bool bt, bool mt, bool ppt) {
            BankTransfer = bt;
            MoneyTransfer = mt;
            PayPalTransfer = ppt;
        }
    }

    internal abstract class PaymentHandler {
        public PaymentHandler Successor { get; set; }
        public abstract void Handle(Receiver receiver);
    }

    internal class BankPaymentHandler : PaymentHandler {
        public override void Handle(Receiver receiver) {
            if (receiver.BankTransfer == true)
                Console.WriteLine("Выполняем банковский перевод");
            else if (Successor != null)
                Successor.Handle(receiver);
        }
    }

    internal class PayPalPaymentHandler : PaymentHandler {
        public override void Handle(Receiver receiver) {
            if (receiver.PayPalTransfer == true)
                Console.WriteLine("Выполняем перевод через PayPal");
            else if (Successor != null)
                Successor.Handle(receiver);
        }
    }

    // переводы с помощью системы денежных переводов
    internal class MoneyPaymentHandler : PaymentHandler {
        public override void Handle(Receiver receiver) {
            if (receiver.MoneyTransfer == true)
                Console.WriteLine("Выполняем перевод через системы денежных переводов");
            else if (Successor != null)
                Successor.Handle(receiver);
        }
    }

    internal static class TestChain {
        public static void ShowResult() {
            Receiver receiver = new Receiver(false, true, true);
            PaymentHandler bankPaymentHandler = new BankPaymentHandler();
            PaymentHandler moneyPaymentHadler = new MoneyPaymentHandler();
            PaymentHandler paypalPaymentHandler = new PayPalPaymentHandler();
            bankPaymentHandler.Successor = paypalPaymentHandler;
            paypalPaymentHandler.Successor = moneyPaymentHadler;
            bankPaymentHandler.Handle(receiver);
        }
    }
}