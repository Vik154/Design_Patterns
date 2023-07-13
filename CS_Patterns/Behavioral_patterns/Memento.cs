/* Паттерн Хранитель (Memento) */
/* Источник - https://metanit.com/sharp/patterns/3.9.php и др. */

/* Паттерн Хранитель (Memento) позволяет выносить внутреннее состояние объекта за его пределы
 * для последующего возможного восстановления объекта без нарушения принципа инкапсуляции.
 - Когда использовать Memento?
 - Когда нужно сохранить состояние объекта для возможного последующего восстановления
 - Когда сохранение состояния должно проходить без нарушения принципа инкапсуляции
 */

// Концепция паттерна "Хранитель"
namespace Сonception {

    // Memento: хранитель, который сохраняет состояние объекта Originator и предоставляет
    // полный доступ только этому объекту Originator
    class Memento {
        public string State { get; private set; }
        public Memento(string state) {
            State = state;
        }
    }

    // Caretaker: выполняет только функцию хранения объекта Memento, в то же время у него нет
    // полного доступа к хранителю и никаких других операций над хранителем,
    // кроме собственно сохранения, он не производит
    class Caretaker {
        public Memento Memento { get; set; }
    }

    // Originator: создает объект хранителя для сохранения своего состояния
    class Originator {
        public string State { get; set; }
        public void SetMemento(Memento memento) {
            State = memento.State;
        }
        public Memento CreateMemento() {
            return new Memento(State);
        }
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Хранитель"
//--------------------------------------------------------------
namespace Patterns.Behavioral {

    // Originator
    internal class Hero {
        private int patrons = 10;   // кол-во патронов
        private int lives = 5;      // кол-во жизней

        public void Shoot() {
            if (patrons > 0) {
                patrons--;
                Console.WriteLine("Производим выстрел. Осталось {0} патронов", patrons);
            }
            else
                Console.WriteLine("Патронов больше нет");
        }

        // сохранение состояния
        public HeroMemento SaveState() {
            Console.WriteLine("Сохранение игры. Параметры: {0} патронов, {1} жизней", patrons, lives);
            return new HeroMemento(patrons, lives);
        }

        // восстановление состояния
        public void RestoreState(HeroMemento memento) {
            patrons = memento.Patrons;
            lives = memento.Lives;
            Console.WriteLine("Восстановление игры. Параметры: {0} патронов, {1} жизней", patrons, lives);
        }
    }

    // Memento
    internal class HeroMemento {
        public int Patrons { get; private set; }
        public int Lives { get; private set; }

        public HeroMemento(int patrons, int lives) {
            Patrons = patrons;
            Lives = lives;
        }
    }

    // Caretaker
    internal class GameHistory {
        public Stack<HeroMemento> History { get; private set; }
        public GameHistory() {
            History = new Stack<HeroMemento>();
        }
    }

    internal static class TestMemento {
        
        public static void ShowResult() {
            Hero hero = new Hero();
            hero.Shoot();                           // делаем выстрел, осталось 9 патронов
            GameHistory game = new GameHistory();
            game.History.Push(hero.SaveState());    // сохраняем игру
            hero.Shoot();                           //делаем выстрел, осталось 8 патронов
            hero.RestoreState(game.History.Pop());
            hero.Shoot();                           //делаем выстрел, осталось 8 патронов
        }
    }
}