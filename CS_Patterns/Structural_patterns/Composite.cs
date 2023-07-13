/* Компоновщик (Composite) */
/* Источник - https://metanit.com/sharp/patterns/4.4.php и др. */

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

// Концепция паттерна "Компоновщик"
namespace Сoncept {

    // Component: определяет интерфейс для всех компонентов в древовидной структуре
    abstract class Component {
        protected string name;

        public Component(string name) {
            this.name = name;
        }
        public abstract void Display();
        public abstract void Add(Component c);
        public abstract void Remove(Component c);
    }

    // Composite: представляет компонент, который может содержать другие компоненты и
    // реализует механизм для их добавления и удаления
    class Composite : Component {
        List<Component> children = new List<Component>();

        public Composite(string name) : base(name) { }

        public override void Add(Component component) {
            children.Add(component);
        }
        public override void Remove(Component component) {
            children.Remove(component);
        }
        public override void Display() {
            Console.WriteLine(name);

            foreach (Component component in children) {
                component.Display();
            }
        }
    }

    // Leaf: представляет отдельный компонент, который не может содержать другие компоненты
    class Leaf : Component {
        public Leaf(string name) : base(name) { }

        public override void Display() {
            Console.WriteLine(name);
        }
        public override void Add(Component component) {
            throw new NotImplementedException();
        }
        public override void Remove(Component component) {
            throw new NotImplementedException();
        }
    }

    /*
    class Client {
        public void Main() {
            Component root = new Composite("Root");
            Component leaf = new Leaf("Leaf");
            Composite subtree = new Composite("Subtree");
            root.Add(leaf);
            root.Add(subtree);
            root.Display();
        }
    }
    */
}

//--------------------------------------------------------------
// Реализация паттерна "Компоновщик"
//--------------------------------------------------------------
namespace Patterns.Structural {

    internal abstract class Component {
        protected string name;
        public Component(string name_) => name = name_;
        public virtual void Add(Component component) { }
        public virtual void Remove(Component component) { }
        public virtual void Print() {
            Console.WriteLine(name);
        }
    }

    internal class Directory : Component {
        private List<Component> components = new List<Component>();

        public Directory(string name) : base(name) { }

        public override void Add(Component component) {
            components.Add(component);
        }
        public override void Remove(Component component) {
            components.Remove(component);
        }
        public override void Print() {
            Console.WriteLine("Узел " + name);
            Console.WriteLine("Подузлы:");
            for (int i = 0; i < components.Count; i++) {
                components[i].Print();
            }
        }
    }

    internal class File : Component {
        public File(string name) : base(name) { }
    }

    internal static class TestComposite {

        public static void ShowResult() {
            Component fileSystem = new Directory("Файловая система");
            Component diskC = new Directory("Диск С");      
            Component pngFile = new File("12345.png");
            Component docxFile = new File("Document.docx");
            diskC.Add(pngFile);
            diskC.Add(docxFile);
            fileSystem.Add(diskC);
            fileSystem.Print();
            Console.WriteLine();
            diskC.Remove(pngFile);
            Component docsFolder = new Directory("Мои Документы");
            Component txtFile = new File("readme.txt");
            Component csFile = new File("Program.cs");
            docsFolder.Add(txtFile);
            docsFolder.Add(csFile);
            diskC.Add(docsFolder);
            fileSystem.Print();
        }
    }
}