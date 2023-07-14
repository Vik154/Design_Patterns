# Паттерн Мост (Bridge)
# Назначение: Разделяет один или несколько классов на две отдельные иерархии —
# абстракцию и реализацию, позволяя изменять их независимо друг от друга.
# https://github.com/RefactoringGuru/design-patterns-python/blob/main/src/Bridge/Conceptual/main.py

from __future__ import annotations
from abc import ABC, abstractmethod

# Концепция паттерна
# Абстракция устанавливает интерфейс для «управляющей» части двух иерархий классов.
# Она содержит ссылку на объект из иерархии Реализации и делегирует ему всю настоящую работу.
class Abstraction:
    def __init__(self, implementation: Implementation) -> None:
        self.implementation = implementation

    def operation(self) -> str:
        return (f"Abstraction: Base operation with:\n"
                f"{self.implementation.operation_implementation()}")


# Можно расширить Абстракцию без изменения классов Реализации.
class ExtendedAbstraction(Abstraction):
    def operation(self) -> str:
        return (f"ExtendedAbstraction: Extended operation with:\n"
                f"{self.implementation.operation_implementation()}")


# Реализация устанавливает интерфейс для всех классов реализации. Он не должен соответствовать
# интерфейсу Абстракции. На практике оба интерфейса могут быть совершенно разными. Как правило,
# интерфейс Реализации предоставляет только примитивные операции, в то время как Абстракция
# определяет операции более высокого уровня, основанные на этих примитивах. 
class Implementation(ABC):
    @abstractmethod
    def operation_implementation(self) -> str:
        pass


# Каждая Конкретная Реализация соответствует определённой платформе и
# реализует интерфейс Реализации с использованием API этой платформы.
class ConcreteImplementationA(Implementation):
    def operation_implementation(self) -> str:
        return "ConcreteImplementationA: Here's the result on the platform A."


class ConcreteImplementationB(Implementation):
    def operation_implementation(self) -> str:
        return "ConcreteImplementationB: Here's the result on the platform B."


# За исключением этапа инициализации, когда объект Абстракции связывается с определённым
# объектом Реализации, клиентский код должен зависеть только от класса Абстракции.
# Таким образом, клиентский код может поддерживать любую комбинацию абстракции и реализации.
def client_code(abstraction: Abstraction) -> None:
    # ...
    print(abstraction.operation(), end="")
    # ...


# Клиентский код должен работать с любой предварительно сконфигурированной
# комбинацией абстракции и реализации.
def run_bridge():
    implementation = ConcreteImplementationA()
    abstraction = Abstraction(implementation)
    client_code(abstraction)

    print("\n")

    implementation = ConcreteImplementationB()
    abstraction = ExtendedAbstraction(implementation)
    client_code(abstraction)


#---------------------------------------------------------------------
# Реализация паттерна "Мост"
#---------------------------------------------------------------------
class IDataReader(ABC):
    @abstractmethod
    def read(self): pass

class DataBaseReader(IDataReader):
    def read(self):
        print("Данные из базы данных ", end='')

class FileReader(IDataReader):
    def read(self):
        print("Данные из файла ", end='')

class Sender(ABC):
    def __init__(self, data_reader: IDataReader) -> None:
        self.reader = data_reader

    def set_data_reader(self, data_reader: IDataReader):
        self.reader = data_reader

    @abstractmethod
    def send(self): pass

class EmailSender(Sender):
    def __init__(self, data_reader: IDataReader):
        super().__init__(data_reader)

    def send(self):
        self.reader.read()
        print("отправлены при помощи Email")

class TelegramBotSender(Sender):
    def __init__(self, data_reader: IDataReader):
        super().__init__(data_reader)

    def send(self):
        self.reader.read()
        print("отправлены при помощи Telegram бота")

def test_bridge():
    sender: Sender = EmailSender(DataBaseReader())
    sender.send()

    sender.set_data_reader(FileReader())
    sender.send()

    sender = TelegramBotSender(DataBaseReader())
    sender.send()