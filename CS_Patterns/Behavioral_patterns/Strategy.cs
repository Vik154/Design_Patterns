/* Паттерн "Стратегия" (Strategy) */
/* Источник - https://metanit.com/sharp/patterns/3.1.php и др. */

namespace Patterns.Behavioral;

/* Паттерн Стратегия (Strategy) - определяет набор алгоритмов, 
- инкапсулирует каждый из них и обеспечивает их взаимозаменяемость. 
В зависимости от ситуации мы можем легко заменить один используемый алгоритм другим.
При этом замена алгоритма происходит независимо от объекта, который использует данный алгоритм.

Когда использовать стратегию?
- Когда есть несколько родственных классов, которые отличаются поведением. 
- Когда необходимо обеспечить выбор из нескольких вариантов алгоритмов,
которые можно легко менять в зависимости от условий
- Когда необходимо менять поведение объектов на стадии выполнения программы
- Когда класс, применяющий определенную функциональность, ничего не должен знать о ее реализации 
 */

// Концепция паттерна:
// Интерфейс IStrategy который определяет метод Algorithm()
// - это общий интерфейс для всех реализующих его алгоритмов.
// Вместо интерфейса можно было использовать абстрактный класс.
public interface IStrategy {
    void Algorithm();
}

// ConcreteStrategy1 и ConcreteStrategy, которые реализуют интерфейс IStrategy,
// предоставляя свою версию метода Algorithm(). Подобных классов-реализаций может быть множество.
public class ConcreteStrategy1 : IStrategy {
    public void Algorithm() { }
}

public class ConcreteStrategy2 : IStrategy {
    public void Algorithm() { }
}

// Класс Context хранит ссылку на объект IStrategy и связан
// с интерфейсом IStrategy отношением агрегации.
public class Context {
    public IStrategy ContextStrategy { get; set; }

    public Context(IStrategy _strategy) {
        ContextStrategy = _strategy;
    }
    public void ExecuteAlgorithm() {
        ContextStrategy.Algorithm();
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Стратегия"
//--------------------------------------------------------------

internal interface ISorting {
    void Sort(List<string> list);
}

internal class QuickSort : ISorting {
    public void Sort(List<string> list) {
        list.Sort();
        Console.WriteLine("QuickSort list");
    }
}

internal class MergeSort : ISorting {
    public void Sort(List<string> list) {
        list.Sort();
        Console.WriteLine("MergeSort list");
    }
}

internal class ContextSort {
    private List<string> list;
    private ISorting sort_strategy;

    public ContextSort(List<string> list, ISorting strategy) {
        this.list = list;
        sort_strategy = strategy;
        sort_strategy.Sort(list);
    }
    public void ShowResult() {
        foreach (var item in list) {
            Console.Write($"{item} <-> ");
        }
        Console.WriteLine('\n' + new string('-', 30));
    }
}

internal static class TestStrategy {

    public static void ShowResult() {
        contextSort = new ContextSort(lst1, quick);
        contextSort.ShowResult();
        contextSort = new ContextSort(lst2, merge);
        contextSort.ShowResult();
    }
    private static List<string> lst1 = new List<string>() { 
        "One", "Two", "Free", "Four"
    };
    private static List<string> lst2 = new List<string>() {
        "Cd", "Af", "Ab", "Fg", "Bb"
    };
    private static ContextSort contextSort;
    private static QuickSort quick = new QuickSort();
    private static MergeSort merge = new MergeSort();
}