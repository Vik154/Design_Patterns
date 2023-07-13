/* Паттерн "Абстрактная фабрика" (Abstract Factory) */
/* Источник - https://metanit.com/sharp/patterns/2.2.php и др. */

namespace Patterns.Creational;

// Когда использовать абстрактную фабрику:
// Когда система не должна зависеть от способа создания и компоновки новых объектов
// Когда создаваемые объекты должны использоваться вместе и являются взаимосвязанными

// Формальное определение паттерна на языке C# может выглядеть следующим образом:
// Абстрактная фабрика - 
abstract class AbstractFactory {
    public abstract AbstractProductA CreateProductA();
    public abstract AbstractProductB CreateProductB();
}

class ConcreteFactory1 : AbstractFactory {
    public override AbstractProductA CreateProductA() {
        return new ProductA1();
    }

    public override AbstractProductB CreateProductB() {
        return new ProductB1();
    }
}
class ConcreteFactory2 : AbstractFactory {
    public override AbstractProductA CreateProductA() {
        return new ProductA2();
    }

    public override AbstractProductB CreateProductB() {
        return new ProductB2();
    }
}

abstract class AbstractProductA { }

abstract class AbstractProductB { }

class ProductA1 : AbstractProductA { }

class ProductB1 : AbstractProductB { }

class ProductA2 : AbstractProductA { }

class ProductB2 : AbstractProductB { }

class Client {
    private AbstractProductA abstractProductA;
    private AbstractProductB abstractProductB;

    public Client(AbstractFactory factory) {
        abstractProductB = factory.CreateProductB();
        abstractProductA = factory.CreateProductA();
    }
    public void Run() { }
}

//------------------------------------------------------
// Реализация паттерна
//------------------------------------------------------
internal interface IBeverageFactory {       // Абстракная фабрика напитков
    public ICoolDrinks CreateCoolDrinks();  // Абстрактный продукт (охлажденные напитки)
    public IHotDrinks CreateHotDrinks();    // Абстракный продукт (горячие напитки)
}

internal interface ICoolDrinks {            // Абстракный продукт (холодные напитки)
    public string MakeCoolProduct();        // Условная логика, которую нужно реализовать
}

internal interface IHotDrinks {             // Абстракный продукт (горячие напитки) 
    public string MakeHotProduct();         // Условная логика, которую нужно реализовать
}

internal class Cofee : IHotDrinks {
    public string MakeHotProduct() { return "Кофе готов!"; }
}

internal class HotTea : IHotDrinks {
    public string MakeHotProduct() { return "Горячий чай готов!"; }
}

internal class IceTea : ICoolDrinks {
    public string MakeCoolProduct() { return "Холодный чай готов!"; }
}

internal class Juice : ICoolDrinks {
    public string MakeCoolProduct() { return "Сок готов!"; }
}

// Конкретная фабрика по производству сока и горячего чая
internal class GreenFactory : IBeverageFactory {
    public ICoolDrinks CreateCoolDrinks() {
        return new Juice();
    }
    public IHotDrinks CreateHotDrinks() {
        return new HotTea();
    }
}

// Конкретная фабрика по производству кофе и холодного чая
internal class RedFactory : IBeverageFactory {
    public ICoolDrinks CreateCoolDrinks() {
        return new IceTea();
    }
    public IHotDrinks CreateHotDrinks() {
        return new Cofee();
    }
}

// Класс клиента, использование фабрики
internal class Clients {
    public Clients(IBeverageFactory abstract_factory) {
        _hotDrinks = abstract_factory.CreateHotDrinks();
        _coolDrinks = abstract_factory.CreateCoolDrinks();
    }
    private IHotDrinks?  _hotDrinks;
    private ICoolDrinks? _coolDrinks;

    public void ShowResult() {
        var hotres = _hotDrinks?.MakeHotProduct();
        var iceres = _coolDrinks?.MakeCoolProduct();
        Console.WriteLine($"Оповещение фабрики: {hotres} и {iceres}");
    }
}

internal static class TestAbstractFactory {
    
    public static void ShowResult() {
        RedFactory redFactory = new RedFactory();
        Clients abstractFactory = new Clients(redFactory);
        abstractFactory.ShowResult();
    }
}