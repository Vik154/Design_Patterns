# Паттерн - Стратегия (Strategy)
# Определяет семейство алгоритмов, инкапсулирует каждый из них и делает их взаимозаменяемыми.
# Стратегия позволяет изменять алгоритмы независимо от клиентов, которые ими пользуются.

from __future__ import annotations
from abc import ABC, abstractmethod
from typing import List

# Контекст определяет интерфейс, представляющий интерес для клиентов.
class Context:
    def __init__(self, strategy: Strategy) -> None:
        self._strategy = strategy

    @property
    def strategy(self) -> Strategy:
        return self._strategy

    @strategy.setter
    def strategy(self, strategy: Strategy) -> None:
        self._strategy = strategy

    def do_some_business_logic(self) -> None:
        print("Context: Sorting data using the strategy (not sure how it'll do it)")
        result = self._strategy.do_algorithm(["a", "b", "c", "d", "e"])
        print(",".join(result))


# Интерфейс Стратегии объявляет операции, общие для всех поддерживаемых 
# версий некоторого алгоритма. Контекст использует этот интерфейс для вызова
#  алгоритма, определённого Конкретными Стратегиями.
class Strategy(ABC):
    @abstractmethod
    def do_algorithm(self, data: List):
        pass


# Конкретные Стратегии реализуют алгоритм, следуя базовому интерфейсу Стратегии.
# Этот интерфейс делает их взаимозаменяемыми в Контексте.
class ConcreteStrategyA(Strategy):
    def do_algorithm(self, data: List) -> List:
        return sorted(data)


class ConcreteStrategyB(Strategy):
    def do_algorithm(self, data: List) -> List:
        return reversed(sorted(data))


def run():
    # Клиентский код выбирает конкретную стратегию и передаёт её в контекст.
    context = Context(ConcreteStrategyA())
    print("Client: Strategy is set to normal sorting.")
    context.do_some_business_logic()
    print("\nClient: Strategy is set to reverse sorting.")
    context.strategy = ConcreteStrategyB()
    context.do_some_business_logic()


# -------------------------------------------------------------------------------
# Реализация паттерна "Стратегия"
# -------------------------------------------------------------------------------
class Reader(ABC):
    @abstractmethod
    def parse(self, url: str): pass


class ResourceReader:
    def __init__(self, reader: Reader):
        self.__reader = reader

    def set_strategy(self, reader: Reader):
        self.__reader = reader

    def read(self, url: str):
        self.__reader.parse(url)


class NewSiteReader(Reader):
    def parse(self, url: str):
        print("Парсинг нового сайта", url)


class SocialNetworkReader(Reader):
    def parse(self, url: str):
        print("Парсинг ленты новостей", url)

        
def test_strategy():
    resource_reader = ResourceReader(NewSiteReader())
    url = "https://news.com"
    resource_reader.read(url)
    url = "https://facebook.com"
    resource_reader.set_strategy(SocialNetworkReader())
    resource_reader.read(url)