

using Patterns.Creational;

namespace Patterns {
    internal class Program {

        static void Main(string[] args) {
            ShowResult show = new ShowResult();
            show.Run();
        }
    }

    /// <summary> Консольное отображение </summary>
    internal class ShowResult {

        public ShowResult() { 
            // ---- Фабричный метод ---------
            Factory = new Patterns.Creational.FactoryMethod();
            // ---- Абстракная фабрика ------
            RedFactory = new RedFactory();
            AbstractFactory = new Patterns.Creational.Clients(RedFactory);
        }

        /// <summary> Паттерн - "Фабричный метод" </summary>
        private readonly Patterns.Creational.FactoryMethod? Factory;
        
        /// <summary> Паттерн - "Абстрактная фаюрика" </summary>
        private readonly Patterns.Creational.Clients? AbstractFactory;
        private RedFactory RedFactory;

        public void Run() {
            ConsoleKey result;
            string info = "\nВыберите команду:" +
                "\nq - Выход" +
                "\n1 - Паттерн \"Фабричный метод\"" +
                "\n2 - Паттерн \"Абстрактная фаюрика\"\n";
            do {
                Console.WriteLine(info);
                result = Console.ReadKey().Key;
                Console.Write('\r');
                switch (result) {
                    case ConsoleKey.D1: Factory?.ShowName(); break;
                    case ConsoleKey.D2: AbstractFactory?.ShowResult(); break;
                    default:
                        Console.WriteLine("Чё ты тыкаешь чё-попало. Такой команды нет, не тыкай!");
                        break;
                }
            } while (result != ConsoleKey.Q);
        }
    }
}