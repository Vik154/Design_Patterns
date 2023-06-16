# Паттерн Абстрактная Фабрика - Предоставляет интерфейс для создания семейств связанных или
# зависимых объектов без привязки к их конкретным классам.
# Источник 1 - https://github.com/RefactoringGuru/design-patterns-python/blob/main/src/AbstractFactory/Conceptual/main.py

from __future__ import annotations
from abc import ABC, abstractmethod

# Абстрактная Фабрика объявляет набор методов, которые возвращают абстрактные продукты
# Эти продукты называются семейством и связаны темой или концепцией высокого уровня
# Продукты одного семейства обычно могут взаимодействовать между собой. Семейство продуктов
# может иметь несколько вариаций, но продукты одной вариации несовместимы с продуктами другой.
class AbstractFactory(ABC):

    @abstractmethod
    def create_product_a(self) -> AbstractProductA: pass

    @abstractmethod
    def create_product_b(self) -> AbstractProductB: pass

# Конкретная Фабрика производит семейство продуктов одной вариации. 
# Фабрика гарантирует совместимость полученных продуктов
class ConcreteFactory1(AbstractFactory):

    def create_product_a(self) -> AbstractProductA:
        return ConcreteProductA1()

    def create_product_b(self) -> AbstractProductB:
        return ConcreteProductB1()

# Каждая Конкретная Фабрика имеет соответствующую вариацию продукта.
class ConcreteFactory2(AbstractFactory):

    def create_product_a(self) -> AbstractProductA:
        return ConcreteProductA2()

    def create_product_b(self) -> AbstractProductB:
        return ConcreteProductB2()


# Каждый отдельный продукт семейства продуктов должен иметь базовый
# интерфейс. Все вариации продукта должны реализовывать этот интерфейс.
class AbstractProductA(ABC):

    @abstractmethod
    def useful_function_a(self) -> str: pass


# Базовый интерфейс другого продукта. Все продукты могут взаимодействовать друг с другом,
# но правильное взаимодействие возможно только между продуктами одной и той же конкретной вариации.
class AbstractProductB(ABC):

    @abstractmethod
    def useful_function_b(self) -> None: pass

    @abstractmethod
    def another_useful_function_b(self, collaborator: AbstractProductA) -> None: pass


# Конкретные продукты создаются соответствующими Конкретными Фабриками.
class ConcreteProductA1(AbstractProductA):
    def useful_function_a(self) -> str:
        return "The result of the product A1."


class ConcreteProductA2(AbstractProductA):
    def useful_function_a(self) -> str:
        return "The result of the product A2."


# Продукт B1 может корректно работать только с Продуктом A1. Тем не менее,
# он принимает любой экземпляр Абстрактного Продукта А в качестве аргумента.
class ConcreteProductB1(AbstractProductB):
    def useful_function_b(self) -> str:
        return "The result of the product B1."

    def another_useful_function_b(self, collaborator: AbstractProductA) -> str:
        result = collaborator.useful_function_a()
        return f"The result of the B1 collaborating with the ({result})"


# Продукт B2 может корректно работать только с Продуктом A2. Тем не менее,
# он принимает любой экземпляр Абстрактного Продукта А в качестве аргумента
class ConcreteProductB2(AbstractProductB):
    def useful_function_b(self) -> str:
        return "The result of the product B2."

    def another_useful_function_b(self, collaborator: AbstractProductA):
        result = collaborator.useful_function_a()
        return f"The result of the B2 collaborating with the ({result})"


# Клиентский код работает с фабриками и продуктами только через абстрактные типы:
# Абстрактная Фабрика и Абстрактный Продукт. Это позволяет передавать любой подкласс 
# фабрики или продукта клиентскому коду, не нарушая его.
def client_code(factory: AbstractFactory) -> None:
    product_a = factory.create_product_a()
    product_b = factory.create_product_b()

    print(f"{product_b.useful_function_b()}")
    print(f"{product_b.another_useful_function_b(product_a)}", end="")


# RU: Клиентский код может работать с любым конкретным классом фабрики.
def go_go():
    print("Client: Testing client code with the first factory type:")
    client_code(ConcreteFactory1())
    print("\n")
    print("Client: Testing the same client code with the second factory type:")
    client_code(ConcreteFactory2())


# --------------------------------------------------------------
# Реализация паттерна "Абстрактная фабрика"
# --------------------------------------------------------------
# Абстрактный класс продукта - мощных двигателей
class IPowerfulEngine(ABC):
    @abstractmethod
    def create_pwengine(self) -> str: pass  # Создает мощный двигатель (продукт)

class IWeakEngine(ABC):
    @abstractmethod
    def create_wkengine(self) -> str: pass  # Создает маломощный двигатель (продукт)


# Абстрактный класс фабрики - производитель двигателей
class IEngineFactory(ABC):
    @abstractmethod
    def create_weak_engine(self) -> IWeakEngine: pass         # Производит маломощный двигатель

    @abstractmethod
    def create_powerful_engine(self) -> IPowerfulEngine: pass # Производит мощный двигатель

# Классы мощных двигателей
class PowerfulEngine1(IPowerfulEngine):
    def create_pwengine(self):
        return "Двигатель 250 л.с готов"

class PowerfulEngine2(IPowerfulEngine):
    def create_pwengine(self):
        return "Двигатель 210 л.с готов"

# Классы маломощных двигателей
class WeakEngine1(IWeakEngine):
    def create_wkengine(self) -> str:
        return "Двигатель 98 л.с готов"

class WeakEngine2(IWeakEngine):
    def create_wkengine(self) -> str:
        return "Двигатель 112 л.с готов"

# Класс фабрики по производству двигателей
class FordFactory(IEngineFactory):
    def create_weak_engine(self) -> IWeakEngine:
        return WeakEngine1()

    def create_powerful_engine(self) -> IPowerfulEngine:
        return PowerfulEngine1()
    
class BMWFactory(IEngineFactory):
    def create_weak_engine(self) -> IWeakEngine:
        return WeakEngine2()

    def create_powerful_engine(self) -> IPowerfulEngine:
        return PowerfulEngine2()

# Клиентский класс
class EngineClient():
    def __init__(self, factory: IEngineFactory) -> None:
        self.pwengine = factory.create_powerful_engine()
        self.wkengine = factory.create_weak_engine()


class FactoryTest():
    def __init__(self):
        self._ford = EngineClient(FordFactory())
        self._bmw  = EngineClient(BMWFactory())
    
    def show(self):
        fres1 = self._ford.pwengine.create_pwengine()
        fres2 = self._ford.wkengine.create_wkengine()
        bres1 = self._bmw.pwengine.create_pwengine()
        bres2 = self._bmw.wkengine.create_wkengine()

        print(f"Ford заявил: {fres1} и {fres2}")
        print(f"BMW заявил: {bres1} и {bres2}")
# --------------------------------------------------------------