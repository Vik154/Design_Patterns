/// <summary> Фабричный метод (Factory Method) </summary> ///
/* Источник - как обычно, сломай глаз, придумай сам */

#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace Creational {

	using std::unique_ptr;
	using std::string;
	using std::vector;
	using std::make_unique;
	using std::cout;
	using std::cin;

	// Абстрактный класс "Продукт"
	class ShapeProduct abstract {
	public:
		ShapeProduct(const string& name);
		virtual ~ShapeProduct() = default;
	protected:
		std::string figure_name;
	};

	class Circle : public ShapeProduct {
	public:
		Circle(const string& name);
	};

	class Rectangle : public ShapeProduct {
	public:
		Rectangle(const string& name);
	};

	class Ellipse : public ShapeProduct {
	public:
		Ellipse(const string& name);
	};

	// Абстрактный класс "Создатель"
	class ShapeCreator {
	public:
		ShapeCreator(const string& name);
		virtual unique_ptr<ShapeProduct> create_product() = 0;
		virtual ~ShapeCreator() = default;
		string get_name() { return creator_name; }
	protected:
		string creator_name;
	};

	class CircleCreator : public ShapeCreator {
	public:
		CircleCreator(const string& name);
		unique_ptr<ShapeProduct> create_product() override;
	};

	class RectangleCreator : public ShapeCreator {
	public:
		RectangleCreator(const string& name);
		unique_ptr<ShapeProduct> create_product() override;
	};

	class EllipseCreator : public ShapeCreator {
	public:
		EllipseCreator(const string& name);
		unique_ptr<ShapeProduct> create_product() override;
	};

	// Просто обслуживающий класс для main
	class FactoryMethod final {
	public:
		FactoryMethod();
		void show_name_creator();
	private:
		vector<unique_ptr<ShapeCreator>> _shape_creator;
	};
}