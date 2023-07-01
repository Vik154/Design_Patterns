# Паттерн "Команда" (Command)
# Команда – это поведенческий паттерн, позволяющий заворачивать запросы или простые
# операции в отдельные объекты. Это позволяет откладывать выполнение команд, 
# выстраивать их в очереди, а также хранить историю и делать отмену. 

from __future__ import annotations
from abc import ABC, abstractmethod

# Концепция паттерна "Команда"
# Интерфейс Команды объявляет метод для выполнения команд.
class Command(ABC):
    @abstractmethod
    def execute(self): pass


class ConcreteCommand(Command):
  def __init__(self, receiver):
    self._receiver = receiver
  def execute(self):
    self._receiver.action()


# Классы Получателей содержат некую важную бизнес-логику. Они умеют выполнять все
# виды операций, связанных с выполнением запроса. 
# Фактически, любой класс может выступать Получателем.
class Receiver:
  def action(self): pass


# Отправитель связан с одной или несколькими командами. Он отправляет запрос команде.
class Invoker:
  def set_command(self, command):
    self._command = command
  def execute_command(self):
    self._command.execute()


# -------------------------------------------------------------------------------
# Реализация паттерна "Команда"
# -------------------------------------------------------------------------------
# Receiver - объект военного отряда
class Troop:
	# Начать движение в определенном направлении
	def move(self, direction: str) -> None:
		print('Отряд начал движение {}'.format(direction))

	# Остановиться
	def stop(self) -> None:
		print('Отряд остановился')


# Базовый класс для всех команд
class ICommand(ABC):
	@abstractmethod
	def execute(self) -> None: pass		# Приступить к выполнению команды

	@abstractmethod
	def unexecute(self) -> None: pass	# Отменить выполнение команды	


# Команда для выполнения атаки
class AttackCommand(ICommand):
	def __init__(self, troop: Troop) -> None:
		self.troop = troop

	def execute(self) -> None:
		self.troop.move('вперед')

	def unexecute(self) -> None:
		self.troop.stop()


class RetreatCommand(Command):
	def __init__(self, troop: Troop) -> None:
		self.troop = troop

	def execute(self) -> None:
		self.troop.move('назад')

	def unexecute(self) -> None:
		self.troop.stop()


# Invoker - интерфейс, через который можно отдать команды определенному отряду
class TroopInterface:
	def __init__(self, attack: AttackCommand, retreat: RetreatCommand) -> None:
		self.attack_command = attack
		self.retreat_command = retreat
		self.current_command = None		# команда, выполняющаяся в данный момент

	def attack(self) -> None:
		self.current_command = self.attack_command
		self.attack_command.execute()

	def retreat(self) -> None:
		self.current_command = self.retreat_command
		self.retreat_command.execute()

	def stop(self) -> None:
		if self.current_command:
			self.current_command.unexecute()
			self.current_command = None
		else:
			print('Отряд не может остановиться, так как не двигается')


def test_command():
	troop = Troop()
	interface = TroopInterface(AttackCommand(troop), RetreatCommand(troop))
	interface.attack()
	interface.stop()
	interface.retreat()
	interface.stop()