/* Паттерн Фасад (Facade) */
/* Источник - https://metanit.com/sharp/patterns/4.3.php и др. */

/* Фасад (Facade) представляет шаблон проектирования, который позволяет скрыть сложность системы
 * с помощью предоставления упрощенного интерфейса для взаимодействия с ней.

 - Когда использовать фасад?
 - Когда имеется сложная система, и необходимо упростить с ней работу. Фасад позволит определить
 - одну точку взаимодействия между клиентом и системой.
 - Когда надо уменьшить количество зависимостей между клиентом и сложной системой. 
 - Фасадные объекты позволяют отделить, изолировать компоненты системы от клиента и развивать 
 - и работать с ними независимо.
 - Когда нужно определить подсистемы компонентов в сложной системе. Создание фасадов для 
 - компонентов каждой отдельной подсистемы позволит упростить взаимодействие между ними и
 - повысить их независимость друг от друга.
 */

// Концепция паттерна "Фасад"
namespace Сonception {

    // Классы SubsystemA, SubsystemB, SubsystemC и т.д. являются компонентами сложной
    // подсистемы, с которыми должен взаимодействовать клиент
    internal class SubsystemA {
        public void A1() { }
    }

    internal class SubsystemB {
        public void B1() { }
    }

    internal class SubsystemC {
        public void C1() { }
    }

    // Facade - непосредственно фасад, который предоставляет интерфейс клиенту
    // для работы с компонентами
    internal class Facade {
        SubsystemA subsystemA;
        SubsystemB subsystemB;
        SubsystemC subsystemC;

        public Facade(SubsystemA sa, SubsystemB sb, SubsystemC sc) {
            subsystemA = sa;
            subsystemB = sb;
            subsystemC = sc;
        }

        public void Operation1() {
            subsystemA.A1();
            subsystemB.B1();
            subsystemC.C1();
        }
        public void Operation2() {
            subsystemB.B1();
            subsystemC.C1();
        }
    }

    /*
    internal class Client {
        public void Main() {
            Facade facade = new Facade(new SubsystemA(), new SubsystemB(), new SubsystemC());
            facade.Operation1();
            facade.Operation2();
        }
    }
    */
}

//--------------------------------------------------------------
// Реализация паттерна "Фасад"
//--------------------------------------------------------------
namespace Patterns.Structural {

    // текстовый редактор
    internal class TextEditor {
        public void CreateCode() {
            Console.WriteLine("Написание кода");
        }
        public void Save() {
            Console.WriteLine("Сохранение кода");
        }
    }

    internal class Compiller {
        public void Compile() {
            Console.WriteLine("Компиляция приложения");
        }
    }

    internal class CLR {
        public void Execute() {
            Console.WriteLine("Выполнение приложения");
        }
        public void Finish() {
            Console.WriteLine("Завершение работы приложения");
        }
    }

    internal class VisualStudioFacade {
        TextEditor textEditor;
        Compiller compiller;
        CLR clr;
        public VisualStudioFacade(TextEditor te, Compiller compil, CLR clr) {
            this.textEditor = te;
            this.compiller = compil;
            this.clr = clr;
        }
        public void Start() {
            textEditor.CreateCode();
            textEditor.Save();
            compiller.Compile();
            clr.Execute();
        }
        public void Stop() {
            clr.Finish();
        }
    }

    internal class Programmer {
        public void CreateApplication(VisualStudioFacade facade) {
            facade.Start();
            facade.Stop();
        }
    }

    internal static class TestFacade {
        public static void ShowResult() {
            TextEditor textEditor = new TextEditor();
            Compiller compiller = new Compiller();
            CLR clr = new CLR();

            VisualStudioFacade ide = new VisualStudioFacade(textEditor, compiller, clr);
            Programmer programmer = new Programmer();
            programmer.CreateApplication(ide);
        }
    }
}