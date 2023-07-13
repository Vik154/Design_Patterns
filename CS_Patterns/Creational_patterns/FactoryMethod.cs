/// <summary> Фабричный метод (Factory Method) </summary> ///
/* Источник - https://metanit.com/sharp/patterns/2.1.php */

namespace Patterns.Creational;

/* Когда надо применять паттерн:
 * Когда заранее неизвестно, объекты каких типов необходимо создавать
 * Когда система должна быть независимой от процесса создания новых объектов и расширяемой:
   в нее можно легко вводить новые классы, объекты которых система должна создавать.
 * Когда создание новых объектов необходимо делегировать из базового класса классам наследникам
 */

// определение паттерна может выглядеть следующим образом:
/// <summary> Product - определяет интерфейс класса, объекты которого надо создавать </summary>
internal abstract class Product {};
internal class ConcreteProductA : Product {};   // представляет реализацию класса Product.
internal class ConcreteProductB : Product {};   // представляет реализацию класса Product.

// Creator - определяет абстрактный фабричный метод FactoryMethod(),
// который возвращает объект Product.
internal abstract class Creator {
    public abstract Product FactoryMethod();
};

// Конкретные классы ConcreteCreatorA и ConcreteCreatorB - наследники класса Creator,
// определяющие свою реализацию метода FactoryMethod(). Причем метод FactoryMethod()
// каждого отдельного класса-создателя возвращает определенный конкретный тип продукта.
// Для каждого конкретного класса продукта определяется свой конкретный класс создателя.
class ConcreteCreatorA : Creator {
    public override Product FactoryMethod() { return new ConcreteProductA(); }
}

class ConcreteCreatorB : Creator {
    public override Product FactoryMethod() { return new ConcreteProductB(); }
}

//-----------------------------------------------------------------------------------------
// Реализация паттерна:
//-----------------------------------------------------------------------------------------
internal abstract class House {};

internal class PanelHouse : House {
    public PanelHouse() { Console.WriteLine("Панельный дом построен, каким-то чудом!"); }
}

internal class WoodHouse : House {
    public WoodHouse() { Console.WriteLine("Деревянный дом построен, 300 беспаспортанцами!"); }
}

internal class BrickHouse : House {
    public BrickHouse() { Console.WriteLine("Кирпичный дом из кирпичей построен!"); }
}

internal class MonolithicHouse : House {
    public MonolithicHouse() { Console.WriteLine("Монолитный дом построен, не входить!"); }
}
//-----------------------------------------------------------------------------------------
internal abstract class Developer {
    
    public Developer(string name) {
        Name = name;
    }
    public string? Name { get; init; }
    public abstract House Create();
}

internal class PanelDeveloper : Developer {
    
    public PanelDeveloper(string name) : base(name) {}
    public override House Create() { return new PanelHouse(); }
}

internal class WoodDeveloper : Developer {

    public WoodDeveloper(string name) : base(name) {}
    public override House Create() { return new WoodHouse(); }
}

internal class BrickDeveloper : Developer {

    public BrickDeveloper(string name) : base(name) {}
    public override House Create() { return new BrickHouse(); }
}

internal class MonolithicDeveloper : Developer {

    public MonolithicDeveloper(string name) : base(name) {}
    public override House Create() { return new MonolithicHouse(); }
}
//-----------------------------------------------------------------------------------------

/// <summary> Класс для теста паттерна "Фабричный метод" из main </summary>
internal static class TestFactoryMethod { 
    
    public static void ShowResult() {
        List<Developer>  DeveloperList = new List<Developer> {
            new PanelDeveloper("ООО \"Шараш-Монтаж Строй\""),
            new WoodDeveloper("ООО \"ВровеньВыпирает Строй\""),
            new BrickDeveloper("ООО \"МонтажКосяк Строй\""),
            new MonolithicDeveloper("ООО \"РукиОткудаНАДА Строй\"")
        };
        for (int i = 0; i < 4; ++i) {
            Console.Write($"Компания: {DeveloperList?[i].Name}\tЗаявляет: ");
            DeveloperList?[i].Create();
        }
    }
}