using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace lab11.Commands
{
    public class RelayCommand : ICommand //реализация команд
    {
        private readonly Action _execute;
        private readonly Func<bool> _canExecute;

        public RelayCommand(Action execute, Func<bool> canExecute = null)
        {
            _execute = execute ?? throw new ArgumentNullException(nameof(execute));
            _canExecute = canExecute;
        }

        public bool CanExecute(object parameter) //может ли команда выполняться 
        {
            return _canExecute == null || _canExecute();
        }

        public void Execute(object parameter) //выполняет логику команды
        {
            _execute();
        }

        public event EventHandler CanExecuteChanged //событие, вызываемое при изменении условий
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }
    }
}
