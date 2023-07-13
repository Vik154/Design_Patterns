/* Паттерн "Одиночка" (Singleton) */
/* Источник - https://metanit.com/sharp/patterns/2.3.php */
/* Источник - https://professorweb.ru/my/it/blog/net/singleton_csharp.php и др. */

namespace Patterns.Creational;

// Одиночка (Singleton, Синглтон) - порождающий паттерн, который гарантирует, что для определенного
// класса будет создан только один объект, а также предоставит к этому объекту точку доступа.

// Когда надо использовать Синглтон?
// Когда необходимо, чтобы для класса существовал только один экземпляр
// Синглтон позволяет создать объект только при его необходимости.
// Если объект не нужен, то он не будет создан. В этом отличие синглтона от глобальных переменных.

// Классическая однопоточная реализация
internal sealed class SingletonTemplate {
    private static SingletonTemplate? instance;

    private SingletonTemplate() { }

    public static SingletonTemplate getInstance() {
        if (instance == null)
            instance = new SingletonTemplate();
        return instance;
    }
}

// Классическая потокобезопасная реализация
public sealed class Singleton {
    private Singleton() { }

    private static Singleton? source = null;
    private static readonly object threadlock = new object();

    public static Singleton Source {
        get {
            lock (threadlock) {
                if (source == null)
                    source = new Singleton();
                return source;
            }
        }
    }
}

//-----------------------------------------------
// Реализия паттерна
//-----------------------------------------------
internal sealed class Logger {

    private Logger(string name) {
        Console.WriteLine($"Ctor Logger: {DateTime.Now}");
        Console.WriteLine($"Thread id {Thread.CurrentThread.ManagedThreadId}");
        Name = name;
    }
    public static Logger Init {
        get {
            lock(ThreadLock)
                init ??= new Logger(Thread.CurrentThread.ManagedThreadId.ToString());
            return init;
        }
    }
    public string Name { get; set; }
    private static Logger? init = null;
    private static readonly object ThreadLock = new object();

    public void Log(in string message) { Console.WriteLine(message); }
}
//-----------------------------------------------

internal static class TestSingleton {
    
    private static void work() {
        Logger logger = Logger.Init;
        Console.Write($"Name ex: {logger.Name} : ");
        logger.Log($"log number: {Thread.CurrentThread.ManagedThreadId}");
    }

    public static void ShowResult() {
        Thread? thread = null;
        for (int i = 0; i < Environment.ProcessorCount; ++i) {
            thread = new Thread(work);
            thread.Start();
        }
        thread?.Join();
    }
}