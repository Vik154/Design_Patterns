/* Паттерн Интерпретатор (Interpreter) */
/* Источник - https://metanit.com/sharp/patterns/3.8.php и др. */

/* Паттерн Интерпретатор (Interpreter) определяет представление грамматики для заданного
 * языка и интерпретатор предложений этого языка. Как правило, данный шаблон проектирования
 * применяется для часто повторяющихся операций.
 */

// Концепция паттерна "Интерпретатор"
namespace Сoncept {

    /* Client: строит предложения языка с данной грамматикой в виде абстрактного 
     * синтаксического дерева, узлами которого являются объекты TerminalExpression и NonterminalExpression
    
    class Client {
        void Main() {
            Context context = new Context();
            var expression = new NonterminalExpression();
            expression.Interpret(context);
        }
    }
    */

    // Context: содержит общую для интерпретатора информацию. Может использоваться объектами
    // терминальных и нетерминальных выражений для сохранения состояния операций и последующего
    // доступа к сохраненному состоянию
    class Context { }

    // AbstractExpression: определяет интерфейс выражения, объявляет метод Interpret()
    abstract class AbstractExpression {
        public abstract void Interpret(Context context);
    }

    // TerminalExpression: терминальное выражение, реализует метод Interpret() для терминальных
    // символов грамматики. Для каждого символа грамматики создается свой объект TerminalExpression
    class TerminalExpression : AbstractExpression {
        public override void Interpret(Context context) { }
    }

    // NonterminalExpression: нетерминальное выражение, представляет правило грамматики.
    // Для каждого отдельного правила грамматики создается свой объект NonterminalExpression.
    class NonterminalExpression : AbstractExpression {
        AbstractExpression expression1 = new TerminalExpression();
        AbstractExpression expression2 = new TerminalExpression();
        public override void Interpret(Context context) { }
    }
}

//--------------------------------------------------------------
// Реализация паттерна "Интерпретатор"
//--------------------------------------------------------------
namespace Patterns.Behavioral {

    /* Например, надо разработать программу для вычислений простейших операций сложения 
     * и вычитания с помощью переменных: x + y - z. Для этого можно определить следующую грамматику:

    IExpression ::= NumberExpression | Constant | AddExpression | SubtractExpression
    AddExpression ::= IExpression + IExpression
    SubtractExpression ::= IExpression - IExpression
    NumberExpression ::= [A-Z,a-z]+
    Constant ::= [1-9]+
     */

    internal class IContext {
        Dictionary<string, int> variables;
        public IContext() {
            variables = new Dictionary<string, int>();
        }
        // получаем значение переменной по ее имени
        public int GetVariable(string name) {
            return variables[name];
        }

        public void SetVariable(string name, int value) {
            if (variables.ContainsKey(name))
                variables[name] = value;
            else
                variables.Add(name, value);
        }
    }

    // интерфейс интерпретатора
    internal interface IExpression {
        int Interpret(IContext context);
    }

    // терминальное выражение
    internal class NumberExpression : IExpression {
        string name; // имя переменной
        public NumberExpression(string variableName) {
            name = variableName;
        }
        public int Interpret(IContext context) {
            return context.GetVariable(name);
        }
    }

    // нетерминальное выражение для сложения
    internal class AddExpression : IExpression {
        IExpression leftExpression;
        IExpression rightExpression;

        public AddExpression(IExpression left, IExpression right) {
            leftExpression = left;
            rightExpression = right;
        }

        public int Interpret(IContext context) {
            return leftExpression.Interpret(context) + rightExpression.Interpret(context);
        }
    }

    // нетерминальное выражение для вычитания
    internal class SubtractExpression : IExpression {
        IExpression leftExpression;
        IExpression rightExpression;

        public SubtractExpression(IExpression left, IExpression right) {
            leftExpression = left;
            rightExpression = right;
        }

        public int Interpret(IContext context) {
            return leftExpression.Interpret(context) - rightExpression.Interpret(context);
        }
    }

    internal static class TestInterpreter {
        
        public static void ShowResult() {
            IContext context = new IContext();
            // определяем набор переменных
            int x = 5;
            int y = 8;
            int z = 2;

            // добавляем переменные в контекст
            context.SetVariable("x", x);
            context.SetVariable("y", y);
            context.SetVariable("z", z);
            // создаем объект для вычисления выражения x + y - z
            IExpression expression = new SubtractExpression(
                new AddExpression(
                    new NumberExpression("x"), new NumberExpression("y")
                ),
                new NumberExpression("z")
            );

            int result = expression.Interpret(context);
            Console.WriteLine("результат: {0}", result);
        }
    }
}