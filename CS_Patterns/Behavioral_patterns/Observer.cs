/* Паттерн "Наблюдатель" (Observer) */
/* Источник - https://metanit.com/sharp/patterns/3.2.php и др. */

/* Паттерн "Наблюдатель" - использует отношение "один ко многим". 
 * В этом отношении есть один наблюдаемый объект и множество наблюдателей. 
 * И при изменении наблюдаемого объекта автоматически происходит оповещение всех наблюдателей.
 * Данный паттерн еще называют Publisher-Subscriber (издатель-подписчик), 
 * поскольку отношения издателя и подписчиков характеризуют действие данного паттерна: 
 * подписчики подписываются email-рассылку определенного сайта. 
 * Сайт-издатель с помощью email-рассылки уведомляет всех подписчиков о изменениях. 
 * А подписчики получают изменения и производят определенные действия:
 * могут зайти на сайт, могут проигнорировать уведомления и т.д.
 */

namespace Сonception {
    // Концепция паттерна "Наблюдатель"
    // IObservable: представляет наблюдаемый объект.
    // Определяет три метода: AddObserver() (для добавления наблюдателя),
    // RemoveObserver() (удаление набюдателя) и NotifyObservers() (уведомление наблюдателей)
    internal interface IObservable {
        void AddObserver(IObserver o);
        void RemoveObserver(IObserver o);
        void NotifyObservers();
    }

    // Конкретная реализация интерфейса IObservable. Определяет коллекцию объектов наблюдателей.
    internal class ConcreteObservable : IObservable {
        private List<IObserver> observers;
        public ConcreteObservable() {
            observers = new List<IObserver>();
        }
        public void AddObserver(IObserver o) {
            observers.Add(o);
        }
        public void RemoveObserver(IObserver o) {
            observers.Remove(o);
        }
        public void NotifyObservers() {
            foreach (IObserver observer in observers)
                observer.Update();
        }
    }

    // IObserver: представляет наблюдателя, который подписывается на все уведомления
    // наблюдаемого объекта. Определяет метод Update(), который вызывается наблюдаемым
    // объектом для уведомления наблюдателя.
    internal interface IObserver {
        void Update();
    }

    // ConcreteObserver: конкретная реализация интерфейса IObserver.
    internal class ConcreteObserver : IObserver {
        public void Update() { }
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Наблюдатель"
//--------------------------------------------------------------
namespace Patterns.Behavioral {
    
    internal interface IObserver {
        void Update(Object ob);
    }

    internal interface IObservable {
        void RegisterObserver(IObserver o);
        void RemoveObserver(IObserver o);
        void NotifyObservers();
    }

    internal class StockInfo {
        public int USD  { get; set; }
        public int Euro { get; set; }
    }

    internal class Stock : IObservable {
        private StockInfo stockInfo;        // Информация о торгах
        private List<IObserver> observers;  // Коллекция наблюдателей

        public Stock() { stockInfo = new(); observers = new(); }

        public void RemoveObserver(IObserver obs) {
            observers.Remove(obs);    
        }
        public void RegisterObserver(IObserver obs) {
            observers.Add(obs);
        }
        public void NotifyObservers() {
            foreach (IObserver obs in observers)
                obs.Update(stockInfo);
        }
        public void Market() {
            Random random = new();
            stockInfo.Euro = random.Next(30, 50);
            stockInfo.USD = random.Next(20, 40);
        }
    }

    internal class Broker : IObserver {

        public string Name { get; set; }
        private IObservable? stock;

        public Broker(string name, IObservable observable) {
            Name = name;
            stock = observable;
            stock.RegisterObserver(this);
        }
        public void Update(object ob) {
            StockInfo? stockInfo = ob as StockInfo;
            if (stockInfo?.USD > 30)
                Console.WriteLine($"Брокер {Name} продает доллары;  Курс доллара: {stockInfo.USD}");
            else
                Console.WriteLine($"Брокер {Name} покупает доллары;  Курс доллара: {stockInfo?.USD}");
        }
        public void StopTrade() {
            stock?.RemoveObserver(this);
            stock = null;
        }
    }

    class Bank : IObserver {
        public string Name { get; set; }
        IObservable stock;

        public Bank(string name, IObservable obs) {
            Name = name;
            stock = obs;
            stock.RegisterObserver(this);
        }
        public void Update(object ob) {
            StockInfo sInfo = (StockInfo)ob;
            if (sInfo.Euro > 40)
                Console.WriteLine("Банк {0} продает евро;  Курс евро: {1}", Name, sInfo.Euro);
            else
                Console.WriteLine("Банк {0} покупает евро;  Курс евро: {1}", Name, sInfo.Euro);
        }
    }

    internal static class TestObserver {
        public static void ShowResult() {
            Stock stock = new Stock();
            StockInfo stockInfo = new StockInfo();
            stockInfo.Euro = 90;
            stockInfo.USD = 78;
            Bank bank = new Bank("ЮнитБанк", stock);
            Broker broker = new Broker("Иван Иваныч", stock);
            // имитация торгов
            stock.Market();
            bank.Update(stockInfo);
            // брокер прекращает наблюдать за торгами
            broker.StopTrade();
            broker.Update(stockInfo);
            // имитация торгов
            stock.Market();
        } 
    }
}