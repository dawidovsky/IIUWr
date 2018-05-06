using System;

namespace Projekt
{
    public class Wydarzenie : Komnata
    {
        public readonly string Co;
        public readonly int Wplyw;
        
        public Wydarzenie(Random rnd)
        {
            var szansa = rnd.Next(1, 7);
            Console.WriteLine("Losowość wyniosła " + szansa);
            switch (szansa)
            {
                case 1:
                    Opis = "Kamień, który toczy się prosto na mnie";
                    Nazwa = "Pułapka z kamieniem";
                    Wplyw = -5;
                    Co = "Hp";
                    break;
                case 2:
                    Opis = "Tryska z niej złowroga energia";
                    Nazwa = "Fontanna";
                    Wplyw = -5;
                    Co = "Hp";
                    break;
                case 3:
                    Opis = "Tryska z niej cudowna energia";
                    Nazwa = "Fontanna";
                    Wplyw = 5;
                    Co = "Hp";
                    break;
                case 4:
                    Opis = "Mogę odpocząć i wyleczyć rany";
                    Nazwa = "Ognisko";
                    Wplyw = 5;
                    Co = "Hp";
                    break;
                case 5:
                    Opis = "Strażnik z Białej Grani byłby dumny";
                    Nazwa = "Strzała w kolano";
                    Wplyw = -1;
                    Co = "MaxHp";
                    break;
                case 6:
                    Opis = "Niezdrowe, ale czuję się silniejszy";
                    Nazwa = "Studia z czekoladą";
                    Wplyw = 1;
                    Co = "MaxHp";
                    break;
                default:
                    Console.WriteLine("Błąd");
                    break;
            }
        }
        
        public void Wyswietl()
        {
            Console.WriteLine(Nazwa);
            Console.WriteLine(Opis);
            Console.WriteLine("Wydarzenie wplywa na : " + Co + " w ilości " + Wplyw);
        }
    }
}