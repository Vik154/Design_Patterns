/* Паттерн Итератор (Iterator) */
/* Источник - https://metanit.com/sharp/patterns/3.5.php и др. */

/* Паттерн Итератор (Iterator) предоставляет абстрактный интерфейс для последовательного
 * доступа ко всем элементам составного объекта без раскрытия его внутренней структуры.
 - Когда использовать итераторы?
 * Когда необходимо осуществить обход объекта без раскрытия его внутренней структуры
 * Когда имеется набор составных объектов, и надо обеспечить единый интерфейс для их перебора
 * Когда необходимо предоставить несколько альтернативных вариантов перебора одного и того же объекта
 */

// Концепция паттерна "Итератор"
using System.Collections;

namespace Сonception {

    // Client: использует объект Aggregate и итератор для его обхода
    /*
    class Client {
        public void Main() {
            Aggregate a = new ConcreteAggregate();
            Iterator i = a.CreateIterator();

            object item = i.First();
            while (!i.IsDone()) {
                item = i.Next();
            }
        }
    }
    */

    // Aggregate: определяет интерфейс для создания объекта-итератора
    abstract class Aggregate {
        public abstract Iterator CreateIterator();
        public abstract int Count { get; protected set; }
        public abstract object this[int index] { get; set; }
    }

    // Конкретная реализация Aggregate. Хранит элементы, которые надо будет перебирать
    class ConcreteAggregate : Aggregate {
        private readonly ArrayList _items = new ArrayList();

        public override Iterator CreateIterator() {
            return new ConcreteIterator(this);
        }
        public override int Count {
            get { return _items.Count; }
            protected set { }
        }
        public override object this[int index] {
            get { return _items[index]; }
            set { _items.Insert(index, value); }
        }
    }

    // Iterator: определяет интерфейс для обхода составных объектов
    abstract class Iterator {
        public abstract object First();
        public abstract object Next();
        public abstract bool IsDone();
        public abstract object CurrentItem();
    }

    // Конкретная реализация итератора для обхода объекта Aggregate.
    // Для фиксации индекса текущего перебираемого элемента использует
    // целочисленную переменную _current
    class ConcreteIterator : Iterator {
        private readonly Aggregate _aggregate;
        private int _current;

        public ConcreteIterator(Aggregate aggregate) {
            this._aggregate = aggregate;
        }
        public override object First() {
            return _aggregate[0];
        }
        public override object Next() {
            object ret = null;
            _current++;
            if (_current < _aggregate.Count) {
                ret = _aggregate[_current];
            }
            return ret;
        }
        public override object CurrentItem() {
            return _aggregate[_current];
        }
        public override bool IsDone() {
            return _current >= _aggregate.Count;
        }
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Итератор"
//--------------------------------------------------------------
namespace Patterns.Behavioral {

    internal class Book {
        public string Name { get; set; }
    }

    internal interface IBookIterator {
        bool HasNext();
        Book Next();
    }

    internal interface IBookNumerable {
        IBookIterator CreateNumerator();
        int Count { get; }
        Book this[int index] { get; }
    }

    internal class Reader {
        public void SeeBooks(Library library) {
            IBookIterator iterator = library.CreateNumerator();
            while (iterator.HasNext()) {
                Book book = iterator.Next();
                Console.WriteLine(book.Name);
            }
        }
    }

    internal class Library : IBookNumerable {
        private Book[] books;
        public Library() {
            books = new Book[] {
                new Book {Name="Война и мир"},
                new Book {Name="Отцы и дети"},
                new Book {Name="Вишневый сад"}
            };
        }
        public int Count {
            get { return books.Length; }
        }
        public Book this[int index] {
            get { return books[index]; }
        }
        public IBookIterator CreateNumerator() {
            return new LibraryNumerator(this);
        }
    }

    internal class LibraryNumerator : IBookIterator {
        IBookNumerable aggregate;
        int index = 0;
        public LibraryNumerator(IBookNumerable a) {
            aggregate = a;
        }
        public bool HasNext() {
            return index < aggregate.Count;
        }
        public Book Next() {
            return aggregate[index++];
        }
    }

    internal static class TestIterator {
        public static void ShowResult() {
            Library library = new Library();
            Reader reader = new Reader();
            reader.SeeBooks(library);
        }
    }
}