#include "Creational_patterns/FactoryMethod.h"
#include "Creational_patterns/AbstractFactory.h"
#include "Creational_patterns/Singleton.hpp"
#include "Creational_patterns/Prototype.hpp"

namespace Pattern {
	using std::unique_ptr;
	using std::make_unique;
	using std::string;
	using std::cout;
	using std::cin;

	class Handler final {
	public:
		Handler() :
			_factory_method(make_unique<Creational::FactoryMethod>()),
			_abstract_factory(make_unique<Creational::AbstractFactoryTest>())
		{}
		
		void run() {
			char result;
			string info = "\nВыберите команду:"
				"\nq - Выход"
				"\n1 - Паттерн \"Фабричный метод\""
				"\n2 - Паттерн \"Абстракная фабрика\""
				"\n3 - Паттерн \"Одиночка\""
				"\n4 - Паттерн \"Прототип\""
				"\n";
			do {
				cout << info;
				cin >> result;
				switch (result) {
				case 49: _factory_method->show_name_creator(); break;
				case 50: _abstract_factory->show_result();     break;
				case 51: Creational::test_singleton();         break;
				case 52: Creational::test_prototype(); break;
				default:
					cout << "Чё ты тыкаешь чё-попало. Такой команды нет, не тыкай!";
					break;
				}
			} while (result != 'q');
		}
	private:
		// Пример паттерна "Фабричный метод"
		unique_ptr<Creational::FactoryMethod> _factory_method;
		// Пример паттерна "Абстракная фабрика"
		unique_ptr<Creational::AbstractFactoryTest> _abstract_factory;

	};
}

int main(int argc, char** argv) {
	using namespace Pattern;
	setlocale(0, "");

	unique_ptr<Handler> handler = make_unique<Handler>();
	handler->run();

	return 0;
}