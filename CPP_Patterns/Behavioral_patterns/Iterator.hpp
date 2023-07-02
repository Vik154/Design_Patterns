/* Паттерн Итератор (Iterator) */
// 1 - https://www.bestprog.net/ru/2021/05/21/patterns-the-iterator-pattern-features-of-implementation-in-c-ru/
/* Итератор – это поведенческий паттерн, позволяющий последовательно обходить сложную коллекцию,
 * без раскрытия деталей её реализации. Благодаря Итератору, клиент может обходить разные 
 * коллекции одним и тем же способом, используя единый интерфейс итераторов.
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>

// Концепция паттерна "Итератор"
namespace Сonception {

	// Абстрактный класс агрегата (интерфейс) - определяет интерфейс контейнера.
	// Содержит чисто виртуальный метод CreateIterator() для возврата итератора,
	// которым служит абстрактный класс Iterator.
    template <typename T> class Iterator;
    
    template <typename T>
	class Aggregate	{
	public:
		// Метод, который будет возвращать итератор для некоторого списка
		virtual Iterator<T>* CreateIterator() const = 0;
	};

	// Абстрактный класс итератора
	template <typename T>
	class Iterator {
	public:
		// Переход (перевод курсора) в начало списка
		virtual void First() = 0;

		// Переход (перевод курсора) на следующий элемент списка
		virtual void Next() = 0;

		// Проверка, достигнут ли конец списка,
		// текущая позиция курсора находится за последним элементом списка
		virtual bool IsDone() const = 0;

		// Получить элемент списка по текущей позиции курсора
		virtual T CurrentItem() const = 0;
	};

	// Конкретный агрегат - реализует интерфейс Aggregate
	template <class T>
	class ConcreteAggregate : public Aggregate<T> {
	private:
		// данные агрегата (список, массив, ...)
	public:
		Iterator<T>* CreateIterator() const { /****/ };
		// Другие методы класса ConcreteAggregate
	};
}

//--------------------------------------------------------------
// Реализация паттерна "Итератор"
//--------------------------------------------------------------
namespace Behavioral {

    using std::cout;
    using std::endl;
    using std::string;
    using std::bad_alloc;

    // Паттерн Iterator для одного агрегата и одного итератора
    template <typename T>
    class Aggregate;

    // Класс итератора
    template <typename T>
    class Iterator {
    private:
        const Aggregate<T>* aggregate;
        long current;
    public:
        // Конструктор, получающий агрегированный объект
        Iterator(const Aggregate<T>* _aggregate) :
            aggregate(_aggregate), current(0)
        { }

        // Переход (перевод курсора) в начало списка
        virtual void First() {
            current = 0;
        }
        // Переход (перевод курсора) на следующий элемент списка
        virtual void Next() {
            current++;
        }
        // Проверка, достигнут ли конец списка.
        // Текущая позиция курсора находится за последним элементом списка
        virtual bool IsDone() const {
            return current >= aggregate->Count();
        }
        // Получить элемент списка по текущей позиции курсора
        virtual T CurrentItem() const {
            if (!IsDone())
                return aggregate->GetItem(current);
            else {
                // Здесь ошибка, можно сгенерировать исключение или выполнить другие действия
                cout << "Error." << endl;
                return 0;
            }
        }
    };

    // Класс агрегата
    template <typename T>
    class Aggregate {
    private:
        // данные агрегата (список, массив, ...)
        T* data;
        long count;
    public:
        // Конструктор
        Aggregate(long _count) {
            if (_count < 0) {
                count = 0;
                data = nullptr;
                return;
            }

            try {
                data = new T[_count];
                count = _count;

                for (int i = 0; i < count; i++)
                    data[i] = (T)0;
            }
            catch (bad_alloc e) {
                cout << e.what() << endl;
                count = 0;
                data = nullptr;
            }
        }

