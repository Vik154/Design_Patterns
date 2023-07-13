/* Паттерн Посетитель (Visitor) */
/* Источник - https://metanit.com/sharp/patterns/3.11.php и др. */

/* Паттерн Посетитель (Visitor) позволяет определить операцию для объектов других классов
 * без изменения этих классов. При использовании паттерна Посетитель определяются две иерархии
 * классов: одна для элементов, для которых надо определить новую операцию, и вторая иерархия 
 * для посетителей, описывающих данную операцию.
 - Когда использовать данный паттерн?
 - Когда имеется много объектов разнородных классов с разными интерфейсами, и требуется выполнить
 - ряд операций над каждым из этих объектов
 - Когда классам необходимо добавить одинаковый набор операций без изменения этих классов
 - Когда часто добавляются новые операции к классам, при этом общая структура классов стабильна
 - и практически не изменяется
 */

// Концепция паттерна "Посетитель"
namespace Сonception {

    // Visitor: интерфейс посетителя, который определяет метод Visit()
    // для каждого объекта Element
    abstract class Visitor {
        public abstract void VisitElementA(ElementA elemA);
        public abstract void VisitElementB(ElementB elemB);
    }

    // ConcreteVisitor1 / ConcreteVisitor2: конкретные классы посетителей,
    // реализуют интерфейс, определенный в Visitor.
    class ConcreteVisitor1 : Visitor {
        public override void VisitElementA(ElementA elementA) {
            elementA.OperationA();
        }
        public override void VisitElementB(ElementB elementB) {
            elementB.OperationB();
        }
    }

    class ConcreteVisitor2 : Visitor {
        public override void VisitElementA(ElementA elementA) {
            elementA.OperationA();
        }
        public override void VisitElementB(ElementB elementB) {
            elementB.OperationB();
        }
    }

    // ObjectStructure: некоторая структура, которая хранит объекты Element и предоставляет к ним доступ.
    // Это могут быть и простые списки, и сложные составные структуры в виде деревьев
    class ObjectStructure {
        List<Element> elements = new List<Element>();
        public void Add(Element element) {
            elements.Add(element);
        }
        public void Remove(Element element) {
            elements.Remove(element);
        }
        public void Accept(Visitor visitor) {
            foreach (Element element in elements)
                element.Accept(visitor);
        }
    }

    // Определяет метод Accept(), в котором в качестве параметра принимается объект Visitor
    abstract class Element {
        public abstract void Accept(Visitor visitor);
        public string SomeState { get; set; }
    }

    // ElementA / ElementB: конкретные элементы, которые реализуют метод Accept()
    class ElementA : Element {
        public override void Accept(Visitor visitor) {
            visitor.VisitElementA(this);
        }
        public void OperationA() { }
    }

    class ElementB : Element {
        public override void Accept(Visitor visitor) {
            visitor.VisitElementB(this);
        }
        public void OperationB() { }
    }

    /*
    class Client {
        void Main() {
            var structure = new ObjectStructure();
            structure.Add(new ElementA());
            structure.Add(new ElementB());
            structure.Accept(new ConcreteVisitor1());
            structure.Accept(new ConcreteVisitor2());
        }
    }
    */
}

//--------------------------------------------------------------
// Реализация паттерна "Посетитель"
//--------------------------------------------------------------
namespace Patterns.Behavioral {

    internal interface IVisitor {
        void VisitPersonAcc(Person acc);
        void VisitCompanyAc(Company acc);
    }

    // сериализатор в HTML
    internal class HtmlVisitor : IVisitor {
        public void VisitPersonAcc(Person acc) {
            string result = "<table><tr><td>Свойство<td><td>Значение</td></tr>";
            result += "<tr><td>Name<td><td>" + acc.Name + "</td></tr>";
            result += "<tr><td>Number<td><td>" + acc.Number + "</td></tr></table>";
            Console.WriteLine(result);
        }

        public void VisitCompanyAc(Company acc) {
            string result = "<table><tr><td>Свойство<td><td>Значение</td></tr>";
            result += "<tr><td>Name<td><td>" + acc.Name + "</td></tr>";
            result += "<tr><td>RegNumber<td><td>" + acc.RegNumber + "</td></tr>";
            result += "<tr><td>Number<td><td>" + acc.Number + "</td></tr></table>";
            Console.WriteLine(result);
        }
    }

    // сериализатор в XML
    internal class XmlVisitor : IVisitor {
        public void VisitPersonAcc(Person acc) {
            string result = "<Person><Name>" + acc.Name + "</Name>" +
                "<Number>" + acc.Number + "</Number><Person>";
            Console.WriteLine(result);
        }

        public void VisitCompanyAc(Company acc) {
            string result = "<Company><Name>" + acc.Name + "</Name>" +
                "<RegNumber>" + acc.RegNumber + "</RegNumber>" +
                "<Number>" + acc.Number + "</Number><Company>";
            Console.WriteLine(result);
        }
    }

    internal class Bank2 {
        List<IAccount> accounts = new List<IAccount>();
        public void Add(IAccount acc) {
            accounts.Add(acc);
        }
        public void Remove(IAccount acc) {
            accounts.Remove(acc);
        }
        public void Accept(IVisitor visitor) {
            foreach (IAccount acc in accounts)
                acc.Accept(visitor);
        }
    }

    internal interface IAccount {
        void Accept(IVisitor visitor);
    }

    internal class Person : IAccount {
        public string Name { get; set; }
        public string Number { get; set; }

        public void Accept(IVisitor visitor) {
            visitor.VisitPersonAcc(this);
        }
    }

    internal class Company : IAccount {
        public string Name { get; set; }
        public string RegNumber { get; set; }
        public string Number { get; set; }

        public void Accept(IVisitor visitor) {
            visitor.VisitCompanyAc(this);
        }
    }

    internal static class TestVisitor {
        public static void ShowResult() {
            var structure = new Bank2();
            structure.Add(new Person { Name = "Иван Алексеев", Number = "82184931" });
            structure.Add(new Company { Name = "Microsoft", RegNumber = "ewuir32141324", Number = "3424131445" });
            structure.Accept(new HtmlVisitor());
            structure.Accept(new XmlVisitor());
        }
    }
}