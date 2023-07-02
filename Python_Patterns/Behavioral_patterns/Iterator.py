# Паттерн Итератор (Iterator)
# Предоставляет способ последовательного доступа ко всем элементам 
# составного объекта, не раскрывая его внутреннего представления.
# https://github.com/ivashkevichdn/PatternsTutorial/blob/master/Behavioral/Python/iterator.py
# https://www.youtube.com/watch?v=RYR5eRB6Xlg&list=PLKP3l9fd3KUHYXVsSy37WXSkvunqenNhS&index=16

from __future__ import annotations
from collections.abc import Iterable, Iterator
from typing import Any, List
from copy import deepcopy

# Для создания итератора в Python есть два абстрактных класса из встроенного
# модуля collections - Iterable, Iterator. Нужно реализовать метод __iter__() в
# итерируемом объекте (списке), а метод __next__() в итераторе.

class AlphabeticalOrderIterator(Iterator):
    """ 
    Конкретные Итераторы реализуют различные алгоритмы обхода. Эти классы
    постоянно хранят текущее положение обхода.
    Атрибут _position хранит текущее положение обхода. У итератора может быть
    множество других полей для хранения состояния итерации, особенно когда он
    должен работать с определённым типом коллекции.
    """
    _position: int = None

    """ Этот атрибут указывает направление обхода. """
    _reverse: bool = False

    def __init__(self, collection: WordsCollection, reverse: bool = False) -> None:
        self._collection = collection
        self._reverse = reverse
        self._position = -1 if reverse else 0

    def __next__(self):
        """
        Метод __next __() должен вернуть следующий элемент в последовательности.
        При достижении конца коллекции и в последующих вызовах должно вызываться
        исключение StopIteration.
        """
        try:
            value = self._collection[self._position]
            self._position += -1 if self._reverse else 1
        except IndexError:
            raise StopIteration()

        return value


class WordsCollection(Iterable):
    """
    Конкретные Коллекции предоставляют один или несколько методов для получения
    новых экземпляров итератора, совместимых с классом коллекции.
    """

    def __init__(self, collection: List[Any] = []) -> None:
        self._collection = collection

    def __iter__(self) -> AlphabeticalOrderIterator:
        """
        Метод __iter__() возвращает объект итератора, по умолчанию мы возвращаем
        итератор с сортировкой по возрастанию.
        """
        return AlphabeticalOrderIterator(self._collection)

    def get_reverse_iterator(self) -> AlphabeticalOrderIterator:
        return AlphabeticalOrderIterator(self._collection, True)

    def add_item(self, item: Any):
        self._collection.append(item)


def client_run():
    # Клиентский код может знать или не знать о Конкретном Итераторе или классах
    # Коллекций, в зависимости от уровня косвенности, который вы хотите
    # сохранить в своей программе.
    collection = WordsCollection()
    collection.add_item("First")
    collection.add_item("Second")
    collection.add_item("Third")

    print("Straight traversal:")
    print("\n".join(collection))
    print("")

    print("Reverse traversal:")
    print("\n".join(collection.get_reverse_iterator()), end="")


# -------------------------------------------------------------------------------
# Реализация паттерна "Итератор"
# -------------------------------------------------------------------------------
class DataStack:
    def __init__(self, my_stack: DataStack = None):
        self.__items = [0] * 10
        self.__length = 0

        if my_stack is not None:
            self.__items = deepcopy(my_stack.__items)
            self.__length = my_stack.__length

    @property
    def items(self):
        return self.__items

    @property
    def length(self):
        return self.__length

    def push(self, item):
        self.__items[self.__length] = item
        self.__length += 1

    def pop(self):
        self.__length -= 1
        return self.__items[self.__length]

    def __eq__(self, other: DataStack) -> bool:
        it1, it2 = StackIterator(self), StackIterator(other)

        while not it1.is_end() or not it2.is_end():
            if next(it1) != next(it2):
                break
        return it1.is_end() and it2.is_end()


class StackIterator:
    def __init__(self, my_stack: DataStack):
        self.__stack = my_stack
        self.__index = 0

    def __iter__(self):
        return self

    def __next__(self):
        current_index = self.__index
        self.__index += 1

        if current_index < self.__stack.length:
            return self.__stack.items[current_index]
        return 0
    
    def is_end(self):
        return self.__index == self.__stack.length + 1


def test_iterator():
    my_stack1 = DataStack()
    for i in range(1, 5):
        my_stack1.push(i)

    my_stack2 = DataStack(my_stack1)
    print(f"Stack 1 == Stack 2 ? {my_stack1 == my_stack2}")
    my_stack2.push(99)
    print(f"Stack 1 == Stack 2 ? {my_stack1 == my_stack2}")