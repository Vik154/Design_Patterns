/* Паттерн Мост (Bridge) */
/* Источник - https://metanit.com/sharp/patterns/4.6.php и др. */

/* Мост (Bridge) - структурный шаблон проектирования, который позволяет отделить абстракцию 
 * от реализации таким образом, чтобы и абстракцию, и реализацию можно было изменять независимо
 * друг от друга. Даже если мы отделим абстракцию от конкретных реализаций, то у нас все равно
 * все наследуемые классы будут жестко привязаны к интерфейсу, определяемому в базовом 
 * абстрактном классе. Для преодоления жестких связей и служит паттерн Мост.

 - Когда использовать данный паттерн?
 - Когда надо избежать постоянной привязки абстракции к реализации
 - Когда наряду с реализацией надо изменять и абстракцию независимо друг от друга. 
 - То есть изменения в абстракции не должно привести к изменениям в реализации
 */

// Концепция паттерна "Мост"
namespace Сonception {

    // Abstraction: определяет базовый интерфейс и хранит ссылку на объект Implementor.
    // Выполнение операций в Abstraction делегируется методам объекта Implementor
    abstract class Abstraction {
        protected Implementor implementor;
        public Implementor Implementor {
            set { implementor = value; }
        }
        public Abstraction(Implementor imp) {
            implementor = imp;
        }
        public virtual void Operation() {
            implementor.OperationImp();
        }
    }

    // Implementor: определяет базовый интерфейс для конкретных реализаций. Как правило,
    // Implementor определяет только примитивные операции. Более сложные операции, которые
    // базируются на примитивных, определяются в Abstraction
    abstract class Implementor {
        public abstract void OperationImp();
    }

    // RefinedAbstraction: уточненная абстракция, наследуется от Abstraction
    // и расширяет унаследованный интерфейс
    class RefinedAbstraction : Abstraction {
        public RefinedAbstraction(Implementor imp)
            : base(imp) { }
        public override void Operation() { }
    }

    // ConcreteImplementorA и ConcreteImplementorB: конкретные реализации,
    // которые унаследованы от Implementor
    class ConcreteImplementorA : Implementor {
        public override void OperationImp() { }
    }

    class ConcreteImplementorB : Implementor {
        public override void OperationImp() { }
    }

    /*
    class Client {
        static void Main() {
            Abstraction abstraction;
            abstraction = new RefinedAbstraction(new ConcreteImplementorA());
            abstraction.Operation();
            abstraction.Implementor = new ConcreteImplementorB();
            abstraction.Operation();
        }
    }
     */
}

//--------------------------------------------------------------
// Реализация паттерна "Мост"
//--------------------------------------------------------------
namespace Patterns.Structural {

    internal interface ILanguage {
        void Build();
        void Execute();
    }

    internal class CPPLanguage : ILanguage {
        public void Build() {
            Console.WriteLine("С помощью компилятора C++ компилируем программу в бинарный код");
        }
        public void Execute() {
            Console.WriteLine("Запускаем исполняемый файл программы");
        }
    }

    internal class CSharpLanguage : ILanguage {
        public void Build() {
            Console.WriteLine("С помощью компилятора Roslyn компилируем исходный код в файл exe");
        }
        public void Execute() {
            Console.WriteLine("JIT компилирует программу бинарный код");
            Console.WriteLine("CLR выполняет скомпилированный бинарный код");
        }
    }

    internal abstract class Programmer2 {
        protected ILanguage language;
        public ILanguage Language {
            set { language = value; }
        }
        public Programmer2(ILanguage lang) {
            language = lang;
        }
        public virtual void DoWork() {
            language.Build();
            language.Execute();
        }
        public abstract void EarnMoney();
    }

    internal class FreelanceProgrammer : Programmer2 {
        public FreelanceProgrammer(ILanguage lang) : base(lang) { }
        public override void EarnMoney() {
            Console.WriteLine("Получаем оплату за выполненный заказ");
        }
    }

    internal class CorporateProgrammer : Programmer2 {
        public CorporateProgrammer(ILanguage lang) : base(lang) { }
        public override void EarnMoney() {
            Console.WriteLine("Получаем в конце месяца зарплату");
        }
    }

    internal static class TestBridge {
        public static void ShowResult() {
            // создаем нового программиста, он работает с с++
            Programmer2 freelancer = new FreelanceProgrammer(new CPPLanguage());
            freelancer.DoWork();
            freelancer.EarnMoney();
            // пришел новый заказ, но теперь нужен c#
            freelancer.Language = new CSharpLanguage();
            freelancer.DoWork();
            freelancer.EarnMoney();
        }
    }
}