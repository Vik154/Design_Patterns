# Паттерн "Строитель" (Builder)

from __future__ import annotations
from abc import ABC, abstractmethod, abstractproperty

# Концепция паттерна:
# Интерфейс Строителя собирает по частям продукт.
class Builder(ABC):

    @abstractproperty
    def product(self) -> None: pass

    @abstractmethod
    def produce_part_a(self) -> None: pass

    @abstractmethod
    def produce_part_b(self) -> None: pass

    @abstractmethod
    def produce_part_c(self) -> None: pass


# Классы конкретных строителей предоставляют конкретные реализации шагов построения продукта
class ConcreteBuilder1(Builder):
    def __init__(self) -> None:
        self.reset()

    def reset(self) -> None:
        self._product = Product1()

    # Различные типы строителей могут создавать совершенно разные продукты 
    # с разными интерфейсами. Поэтому такие методы не могут быть объявлены в базовом интерфейсе
    @property
    def product(self) -> Product1:
        product = self._product
        self.reset()
        return product

    def produce_part_a(self) -> None:
        self._product.add("PartA1")

    def produce_part_b(self) -> None:
        self._product.add("PartB1")

    def produce_part_c(self) -> None:
        self._product.add("PartC1")


# Паттерн Строитель используется, когда продукты достаточно сложны и требуют 
# обширной конфигурации. Различные конкретные строители могут производить несвязанные продукты.
# Результаты различных строителей могут не всегда следовать одному и тому же интерфейсу.
class Product1():
    def __init__(self) -> None:
        self.parts = []

    def add(self, part) -> None:
        self.parts.append(part)

    def list_parts(self) -> None:
        print(f"Product parts: {', '.join(self.parts)}", end="")


# Директор отвечает только за выполнение шагов построения в определённой последовательности.
# Класс Директор необязателен, так как клиент может напрямую управлять строителями.
class Director:
    def __init__(self) -> None:
        self._builder = None

    @property
    def builder(self) -> Builder:
        return self._builder

    @builder.setter
    def builder(self, builder: Builder) -> None:
        self._builder = builder

    def build_minimal_viable_product(self) -> None:
        self.builder.produce_part_a()

    def build_full_featured_product(self) -> None:
        self.builder.produce_part_a()
        self.builder.produce_part_b()
        self.builder.produce_part_c()


#-------------------------------------------------------------------
# Реализация паттерна Строитель
#-------------------------------------------------------------------
class Phone:
    def __init__(self):
        self.info: str = ""

    def about_phone(self) -> str:
        return self.info

    def append_info(self, info_: str):
        self.info += info_


class IDeveloper(ABC):
    
    @abstractmethod
    def create_display(self): pass

    @abstractmethod
    def create_box(self): pass

    @abstractmethod
    def system_install(self): pass

    @abstractmethod
    def get_phone(self) -> Phone: pass


class AndroidDeveloper(IDeveloper):

    def __init__(self):
        self.__phone = Phone()

    def create_display(self):
        self.__phone.append_info("Произведен дисплей Samsung\n")

    def create_box(self):
        self.__phone.append_info("Произведен корпус Samsung\n")

    def system_install(self):
        self.__phone.append_info("Установлена OS 10.5\n")
        
    def get_phone(self) -> Phone:
        return self.__phone


class IphoneDeveloper(IDeveloper):

    def __init__(self):
        self.__phone = Phone()

    def create_display(self):
        self.__phone.append_info("Произведен дисплей Iphone\n")

    def create_box(self):
        self.__phone.append_info("Произведен корпус Iphone\n")

    def system_install(self):
        self.__phone.append_info("Установлена OS IOS\n")
        
    def get_phone(self) -> Phone:
        return self.__phone


class Director:
    def __init__(self, developer: IDeveloper):
        self.__developer = developer

    def set_developer(self, developer: IDeveloper):
        self.__developer = developer

    def mount_only_phone(self) -> Phone:
        self.__developer.create_box()
        self.__developer.create_display()
        return self.__developer.get_phone()

    def mount_full_phone(self) -> Phone:
        self.__developer.create_box()
        self.__developer.create_display()
        self.__developer.system_install()
        return self.__developer.get_phone()


def test_builder():
    android_dev = AndroidDeveloper()
    director = Director(android_dev)
    samsung = director.mount_full_phone()
    print(samsung.about_phone())

    iphone_dev = IphoneDeveloper()
    director.set_developer(iphone_dev)
    iphone = director.mount_only_phone()
    print(iphone.about_phone())