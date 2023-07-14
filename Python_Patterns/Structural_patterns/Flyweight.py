# Паттерн Приспособленец (Flyweight)
# Назначение: Позволяет вместить бóльшее количество объектов в отведённую
# оперативную память. Легковес экономит память, разделяя общее состояние объектов
# между собой, вместо хранения одинаковых данных в каждом объекте.
# https://github.com/Vik154/Design_Patterns/blob/work/CPP_Patterns/Structural_patterns/Flyweight.hpp


import json
from typing import Dict


# Легковес хранит общую часть состояния (также называемую внутренним состоянием), которая
# принадлежит нескольким реальным бизнес-объектам. Легковес принимает оставшуюся часть
# состояния (внешнее состояние, уникальное для каждого объекта) через его параметры метода.
class Flyweight():
    def __init__(self, shared_state: str) -> None:
        self._shared_state = shared_state

    def operation(self, unique_state: str) -> None:
        s = json.dumps(self._shared_state)
        u = json.dumps(unique_state)
        print(f"Flyweight: Displaying shared ({s}) and unique ({u}) state.", end="")


# Фабрика Легковесов создает объекты-Легковесы и управляет ими. Она обеспечивает правильное
# разделение легковесов. Когда клиент запрашивает легковес, фабрика либо возвращает
# существующий экземпляр, либо создает новый, если он ещё не существует.
class FlyweightFactory():
    _flyweights: Dict[str, Flyweight] = {}

    def __init__(self, initial_flyweights: Dict) -> None:
        for state in initial_flyweights:
            self._flyweights[self.get_key(state)] = Flyweight(state)

    # Возвращает хеш строки Легковеса для данного состояния.
    def get_key(self, state: Dict) -> str:
        return "_".join(sorted(state))

    # Возвращает существующий Легковес с заданным состоянием или создает новый.
    def get_flyweight(self, shared_state: Dict) -> Flyweight:
        key = self.get_key(shared_state)

        if not self._flyweights.get(key):
            print("FlyweightFactory: Can't find a flyweight, creating new one.")
            self._flyweights[key] = Flyweight(shared_state)
        else:
            print("FlyweightFactory: Reusing existing flyweight.")

        return self._flyweights[key]

    def list_flyweights(self) -> None:
        count = len(self._flyweights)
        print(f"FlyweightFactory: I have {count} flyweights:")
        print("\n".join(map(str, self._flyweights.keys())), end="")


def add_car_to_police_database(factory: FlyweightFactory, plates: str, owner: str,
                               brand: str, model: str, color: str) -> None:
    print("\n\nClient: Adding a car to database.")
    flyweight = factory.get_flyweight([brand, model, color])
    flyweight.operation([plates, owner])


def test_flyweight():

    factory = FlyweightFactory([
        ["Chevrolet", "Camaro2018", "pink"],
        ["Mercedes Benz", "C300", "black"],
        ["Mercedes Benz", "C500", "red"],
        ["BMW", "M5", "red"],
        ["BMW", "X6", "white"],
    ])

    factory.list_flyweights()
    add_car_to_police_database(factory, "CL234IR", "James Doe", "BMW", "M5", "red")
    add_car_to_police_database(factory, "CL234IR", "James Doe", "BMW", "X1", "red")
    print("\n")
    factory.list_flyweights()