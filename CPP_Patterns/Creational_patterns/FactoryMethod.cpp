#include "FactoryMethod.h"

namespace Creational {

	// ����������� ������������ ������ "�������"
	ShapeProduct::ShapeProduct(const string& name) : figure_name(name) {}

	// ����������� ������������ ������ �� ShapeProduct
	Circle::Circle(const string& name) : ShapeProduct(name) { 
		cout << "������ ����\n"; 
	}
	// ����������� ������������ ������ �� ShapeProduct
	Rectangle::Rectangle(const string& name) : ShapeProduct(name) { 
		cout << "������ �������������\n";
	}
	// ����������� ������������ ������ �� ShapeProduct
	Ellipse::Ellipse(const string& name) : ShapeProduct(name) {
		cout << "������ ������\n";
	}
	
	// ����������� ����� "���������"
	ShapeCreator::ShapeCreator(const string& name) : creator_name(name) {}

	// ����������� ������������ ������
	CircleCreator::CircleCreator(const string& name) : ShapeCreator(name) {}

	// ������ ��������� �� ������� �����
	unique_ptr<ShapeProduct> CircleCreator::create_product() {
		cout << "����� ����\n";
		return unique_ptr<ShapeProduct>();
	}
	// ����������� ������������ ������
	RectangleCreator::RectangleCreator(const string& name) : ShapeCreator(name) {}

	unique_ptr<ShapeProduct> RectangleCreator::create_product() {
		cout << "����� �������������\n";
		return unique_ptr<ShapeProduct>();
	}

	// ����������� ������������ ������
	EllipseCreator::EllipseCreator(const string& name) : ShapeCreator(name) {}

	unique_ptr<ShapeProduct> EllipseCreator::create_product() {
		cout << "����� ������\n";
		return unique_ptr<ShapeProduct>();
	}

	// ����������� �������������� ������
	FactoryMethod::FactoryMethod() {
		_shape_creator.reserve(3);
		_shape_creator.push_back(make_unique<EllipseCreator>("���������� ��������"));
		_shape_creator.push_back(make_unique<RectangleCreator>("���������� ���������������"));
		_shape_creator.push_back(make_unique<CircleCreator>("���������� ������"));
	}

	void FactoryMethod::show_name_creator() {
		for (int i = 0; i < 3; ++i) {
			cout << _shape_creator[i]->get_name() << " �������: ";
			_shape_creator[i]->create_product();
		}
	}
}