# Паттерн Фабричный Метод - определяет общий интерфейс для создания объектов
# в суперклассе, позволяя подклассам изменять тип создаваемых объектов.
# Источник 1 - https://github.com/RefactoringGuru/design-patterns-python/blob/main/src/FactoryMethod/Conceptual/main.py

from abc import ABC, abstractmethod
from venv import create

# Интерфейс Продукта объявляет операции, которые должны выполнять все конкретные продукты.
class Product(ABC):

    @abstractmethod
    def operation(self) -> str:
        pass


# Конкретные Продукты предоставляют различные реализации интерфейса Продукта.
class ConcreteProduct1(Product):
    def operation(self) -> str:
        return "{Result of the ConcreteProduct1}"


class ConcreteProduct2(Product):
    def operation(self) -> str:
        return "{Result of the ConcreteProduct2}"


# Класс Создатель объявляет фабричный метод, который должен возвращать объект класса Продукт.
# Подклассы Создателя обычно предоставляют реализацию этого метода.
class Creator(ABC):

    @abstractmethod
    def factory_method(self): pass

    def some_operation(self) -> str:
        product = self.factory_method()             # Получение объекта-продукта.
        result = f"Creator: {product.operation()}"  # Далее, работаем с этим продуктом.
        return result


# Конкретные Создатели переопределяют фабричный метод для того, 
# чтобы изменить тип результирующего продукта.
class ConcreteCreator1(Creator):
    """
    Сигнатура метода по-прежнему использует тип абстрактного продукта, 
    хотя фактически из метода возвращается конкретный продукт. 
    Таким образом, Создатель может оставаться независимым от конкретных классов продуктов.
    """
    def factory_method(self) -> Product:
        return ConcreteProduct1()


class ConcreteCreator2(Creator):
    def factory_method(self) -> Product:
        return ConcreteProduct2()


def client_code(creator: Creator) -> None:
    """
    Клиентский код работает с экземпляром конкретного создателя, хотя и
    через его базовый интерфейс. Пока клиент продолжает работать с создателем
    через базовый интерфейс, вы можете передать ему любой подкласс создателя.
    """

    print(f"Client: I'm not aware of the creator's class, but it still works.\n"
          f"{creator.some_operation()}", end="")


def go():
    print("App: Launched with the ConcreteCreator1.")
    client_code(ConcreteCreator1())
    print("\n")

    print("App: Launched with the ConcreteCreator2.")
    client_code(ConcreteCreator2())


# Реализация паттерна
class IProductVoice(ABC):   # Абстрактный класс Продукта

    @abstractmethod         # Абстрактный метод (логика реализуется в каждом наследнике)
    def release(self): pass


class Myay(IProductVoice):

    def release(self):
        return "Я мяукаю"

class Gaff(IProductVoice):

    def release(self):
        return "Я гавкаю"
 
# --------------------------
class ICreatorVoice(ABC):   # Абстракный класс Создателя

    def __init__(self, name):
        self._creator_name = name
        self._product = self.create()

    @abstractmethod         # Абстрактный метод, создающий конкретный продукт
    def create(self): pass


class Cat(ICreatorVoice):

    def __init__(self, name):
        self._creator_name = name
        self._product = self.create().release()

    def create(self):
        return Myay()
    

class Dog(ICreatorVoice):

    def __init__(self, name):
        self._creator_name = name
        self._product = self.create().release()

    def create(self):
        return Gaff()
#----------------------------------------

class ReleaseFactoryMethod():
    
    def __init__(self):
        self._dog = Dog("Пёс")
        self._cat = Cat("Кот")

    def show(self):
        print(f"{self._dog._creator_name} говорит {self._dog._product}")
        print(f"{self._cat._creator_name} говорит {self._cat._product}")


def test_factory_method():
    factory_method = ReleaseFactoryMethod()
    factory_method.show()