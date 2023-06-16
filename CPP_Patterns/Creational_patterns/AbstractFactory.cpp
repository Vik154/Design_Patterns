#include "AbstractFactory.h"

namespace Creational {

	// ����������� ����������� ��������
	LinuxButton::LinuxButton(const string& wtype)     : _widget_type(wtype) {}
	LinuxMenu::LinuxMenu(const string& wtype)         : _widget_type(wtype) {}
	WindowsButton::WindowsButton(const string& wtype) : _widget_type(wtype) {}
	WindowsMenu::WindowsMenu(const string& wtype)     : _widget_type(wtype) {}

	// ������ ���������� ��������� (���������� ���������� Widget)
	void LinuxMenu::make_widget()     { cout << "������� ���� Linux\n"; }
	void LinuxButton::make_widget()   { cout << "������� ������ Linux\n"; }
	void WindowsButton::make_widget() { cout << "������� ������ Windows\n"; }
	void WindowsMenu::make_widget()   { cout << "������� ���� Windows\n"; }

	const string& LinuxButton::get_name()   { return _widget_type; }
	const string& LinuxMenu::get_name()     { return _widget_type; }
	const string& WindowsButton::get_name() { return _widget_type; }
	const string& WindowsMenu::get_name()   { return _widget_type; }

	// ���������� ���������� ���������� ������
	// Linux
	LinuxFactory::LinuxFactory(const string& fname) : _name_factory(fname) {}

	unique_ptr<Widget> LinuxFactory::create_button() {
		return make_unique<LinuxButton>("Linux ������");
	}
	unique_ptr<Widget> LinuxFactory::create_menu() {
		return make_unique<LinuxMenu>("Linux ����");
	}
	const string& LinuxFactory::get_name() { return _name_factory; }

	// Windows
	WindowsFactory::WindowsFactory(const string& fname) : _name_factory(fname) {}

	unique_ptr<Widget> WindowsFactory::create_button() {
		return make_unique<WindowsButton>("Windows ������");
	}
	unique_ptr<Widget> WindowsFactory::create_menu() {
		return make_unique<WindowsMenu>("Windows ����");
	}
	const string& WindowsFactory::get_name() { return _name_factory; }
	//----------------------------------------------------

	// ���������� �������
	Client::Client(unique_ptr<WidgetsFactory>&& concrete_factory) :
		_button_widget(concrete_factory->create_button()),
		_menu_widget(concrete_factory->create_menu())
	{ }

	void Client::show_result() {
		cout << _button_widget->get_name() << " �������: ";
		_button_widget->make_widget();
		cout << _menu_widget->get_name() << " �������: ";
		_menu_widget->make_widget();
		cout << "--------------------------------------\n";
	}
	//----------------------------------------------------------
}
