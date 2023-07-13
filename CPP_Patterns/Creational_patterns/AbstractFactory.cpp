#include "AbstractFactory.h"

namespace Creational {

	// Конструктор конкретного продукта
	LinuxButton::LinuxButton(const string& wtype)     : _widget_type(wtype) {}
	LinuxMenu::LinuxMenu(const string& wtype)         : _widget_type(wtype) {}
	WindowsButton::WindowsButton(const string& wtype) : _widget_type(wtype) {}
	WindowsMenu::WindowsMenu(const string& wtype)     : _widget_type(wtype) {}

	// Методы конкретных продуктов (реализация интерфейса Widget)
	void LinuxMenu::make_widget()     { cout << "Создано меню Linux\n"; }
	void LinuxButton::make_widget()   { cout << "Создана кнопка Linux\n"; }
	void WindowsButton::make_widget() { cout << "Создана кнопка Windows\n"; }
	void WindowsMenu::make_widget()   { cout << "Создано меню Windows\n"; }

	const string& LinuxButton::get_name()   { return _widget_type; }
	const string& LinuxMenu::get_name()     { return _widget_type; }
	const string& WindowsButton::get_name() { return _widget_type; }
	const string& WindowsMenu::get_name()   { return _widget_type; }

	// Реализация интерфейса конкретных фабрик
	// Linux
	LinuxFactory::LinuxFactory(const string& fname) : _name_factory(fname) {}

	unique_ptr<Widget> LinuxFactory::create_button() {
		return make_unique<LinuxButton>("Linux кнопка");
	}
	unique_ptr<Widget> LinuxFactory::create_menu() {
		return make_unique<LinuxMenu>("Linux меню");
	}
	const string& LinuxFactory::get_name() { return _name_factory; }

	// Windows
	WindowsFactory::WindowsFactory(const string& fname) : _name_factory(fname) {}

	unique_ptr<Widget> WindowsFactory::create_button() {
		return make_unique<WindowsButton>("Windows кнопка");
	}
	unique_ptr<Widget> WindowsFactory::create_menu() {
		return make_unique<WindowsMenu>("Windows меню");
	}
	const string& WindowsFactory::get_name() { return _name_factory; }
	//----------------------------------------------------

	// Реализация клиента
	Client::Client(unique_ptr<WidgetsFactory>&& concrete_factory) :
		_button_widget(concrete_factory->create_button()),
		_menu_widget(concrete_factory->create_menu())
	{ }

	void Client::show_result() {
		cout << _button_widget->get_name() << " говорит: ";
		_button_widget->make_widget();
		cout << _menu_widget->get_name() << " говорит: ";
		_menu_widget->make_widget();
		cout << "--------------------------------------\n";
	}
	//----------------------------------------------------------
	void test_abstract_factory() {
		unique_ptr<AbstractFactoryTest> _abstract_factory = make_unique<AbstractFactoryTest>();
		_abstract_factory->show_result();
	}
}
