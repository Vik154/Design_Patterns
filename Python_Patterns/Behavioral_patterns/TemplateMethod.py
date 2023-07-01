# Паттерн "Шаблонный метод" (Template Method)
# 1 - https://github.com/Volodichev/patterns/blob/main/template_method/template_method.py
# 2 - https://ru.wikipedia.org/wiki/%D0%A8%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD%D0%BD%D1%8B%D0%B9_%D0%BC%D0%B5%D1%82%D0%BE%D0%B4_(%D1%88%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD_%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)#C++11

from abc import ABC, abstractmethod

# Абстрактный Класс определяет шаблонный метод, содержащий скелет некоторого алгоритма,
# состоящего из вызовов (обычно) абстрактных примитивных операций. Конкретные подклассы
# должны реализовать эти операции, но оставить сам шаблонный метод без изменений.

class AbstractClass(ABC):

    # Шаблонный метод определяет скелет алгоритма.
    def template_method(self) -> None:
        self.base_operation1()
        self.required_operations1()
        self.base_operation2()
        self.hook1()
        self.required_operations2()
        self.base_operation3()
        self.hook2()

    # Эти операции уже имеют реализации.
    def base_operation1(self) -> None:
        print("AbstractClass says: I am doing the bulk of the work")

    def base_operation2(self) -> None:
        print("AbstractClass says: But I let subclasses override some operations")

    def base_operation3(self) -> None:
        print("AbstractClass says: But I am doing the bulk of the work anyway")

    # А эти операции должны быть реализованы в подклассах.
    @abstractmethod
    def required_operations1(self) -> None:
        pass

    @abstractmethod
    def required_operations2(self) -> None:
        pass


# Конкретные классы должны реализовать все абстрактные операции базового класса.
# Они также могут переопределить некоторые операции с реализацией по умолчанию.
class ConcreteClass1(AbstractClass):
    def required_operations1(self) -> None:
        print("ConcreteClass1 says: Implemented Operation1")

    def required_operations2(self) -> None:
        print("ConcreteClass1 says: Implemented Operation2")


class ConcreteClass2(AbstractClass):
    def required_operations1(self) -> None:
        print("ConcreteClass2 says: Implemented Operation1")

    def required_operations2(self) -> None:
        print("ConcreteClass2 says: Implemented Operation2")


# Клиентский код вызывает шаблонный метод для выполнения алгоритма. Клиентский код
# не должен знать конкретный класс объекта, с которым работает, при условии, что 
# он работает с объектами через интерфейс их базового класса.
def client_code(abstract_class: AbstractClass) -> None:
    # ...
    abstract_class.template_method()
    # ...


# -------------------------------------------------------------------------------
# Реализация паттерна "Шаблонный метод"
# -------------------------------------------------------------------------------
class Unit(ABC):
	def __init__(self, speed: int) -> None:
		self._speed = speed

	# Шаблонный метод
	def hit_and_run(self) -> None:
		self._move('вперед')
		self._stop()
		self._attack()
		self._move('назад')

	@abstractmethod
	def _attack(self) -> None: pass

	@abstractmethod
	def _stop(self) -> None: pass

	def _move(self, direction: str) -> None:
		self._output('движется {} со скоростью {}'.format(direction, self._speed))

	def _output(self, message: str) -> None:
		print('Отряд типа {} {}'.format(self.__class__.__name__, message))


class Archers(Unit):
	def _attack(self) -> None:
		self._output('обстреливает врага')

	def _stop(self) -> None:
		self._output('останавливается в 100 шагах от врага')


class Cavalrymen(Unit):
	def _attack(self) -> None:
		self._output('на полном скаку врезается во вражеский строй')

	def _stop(self) -> None:
		self._output('летит вперед, не останавливаясь')


def test_template():
	print('OUTPUT:')
	archers = Archers(4)
	archers.hit_and_run()
	cavalrymen = Cavalrymen(8)
	cavalrymen.hit_and_run()