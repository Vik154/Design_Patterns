/* Паттерн "Прототип" (Prototype) */
/* Источник - https://metanit.com/sharp/patterns/2.4.php */

//  Прототип —​ позволяет создавать новые объекты путем клонирования уже существующих.
//  По сути данный паттерн предлагает технику клонирования объектов

namespace Patterns.Creational;

// Концепция паттерна:
internal class PClient {
    void Operation() {
        Prototype prototype = new ConcretePrototype1(1);
        Prototype clone = prototype.Clone();
        prototype = new ConcretePrototype2(2);
        clone = prototype.Clone();
    }
}

// Определяет интерфейс для клонирования самого себя, который, представляет метод Clone()
internal abstract class Prototype {
    public int Id { get; private set; }
    public Prototype(int id) { Id = id; }
    public abstract Prototype Clone();
}

internal class ConcretePrototype1 : Prototype {
    public ConcretePrototype1(int id) : base(id) { }
    public override Prototype Clone() {
        return new ConcretePrototype1(Id);
    }
}

internal class ConcretePrototype2 : Prototype {
    public ConcretePrototype2(int id) : base(id) { }
    public override Prototype Clone() {
        return new ConcretePrototype2(Id);
    }
}

//----------------------------------------------------
// Реализация паттерна "Прототип"
//----------------------------------------------------
internal interface IStudentPrototype {
    IStudentPrototype Clone();
    int Id { get; }
    int Age { get; }
    string? Name { get; }
}

internal class Student : IStudentPrototype {
    
    public Student(string? name, int age, int id) {
        Name = name;
        Age = age;
        Id = id;
    }
    public string? Name { get; private set; }
    public int Age { get; private set; }
    public int Id { get; private set; }

    public IStudentPrototype Clone() {
        return new Student(Name, Age, Id);
    }
}

internal static class TestPrototype {
    static TestPrototype() {
        students = new List<IStudentPrototype>() {
            new Student("Jack", 22, 1),
            new Student("Pol", 21, 2),
            new Student("Aerith", 22, 3),
            new Student("Abygail", 22, 4)
        };
    }
    static private List<IStudentPrototype> students;

    static public void show_res() {
        IStudentPrototype student1 = students[1].Clone();
        IStudentPrototype student2 = students[2].Clone();
        Console.WriteLine($"Name: {student1.Name}; id: {student1.Id}");
        Console.WriteLine($"Name: {students[1].Name}; id: {students[1].Id}");
        Console.WriteLine($"Name: {student2.Name}; id: {student2.Id}");
        Console.WriteLine($"Name: {students[2].Name}; id: {students[2].Id}");
    }
}
//----------------------------------------------------