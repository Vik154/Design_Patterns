# Паттерн Компоновщик (Composite)
# Компонует объекты в древовидные структуры для представления иерархий часть-целое.
# Позволяет клиентам единообразно трактовать индивидуальные и составные объекты.
# https://github.com/ivashkevichdn/PatternsTutorial/blob/master/Structural/Python/composite.py

from __future__ import annotations
from abc import ABC, abstractmethod
from typing import List


# Базовый класс Компонент объявляет общие операции как для простых, 
# так и для сложных объектов структуры.
class Component(ABC):
    @property
    def parent(self) -> Component:
        return self._parent

    # Базовый Компонент может объявить интерфейс для установки и получения родителя
    # компонента в древовидной структуре. Он также может предоставить некоторую 
    # реализацию по умолчанию для этих методов.
    @parent.setter
    def parent(self, parent: Component):
        self._parent = parent

    def add(self, component: Component) -> None: pass

    def remove(self, component: Component) -> None: pass

    # Вы можете предоставить метод, который позволит клиентскому коду понять,
    # может ли компонент иметь вложенные объекты.
    def is_composite(self) -> bool:
        return False

    # Базовый Компонент может сам реализовать некоторое поведение по умолчанию или 
    # поручить это конкретным классам, объявив метод, содержащий поведение абстрактным.
    @abstractmethod
    def operation(self) -> str: pass


# Класс Лист представляет собой конечные объекты структуры. Лист не может иметь вложенных
# компонентов. Обычно объекты Листьев выполняют фактическую работу, тогда как объекты
# Контейнера лишь делегируют работу своим подкомпонентам.
class Leaf(Component):
    def operation(self) -> str:
        return "Leaf"


# Класс Контейнер содержит сложные компоненты, которые могут иметь вложенные компоненты.
# Обычно объекты Контейнеры делегируют фактическую работу своим детям, а затем «суммируют» результат.
class Composite(Component):
    def __init__(self) -> None:
        self._children: List[Component] = []

    # Объект контейнера может как добавлять компоненты в свой список вложенных
    # компонентов, так и удалять их, как простые, так и сложные.
    def add(self, component: Component) -> None:
        self._children.append(component)
        component.parent = self

    def remove(self, component: Component) -> None:
        self._children.remove(component)
        component.parent = None

    def is_composite(self) -> bool:
        return True

    # Контейнер выполняет свою основную логику особым образом. Он проходит рекурсивно через
    # всех своих детей, собирая и суммируя их результаты. Поскольку потомки контейнера
    # передают эти вызовы своим потомкам и так далее, в результате обходится всё дерево объектов.
    def operation(self) -> str:
        results = []
        for child in self._children:
            results.append(child.operation())
        return f"Branch({'+'.join(results)})"


# Клиентский код работает со всеми компонентами через базовый интерфейс.
def client_code(component: Component) -> None:
    print(f"RESULT: {component.operation()}", end="")


# Благодаря тому, что операции управления потомками объявлены в базовом классе Компонента,
# клиентский код может работать как с простыми, так и со сложными компонентами,
# вне зависимости от их конкретных классов.
def client_code2(component1: Component, component2: Component) -> None:
    if component1.is_composite():
        component1.add(component2)

    print(f"RESULT: {component1.operation()}", end="")


def run_composite():
    # Таким образом, клиентский код может поддерживать простые компоненты-листья...
    simple = Leaf()
    print("Client: I've got a simple component:")
    client_code(simple)
    print("\n")

    # ...а также сложные контейнеры.
    tree = Composite()

    branch1 = Composite()
    branch1.add(Leaf())
    branch1.add(Leaf())

    branch2 = Composite()
    branch2.add(Leaf())

    tree.add(branch1)
    tree.add(branch2)

    print("Client: Now I've got a composite tree:")
    client_code(tree)
    print("\n")

    print("Client: I don't need to check the components classes even when managing the tree:")
    client_code2(tree, simple)


#-------------------------------------------------------------------------
# Реализация паттерна "Компоновщик"
#-------------------------------------------------------------------------
# Класс представляющий одновременно примитивы и контейнеры
class Graphic(object):
    def draw(self):
        raise NotImplementedError()
 
    def add(self, obj):
        raise NotImplementedError()
 
    def remove(self, obj):
        raise NotImplementedError()
 
    def get_child(self, index):
        raise NotImplementedError()
 
 
class Line(Graphic):
    def draw(self):
        print('Линия')
 
 
class Rectangle(Graphic):
    def draw(self):
        print('Прямоугольник')
 
 
class Text(Graphic):
    def draw(self):
        print('Текст')
 
 
class Picture(Graphic):
    def __init__(self):
        self._children = []
 
    def draw(self):
        print('Изображение')
        # вызываем отрисовку у вложенных объектов
        for obj in self._children:
            obj.draw()
 
    def add(self, obj):
        if isinstance(obj, Graphic) and not obj in self._children:
            self._children.append(obj)
 
    def remove(self, obj):
        index = self._children.index(obj)
        del self._children[index]
 
    def get_child(self, index):
        return self._children[index]
 
 
def test_composite():
    pic = Picture()
    pic.add(Line())
    pic.add(Rectangle())
    pic.add(Text())
    pic.draw() 
    line = pic.get_child(0)
    line.draw() # Линия