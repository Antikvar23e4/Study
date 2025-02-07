using System;
using System.Runtime.Serialization;
using System.Xml.Linq;


namespace lab13
{
    [DataContract]
    [Serializable]
    public class TennisBall : Ball
    {
        public TennisBall() { }

        public TennisBall(string name, double weight, bool isRepaired)
        {
            Name = name;
            Weight = weight;
            IsRepaired = isRepaired;
        }
        [DataMember]
        //[NonSerialized]
        public bool IsRepaired;

        public override string ToString()
        {
            return $"Теннисный мяч {Name}";
        }
    }

    [DataContract]
    [Serializable]
    public class Ball
    {
        public Ball() { }

        [DataMember]
        public string Name { get; set; }
        [DataMember] 
        public double Weight { get; set; }

        public override string ToString()
        {
            return $"Мяч {Name}";
        }
    }
}