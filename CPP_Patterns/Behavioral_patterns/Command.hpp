/* Паттерн "Команда" (Command) */
// Команда – это поведенческий паттерн, позволяющий заворачивать запросы или простые
// операции в отдельные объекты. Это позволяет откладывать выполнение команд, 
// выстраивать их в очереди, а также хранить историю и делать отмену. 

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>

// Концепция паттерна "Команда"
namespace Сonception {
	
    // Command: интерфейс, представляющий команду. Обычно определяет метод Execute()
    // для выполнения действия, а также нередко включает метод Undo(),
    // реализация которого должна заключаться в отмене действия команды.
    class Command abstract {
    public:
        virtual ~Command() { }
        virtual void Execute() = 0;
        virtual void Undo() = 0;
    };

    // Receiver: получатель команды. Определяет действия, которые должны
    // выполняться в результате запроса.
    class Receiver {
    public:
        void Operation() { }
    };

    // Конкретная реализация команды, реализует метод Execute(), в котором вызывается
    // определенный метод, определенный в классе Receiver
    class ConcreteCommand : public Command {
    private:
        Receiver* receiver;
    public:
        ConcreteCommand(Receiver* r) : receiver(r) {};
        void Execute() override {
            receiver->Operation();
        }
        void Undo() override { }
    };

    // Invoker: инициатор команды - вызывает команду для выполнения определенного запроса
    class Invoker {
    public:
        Command* command;
        void SetCommand(Command* c) { command = c; }
        void Run() { command->Execute(); }
        void Cancel() { command->Undo(); }
    };

    /* Client - создает команду и устанавливает ее получателя с помощью метода SetCommand()
    class Client {
    public:
        void Main() {
            Invoker invoker = new Invoker();
            Receiver receiver = new Receiver();
            ConcreteCommand command = new ConcreteCommand(receiver);
            invoker.SetCommand(command);
            invoker.Run();
        }
    };
    */
}

//-----------------------------------------------------------
// Реализация паттерна "Команда"
//-----------------------------------------------------------
namespace Behavioral {

    using std::cout;
    using std::vector;
    using std::stack;

    class ICommand abstract {
    public:
        virtual ~ICommand() {};
        virtual void positive() = 0;
        virtual void negative() = 0;
    };

    class Conveyor final {
    public:
        void start() { cout << "Конвейер запущен!\n"; }
        void stop() { cout << "Конвейер остановлен!\n"; }
        void speed_increase() { cout << "Скорость увеличена\n"; }
        void speed_decrease() { cout << "Скорость снижена\n"; }
    };

    class ConveyorCommand final : public ICommand {
    private:
        Conveyor* conveyor;
    public:
        ConveyorCommand(Conveyor* conv) : conveyor(conv) {};
        void positive() override { conveyor->start(); }
        void negative() override { conveyor->stop(); }
    };

    class ConveyorAdjust final : public ICommand {
    private:
        Conveyor* conveyor;
    public:
        ConveyorAdjust(Conveyor* con) : conveyor(con) {};
        void positive() override { conveyor->speed_increase(); }
        void negative() override { conveyor->speed_decrease(); }
    };

    class MultiPult final {
    private:
        vector<ICommand*> commands;
        stack<ICommand*> history;
    public:
        MultiPult() { commands.resize(2); }
        void set_command(int button, ICommand* command) {
            commands[button] = command;
        }
        void press_on(int button) {
            commands[button]->positive();
            history.push(commands[button]);
        }
        void press_cancel() {
            if (!history.empty()) {
                history.top()->negative();
                history.pop();
            }
        }
    };

    void test_command() {
        Conveyor* conveyor = new Conveyor();
        MultiPult* pult = new MultiPult();

        pult->set_command(0, new ConveyorCommand(conveyor));
        pult->set_command(1, new ConveyorAdjust(conveyor));
        pult->press_on(0);
        pult->press_on(1);
        pult->press_cancel();
        pult->press_cancel();
    }
}