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
#include "Behavioral_patterns/Chain_of_responsibility.hpp"
#include "Behavioral_patterns/Interpreter.hpp"
#include "Behavioral_patterns/Mediator.hpp"
#include "Behavioral_patterns/Memento.hpp"
#include "Behavioral_patterns/Visitor.hpp"
#include "Structural_patterns/Decorator.hpp"


namespace Pattern {
	using std::unique_ptr;
	using std::make_unique;
	using std::string;
	using std::cout;
	using std::cin;


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
			"\n11 - Паттерн \"Состояние\""
			"\n12 - Паттерн \"Цепочка обязанностей\""
			"\n13 - Паттерн \"Интерпретатор\""
			"\n14 - Паттерн \"Посредник\""
			"\n15 - Паттерн \"Хранитель\""
			"\n16 - Паттерн \"Посетитель\""
			"\n17 - Паттерн \"Декоратор\""
			"\n";

		while (true) {
			cout << info;
			cin >> result;

			try {
				if (result == "q") return;
				int res = stoi(result);
			}
			catch (...) {
				cout << "Чё ты тыкаешь чё-попало. Такой команды нет, не тыкай!";
				cin.clear();
				continue;
			}

			switch (stoi(result)) {
			case 1: Creational::test_factory_method();    break;
			case 2: Creational::test_abstract_factory();  break;
			case 3: Creational::test_singleton();         break;
			case 4: Creational::test_prototype();         break;
			case 5: Creational::test_builder();           break;
			case 6: Behavioral::test_strategey();         break;
			case 7: Behavioral::test_observer();          break;
			case 8: Behavioral::test_command();           break;
			case 9: Behavioral::test_template();          break;
			case 10: Behavioral::test_iterator();         break;
			case 11: Behavioral::test_state();            break;
			case 12: Behavioral::test_chain();            break;
			case 13: Behavioral::test_interpreter();      break;
			case 14: Behavioral::test_mediator();         break;
			case 15: Behavioral::test_memento();          break;
			case 16: Behavioral::test_visitor();          break;
			case 17: Structural::test_decorator();        break;
			default: cin.clear();                         break;
			}
		}
	}
}

// ---------------------------------------------------------------
int main(int argc, char** argv) {
	setlocale(0, "");
	Pattern::run();
	return 0;
}
// ---------------------------------------------------------------