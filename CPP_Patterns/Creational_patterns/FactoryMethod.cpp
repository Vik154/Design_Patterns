#include "FactoryMethod.h"

namespace Creational {

	// Конструктор абстрактного класса "Продукт"
	ShapeProduct::ShapeProduct(const string& name) : figure_name(name) {}

	// Конструктор производного класса от ShapeProduct
	Circle::Circle(const string& name) : ShapeProduct(name) { 
		cout << "Рисует круг\n"; 
	}
	// Конструктор производного класса от ShapeProduct
	Rectangle::Rectangle(const string& name) : ShapeProduct(name) { 
		cout << "Рисует прямоугольник\n";
	}
	// Конструктор производного класса от ShapeProduct
	Ellipse::Ellipse(const string& name) : ShapeProduct(name) {
		cout << "Рисует эллипс\n";
	}
	
	// Абстрактный класс "Создатель"
	ShapeCreator::ShapeCreator(const string& name) : creator_name(name) {}

	// Конструктор производного класса
	CircleCreator::CircleCreator(const string& name) : ShapeCreator(name) {}

	// Логика указателя на базовый класс
	unique_ptr<ShapeProduct> CircleCreator::create_product() {
		cout << "Рисую круг\n";
		return unique_ptr<ShapeProduct>();
	}
	// Конструктор производного класса
	RectangleCreator::RectangleCreator(const string& name) : ShapeCreator(name) {}

	unique_ptr<ShapeProduct> RectangleCreator::create_product() {
		cout << "Рисую прямоугольник\n";
		return unique_ptr<ShapeProduct>();
	}

	// Конструктор производного класса
	EllipseCreator::EllipseCreator(const string& name) : ShapeCreator(name) {}

	unique_ptr<ShapeProduct> EllipseCreator::create_product() {
		cout << "Рисую эллипс\n";
		return unique_ptr<ShapeProduct>();
	}

	// Конструктор обслуживающего класса
	FactoryMethod::FactoryMethod() {
		_shape_creator.reserve(3);
		_shape_creator.push_back(make_unique<EllipseCreator>("Рисователь эллипсов"));
		_shape_creator.push_back(make_unique<RectangleCreator>("Рисователь прямоугольников"));
		_shape_creator.push_back(make_unique<CircleCreator>("Рисователь кругов"));
	}

	void FactoryMethod::show_name_creator() {
		for (int i = 0; i < 3; ++i) {
			cout << _shape_creator[i]->get_name() << " говорит: ";
			_shape_creator[i]->create_product();
		}
	}
}