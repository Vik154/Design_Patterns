from Behavioral_patterns.Command import test_command
from Creational_patterns.Prototype import test_prototype
import FactoryMethod
from Creational_patterns.AbstractFactory import *
from Creational_patterns.Singleton import test_singleton
from Creational_patterns.Builder import test_builder
from Behavioral_patterns.Strategy import test_strategy
from Behavioral_patterns.Observer import test_observer
from Behavioral_patterns.TemplateMethod import test_template


class Handler():
    def __init__(self):
        self._factory_method = FactoryMethod.ReleaseFactoryMethod()
        self._abstract_factory = FactoryTest()

    def run(self):

        info = "\nВыберите команду: \
        \nq - Выход \
        \n1 - Паттерн \"Фабричный метод\" \
        \n2 - Паттерн \"Абстрактнрая фабрика\" \
        \n3 - Паттерн \"Singleton\" \
        \n4 - Паттерн \"Прототип\" \
        \n5 - Паттерн \"Строитель\" \
        \n6 - Паттерн \"Стратегия\" \
        \n7 - Паттерн \"Наблюдатель\" \
        \n8 - Паттерн \"Команда\" \
        \n9 - Паттерн \"Наблюдатель\" \
        \n";

        while (True):
            key = input(info)
            match key:
                case 'q': return;
                case 'й': return;
                case '1': self._factory_method.show();   continue;
                case '2': self._abstract_factory.show(); continue;
                case '3': test_singleton();              continue;
                case '4': test_prototype();              continue;
                case '5': test_builder();                continue;
                case '6': test_strategy();               continue;
                case '7': test_observer();               continue;
                case '8': test_command();                continue;
                case '9': test_template();               continue;
                case _:
                    print("Не тыкай чё-попало")
                

# ------------------------
if __name__ == "__main__":
    handler = Handler()
    handler.run()