# Паттерн Декоратор (Decorator)
# Динамически добавляет объекту новые обязанности.
# Является гибкой альтернативой порождению подклассов с целью расширения функциональности.
# https://github.com/ivashkevichdn/PatternsTutorial/blob/master/Structural/Python/decorator.py


# Базовый интерфейс Компонента определяет поведение, которое изменяется декораторами.
class Component:
    def operation(self) -> str:
        pass


# Конкретные Компоненты предоставляют реализации поведения по умолчанию. 
# Может быть несколько вариаций этих классов.
class ConcreteComponent(Component):
    def operation(self) -> str:
        return "ConcreteComponent"


# Базовый класс Декоратора следует тому же интерфейсу, что и другие компоненты. Основная 
# цель этого класса - определить интерфейс обёртки для всех конкретных декораторов. 
# Реализация кода обёртки по умолчанию может включать в себя поле для хранения завёрнутого
# компонента и средства его инициализации.
class Decorator(Component):
    _component: Component = None

    def __init__(self, component: Component) -> None:
        self._component = component

    @property
    def component(self) -> str:
        return self._component

    def operation(self) -> str:
        self._component.operation()


# Конкретные Декораторы вызывают обёрнутый объект и изменяют его результат некоторым образом.
class ConcreteDecoratorA(Decorator):
    def operation(self) -> str:
        """
        Декораторы могут вызывать родительскую реализацию операции, вместо того,
        чтобы вызвать обёрнутый объект напрямую. Такой подход упрощает
        расширение классов декораторов.
        """
        return f"ConcreteDecoratorA({self.component.operation()})"


# Декораторы могут выполнять своё поведение до или после вызова обёрнутого объекта.
class ConcreteDecoratorB(Decorator):
    def operation(self) -> str:
        return f"ConcreteDecoratorB({self.component.operation()})"


# Клиентский код работает со всеми объектами, используя интерфейс Компонента. Таким образом,
# он остаётся независимым от конкретных классов компонентов, с которыми работает.
def client_code(component: Component) -> None:
    # ...
    print(f"RESULT: {component.operation()}", end="")
    # ...


def test_decorator():
    simple = ConcreteComponent()
    print("Client: I've got a simple component:")
    client_code(simple)
    print("\n")

    decorator1 = ConcreteDecoratorA(simple)
    decorator2 = ConcreteDecoratorB(decorator1)
    print("Client: Now I've got a decorated component:")
    client_code(decorator2)