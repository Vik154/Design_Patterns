import FactoryMethod
from Creational_patterns.AbstractFactory import *


class Handler():
    def __init__(self) -> object:
        self._factory_method = FactoryMethod.ReleaseFactoryMethod()
        self._abstract_factory = FactoryTest()

    def run(self):
        info = "\nВыберите команду: \
        \nq - Выход \
        \n1 - Паттерн \"Фабричный метод\" \
        \n2 - Паттерн \"\" \n";

        while (True):
            key = input(info)
            match key:
                case 'q':
                    return
                case '1': self._factory_method.show(); continue;
                case '2': self._abstract_factory.show(); continue;
                case _:
                    print("Не тыкай чё-попало")
                

# ------------------------
if __name__ == "__main__":
    handler = Handler()
    handler.run()