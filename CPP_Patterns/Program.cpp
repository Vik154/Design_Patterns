#include "Creational_patterns/FactoryMethod.h"

namespace Pattern {
	using std::unique_ptr;
	using std::make_unique;
	using std::string;
	using std::cout;
	using std::cin;

	class Handler final {
	public:
		Handler() :
			_factory_method(make_unique<Creational::FactoryMethod>()) 
		{}

		void run() {
			char result;
			string info = "\n�������� �������:"
				"\nq - �����"
				"\n1 - ������� \"��������� �����\""
				"\n2 - ������� \"\" \n";
			do {
				cout << info;
				cin >> result;
				switch (result) {
				case 49: _factory_method->show_name_creator(); break;
				case 50: cout << "CHAAAAAR";
					break;
				default:
					cout << "׸ �� ������� ��-������. ����� ������� ���, �� �����!";
					break;
				}
			} while (result != 'q');
		}
	private:
		// ������ �������� "��������� �����"
		unique_ptr<Creational::FactoryMethod> _factory_method;
	};
}

int main(int argc, char** argv) {
	using namespace Pattern;
	setlocale(0, "");

	unique_ptr<Handler> handler = make_unique<Handler>();
	handler->run();

	return 0;
}