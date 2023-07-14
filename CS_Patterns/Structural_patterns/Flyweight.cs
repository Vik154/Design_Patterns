/* Паттерн Приспособленец (Flyweight) */
/* Источник - https://metanit.com/sharp/patterns/4.7.php и др. */

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

// Концепция паттерна "Приспособленец"
using System.Collections;

namespace Сonception {

    // FlyweightFactory: фабрика приспособленцев - создает объекты разделяемых приспособленцев.
    // Так как приспособленцы разделяются, то клиент не должен создавать их напрямую.
    // Все созданные объекты хранятся в пуле. В примере выше для определения пула используется
    // объект Hashtable, но это не обязательно. Можно применять и другие классы коллекций.
    // Однако в зависимости от сложности структуры, хранящей разделяемые объекты,
    // особенно если у нас большое количество приспособленцев, то может увеличиваться время
    // на поиск нужного приспособленца - наверное это один из немногих недостатков данного паттерна.
    class FlyweightFactory {
        Hashtable flyweights = new Hashtable();
        public FlyweightFactory() {
            flyweights.Add("X", new ConcreteFlyweight());
            flyweights.Add("Y", new ConcreteFlyweight());
            flyweights.Add("Z", new ConcreteFlyweight());
        }
        public Flyweight GetFlyweight(string key) {
            if (!flyweights.ContainsKey(key))
                flyweights.Add(key, new ConcreteFlyweight());
            return flyweights[key] as Flyweight;
        }
    }

    // Flyweight: определяет интерфейс, через который приспособленцы-разделяемые объекты
    // могут получать внешнее состояние или воздействовать на него
    abstract class Flyweight {
        public abstract void Operation(int extrinsicState);
    }

    // ConcreteFlyweight: конкретный класс разделяемого приспособленца.
    // Реализует интерфейс, объявленный в типе Flyweight, и при необходимости добавляет
    // внутреннее состояние. Причем любое сохраняемое им состояние должно быть внутренним,
    // не зависящим от контекста
    class ConcreteFlyweight : Flyweight {
        // int intrinsicState;
        public override void Operation(int extrinsicState) { }
    }

    // UnsharedConcreteFlyweight: еще одна конкретная реализация интерфейса, определенного в
    // типе Flyweight, только теперь объекты этого класса являются неразделяемыми
    class UnsharedConcreteFlyweight : Flyweight {
        int allState;
        public override void Operation(int extrinsicState) {
            allState = extrinsicState;
        }
    }

    /*
    class Client {
        void Main() {
            int extrinsicstate = 22;

            FlyweightFactory f = new FlyweightFactory();

            Flyweight fx = f.GetFlyweight("X");
            fx.Operation(--extrinsicstate);

            Flyweight fy = f.GetFlyweight("Y");
            fy.Operation(--extrinsicstate);

            Flyweight fd = f.GetFlyweight("D");
            fd.Operation(--extrinsicstate);

            UnsharedConcreteFlyweight uf = new UnsharedConcreteFlyweight();

            uf.Operation(--extrinsicstate);
        }
    }
    */
}

//--------------------------------------------------------------
// Реализация паттерна "Приспособленец"
//--------------------------------------------------------------
namespace Patterns.Structural {

    internal abstract class House {
        protected int stages; // количество этажей
        public abstract void Build(double longitude, double latitude);
    }

    internal class PanelHouse : House {
        public PanelHouse() { stages = 16; }
        public override void Build(double longitude, double latitude) {
            Console.WriteLine("Построен панельный дом из 16 этажей; координаты: {0} широты и {1} долготы",
                latitude, longitude);
        }
    }

    internal class BrickHouse : House {
        public BrickHouse() {
            stages = 5;
        }
        public override void Build(double longitude, double latitude) {
            Console.WriteLine("Построен кирпичный дом из 5 этажей; координаты: {0} широты и {1} долготы",
                latitude, longitude);
        }
    }

    internal class HouseFactory {
        Dictionary<string, House> houses = new Dictionary<string, House>();
        public HouseFactory() {
            houses.Add("Panel", new PanelHouse());
            houses.Add("Brick", new BrickHouse());
        }
        public House GetHouse(string key) {
            if (houses.ContainsKey(key))
                return houses[key];
            else
                return null;
        }
    }

    internal static class TestFlyweight {
        public static void ShowResult() {
            double longitude = 37.61;
            double latitude = 55.74;

            HouseFactory houseFactory = new HouseFactory();
            for (int i = 0; i < 5; i++) {
                House panelHouse = houseFactory.GetHouse("Panel");
                if (panelHouse != null)
                    panelHouse.Build(longitude, latitude);
                longitude += 0.1;
                latitude += 0.1;
            }

            for (int i = 0; i < 5; i++) {
                House brickHouse = houseFactory.GetHouse("Brick");
                if (brickHouse != null)
                    brickHouse.Build(longitude, latitude);
                longitude += 0.1;
                latitude += 0.1;
            }
        }
    }
}