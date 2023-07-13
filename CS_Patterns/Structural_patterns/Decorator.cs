/* Паттерн Декоратор (Decorator) */
/* Источник - https://metanit.com/sharp/patterns/4.1.php и др. */

/* Декоратор (Decorator) представляет структурный шаблон проектирования, который позволяет
 * динамически подключать к объекту дополнительную функциональность.
 * Для определения нового функционала в классах нередко используется наследование.
 * Декораторы же предоставляет наследованию более гибкую альтернативу, поскольку позволяют
 * динамически в процессе выполнения определять новые возможности у объектов.

 - Когда следует использовать декораторы?
 - Когда надо динамически добавлять к объекту новые функциональные возможности. 
 - При этом данные возможности могут быть сняты с объекта
 - Когда применение наследования неприемлемо. Например, если нам надо определить множество
 - различных функциональностей и для каждой функциональности наследовать отдельный класс, 
 - то структура классов может очень сильно разрастись. Еще больше она может разрастись, если нам
 - необходимо создать классы, реализующие все возможные сочетания добавляемых функциональностей.
 */

// Концепция паттерна "Декоратор"
namespace Сonception {

    // Component: абстрактный класс, который определяет интерфейс для наследуемых объектов
    abstract class Component {
        public abstract void Operation();
    }

    // ConcreteComponent: конкретная реализация компонента, в которую с помощью
    // декоратора добавляется новая функциональность
    class ConcreteComponent : Component {
        public override void Operation() { }
    }

    // Decorator: реализуется в виде абстрактного класса и имеет тот же базовый класс,
    // что и декорируемые объекты. Поэтому базовый класс Component должен быть по возможности
    // легким и определять только базовый интерфейс.
    // Класс декоратора также хранит ссылку на декорируемый объект в виде объекта базового класса
    // Component и реализует связь с базовым классом как через наследование,
    // так и через отношение агрегации.
    abstract class Decorator : Component {
        protected Component component;

        public void SetComponent(Component component) {
            this.component = component;
        }
        public override void Operation() {
            if (component != null)
                component.Operation();
        }
    }

    // Классы ConcreteDecoratorA и ConcreteDecoratorB представляют дополнительные
    // функциональности, которыми должен быть расширен объект ConcreteComponent.
    class ConcreteDecoratorA : Decorator {
        public override void Operation() {
            base.Operation();
        }
    }

    class ConcreteDecoratorB : Decorator {
        public override void Operation() {
            base.Operation();
        }
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Декоратор"
//--------------------------------------------------------------
namespace Patterns.Structural {

    internal abstract class Pizza {
        public Pizza(string n) { Name = n; }
        public string Name { get; protected set; }
        public abstract int GetCost();
    }

    internal class ItalianPizza : Pizza {
        public ItalianPizza() : base("Итальянская пицца") { }
        public override int GetCost() { return 10; }
    }

    internal class BulgerianPizza : Pizza {
        public BulgerianPizza() : base("Болгарская пицца") { }
        public override int GetCost() { return 8; }
    }

    internal abstract class PizzaDecorator : Pizza {
        protected Pizza pizza;
        public PizzaDecorator(string n, Pizza pizza) : base(n) {
            this.pizza = pizza;
        }
    }

    internal class TomatoPizza : PizzaDecorator {
        public TomatoPizza(Pizza p)
            : base(p.Name + ", с томатами", p) { }

        public override int GetCost() {
            return pizza.GetCost() + 3;
        }
    }

    internal class CheesePizza : PizzaDecorator {
        public CheesePizza(Pizza p)
            : base(p.Name + ", с сыром", p) { }

        public override int GetCost() {
            return pizza.GetCost() + 5;
        }
    }

    internal static class TestDecorator {
        public static void ShowResult() {
            Pizza pizza1 = new ItalianPizza();
            pizza1 = new TomatoPizza(pizza1); // итальянская пицца с томатами
            Console.WriteLine("Название: {0}", pizza1.Name);
            Console.WriteLine("Цена: {0}", pizza1.GetCost());

            Pizza pizza2 = new ItalianPizza();
            pizza2 = new CheesePizza(pizza2);// итальянская пиццы с сыром
            Console.WriteLine("Название: {0}", pizza2.Name);
            Console.WriteLine("Цена: {0}", pizza2.GetCost());

            Pizza pizza3 = new BulgerianPizza();
            pizza3 = new TomatoPizza(pizza3);
            pizza3 = new CheesePizza(pizza3);// болгарская пиццы с томатами и сыром
            Console.WriteLine("Название: {0}", pizza3.Name);
            Console.WriteLine("Цена: {0}", pizza3.GetCost());
        }
    }
}