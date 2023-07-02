#include "Creational_patterns/FactoryMethod.h"
#include "Creational_patterns/AbstractFactory.h"
#include "Creational_patterns/Singleton.hpp"
#include "Creational_patterns/Prototype.hpp"
#include "Creational_patterns/Builder.hpp"
#include "Behavioral_patterns/Strategy.hpp"
#include "Behavioral_patterns/Observer.hpp"
#include "Behavioral_patterns/Command.hpp"
#include "Behavioral_patterns/TemplateMethod.hpp"
#include "Behavioral_patterns/Iterator.hpp"
#include "Behavioral_patterns/State.hpp"


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
			string result;
			string info = "\nВыберите команду:"
				"\nq - Выход"
				"\n1 - Паттерн \"Фабричный метод\""
				"\n2 - Паттерн \"Абстракная фабрика\""
				"\n3 - Паттерн \"Одиночка\""
				"\n4 - Паттерн \"Прототип\""
				"\n5 - Паттерн \"Строитель\""
				"\n6 - Паттерн \"Стратегия\""
				"\n7 - Паттерн \"Наблюдатель\""
				"\n8 - Паттерн \"Команда\""
				"\n9 - Паттерн \"Шаблонный метод\""
				"\n10 - Паттерн \"Итератор\""
				"\n10 - Паттерн \"Состояние\""
				"\n";

			while (true) {
				cout << info;
				cin >> result;

				try {
					if (result == "q") return;
					int res = stoi(result); }
				catch (...) {
					cout << "Чё ты тыкаешь чё-попало. Такой команды нет, не тыкай!";
					cin.clear();
					continue;
				}

				switch (stoi(result)) {
					case 1: _factory_method->show_name_creator(); break;
					case 2: _abstract_factory->show_result();     break;
					case 3: Creational::test_singleton();         break;
					case 4: Creational::test_prototype();         break;
					case 5: Creational::test_builder();           break;
					case 6: Behavioral::test_strategey();         break;
					case 7: Behavioral::test_observer();          break;
					case 8: Behavioral::test_command();           break;
					case 9: Behavioral::test_template();          break;
					case 10: Behavioral::test_iterator();         break;
					case 11: Behavioral::test_state();            break;
					default: cin.clear();                         break;
				}
			}
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