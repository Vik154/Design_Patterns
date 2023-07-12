# Паттерн Цепочка Обязанностей (Chain of responsibility)
# Позволяет избежать привязки отправителя запроса к его получателю, давая шанс
# обработать запрос нескольким объектам. Связывает объекты-получатели в цепочку
# и передает запрос вдоль этой цепочки, пока его не обработают.
# Источник - https://github.com/ivashkevichdn/PatternsTutorial/blob/master/Behavioral/Python/chain_of_responsibility.py

from __future__ import annotations
from abc import ABC, abstractmethod
from typing import Any, Optional

# Интерфейс Обработчика объявляет метод построения цепочки обработчиков.
# Он также объявляет метод для выполнения запроса.
class Handler(ABC):
    @abstractmethod
    def set_next(self, handler: Handler) -> Handler:
        pass

    @abstractmethod
    def handle(self, request) -> Optional[str]:
        pass


# Поведение цепочки по умолчанию может быть реализовано внутри базового класса обработчика.
class AbstractHandler(Handler):
    _next_handler: Handler = None

    def set_next(self, handler: Handler) -> Handler:
        self._next_handler = handler
        # Возврат обработчика отсюда позволит связать обработчики простым способом, вот так:
        # monkey.set_next(squirrel).set_next(dog)
        return handler

    @abstractmethod
    def handle(self, request: Any) -> str:
        if self._next_handler:
            return self._next_handler.handle(request)
        return None


# Все Конкретные Обработчики либо обрабатывают запрос, 
# либо передают его следующему обработчику в цепочке.
class MonkeyHandler(AbstractHandler):
    def handle(self, request: Any) -> str:
        if request == "Banana":
            return f"Monkey: I'll eat the {request}"
        else:
            return super().handle(request)


class SquirrelHandler(AbstractHandler):
    def handle(self, request: Any) -> str:
        if request == "Nut":
            return f"Squirrel: I'll eat the {request}"
        else:
            return super().handle(request)


class DogHandler(AbstractHandler):
    def handle(self, request: Any) -> str:
        if request == "MeatBall":
            return f"Dog: I'll eat the {request}"
        else:
            return super().handle(request)


# Обычно клиентский код приспособлен для работы с единственным обработчиком. В большинстве
# случаев клиенту даже неизвестно, что этот обработчик является частью цепочки.
def client_code(handler: Handler) -> None:
    for food in ["Nut", "Banana", "Cup of coffee"]:
        print(f"\nClient: Who wants a {food}?")
        result = handler.handle(food)
        if result:
            print(f"  {result}", end="")
        else:
            print(f"  {food} was left untouched.", end="")


def test_chain():
    monkey = MonkeyHandler()
    squirrel = SquirrelHandler()
    dog = DogHandler()
    monkey.set_next(squirrel).set_next(dog)
    print("Chain: Monkey > Squirrel > Dog")
    client_code(monkey)
    print("\n")
    print("Subchain: Squirrel > Dog")
    client_code(squirrel)