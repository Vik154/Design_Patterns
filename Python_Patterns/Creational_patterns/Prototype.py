# Паттерн "Прототип" (Prototype)

from abc import ABC, abstractmethod
from copy import deepcopy

# Концепция паттерна:
class Prototype(ABC):

    @abstractmethod
    def clone(self): pass


class MyObject(Prototype):
    def __init__(self, arg1, arg2):
        self.field1 = arg1
        self.field2 = arg2

    def __operation__(self):
        self.performed_operation = True

    def clone(self):
        return deepcopy(self)

#----------------------------------------------
# Реализация паттерна "Прототип"
#----------------------------------------------
class IBook(ABC):
    def __init__(self, year: int, author: str, id_: int ) -> None:
        self._year = year
        self._author = author
        self._id = id_
    
    @abstractmethod
    def clone(self): pass


class Book1(IBook):
    def __init__(self, year: int, author: str, id_: int ) -> None:
        super().__init__(year, author, id_)

    def clone(self):
        return deepcopy(self)

    def get_info(self):
        print(f"author: {self._author}; year: {self._year}; id: {self._id}")


class Book2(IBook):
    def __init__(self, year: int, author: str, id_: int ): 
        super().__init__(year, author, id_)

    def clone(self):
        return deepcopy(self)

    def get_info(self):
        print(f"author: {self._author}; year: {self._year}; id: {self._id}")
#----------------------------------------------

def initialize(book: IBook):
    book1 = book
    book2 = book.clone()
    book1.get_info()
    book2.get_info()
    print(f"id: {id(book)};\nid: {id(book2)};")

# Тест прототипа
def test_prototype():
    initialize(Book1(2000, "NO Name", 1))
    initialize(Book2(1995, "Secret Name", 23))