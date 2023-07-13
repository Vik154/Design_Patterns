using Patterns.Behavioral;
using Patterns.Creational;
using Patterns.Structural;


namespace Patterns {

    internal class Program {
        static void Main(string[] args) {
            ShowResult show = new ShowResult();
            show.Run();
        }
    }

    /// <summary> Консольное отображение </summary>
    internal class ShowResult {

        public void Run() {
            string? result;
            string info = "\nВыберите команду:" +
                "\nq  - Выход" +
                "\n1  - Паттерн \"Фабричный метод\"" +
                "\n2  - Паттерн \"Абстрактная фаюрика\"" +
                "\n3  - Паттерн \"Одиночка\"" +
                "\n4  - Паттерн \"Прототип\"" +
                "\n5  - Паттерн \"Строитель\"" +
                "\n6  - Паттерн \"Стратегия\"" +
                "\n7  - Паттерн \"Наблюдатель\"" +
                "\n8  - Паттерн \"Команда\"" +
                "\n9  - Паттерн \"Шаблонный метод\"" +
                "\n10 - Паттерн \"Итератор\"" +
                "\n11 - Паттерн \"Состояние\"" +
                "\n12 - Паттерн \"Цепочка Обязанностей\"" +
                "\n13 - Паттерн \"Интерпретатор\"" +
                "\n14 - Паттерн \"Посредник\"" +
                "\n15 - Паттерн \"Хранитель\"" +
                "\n16 - Паттерн \"Посетитель\"" +
                "\n17 - Паттерн \"Декоратор\"" +
                "\n18 - Паттерн \"Адаптер\"" +
                "\n19 - Паттерн \"Фасад\"" +
                "\n20 - Паттерн \"Компоновщик\"" +
                "\n";

            while (true) {
                Console.WriteLine(info);
                result = Console.ReadLine();
                Console.Write('\r');
                switch (result) {
                    case "й": case "q": case "Q": case "Й":     return;
                    case "1": TestFactoryMethod.ShowResult();   break;
                    case "2": TestAbstractFactory.ShowResult(); break;
                    case "3": TestSingleton.ShowResult();       break;
                    case "4": TestPrototype.ShowResult();       break;
                    case "5": TestBuilder.ShowResult();         break;
                    case "6": TestStrategy.ShowResult();        break;
                    case "7": TestObserver.ShowResult();        break;
                    case "8": TestCommand.ShowResult();         break;
                    case "9": TestTemplate.ShowResult();        break;
                    case "10": TestIterator.ShowResult();       break;
                    case "11": TestState.ShowResult();          break;
                    case "12": TestChain.ShowResult();          break;
                    case "13": TestInterpreter.ShowResult();    break;
                    case "14": TestMediator.ShowResult();       break;
                    case "15": TestMemento.ShowResult();        break;
                    case "16": TestVisitor.ShowResult();        break;
                    case "17": TestDecorator.ShowResult();      break;
                    case "18": TestAdapter.ShowResult();        break;
                    case "19": TestFacade.ShowResult();         break;
                    case "20": TestComposite.ShowResult();      break;
                    default:
                        Console.WriteLine("Такой команды нет, не тыкай чё-попало!");
                        break;
                } // switch
            } // while
        } // Run()
    } // class ShowResult
}