using System;

namespace Projekt
{
    public class Skrzynia : Komnata
    {
        public bool Zam;
        public readonly Przedmioty Wnetrze;

        public Skrzynia(int max, Random rnd)
        {
            var szansa = rnd.Next(1, 11);
            Zam = szansa >= 3;
            Wnetrze = new Przedmioty(max,rnd);
        }

        public void Open()
        {
            Zam = false;
        }
    }
}