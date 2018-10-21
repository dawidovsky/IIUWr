using System;

namespace Projekt
{
    public class Komnata
    {
        public int Typ; // 1 - Przeciwnik, 2 - Przedmiot, 3 - Wydarzenie, 4 - Skrzynia, 5 - Pusta
        protected string Opis;
        protected string Nazwa;

        // konstruktor losujący komnatę 
        public Komnata(Random rnd)
        {
            var szansa = rnd.Next(1, 20);
            if (szansa < 6)
                Typ = 1;
            else if (szansa > 4 && szansa < 14)
                Typ = 2;
            else if (szansa > 13 && szansa < 17)
                Typ = 4;
            else
                Typ = 3;
        }
        // konstruktor bezparametrowy tworzący pustą komnatę 
        protected Komnata()
        {
            Typ = 5;
        }
    }
}