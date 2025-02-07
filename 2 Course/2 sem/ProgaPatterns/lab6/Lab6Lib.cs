using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab6Lib
{
    public interface ISubscriber
    {
        void Update(string eventname); 
    }

    public class Publisher
    {
        private delegate void EventRaisedHandler(string eventName);//делегат длч определ метода
        private event EventRaisedHandler eventCall;
        private string nameOfEvent;

        public Publisher(string eventName)
        {
            nameOfEvent = eventName;
        }

        public void Subscribe(ISubscriber subscriber)
        {
            eventCall += subscriber.Update;//будет возвращ название события
        }

        public bool Unsubscribe(ISubscriber subscriber)
        {
            eventCall -= subscriber.Update;
            return true;
        }

        public int Notify() //уведомление о событии
        {
            EventRaisedHandler handler = eventCall;

            if (handler is not null)
            {
                handler(nameOfEvent);
                int count = eventCall.GetInvocationList().Count();
                Console.WriteLine($"Количество подписчиков на событие '{nameOfEvent}': {count}");
                return count;
            }
            Console.WriteLine($"Количество подписчиков на событие'{nameOfEvent}': 0");
            return 0;
        }
    }

}
