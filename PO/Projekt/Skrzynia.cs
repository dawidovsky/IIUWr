using System;

namespace Projekt
{
    public class Skrzynia : Komnata
    {
        public bool Zam;
        public readonly Przedmioty Wnetrze;

        // tworzenie skrzyni z przedmiotem i określanie czy jest otwarta 
        public Skrzynia(int max, Random rnd)
        {
            var szansa = rnd.Next(1, 11);
            Zam = szansa >= 3;
            Wnetrze = new Przedmioty(max,rnd);
        }

        // otwieranie skrzyni
        public void Open()
        {
            Zam = false;
        }
    }
}