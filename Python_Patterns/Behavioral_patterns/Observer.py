# Паттерн - Наблюдатель (Observer)
# Определяет зависимость типа "один ко многим" между объектами таким образом,
# что при изменении состояния одного объекта все зависящие от него оповещаются об этом
# и автоматически обновляются.
# https://github.com/RefactoringGuru/design-patterns-python/blob/main/src/Observer/Conceptual/main.py
# https://github.com/ivashkevichdn/PatternsTutorial/blob/master/Behavioral/Python/observer.py
# https://www.geeksforgeeks.org/observer-method-python-design-patterns/


from __future__ import annotations
from abc import ABC, abstractmethod
from random import randrange
from typing import List


# Интферфейс издателя объявляет набор методов для управлениями подпискичами.
class Subject(ABC):
    # Присоединяет наблюдателя к издателю.
    @abstractmethod
    def attach(self, observer: Observer) -> None: pass

    # Отсоединяет наблюдателя от издателя.
    @abstractmethod
    def detach(self, observer: Observer) -> None: pass

    # Уведомляет всех наблюдателей о событии.
    @abstractmethod
    def notify(self) -> None: pass


# Издатель владеет некоторым важным состоянием и оповещает наблюдателей о его изменениях.
class ConcreteSubject(Subject):
    _state: int = None                  # Cостояние Издателя, необходимое всем подписчикам.
    _observers: List[Observer] = []     # Список подписчиков

    def attach(self, observer: Observer) -> None:
        print("Subject: Attached an observer.")
        self._observers.append(observer)

    def detach(self, observer: Observer) -> None:
        self._observers.remove(observer)

    def notify(self) -> None:
        print("Subject: Notifying observers...")
        for observer in self._observers:
            observer.update(self)

    def some_business_logic(self) -> None:
        print("\nSubject: I'm doing something important.")
        self._state = randrange(0, 10)
        print(f"Subject: My state has just changed to: {self._state}")
        self.notify()


# Интерфейс Наблюдателя объявляет метод уведомления, который издатели
# используют для оповещения своих подписчиков.
class Observer(ABC):
    # Получить обновление от субъекта.
    @abstractmethod
    def update(self, subject: Subject) -> None: pass


# Конкретные Наблюдатели реагируют на обновления, выпущенные Издателем,
# к которому они прикреплены.
class ConcreteObserverA(Observer):
    def update(self, subject: Subject) -> None:
        if subject._state < 3:
            print("ConcreteObserverA: Reacted to the event")


class ConcreteObserverB(Observer):
    def update(self, subject: Subject) -> None:
        if subject._state == 0 or subject._state >= 2:
            print("ConcreteObserverB: Reacted to the event")


# Клиентский код.
def run2():
    subject = ConcreteSubject()
    observer_a = ConcreteObserverA()
    subject.attach(observer_a)
    observer_b = ConcreteObserverB()
    subject.attach(observer_b)
    subject.some_business_logic()
    subject.some_business_logic()
    subject.detach(observer_a)
    subject.some_business_logic()


# -------------------------------------------------------------------------------
# Реализация паттерна "Наблюдатель"
# -------------------------------------------------------------------------------
class ISubject:
	def __init__(self):
		self._observers = []

	def notify(self, modifier = None):
		for observer in self._observers:
			if modifier != observer:
				observer.update(self)

	def attach(self, observer):
		if observer not in self._observers:
			self._observers.append(observer)

	def detach(self, observer):
		try:
			self._observers.remove(observer)
		except ValueError:
			pass



class Data(ISubject):
	def __init__(self, name =''):
		ISubject.__init__(self)
		self.name = name
		self._data = 0

	@property
	def data(self):
		return self._data

	@data.setter
	def data(self, value):
		self._data = value
		self.notify()


class HexViewer:
	def update(self, subject):
		print('HexViewer: Subject {} has data 0x{:x}'.format(subject.name, subject.data))


class OctalViewer:
	def update(self, subject):
		print('OctalViewer: Subject' + str(subject.name) + 'has data '+str(oct(subject.data)))


class DecimalViewer:
	def update(self, subject):
		print('DecimalViewer: Subject % s has data % d' % (subject.name, subject.data))


def test_observer():
	obj1 = Data('Data 1')
	obj2 = Data('Data 2')

	view1 = DecimalViewer()
	view2 = HexViewer()
	view3 = OctalViewer()

	obj1.attach(view1)
	obj1.attach(view2)
	obj1.attach(view3)

	obj2.attach(view1)
	obj2.attach(view2)
	obj2.attach(view3)

	obj1.data = 10
	obj2.data = 15