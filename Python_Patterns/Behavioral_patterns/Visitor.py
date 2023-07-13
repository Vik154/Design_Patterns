# Постетитель (Visitor) - паттерн поведения объектов.
# Описывает операцию, выполняемую с каждым объектом из некоторой структуры.
# Паттерн посетитель позволяет определить новую операцию, не изменяя классы этих объектов.
# https://github.com/ivashkevichdn/PatternsTutorial/blob/master/Behavioral/Python/visitor.py

from __future__ import annotations
from abc import ABC, abstractmethod
from typing import List


# Интерфейс Компонента объявляет метод accept, который в качестве аргумента
# может получать любой объект, реализующий интерфейс посетителя.
class Component(ABC):
    @abstractmethod
    def accept(self, visitor: Visitor) -> None:
        pass


# Каждый Конкретный Компонент должен реализовать метод accept таким образом,
# чтобы он вызывал метод посетителя, соответствующий классу компонента.
class ConcreteComponentA(Component):
    def accept(self, visitor: Visitor) -> None:
        visitor.visit_concrete_component_a(self)

    def exclusive_method_of_concrete_component_a(self) -> str:
        return "A"


class ConcreteComponentB(Component):
    def accept(self, visitor: Visitor):
        visitor.visit_concrete_component_b(self)

    def special_method_of_concrete_component_b(self) -> str:
        return "B"


# Интерфейс Посетителя объявляет набор методов посещения, соответствующих
# классам компонентов. Сигнатура метода посещения позволяет посетителю
# определить конкретный класс компонента, с которым он имеет дело.
class Visitor(ABC):
    @abstractmethod
    def visit_concrete_component_a(self, element: ConcreteComponentA) -> None:
        pass

    @abstractmethod
    def visit_concrete_component_b(self, element: ConcreteComponentB) -> None:
        pass



# Конкретные Посетители реализуют несколько версий одного и того же алгоритма,
# которые могут работать со всеми классами конкретных компонентов.
class ConcreteVisitor1(Visitor):
    def visit_concrete_component_a(self, element) -> None:
        print(
            f"{element.exclusive_method_of_concrete_component_a()} + ConcreteVisitor1"
        )

    def visit_concrete_component_b(self, element) -> None:
        print(f"{element.special_method_of_concrete_component_b()} + ConcreteVisitor1")


class ConcreteVisitor2(Visitor):
    def visit_concrete_component_a(self, element) -> None:
        print(
            f"{element.exclusive_method_of_concrete_component_a()} + ConcreteVisitor2"
        )

    def visit_concrete_component_b(self, element) -> None:
        print(f"{element.special_method_of_concrete_component_b()} + ConcreteVisitor2")


# Клиентский код может выполнять операции посетителя над любым набором
# элементов, не выясняя их конкретных классов. Операция принятия направляет
# вызов к соответствующей операции в объекте посетителя.
def client_code(components: List[Component], visitor: Visitor) -> None:
    # ...
    for component in components:
        component.accept(visitor)
    # ...


# ------------------------------------------------------------------------------------
def test_visitor():
    components = [ConcreteComponentA(), ConcreteComponentB()]

    print("The client code works with all visitors via the base Visitor interface:")
    visitor1 = ConcreteVisitor1()
    client_code(components, visitor1)

    print("It allows the same client code to work with different types of visitors:")
    visitor2 = ConcreteVisitor2()
    client_code(components, visitor2)
# ------------------------------------------------------------------------------------