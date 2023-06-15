import FactoryMethod


class Handler():
    def __init__(self) -> object:
        self._factory_method = FactoryMethod.ReleaseFactoryMethod()

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
                case '2':
                    pass
                case _:
                    print("Не тыкай чё-попало")
                

# ------------------------
if __name__ == "__main__":
    handler = Handler()
    handler.run()