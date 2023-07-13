/* Компоновщик (Composite) */
/* Источники - https://metanit.com/sharp/patterns/4.4.php и др. */
/* https://www.geeksforgeeks.org/composite-pattern-cpp/ */
/* https://radioprog.ru/post/1481 */

/* Паттерн Компоновщик (Composite) объединяет группы объектов в древовидную структуру по принципу
 * "часть-целое и позволяет клиенту одинаково работать как с отдельными объектами, так и с
 * группой объектов. Образно реализацию паттерна можно представить в виде меню, которое имеет
 * различные пункты. Эти пункты могут содержать подменю, в которых, в свою очередь, также имеются
 * пункты. То есть пункт меню служит с одной стороны частью меню, а с другой стороны еще одним
 * меню. В итоге мы однообразно можем работать как с пунктом меню, так и со всем меню в целом.

 - Когда использовать компоновщик?
 - Когда объекты должны быть реализованы в виде иерархической древовидной структуры
 - Когда клиенты единообразно должны управлять как целыми объектами, так и их составными частями.
 - То есть целое и его части должны реализовать один и тот же интерфейс
 */

#pragma once
#include <iostream>
#include <vector>

 // Концепция паттерна "Компоновщик"
namespace Сoncept {

	// Базовый класс Компонент объявляет общие операции для простых и сложных объектов структуры.
	class Component {
		/* @var Component */
	protected:
		Component* parent_;
		/**
		 * При необходимости базовый Компонент может объявить интерфейс для установки
		 * и получения родителя компонента в древовидной структуре. Он также может
		 * предоставить некоторую реализацию по умолчанию для этих методов.
		 */
	public:
		virtual ~Component() {}
		void SetParent(Component* parent) { parent_ = parent; }
		Component* GetParent() const { return parent_; }

		virtual void Add(Component* component) {}
		virtual void Remove(Component* component) {}
		virtual bool IsComposite() const { return false; }
		virtual std::string Operation() const = 0;
	};

	// Класс Лист представляет собой конечные объекты структуры. 
	// Лист не может иметь вложенных компонентов. Обычно объекты Листьев выполняют 
	// фактическую работу, тогда как объекты Контейнера лишь делегируют работу своим подкомпонентам.
	class Leaf : public Component {
	public:
		std::string Operation() const override { return "Leaf"; }
	};

	// Класс Контейнер содержит сложные компоненты, которые могут иметь вложенные компоненты.
	// Обычно объекты Контейнеры делегируют фактическую работу своим детям, а затем «суммируют» результат.
	class Composite : public Component {
	protected:
		std::list<Component*> children_;
	public:
		void Add(Component* component) override {
			children_.push_back(component);
			component->SetParent(this);
		}
		void Remove(Component* component) override {
			children_.remove(component);
			component->SetParent(nullptr);
		}
		bool IsComposite() const override {
			return true;
		}
		std::string Operation() const override {
			std::string result;
			for (const Component* c : children_) {
				if (c == children_.back()) {
					result += c->Operation();
				}
				else {
					result += c->Operation() + "+";
				}
			}
			return "Branch(" + result + ")";
		}
	};

	/* Клиентский код работает со всеми компонентами через базовый интерфейс. */
	void ClientCode(Component* component) {
		// ...
		std::cout << "RESULT: " << component->Operation();
		// ...
	}

	void ClientCode2(Component* component1, Component* component2) {
		// ...
		if (component1->IsComposite()) {
			component1->Add(component2);
		}
		std::cout << "RESULT: " << component1->Operation();
		// ...
	}
}

//--------------------------------------------------------------
// Реализация паттерна "Компоновщик"
//--------------------------------------------------------------
namespace Structural {

	class PageObject {
	public:
		virtual void Add(PageObject a) { }
		virtual void Remove() { } 
		virtual void Delete(PageObject a) { }
	};

	class Page : public PageObject {
	public:
		void Add(PageObject a)    { std::cout << "something is added to the page\n"; }
		void Remove()             { std::cout << "something is removed from the page\n"; }
		void Delete(PageObject a) { std::cout << "something is deleted from page \n"; }
	};

	class Copy : public PageObject {
		std::vector<PageObject> copyPages;
	public:
		void AddElement(PageObject a) { copyPages.push_back(a); }
		void Add(PageObject a)    { std::cout << "something is added to the copy\n"; }
		void Remove()	          { std::cout << "something is removed from the copy\n"; }
		void Delete(PageObject a) { std::cout << "something is deleted from the copy\n"; }
	};

	void test_composite() {
		Page a;
		Page b;
		Copy allcopy;
		allcopy.AddElement(a);
		allcopy.AddElement(b);
		allcopy.Add(a);
		a.Add(b);
		allcopy.Remove();
		b.Remove();
	}
}