# Паттерн "Одиночка" (Singleton)
# Источник 1 (метапрограммирование) - https://pythonist.ru/metaklassy-v-python/
# Источник 2 (синглтон) - https://www.youtube.com/watch?v=bnY1Z4Hoo_o

from threading import Lock, Thread

#-----------------------------------------
# Концепция паттернна (в пайтоне реализуется с помощью метапрограммирования)
#-----------------------------------------
# Однопоточная реализация:
# Python создает классы, используя метакласс
# Всякий раз, когда мы вызываем class для создания класса, есть метакласс,
# который колдует над созданием класса за кулисами.
# При определении класса и отсутствии метакласса по умолчанию будет использоваться метакласс type.
# Если задан метакласс, не являющийся экземпляром type(), то он используется непосредственно как метакласс. 
class Singleton(type):
    # Создается словарь, где будет хранится экземпляр класса Singleton
    _instances = {}         
    # Перегрузка оператора вызова () определив собственный метод __call__() в метаклассе,
    # что позволит настроить поведение при вызове класса. 
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            instance = super().__call__(*args, **kwargs)
        cls._instances[cls] = instance
        return cls._instances[cls]

# С защитой критической секции (многопоточный)
class SingletonTh(type):
    _instances = {}
    _lock: Lock = Lock()
    def __call__(cls, *args, **kwargs):
        with cls._lock:
            if cls not in cls._instances:
                instance = super().__call__(*args, **kwargs)
                cls._instances[cls] = instance
        return cls._instances[cls]


# Пример использования
class Logger(metaclass=SingletonTh):
    def __init__(self, name):
        self.name = name
    def write_log(self, path):
        pass


def test_logger(name):
    logger = Logger(name)
    print(logger.name)

def test_singleton():
    process1 = Thread(target=test_logger, args=("FOO",))
    process2 = Thread(target=test_logger, args=("BAR",))
    process1.start()
    process2.start()
#-----------------------------------------