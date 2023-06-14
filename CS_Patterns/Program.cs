using System.Text;

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
            Factory = new Patterns.Creational.FactoryMethod(); }

        /// <summary> Паттерн - "Фабричный метод" </summary>
        private readonly Patterns.Creational.FactoryMethod? Factory;

        public void Run() {
            ConsoleKey result;
            string info = "\nВыберите команду:" +
                "\nq - Выход" +
                "\n1 - Паттерн \"Фабричный метод\"" +
                "\n2 - Паттерн \"\" \n";
            do {
                Console.WriteLine(info);
                result = Console.ReadKey().Key;
                Console.Write('\r');
                switch (result) {
                    case ConsoleKey.D1: Factory?.ShowName(); break;
                    case ConsoleKey.D2:
                        break;
                    default:
                        Console.WriteLine("Чё ты тыкаешь чё-попало. Такой команды нет, не тыкай!");
                        break;
                }
            } while (result != ConsoleKey.Q);
        }
    }
}