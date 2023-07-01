/* Паттерн "Команда" (Command) */
/* Источник - https://metanit.com/sharp/patterns/3.3.php и др. */

/* Паттерн "Команда" (Command) позволяет инкапсулировать запрос на выполнение 
 * определенного действия в виде отдельного объекта. Этот объект запроса на действие 
 * и называется командой. При этом объекты, инициирующие запросы на выполнение действия,
 * отделяются от объектов, которые выполняют это действие.
 * Команды могут использовать параметры, которые передают ассоциированную с командой информацию.
 * Кроме того, команды могут ставиться в очередь и также могут быть отменены.
 - Когда использовать команды?
 * Когда надо передавать в качестве параметров определенные действия, вызываемые в ответ на другие
 * действия. То есть когда необходимы функции обратного действия в ответ на определенные действия.
 * Когда необходимо обеспечить выполнение очереди запросов, а также их возможную отмену.
 * Когда надо поддерживать логгирование изменений в результате запросов.
 * Использование логов может помочь восстановить состояние системы - 
 * для этого необходимо будет использовать последовательность запротоколированных команд.
 */

// Концепция паттерна "Команда"
namespace Сonception {

    // Command: интерфейс, представляющий команду. Обычно определяет метод Execute()
    // для выполнения действия, а также нередко включает метод Undo(),
    // реализация которого должна заключаться в отмене действия команды.
    abstract class Command {
        public abstract void Execute();
        public abstract void Undo();
    }

    // Конкретная реализация команды, реализует метод Execute(), в котором вызывается
    // определенный метод, определенный в классе Receiver
    class ConcreteCommand : Command {
        Receiver receiver;
        public ConcreteCommand(Receiver r) {
            receiver = r;
        }
        public override void Execute() {
            receiver.Operation();
        }
        public override void Undo() { }
    }

    // Receiver: получатель команды. Определяет действия, которые должны
    // выполняться в результате запроса.
    class Receiver {
        public void Operation() { }
    }

    // Invoker: инициатор команды - вызывает команду для выполнения определенного запроса
    class Invoker {
        Command command;
        public void SetCommand(Command c) {
            command = c;
        }
        public void Run() {
            command.Execute();
        }
        public void Cancel() {
            command.Undo();
        }
    }

    // Client - создает команду и устанавливает ее получателя с помощью метода SetCommand()
    /*
    class Client {
        void Main() {
            Invoker invoker = new Invoker();
            Receiver receiver = new Receiver();
            ConcreteCommand command = new ConcreteCommand(receiver);
            invoker.SetCommand(command);
            invoker.Run();
        }
    }
    */
}

//--------------------------------------------------------------
// Реализация паттерна "Команда"
//--------------------------------------------------------------
namespace Patterns.Behavioral {
    
    internal interface ICommand {
        void Execute();
        void Undo();
    }

    // Receiver - получатель
    internal sealed class TV {
        public void On()  => Console.WriteLine("Телевизор включен!");
        public void Off() => Console.WriteLine("Телевизор выключен!");
    }

    internal sealed class TVCommand : ICommand {
        private TV tv;
        public TVCommand(TV tvset) => tv = tvset;
        public void Execute() => tv.On();
        public void Undo()    => tv.Off();
    }

    // Invoker - иницатор
    internal sealed class Pult {
        private ICommand command;
        public void SetCommand(ICommand com) => command = com;
        public void PressButton() => command.Execute();
        public void PressUndo() => command.Undo();
    }

    internal static class TestCommand {
        public static void ShowResult() {
            Pult pult = new Pult();
            TV tV = new TV();
            pult.SetCommand(new TVCommand(tV));
            pult.PressButton();
            pult.PressUndo();
        }
    }
}
