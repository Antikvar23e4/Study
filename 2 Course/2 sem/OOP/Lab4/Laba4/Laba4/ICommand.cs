using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Laba4
{
    public class RelayCommand : ICommand // создание логики обработки действий пользователя
    {
        private readonly Action<object> _execute; // для выполнения команды
        private readonly Func<object, bool> _canExecute; // для проверки, может ли команда быть выполнена

        public RelayCommand(Action<object> execute, Func<object, bool> canExecute = null)
        {
            _execute = execute ?? throw new ArgumentNullException(nameof(execute));
            _canExecute = canExecute;
        }

        public event EventHandler CanExecuteChanged // генерируется, когда изменяется состояние, влияющее на возможность выполнения команды
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter)
        {
            return _canExecute == null || _canExecute(parameter);
        }

        public void Execute(object parameter)
        {
            _execute(parameter);
        }
    }


}
