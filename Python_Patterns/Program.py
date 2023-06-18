from Creational_patterns.Prototype import test_prototype
import FactoryMethod
from Creational_patterns.AbstractFactory import *
from Creational_patterns.Singleton import test_singleton


class Handler():
    def __init__(self) -> object:
        self._factory_method = FactoryMethod.ReleaseFactoryMethod()
        self._abstract_factory = FactoryTest()

    def run(self):

        info = "\nВыберите команду: \
        \nq - Выход \
        \n1 - Паттерн \"Фабричный метод\" \
        \n2 - Паттерн \"Абстрактнрая фабрика\" \
        \n3 - Паттерн \"Singleton\" \
        \n4 - Паттерн \"Прототип\" \
        \n";

        while (True):
            key = input(info)
            match key:
                case 'q': return;
                case 'й': return;
                case '1': self._factory_method.show(); continue;
                case '2': self._abstract_factory.show(); continue;
                case '3': test_singleton(); continue;
                case '4': test_prototype(); continue;
                case _:
                    print("Не тыкай чё-попало")
                

# ------------------------
if __name__ == "__main__":
    handler = Handler()
    handler.run()