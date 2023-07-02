# /* Паттерн Состояние (State) */
# Назначение: Позволяет объектам менять поведение в зависимости от своего
# состояния. Извне создаётся впечатление, что изменился класс объекта.
# https://github.com/RefactoringGuru/design-patterns-python/blob/main/src/State/Conceptual/main.py
# https://ru.wikipedia.org/wiki/%D0%A1%D0%BE%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%B8%D0%B5_(%D1%88%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD_%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)#%D0%9F%D1%80%D0%B8%D0%BC%D0%B5%D1%80_%D0%BD%D0%B0_Python


from __future__ import annotations
from abc import ABC, abstractmethod


# Концепция паттерна "Состояние"
# Контекст определяет интерфейс, представляющий интерес для клиентов. Он также хранит
# ссылку на экземпляр подкласса Состояния, который отображает текущее состояние Контекста.
class Context:
    _state = None

	# Ссылка на текущее состояние Контекста.
    def __init__(self, state: State) -> None:
        self.transition_to(state)

	# Контекст позволяет изменять объект Состояния во время выполнения.
    def transition_to(self, state: State):
        print(f"Context: Transition to {type(state).__name__}")
        self._state = state
        self._state.context = self

	# Контекст делегирует часть своего поведения текущему объекту Состояния.
    def request1(self):
        self._state.handle1()

    def request2(self):
        self._state.handle2()


# Базовый класс Состояния объявляет методы, которые должны реализовать все Конкретные
# Состояния, а также предоставляет обратную ссылку на объект Контекст, связанный с Состоянием.
# Эта обратная ссылка может использоваться Состояниями для передачи Контекста другому Состоянию.
class State(ABC):
    @property
    def context(self) -> Context:
        return self._context

    @context.setter
    def context(self, context: Context) -> None:
        self._context = context

    @abstractmethod
    def handle1(self) -> None:
        pass

    @abstractmethod
    def handle2(self) -> None:
        pass


# Конкретные Состояния реализуют различные модели поведения, связанные с состоянием Контекста.
class ConcreteStateA(State):
    def handle1(self) -> None:
        print("ConcreteStateA handles request1.")
        print("ConcreteStateA wants to change the state of the context.")
        self.context.transition_to(ConcreteStateB())

    def handle2(self) -> None:
        print("ConcreteStateA handles request2.")


class ConcreteStateB(State):
    def handle1(self) -> None:
        print("ConcreteStateB handles request1.")

    def handle2(self) -> None:
        print("ConcreteStateB handles request2.")
        print("ConcreteStateB wants to change the state of the context.")
        self.context.transition_to(ConcreteStateA())


# Клиентский код
def state_run():
    context = Context(ConcreteStateA())
    context.request1()
    context.request2()


# -------------------------------------------------------------------------------
# Реализация паттерна "Состояние"
# -------------------------------------------------------------------------------
class State(ABC):

	@abstractmethod
	def eat(self) -> str:
		pass

	@abstractmethod
	def find_food(self) -> str:
		pass

	@abstractmethod
	def move(self) -> str:
		pass

	@abstractmethod
	def dream(self) -> str:
		pass


class SleepState(State):

	def eat(self) -> str:
		return 'не может есть, пока спит'

	def find_food(self) -> str:
		return 'ищет еду, но только в своих мечтах'

	def move(self) -> str:
		return 'не может двигаться, пока спит'

	def dream(self) -> str:
		return 'спит и видит чудный сон'


class OnGroundState(State):

	def eat(self) -> str:
		return 'вываливает на пузо добытых моллюсков и начинает неспешно их есть'

	def find_food(self) -> str:
		return 'находит дурно пахнущую, но вполне съедобную тушу выбросившегося на берег кита'

	def move(self) -> str:
		return 'неуклюже ползет вдоль береговой линии'

	def dream(self) -> str:
		return 'на мгновние останавливается, замечтавшись об одной знакомой самке'


class InWaterState(State):

	def eat(self) -> str:
		return 'не может есть в воде'

	def find_food(self) -> str:
		return 'вспахивает бивнями морское дно, вылавливая моллюсков своими вибриссами'

	def move(self) -> str:
		return 'грациозно рассекает волны мирового океана'

	def dream(self) -> str:
		return 'не спит и не мечтает в воде - это слишком сложно'


class Walrus:

	def __init__(self, state: State) -> None:
		self._state = state

	def change_state(self, state: State) -> None:
		self._state = state

	def eat(self) -> None:
		self._execute('eat')

	def find_food(self) -> None:
		self._execute('find_food')

	def move(self) -> None:
		self._execute('move')

	def dream(self) -> None:
		self._execute('dream')

	def _execute(self, operation: str) -> None:
		try:
			func = getattr(self._state, operation)
			print('Морж {}.'.format(func()))
		except AttributeError:
			print('Морж такого делать не умеет.')


def test_state():
	sleep = SleepState()
	on_ground = OnGroundState()
	in_water = InWaterState()
	walrus = Walrus(on_ground)
	print('OUTPUT:')
	walrus.change_state(in_water)
	walrus.move()
	walrus.find_food()
	walrus.change_state(on_ground)
	walrus.eat()
	walrus.move()
	walrus.dream()
	walrus.change_state(sleep)
	walrus.dream()