/* Паттерн Заместитель (Proxy) */
/* Источник - https://metanit.com/sharp/patterns/4.5.php и др. */
/* https://rutube.ru/video/88f197210f9f1552f0fe3fad173070f7/ */

/* Паттерн Заместитель (Proxy) предоставляет объект-заместитель, который управляет доступом 
 * к другому объекту. То есть создается объект-суррогат, который может выступать 
 * в роли другого объекта и замещать его.

 - Когда использовать прокси?
 - Когда надо осуществлять взаимодействие по сети, а объект-проси должен имитировать поведения
 - объекта в другом адресном пространстве. Использование прокси позволяет снизить накладные
 - издержки при передачи данных через сеть. Подобная ситуация еще называется удалённый 
 - заместитель (remote proxies)

 - Когда нужно управлять доступом к ресурсу, создание которого требует больших затрат. 
 - Реальный объект создается только тогда, когда он действительно может понадобится, а до этого
 - все запросы к нему обрабатывает прокси-объект. Подобная ситуация еще называется виртуальный
 - заместитель (virtual proxies)

 - Когда необходимо разграничить доступ к вызываемому объекту в зависимости от прав вызывающего
 - объекта. Подобная ситуация еще называется защищающий заместитель (protection proxies)

 - Когда нужно вести подсчет ссылок на объект или обеспечить потокобезопасную работу с реальным
 - объектом. Подобная ситуация называется "умные ссылки" (smart reference)
 */

// Концепция паттерна "Заместитель"
namespace Сonception {

    // Subject: определяет общий интерфейс для Proxy и RealSubject.
    // Поэтому Proxy может использоваться вместо RealSubject
    abstract class Subject {
        public abstract void Request();
    }

    // RealSubject: представляет реальный объект, для которого создается прокси
    class RealSubject : Subject {
        public override void Request() { }
    }

    // Proxy: заместитель реального объекта. Хранит ссылку на реальный объект, контролирует
    // к нему доступ, может управлять его созданием и удалением.
    // При необходимости Proxy переадресует запросы объекту RealSubject
    class Proxy : Subject {
        RealSubject realSubject;
        public override void Request() {
            if (realSubject == null)
                realSubject = new RealSubject();
            realSubject.Request();
        }
    }

    // Client: использует объект Proxy для доступа к объекту RealSubject
    /* class Client {
         void Main() {
            Subject subject = new Proxy();
            subject.Request();
       }
    }*/
}

//--------------------------------------------------------------
// Реализация паттерна "Заместитель"
//--------------------------------------------------------------
namespace Patterns.Structural {

    internal interface ISite {
        string GetPage(int number);
    }

    internal class Site : ISite {
        public string GetPage(int number) => "Страница номер " + number;
    }

    internal class SiteProxy : ISite {
        private ISite site;
        private Dictionary<int, string> cache;
        public SiteProxy(ISite site_) {
            site = site_;
            cache = new Dictionary<int, string>();
        }
        public string GetPage(int number) {
            string page;
            if (cache.ContainsKey(number)) {
                page = cache[number];
                page = "из кеша " + page;
            }
            else {
                page = site.GetPage(number);
                cache.Add(number, page);
            }
            return page;
        }
    }

    internal static class TestProxy {
        public static void ShowResult() {
            ISite site = new SiteProxy(new Site());
            Console.WriteLine(site.GetPage(1));
            Console.WriteLine(site.GetPage(2));
            Console.WriteLine(site.GetPage(3));
            Console.WriteLine(site.GetPage(2));
        }
    }
}