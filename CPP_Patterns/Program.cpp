#include "Creational_patterns/FactoryMethod.h"
#include "Creational_patterns/AbstractFactory.h"
#include "Creational_patterns/Singleton.hpp"
#include "Creational_patterns/Prototype.hpp"
#include "Creational_patterns/Builder.hpp"
#include "Behavioral_patterns/Strategy.hpp"
#include "Behavioral_patterns/Observer.hpp"
#include "Behavioral_patterns/Command.hpp"

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
			string info = "\n�������� �������:"
				"\nq - �����"
				"\n1 - ������� \"��������� �����\""
				"\n2 - Паттерн \"Абстракная фабрика\""
				"\n3 - Паттерн \"Одиночка\""
				"\n4 - Паттерн \"Прототип\""
				"\n5 - Паттерн \"Строитель\""
				"\n6 - Паттерн \"Стратегия\""
				"\n7 - Паттерн \"Наблюдатель\""
				"\n8 - Паттерн \"Команда\""
				"\n9 - Паттерн \"Команда\""
				"\n";
			do {
				cout << info;
				cin >> result;
				switch (result) {
				case 49: _factory_method->show_name_creator(); break;
				case 50: _abstract_factory->show_result();     break;
				case 51: Creational::test_singleton();         break;
				case 52: Creational::test_prototype();         break;
				case 53: Creational::test_builder();           break;
				case 54: Behavioral::test_strategey();         break;
				case 55: Behavioral::test_observer();          break;
				case 56: Behavioral::test_command();           break;
				default:
					cout << "׸ �� ������� ��-������. ����� ������� ���, �� �����!";
					break;
				}
			} while (result != 'q');
		}
	private:
		// ������ �������� "��������� �����"
		unique_ptr<Creational::FactoryMethod> _factory_method;
		// ������ �������� "���������� �������"
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