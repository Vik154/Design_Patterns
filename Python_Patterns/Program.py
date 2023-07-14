from Creational_patterns.Prototype               import test_prototype
from Creational_patterns.FactoryMethod           import test_factory_method
from Creational_patterns.AbstractFactory         import test_abstract_factory
from Creational_patterns.Singleton               import test_singleton
from Creational_patterns.Builder                 import test_builder
from Behavioral_patterns.Strategy                import test_strategy
from Behavioral_patterns.Observer                import test_observer
from Behavioral_patterns.TemplateMethod          import test_template
from Behavioral_patterns.Iterator                import test_iterator
from Behavioral_patterns.State                   import test_state
from Behavioral_patterns.Chain_of_responsibility import test_chain
from Behavioral_patterns.Command                 import test_command
from Behavioral_patterns.Interpreter             import test_interpreter
from Behavioral_patterns.Mediator                import test_mediator
from Behavioral_patterns.Memento                 import test_memento
from Behavioral_patterns.Visitor                 import test_visitor
from Structural_patterns.Decorator               import test_decorator
from Structural_patterns.Adapter                 import test_adapter
from Structural_patterns.Facade                  import test_facade
from Structural_patterns.Composite               import test_composite
from Structural_patterns.Proxy                   import test_proxy
from Structural_patterns.Bridge                  import test_bridge


def run():
    info = "\nВыберите команду: \
    \nq  - Выход \
    \n1  - Паттерн \"Фабричный метод\" \
    \n2  - Паттерн \"Абстрактнрая фабрика\" \
    \n3  - Паттерн \"Singleton\" \
    \n4  - Паттерн \"Прототип\" \
    \n5  - Паттерн \"Строитель\" \
    \n6  - Паттерн \"Стратегия\" \
    \n7  - Паттерн \"Наблюдатель\" \
    \n8  - Паттерн \"Команда\" \
    \n9  - Паттерн \"Наблюдатель\" \
    \n10 - Паттерн \"Итератор\" \
    \n11 - Паттерн \"Состояние\" \
    \n12 - Паттерн \"Цепочка обязанностей\" \
    \n13 - Паттерн \"Интерпретатор\" \
    \n14 - Паттерн \"Посредник\" \
    \n15 - Паттерн \"Хранитель\" \
    \n16 - Паттерн \"Посетитель\" \
    \n17 - Паттерн \"Декоратор\" \
    \n18 - Паттерн \"Адаптер\" \
    \n19 - Паттерн \"Фасад\" \
    \n20 - Паттерн \"Компоновщик\" \
    \n21 - Паттерн \"Заместитель\" \
    \n22 - Паттерн \"Мост\" \
    \n";

    while (True):
        key = input(info)
        match key:
            case 'q': return;
            case 'й': return;
            case '1':  test_factory_method();   continue;
            case '2':  test_abstract_factory(); continue;
            case '3':  test_singleton();        continue;
            case '4':  test_prototype();        continue;
            case '5':  test_builder();          continue;
            case '6':  test_strategy();         continue;
            case '7':  test_observer();         continue;
            case '8':  test_command();          continue;
            case '9':  test_template();         continue;
            case '10': test_iterator();         continue;
            case '11': test_state();            continue;
            case '12': test_chain();            continue;
            case '13': test_interpreter();      continue;
            case '14': test_mediator();         continue;
            case '15': test_memento();          continue;
            case '16': test_visitor();          continue;
            case '17': test_decorator();        continue;
            case '18': test_adapter();          continue;
            case '19': test_facade();           continue;
            case '20': test_composite();        continue;
            case '21': test_proxy();            continue;
            case '22': test_bridge();           continue;
            case _:
                print("Не тыкай чё-попало")
                
                
# -------------------------------------------------------
if __name__ == "__main__":
    run()
# -------------------------------------------------------