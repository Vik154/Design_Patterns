# Паттерн Адаптер (Adapter)
# Адаптер - паттерн, структурирующий классы и объекты.
# Преобразует интерфейс одного класса в интерфейс другого, который ожидают клиенты.
# Адаптер обеспечивает совместную работу классов с несовместимыми интерфейсами, 
# которая без него была бы невозможна.
# https://github.com/ivashkevichdn/PatternsTutorial/blob/master/Structural/Python/adapter.py


# Целевой класс объявляет интерфейс, с которым может работать клиентский код.
class Target():
    def request(self) -> str:
        return "Target: The default target's behavior."


# Адаптируемый класс содержит некоторое полезное поведение, но его интерфейс
# несовместим с существующим клиентским кодом. Адаптируемый класс нуждается в
# некоторой доработке, прежде чем клиентский код сможет его использовать.
class Adaptee:
    def specific_request(self) -> str:
        return ".eetpadA eht fo roivaheb laicepS"


# Адаптер делает интерфейс Адаптируемого класса совместимым с целевым интерфейсом.
class Adapter(Target):
    def __init__(self, adaptee: Adaptee) -> None:
        self.adaptee = adaptee

    def request(self) -> str:
        return f"Adapter: (TRANSLATED) {self.adaptee.specific_request()[::-1]}"


# Клиентский код поддерживает все классы, использующие интерфейс Target.
def client_code(target: Target) -> None:
    print(target.request(), end="")


def test_adapter():
    print("Client: I can work just fine with the Target objects:")
    target = Target()
    client_code(target)
    print("\n")

    adaptee = Adaptee()
    print("Client: The Adaptee class has a weird interface. See, I don't understand it:")
    print(f"Adaptee: {adaptee.specific_request()}", end="\n\n")

    print("Client: But I can work with it via the Adapter:")
    adapter = Adapter(adaptee)
    client_code(adapter)