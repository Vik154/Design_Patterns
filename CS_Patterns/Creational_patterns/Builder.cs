/* Паттерн "Строитель" (Builder) */
/* Источник - https://metanit.com/sharp/patterns/2.5.php и др. */

// Строитель (Builder) - шаблон проектирования, который инкапсулирует
// создание объекта и позволяет разделить его на различные этапы.
// Участники:
// 1. Builder определяет интерфейс конструирования продукта по частям;
// 2. Director управляет процессом создания, не зная, какой продукт будет создан в результате;
// 3. ConcreteBuilder — конкретный строитель, который создает только известный ему объект класса Product

namespace Patterns.Creational;

// Концепция паттерна:
internal class Director {
    Builder builder;
    public Director(Builder builder) {
        this.builder = builder;
    }
    public void Construct() {
        builder.BuildPartA();
        builder.BuildPartB();
        builder.BuildPartC();
    }
}

internal abstract class Builder {
    public abstract void BuildPartA();
    public abstract void BuildPartB();
    public abstract void BuildPartC();
    public abstract BProduct GetResult();
}

internal class BProduct {
    List<object> parts = new List<object>();
    public void Add(string part) {
        parts.Add(part);
    }
}

internal class ConcreteBuilder : Builder {
    BProduct product = new BProduct();
    public override void BuildPartA() {
        product.Add("Part A");
    }
    public override void BuildPartB() {
        product.Add("Part B");
    }
    public override void BuildPartC() {
        product.Add("Part C");
    }
    public override BProduct GetResult() {
        return product;
    }
}

//----------------------------------------------------
// Реализация паттерна "Строитель"
//----------------------------------------------------
// Класс - Product
internal class Pizza {
    private string? _dough = "", _sauce = "", _topping = "";

    public void SetDough(string dough)     { _dough = dough; }
    public void SetSauce(string sauce)     { _sauce = sauce; }
    public void SetTopping(string topping) { _topping = topping; }

    public void Show() {
        Console.WriteLine($"Pizza consists of {_dough}, {_sauce}, {_topping}");
    }
}

// Интерфейс - Builder(строитель)
internal interface IPizzaBuilder {
    void SetDough();
    void SetSauce();
    void SetTopping();
    Pizza GetPizza();
}

// Класс - ConcreteBuilder
internal class PizzaBuilder : IPizzaBuilder {
    private Pizza _pizza = new Pizza();

    public void SetDough()   { _pizza.SetDough("cross"); }
    public void SetSauce()   { _pizza.SetSauce("mild"); }
    public void SetTopping() { _pizza.SetTopping("ham+pineapple"); }
    public Pizza GetPizza()  { return _pizza; }
}

// Класс - Director
internal class Waiter {
    private IPizzaBuilder? _pizzaBuilder;

    public void SetPizzaBuilder(IPizzaBuilder pizzaBuilder) {
        _pizzaBuilder = pizzaBuilder;
    }
    public Pizza GetPizza() {
        return _pizzaBuilder.GetPizza();
    }
    public void ConstructPizza() {
        _pizzaBuilder.SetDough();
        _pizzaBuilder.SetSauce();
        _pizzaBuilder.SetTopping();
    }
}
//----------------------------------------------------
// Тест паттерна
internal static class TestBuilder {

    static public void ShowResult() {
        var director = new Waiter();
        var builder = new PizzaBuilder();
        director.SetPizzaBuilder(builder);
        director.ConstructPizza();
        var product = builder.GetPizza();
        product.Show();
    }
}