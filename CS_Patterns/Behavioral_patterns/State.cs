/* Паттерн Состояние (State) */
/* Источник - https://metanit.com/sharp/patterns/3.6.php и др. */

/* Состояние (State) - шаблон проектирования, который позволяет объекту изменять 
 * свое поведение в зависимости от внутреннего состояния.
 - Когда применяется данный паттерн?
 * Когда поведение объекта должно зависеть от его состояния и может изменяться 
 * динамически во время выполнения
 * Когда в коде методов объекта используются многочисленные условные конструкции,
 * выбор которых зависит от текущего состояния объекта
 */

// Концепция паттерна "Состояние"
namespace Сonception {

    // State: определяет интерфейс состояния
    abstract class State {
        public abstract void Handle(Context context);
    }

    // Классы StateA и StateB - конкретные реализации состояний
    class StateA : State {
        public override void Handle(Context context) {
            context.State = new StateB();
        }
    }

    class StateB : State {
        public override void Handle(Context context) {
            context.State = new StateA();
        }
    }

    // Context: представляет объект, поведение которого должно динамически изменяться
    // в соответствии с состоянием. Выполнение конкретных действий делегируется объекту состояния
    class Context {
        public State State { get; set; }
        public Context(State state) {
            this.State = state;
        }
        public void Request() {
            this.State.Handle(this);
        }
    }

    /* Использование:
    class Program {
        static void Main() {
            Context context = new Context(new StateA());
            context.Request(); // Переход в состояние StateB
            context.Request();  // Переход в состояние StateA
        }
    }
    */
}

//--------------------------------------------------------------
// Реализация паттерна "Состояние"
//--------------------------------------------------------------
namespace Patterns.Behavioral {

    internal class Water {
        public IWaterState State { get; set; }
        public Water(IWaterState ws) => State = ws;
        public void Heat() => State.Heat(this);
        public void Frost() => State.Frost(this);
    }

    internal interface IWaterState {
        void Heat(Water water);
        void Frost(Water water);
    }

    internal class SolidWaterState : IWaterState {
        public void Heat(Water water) {
            Console.WriteLine("Превращаем лед в жидкость");
            water.State = new LiquidWaterState();
        }
        public void Frost(Water water) {
            Console.WriteLine("Продолжаем заморозку льда");
        }
    }

    internal class LiquidWaterState : IWaterState {
        public void Heat(Water water) {
            Console.WriteLine("Превращаем жидкость в пар");
            water.State = new GasWaterState();
        }
        public void Frost(Water water) {
            Console.WriteLine("Превращаем жидкость в лед");
            water.State = new SolidWaterState();
        }
    }

    internal class GasWaterState : IWaterState {
        public void Heat(Water water) {
            Console.WriteLine("Повышаем температуру водяного пара");
        }
        public void Frost(Water water) {
            Console.WriteLine("Превращаем водяной пар в жидкость");
            water.State = new LiquidWaterState();
        }
    }

    internal static class TestState {
        public static void ShowResult() {
            Water water = new Water(new LiquidWaterState());
            water.Heat();
            water.Frost();
            water.Frost();
        }
    }
}