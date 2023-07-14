# Паттерн Заместитель (Proxy)
# Назначение: Позволяет подставлять вместо реальных объектов специальные
# объекты-заменители. Эти объекты перехватывают вызовы к оригинальному объекту,
# позволяя сделать что-то до или после передачи вызова оригиналу.
# https://github.com/RefactoringGuru/design-patterns-python/blob/main/src/Proxy/Conceptual/main.py
# https://www.youtube.com/watch?v=s17zz1DUfkQ

from abc import ABC, abstractmethod
from typing import Dict

# Концепция паттерна
# Интерфейс Субъекта объявляет общие операции как для Реального Субъекта,
# так и для Заместителя. Пока клиент работает с Реальным Субъектом, используя
# этот интерфейс, вы сможете передать ему заместителя вместо реального субъекта.
class Subject(ABC):
    @abstractmethod
    def request(self) -> None: pass


# Реальный Субъект содержит некоторую базовую бизнес-логику. Как правило, Реальные Субъекты
# способны выполнять некоторую полезную работу, которая к тому же может быть очень медленной
# или точной – например, коррекция входных данных. Заместитель может решить эти задачи без
# каких-либо изменений в коде Реального Субъекта.
class RealSubject(Subject):
    def request(self) -> None:
        print("RealSubject: Handling request.")


# Интерфейс Заместителя идентичен интерфейсу Реального Субъекта.
class Proxy(Subject):
    def __init__(self, real_subject: RealSubject) -> None:
        self._real_subject = real_subject

    def request(self) -> None:
        if self.check_access():
            self._real_subject.request()
            self.log_access()

    def check_access(self) -> bool:
        print("Proxy: Checking access prior to firing a real request.")
        return True

    def log_access(self) -> None:
        print("Proxy: Logging the time of request.", end="")


# Клиентский код должен работать со всеми объектами (как с реальными, так и заместителями)
# через интерфейс Субъекта, чтобы поддерживать как реальные субъекты, так и заместителей.
# В реальной жизни, однако, клиенты в основном работают с реальными субъектами напрямую.
# В этом случае, для более простой реализации паттерна, можно расширить заместителя 
# из класса реального субъекта.
def client_code(subject: Subject) -> None:
    # ...
    subject.request()
    # ...


def run_proxy():
    print("Client: Executing the client code with a real subject:")
    real_subject = RealSubject()
    client_code(real_subject)

    print("")

    print("Client: Executing the same client code with a proxy:")
    proxy = Proxy(real_subject)
    client_code(proxy)


#---------------------------------------------------------------------
# Реализация паттерна "Заместитель"
#---------------------------------------------------------------------
class ISite(ABC):
    @abstractmethod
    def get_page(self, number: int) -> str: pass


class Site(ISite):
    def get_page(self, number: int) -> str:
        return f"Страница номер {number}"


class SiteProxy(ISite):
    def __init__(self, site: ISite) -> None:
        self.__site = site
        self.__cache: Dict[int, str] = {}

    def get_page(self, number: int) -> str:
        page: str = ""
        if self.__cache.get(number) is not None:
            page = self.__cache[number]
            page = "из кеша " + page
        else:
            page = self.__site.get_page(number)
            self.__cache[number] = page
        return page


def test_proxy():
    site: ISite = SiteProxy(Site())

    print(site.get_page(1))
    print(site.get_page(2))
    print(site.get_page(3))
    print(site.get_page(1))