# Паттерн Фасад (Facade)
# Предоставляет унифицированный интерфейс вместо набора интерфейсов некоторой подсистемы.
# Фасад определяет интерфейс более высокого уровня, который упрощает использование подсистемы.
# https://github.com/ivashkevichdn/PatternsTutorial/blob/master/Structural/Python/facade.py
# https://www.geeksforgeeks.org/facade-method-python-design-patterns/

from __future__ import annotations

# Концепция паттерна
# Класс Фасада предоставляет простой интерфейс для сложной логики одной или нескольких 
# подсистем. Фасад делегирует запросы клиентов соответствующим объектам внутри подсистемы.
# Фасад также отвечает за управление их жизненным циклом. 
# Все это защищает клиента от нежелательной сложности подсистемы.
class Facade:
    # В зависимости от потребностей вашего приложения вы можете предоставить Фасаду
    # существующие объекты подсистемы или заставить Фасад создать их самостоятельно.
    def __init__(self, subsystem1: Subsystem1, subsystem2: Subsystem2) -> None:
        self._subsystem1 = subsystem1 or Subsystem1()
        self._subsystem2 = subsystem2 or Subsystem2()

    # Методы Фасада удобны для быстрого доступа к сложной функциональности подсистем.
    # Однако клиенты получают только часть возможностей подсистемы.
    def operation(self) -> str:
        results = []
        results.append("Facade initializes subsystems:")
        results.append(self._subsystem1.operation1())
        results.append(self._subsystem2.operation1())
        results.append("Facade orders subsystems to perform the action:")
        results.append(self._subsystem1.operation_n())
        results.append(self._subsystem2.operation_z())
        return "\n".join(results)


# Подсистема может принимать запросы либо от фасада, либо от клиента напрямую. В любом 
# случае, для Подсистемы Фасад – это ещё один клиент, и он не является частью Подсистемы.
class Subsystem1:
    def operation1(self) -> str:
        return "Subsystem1: Ready!"
    
    # ...

    def operation_n(self) -> str:
        return "Subsystem1: Go!"


# Некоторые фасады могут работать с разными подсистемами одновременно.
class Subsystem2:
    def operation1(self) -> str:
        return "Subsystem2: Get ready!"

    # ...

    def operation_z(self) -> str:
        return "Subsystem2: Fire!"


# Клиентский код работает со сложными подсистемами через простой интерфейс, предоставляемый
# Фасадом. Когда фасад управляет жизненным циклом подсистемы, клиент может даже не знать о
# существовании подсистемы. Такой подход позволяет держать сложность под контролем.
def client_code(facade: Facade) -> None:
    print(facade.operation(), end="")


def run_facade():
    # В клиентском коде могут быть уже созданы некоторые объекты подсистемы. В
    # этом случае может оказаться целесообразным инициализировать Фасад с этими
    # объектами вместо того, чтобы позволить Фасаду создавать новые экземпляры.
    subsystem1 = Subsystem1()
    subsystem2 = Subsystem2()
    facade = Facade(subsystem1, subsystem2)
    client_code(facade)


#----------------------------------------------
# Реализация паттерна "Фасад"
#----------------------------------------------
class Washing:
    '''Subsystem # 1'''
  
    def wash(self):
        print("Washing...")
  
  
class Rinsing:
    '''Subsystem # 2'''
  
    def rinse(self):
        print("Rinsing...")
  
  
class Spinning:
    '''Subsystem # 3'''
  
    def spin(self):
        print("Spinning...")
  
  
class WashingMachine:
    '''Facade'''
  
    def __init__(self):
        self.washing = Washing()
        self.rinsing = Rinsing()
        self.spinning = Spinning()
  
    def startWashing(self):
        self.washing.wash()
        self.rinsing.rinse()
        self.spinning.spin()
  

# Клиентская часть
def test_facade():
    washingMachine = WashingMachine()
    washingMachine.startWashing()