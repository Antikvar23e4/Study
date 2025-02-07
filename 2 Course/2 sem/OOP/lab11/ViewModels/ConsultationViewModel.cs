using lab11.Commands;
using lab11.Data;
using lab11.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace lab11.ViewModels
{
    public class ConsultationViewModel : ViewModelBase // данные и команды
    {
        private string _teacherName;
        private string _subject;
        private DateTime _date;
        private TimeSpan _startTime;
        private TimeSpan _endTime;
        public string TeacherName
        {
            get { return _teacherName; }
            set
            {
                _teacherName = value;
                OnPropertyChanged(nameof(TeacherName));
            }
        }
        public string Subject
        {
            get { return _subject; }
            set
            {
                _subject = value;
                OnPropertyChanged(nameof(Subject));
            }
        }
        public DateTime Date
        {
            get { return _date; }
            set
            {
                _date = value;
                OnPropertyChanged(nameof(Date));
            }
        }
        public TimeSpan StartTime
        {
            get { return _startTime; }
            set
            {
                _startTime = value;
                OnPropertyChanged(nameof(StartTime));
            }
        }
        public TimeSpan EndTime
        {
            get { return _endTime; }
            set
            {
                _endTime = value;
                OnPropertyChanged(nameof(EndTime));
            }
        }

        private readonly ConsultaitionsData _consultationsData;
        private ObservableCollection<Consultation> _consultations;
        private ObservableCollection<Consultation> _bookedConsultations;
        private Consultation _selectedConsultation;
        private Consultation _selectedBookedConsultation;

        public ConsultationViewModel()
        {
            _consultationsData = new ConsultaitionsData ();
            _consultations = new ObservableCollection<Consultation>(_consultationsData.GetAllConsultations());
            _bookedConsultations = new ObservableCollection<Consultation>();

            BookConsultationCommand = new RelayCommand(BookConsultation);
            CancelConsultationCommand = new RelayCommand(CancelConsultation);
        }

        public ObservableCollection<Consultation> Consultations
        {
            get { return _consultations; }
            set
            {
                _consultations = value;
                OnPropertyChanged(nameof(Consultations));
            }
        }

        public ObservableCollection<Consultation> BookedConsultations
        {
            get { return _bookedConsultations; }
            set
            {
                _bookedConsultations = value;
                OnPropertyChanged(nameof(BookedConsultations));
            }
        }

        public Consultation SelectedConsultation
        {
            get { return _selectedConsultation; }
            set
            {
                _selectedConsultation = value;
                OnPropertyChanged(nameof(SelectedConsultation));
            }
        }

        public Consultation SelectedBookedConsultation
        {
            get { return _selectedBookedConsultation; }
            set
            {
                _selectedBookedConsultation = value;
                OnPropertyChanged(nameof(SelectedBookedConsultation));
            }
        }

        public ICommand BookConsultationCommand { get; }
        public ICommand CancelConsultationCommand { get; }

        private bool HasConsultationsWithTeacher(Consultation consultation)
        {
            return BookedConsultations.Any(c => c.TeacherName == consultation.TeacherName);
        }
        private void BookConsultation()
        {
            if (SelectedConsultation != null &&
                !BookedConsultations.Contains(SelectedConsultation) &&
                !HasConsultationsWithTeacher(SelectedConsultation))
            {
                BookedConsultations.Add(SelectedConsultation);
            }
            else
            {
                MessageBox.Show("Нельзя записаться на несколько консультаций к одному преподавателю.");
            }
        }

        private void CancelConsultation()
        {
            if (SelectedBookedConsultation != null)
            {
                BookedConsultations.Remove(SelectedBookedConsultation);
            }
        }
     
    }
}

