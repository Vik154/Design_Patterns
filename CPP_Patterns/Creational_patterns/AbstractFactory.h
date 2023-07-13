/// <summary> Фабричный метод (Factory Method) </summary> ///
/* Источник - эти ваши интернеты */
#pragma once
#include <iostream>
#include <memory>
#include <vector>

//-----------------------------------------------------------
// Концепция паттерна "Абстракная фабрика"
//-----------------------------------------------------------
namespace Сonception {
	// Создаются абстрактные классы продуктов, некий интерфейс
	class AbstractProduct1 abstract {
	public:
		virtual ~AbstractProduct1() {}
		virtual void release() = 0;
	};
	class AbstractProduct2 abstract {
	public:
		virtual ~AbstractProduct2() {}
		virtual void release() = 0;
	};

	// Создаются конкретные продукты, реализующие интерфейс базового абстракного класса
	class ConcreteProduct1 : public AbstractProduct1 {
	public:
		void release() override { /* определяется логика */ }
	};
	class ConcreteProduct2 : public AbstractProduct1 {
	public:
		void release() override { /* определяется логика */ }
	};
	class ConcreteProduct3 : public AbstractProduct2 {
	public:
		void release() override { /* определяется логика */ }
	};
	class ConcreteProduct4 : public AbstractProduct2 {
	public:
		void release() override { /* определяется логика */ }
	};
	
	// Создается абстракный класс Фабрики, в котором 
	// создаются объекты абстрактных классов продуктов
	class AbstractFactory abstract {
	public:
		virtual ~AbstractFactory() {}
		virtual AbstractProduct1* create_product1() = 0;
		virtual AbstractProduct2* create_product2() = 0;
	};
	// После реализуются конкретные фабрики, в которых
	// реализована логика + полиморфное поведение
	class ConcreteFactory1 : public AbstractFactory {
	public:
		AbstractProduct1* create_product1() override {
			return new ConcreteProduct1();
		}
		AbstractProduct2* create_product2() override {
			return new ConcreteProduct3();
		}
	};
	// После создается класс Client и использует класс фабрики для создания объектов. 
	// При этом он использует исключительно абстрактный класс фабрики AbstractFactory 
	// и абстрактные классы продуктов AbstractProductA и AbstractProductB и никак не зависит от их конкретных реализаций
	class Client {
	public:
		Client(AbstractFactory* factory) {
			_abstract_product1 = factory->create_product1();
			_abstract_product2 = factory->create_product2();
		}
		void run() {}
	private:
		AbstractProduct1* _abstract_product1;
		AbstractProduct2* _abstract_product2;
	};
}
//-----------------------------------------------------------

//-----------------------------------------------------------
// Реализация паттерна "Абстракная фабрика"
// За идею взят - https://iq.opengenus.org/abstract-factory-pattern-cpp/
//-----------------------------------------------------------
namespace Creational {

	using std::vector;
	using std::string;
	using std::unique_ptr;
	using std::shared_ptr;
	using std::make_shared;
	using std::make_unique;
	using std::cout;

	// Абстракный класс продукта
	class Widget abstract {
	public:
		virtual void make_widget() = 0;
		virtual const string& get_name() = 0;
		virtual ~Widget() {}
	};

	// Абстрактная фабрика
	class WidgetsFactory abstract {
	public:
		virtual unique_ptr<Widget> create_button() = 0;
		virtual unique_ptr<Widget> create_menu() = 0;
		virtual const string& get_name() = 0;
		virtual ~WidgetsFactory() {}
	};
	
	// Конкретный продукт, реализующий интерфейс Widget
	//-----------------------------------
	class LinuxButton : public Widget {
	public:
		LinuxButton(const string& wtype);
		void make_widget() override;
		const string& get_name() override;
	private:
		string _widget_type;
	};

	class LinuxMenu : public Widget {
	public:
		LinuxMenu(const string& wtype);
		void make_widget() override;
		const string& get_name() override;
	private:
		string _widget_type;
	};
	//-----------------------------------
	
	class WindowsButton : public Widget {
	public:
		WindowsButton(const string& wtype);
		void make_widget() override;
		const string& get_name() override;
	private:
		string _widget_type;
	};

	class WindowsMenu : public Widget {
	public:
		WindowsMenu(const string& wtype);
		void make_widget() override;
		const string& get_name() override;
	private:
		string _widget_type;
	};
	//-----------------------------------

	//-----------------------------------
	// Конкретные фабрики, реализующие интерфейс WidgetsFactory
	class LinuxFactory : public WidgetsFactory {
	public:
		LinuxFactory(const string& fname);
		unique_ptr<Widget> create_button();
		unique_ptr<Widget> create_menu();
		const string& get_name() override;
	private:
		string _name_factory;
	};

	class WindowsFactory : public WidgetsFactory {
	public:
		WindowsFactory(const string& fname);
		unique_ptr<Widget> create_button();
		unique_ptr<Widget> create_menu();
		const string& get_name() override;
	private:
		string _name_factory;
	};
	//-----------------------------------

	//-----------------------------------
	// Клиентский класс для работы с фабриками
	class Client final {
	public:
		Client(unique_ptr<WidgetsFactory>&& fact);
		void show_result();
	private:
		unique_ptr<Widget> _button_widget;
		unique_ptr<Widget> _menu_widget;
	};
	//-----------------------------------
		
	//----------------------------------------------------------
	// Класс для теста
	//----------------------------------------------------------
	class AbstractFactoryTest {
	public:
		AbstractFactoryTest() { init(); }
		void show_result() {
			if (!_linux_factory) { init(); }

			cout << "Клиент создаёт " << _linux_factory->get_name() << '\n';
			_client = make_unique<Client>(std::move(_linux_factory));
			_client->show_result();
			_client.release();

			cout << "Клиент создаёт " << _windows_factory->get_name() << '\n';
			_client = make_unique<Client>(std::move(_windows_factory));
			_client->show_result();
			_client.release();
		}
	private:
		unique_ptr<LinuxFactory>   _linux_factory;
		unique_ptr<WindowsFactory> _windows_factory;
		unique_ptr<Client> _client;

		void init() {
			_linux_factory = make_unique<LinuxFactory>("Linux Фабрика");
			_windows_factory = make_unique<WindowsFactory>("Windows фабрика");
			_client = nullptr;
		}
	};
	//----------------------------------------------------------
	void test_abstract_factory();
}