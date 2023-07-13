# Паттерн "Интерпретатор" (Interpreter)
# https://sourcemaking.com/design_patterns/interpreter/python/1
# https://ru.wikipedia.org/wiki/%D0%98%D0%BD%D1%82%D0%B5%D1%80%D0%BF%D1%80%D0%B5%D1%82%D0%B0%D1%82%D0%BE%D1%80_(%D1%88%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD_%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)

from abc import ABC, abstractmethod

# Концепция паттерна "Интерпретатор"
class AbstractExpression(ABC):
    @abstractmethod
    def interpret(self):
        pass


class NonterminalExpression(AbstractExpression):
    def __init__(self, expression):
        self._expression = expression

    def interpret(self):
        self._expression.interpret()


class TerminalExpression(AbstractExpression):
    def interpret(self):
        pass


def main():
    abstract_syntax_tree = NonterminalExpression(TerminalExpression())
    abstract_syntax_tree.interpret()


# -------------------------------------------------------------------------------
# Реализация паттерна "Интерпретатор"
# -------------------------------------------------------------------------------
# Система для вычисления и манипулирования булевыми выражениями. Пример из книги 
# Gang of Four - "Design Patterns: Elements of Reusable Object-Oriented Software"


# Контекст среды исполнения интерпретатора
class Context:
	def __init__(self, variables: dict = {}) -> None:
		# словарь соответствий имен переменных их значениям
		self._variables = variables

	# Исключение, прокидываемое в случае некорректной работы с данным классом
	class ContextException(Exception): pass

	# Получает значение переменной по ее имени
	def lookup(self, name: str) -> bool:
		if name in self._variables:
			return self._variables[name]
		raise self.ContextException('Неизвестная переменная {}'.format(name))

	# Назначает значение переменной по ее имени
	def assign(self, name: str, value: bool) -> None:
		self._variables[name] = value


# Абстрактное логическое выражение
class BooleanExp(ABC):
	# Получение результата логического выражения
	@abstractmethod
	def evaluate(self, context: Context) -> bool: pass


# Логическая константа
class ConstantExp(BooleanExp):
	def __init__(self, value: bool):
		self._value = value

	def evaluate(self, context: Context):
		return self._value


# Логическая переменная (значение переменных хранится в объекте контекста интерпретатора)
class VariableExp(BooleanExp):
	def __init__(self, name: str) -> None:
		self._name = name

	def evaluate(self, context: Context) -> bool:
		return context.lookup(self._name)


# Абстрактный класс для бинарных логических операций
class BinaryOperationExp(BooleanExp, ABC):
	def __init__(self, left: BooleanExp, right: BooleanExp) -> None:
		self._left = left
		self._right = right


# Конъюнкция
class AndExp(BinaryOperationExp):
	def evaluate(self, context: Context) -> bool:
		return self._left.evaluate(context) and self._right.evaluate(context)


# Дизъюнкция
class OrExp(BinaryOperationExp):
	def evaluate(self, context: Context) -> bool:
		return self._left.evaluate(context) or self._right.evaluate(context)


# Отрицание
class NotExp(BooleanExp):
	def __init__(self, operand: BooleanExp) -> None:
		self._operand = operand

	def evaluate(self, context: Context) -> bool:
		return not self._operand.evaluate(context)


# Функция для выполнения тестирования нашего интерпретатора
def execute_test(context: Context, x: bool, y: bool) -> None:
	context.assign('x', x)
	context.assign('y', y)
	expression = OrExp(		# (True and x) or (у and (not x))
		AndExp(ConstantExp(True), VariableExp('x')), 
		AndExp(VariableExp('y'), NotExp(VariableExp('x')))
	)
	print(expression.evaluate(context))


def test_interpreter():
	print('OUTPUT:')
	context = Context()
	execute_test(context, True, False)
	execute_test(context, False, True)
	execute_test(context, False, False)