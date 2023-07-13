# Паттерн Хранитель (Memento)
# https://github.com/ivashkevichdn/PatternsTutorial/blob/master/Behavioral/Python/memento.py
# Хранитель (Memento) - паттерн поведения объектов.
# Не нарушая инкапсуляции, фиксирует и выносит за пределы объекта его внутреннее
# состояние так, чтобы позднее можно было восстановить в нем объект.

from __future__ import annotations
from abc import ABC, abstractmethod
from datetime import datetime
from random import sample
from string import ascii_letters, digits

# Создатель содержит некоторое важное состояние, которое может со временем меняться.
# Он также объявляет метод сохранения состояния внутри снимка и метод восстановления состояния из него.
class Originator:
    # Для удобства состояние создателя хранится внутри одной переменной.
    _state = None

    def __init__(self, state: str) -> None:
        self._state = state
        print(f"Originator: My initial state is: {self._state}")

    def do_something(self) -> None:
        print("Originator: I'm doing something important.")
        self._state = self._generate_random_string(30)
        print(f"Originator: and my state has changed to: {self._state}")

    def _generate_random_string(self, length: int = 10) -> None:
        return "".join(sample(ascii_letters, length))

    # Сохраняет текущее состояние внутри снимка.
    def save(self) -> Memento:
        return ConcreteMemento(self._state)

    # Восстанавливает состояние Создателя из объекта снимка.
    def restore(self, memento: Memento) -> None:
        self._state = memento.get_state()
        print(f"Originator: My state has changed to: {self._state}")


# Интерфейс Снимка предоставляет способ извлечения метаданных снимка, таких
# как дата создания или название. Однако он не раскрывает состояние Создателя.
class Memento(ABC):
    @abstractmethod
    def get_name(self) -> str:
        pass

    @abstractmethod
    def get_date(self) -> str:
        pass


class ConcreteMemento(Memento):
    def __init__(self, state: str) -> None:
        self._state = state
        self._date = str(datetime.now())[:19]

    # Создатель использует этот метод, когда восстанавливает своё состояние.
    def get_state(self) -> str:
        return self._state

    # Остальные методы используются Опекуном для отображения метаданных.
    def get_name(self) -> str:
        return f"{self._date} / ({self._state[0:9]}...)"

    def get_date(self) -> str:
        return self._date


# Опекун не зависит от класса Конкретного Снимка. Таким образом, он не имеет 
# доступа к состоянию создателя, хранящемуся внутри снимка. 
# Он работает со всеми снимками через базовый интерфейс Снимка.
class Caretaker:
    def __init__(self, originator: Originator) -> None:
        self._mementos = []
        self._originator = originator

    def backup(self) -> None:
        print("\nCaretaker: Saving Originator's state...")
        self._mementos.append(self._originator.save())

    def undo(self) -> None:
        if not len(self._mementos):
            return

        memento = self._mementos.pop()
        print(f"Caretaker: Restoring state to: {memento.get_name()}")
        try:
            self._originator.restore(memento)
        except Exception:
            self.undo()

    def show_history(self) -> None:
        print("Caretaker: Here's the list of mementos:")
        for memento in self._mementos:
            print(memento.get_name())


def test_memento():
    originator = Originator("Super-duper-super-puper-super.")
    caretaker = Caretaker(originator)

    caretaker.backup()
    originator.do_something()

    caretaker.backup()
    originator.do_something()

    caretaker.backup()
    originator.do_something()

    print()
    caretaker.show_history()

    print("\nClient: Now, let's rollback!\n")
    caretaker.undo()

    print("\nClient: Once more!\n")
    caretaker.undo()