        // Конструктор копирования
        Aggregate(const Aggregate& obj) {
            // скопировать данные из obj в текущий экземпляр
            count = obj.count;

            // выделить память для массива в целом
            try {
                data = new T[count];
                for (int i = 0; i < count; i++)
                    data[i] = obj.data[i];
            }
            catch (bad_alloc e) {
                cout << e.what() << endl;
                count = 0;
            }
        }

        // Метод, возвращающий итератор
        Iterator<T>* CreateIterator() const {
            return new Iterator<T>(this);
        }

        // Другие методы класса ConcreteAggregate
        long Count() const {
            return count;
        }

        T GetItem(long index) const {
            if ((index >= 0) && (index < count))
                return data[index];
            return data[0];
        }

        // Метод, добавляющий в конец списка элемент
        void Append(T value) {
            T* data2 = data;
            data = new T[count + 1];

            for (int i = 0; i < count; i++)
                data[i] = data2[i];

            data[count++] = value;
            delete[] data2;
        }

        // Удаление элемента из списка,
        // index = 0, 1, ..., count-1
        void Remove(long index) {
            if ((index >= 0) && (index < count)) {
                // Удалить элемент из списка
                T* data2 = data;
                data = new T[count - 1];

                for (int i = 0; i < index; i++)
                    data[i] = data2[i];

                for (int i = index + 1; i < count; i++)
                    data[i - 1] = data2[i];

                count--;
                delete[] data2;
            }
        }

        // Деструктор
        ~Aggregate() {
            if (count > 0)
                delete[] data;
        }

        // Вывод содержимого агрегата
        void Print(string text) {
            cout << text << endl;
            for (int i = 0; i < count; i++)
                cout << data[i] << " ";
            cout << endl;
        }
    };

    // Класс, реализующий внутренний итератор.
    // Этот класс есть базовым для подклассов, которые будут реализовывать
    // конкретные операции.
    template <class T>
    class AggregateProcess {
    private:
        // Итератор всередине класса
        Iterator<T> it;
    public:
        // Конструктор - создает итератор в классе
        AggregateProcess(Aggregate<T>* ag) : it(ag)
        { }

        // Метод, который обрабатывает все элементы
        bool ProcessItems() {
            bool res = false;

            // 1. Перейти на следующий элемент в контейнере
            it.First();

            // 2. Цикл перебора всех элементов
            while (!it.IsDone()) {
                // 2.1. Обработать текущий элемент, на который указывает итератор it
                res = ProcessItem(it.CurrentItem());

                // 2.2. Если элемент не обработан, то выйти из цикла
                if (!res) break;

                // 2.3. Перейти к следующему элементу
                it.Next();
            }
            // 3. Вернуть результат обработки
            return res;
        }
    protected:
        // Виртуальный метод, обрабатывающий один элемент.
        // В подклассах этот метод должен быть заменен
        // конкретной реализацией, которая осуществляет специфическую обработку.
        virtual bool ProcessItem(const T&) = 0;
    };

    // Подкласс, определяющий операцию обработки отдельного элемента контейнера.
    // Этот подкласс наследует класс AggregateProcess, для того
    // чтобы переопределить операцию ProcessItem ().
    template <class T>
    class MultItemBy2 : public AggregateProcess<T> {
    public:
        // Конструктор
        MultItemBy2(Aggregate<T>* ag) : AggregateProcess<T>(ag) { }
    protected:
        // Метод обработки одного элемента контейнера
        bool ProcessItem(const T& item) {
            // Вывести элемент, умноженный на 2
            cout << item * 2 << " ";

            // Обработка прошла успешно
            return true;
        }
    };

    void test_iterator() {
        // 1. Создать агрегат
        Aggregate<double> ag(0);
        ag.Append(2.55);
        ag.Append(3.8);
        ag.Append(-1.557);
        ag.Append(7.32);

        // 2. Создать внутренний итератор, который будет выводить на экран
        // каждый элемент контейнера умноженный на 2
        MultItemBy2<double> it(&ag);
        bool res = it.ProcessItems();
        if (res == true)
            cout << "\nOk!\n";
        else
            cout << "\nError\n";
    }
}