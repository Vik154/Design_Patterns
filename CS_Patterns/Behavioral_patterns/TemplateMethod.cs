/* Паттерн "Шаблонный метод" (Template Method) */
/* Источник - https://metanit.com/sharp/patterns/3.4.php и др. */

/* Шаблонный метод (Template Method) определяет общий алгоритм поведения подклассов,
 * позволяя им переопределить отдельные шаги этого алгоритма без изменения его структуры.
 - Когда использовать шаблонный метод?
 * Когда планируется, что в будущем подклассы должны будут переопределять различные 
 * этапы алгоритма без изменения его структуры
 * Когда в классах, реализующим схожий алгоритм, происходит дублирование кода. 
 * Вынесение общего кода в шаблонный метод уменьшит его дублирование в подклассах.
 */

// Концепция паттерна "Шаблонный метод"
namespace Сonception {

    /* AbstractClass: определяет шаблонный метод TemplateMethod(), который реализует алгоритм.
     * Алгоритм может состоять из последовательности вызовов других методов, часть из которых
     * может быть абстрактными и должны быть переопределены в классах-наследниках. 
     * При этом сам метод TemplateMethod(), представляющий структуру алгоритма, 
     * переопределяться не должен.
     */
    abstract class AbstractClass {
        public void TemplateMethod() {
            Operation1();
            Operation2();
        }
        public abstract void Operation1();
        public abstract void Operation2();
    }
    /* ConcreteClass: подкласс, который может переопределять различные методы родительского класса. */
    class ConcreteClass : AbstractClass {
        public override void Operation1() { }
        public override void Operation2() { }
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Шаблонный метод"
//--------------------------------------------------------------
namespace Patterns.Behavioral {

    internal abstract class HouseTemplate {
        // Шаблонный метод (определяет последовательность построения дома)
        public void BuildHouse() {
            BuildFoundation();      // Шаг 1
            BuildPillars();         // Шаг 2
            BuildWalls();           // Шаг 3
            BuildWindows();         // Шаг 4
            Console.WriteLine("Дом построен");
        }
        // Методы, которые будут реализованы подклассами
        protected abstract void BuildFoundation();
        protected abstract void BuildPillars();
        protected abstract void BuildWalls();
        protected abstract void BuildWindows();
    }

    internal class ConcreteHouse : HouseTemplate {
        protected override void BuildFoundation() {
            Console.WriteLine("Строим фундамент");
        }
        protected override void BuildPillars() {
            Console.WriteLine("Возводим столбы");
        }
        protected override void BuildWalls() {
            Console.WriteLine("Возводим бетонные стены");
        }
        protected override void BuildWindows() {
            Console.WriteLine("Ставим окна");
        }
    }

    internal class WoodenHouse : HouseTemplate {
        protected override void BuildFoundation() {
            Console.WriteLine("Заливаем фундамент");
        }
        protected override void BuildPillars() {
            Console.WriteLine("Строим колонны");
        }
        protected override void BuildWalls() {
            Console.WriteLine("Выкладываем стены");
        }
        protected override void BuildWindows() {
            Console.WriteLine("Устанавливаем окна");
        }
    }

    internal static class TestTemplate {
        public static void ShowResult() {
            Console.WriteLine("Строим конкретный дом");
            HouseTemplate houseTemplate = new ConcreteHouse();
            houseTemplate.BuildHouse();
            Console.WriteLine();
            Console.WriteLine("Строим деревянный дом\n");
            houseTemplate = new WoodenHouse();
            houseTemplate.BuildHouse();
        } 
    }

}
