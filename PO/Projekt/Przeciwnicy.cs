using System;

namespace Projekt
{
    

    public class Przeciwnicy : Komnata
    {
        private readonly int _maxHp; // maksymalne życie przeciwnika 
        public int Hp; // aktualne życie przeciwnika 
        public readonly int Att; // siła ataku przeciwnika
        public readonly int Arm; // moc obrony przeciwnika 
        public readonly int Exp; // ilość doświadczenia jaką zdobędzie gracz za pokonanie tego przeciwnika 

        // baza przeciwników 
        public Przeciwnicy(int max, Random rnd)
        {
            var szansa = rnd.Next(1, max + 1);
            switch (szansa)
            {
                case 1:
                    szansa = rnd.Next(1, 5);
                    switch (szansa)
                    {
                        case 1:
                            _maxHp = Hp = 2;
                            Att = 1;
                            Arm = 0;
                            Exp = 1;
                            Opis = "Wygląda milusio";
                            Nazwa = "Mysz";
                            break;
                        case 2: 
                            _maxHp = Hp = 3;
                            Att = 2;
                            Arm = 0;
                            Exp = 2;
                            Opis = "Taka większa mysz";
                            Nazwa = "Szczur";
                            break;
                        case 3:
                            _maxHp = Hp = 3;
                            Att = 1;
                            Arm = 1;
                            Exp = 3;
                            Opis = "Wygląda smakowicie";
                            Nazwa = "Krab";
                            break;
                        case 4:
                            _maxHp = Hp = 3;
                            Att = 2;
                            Arm = 0;
                            Exp = 2;
                            Opis = "Moja krew nie jest smaczna";
                            Nazwa = "Ogromny komar";
                            break;
                        default: Console.WriteLine("Błąd");break;
                    }
                    break;
                case 2:
                    szansa = rnd.Next(1, 5);
                    switch (szansa)
                    {
                         case 1:
                             _maxHp = Hp = 5;
                             Att = 2;
                             Arm = 1;
                             Exp = 3;
                             Opis = "Mam nadzieję, że nie zamienie się w wampira";
                             Nazwa = "Nietoperz";
                             break;
                         case 2:
                             _maxHp = Hp = 4;
                             Att = 3;
                             Arm = 2;
                             Exp = 4;
                             Opis = "W każdym lochu tego pełno";
                             Nazwa = "Goblin";
                             break;
                         case 3:
                             _maxHp = Hp = 6;
                             Att = 3;
                             Arm = 0;
                             Exp = 3;
                             Opis = "Od kiedy szczury są takie zielone";
                             Nazwa = "Zmutowany szczur";
                             break;
                         case 4:
                             _maxHp = Hp = 5;
                             Att = 3;
                             Arm = 1;
                             Exp = 4;
                             Opis = "Spokojnie piesku, spokojnie";
                             Nazwa = "Agresywny pies";
                             break;
                        default: Console.WriteLine("Błąd");break;
                    }
                    break;
                case 3:
                    szansa = rnd.Next(1, 5);
                    switch (szansa)
                    {
                         case 1:
                             _maxHp = Hp = 8;
                             Att = 5;
                             Arm = 2;
                             Exp = 5;
                             Opis = "Pół tuzina takich skór, a dostanę złota wór";
                             Nazwa = "Wilk";
                             break;
                         case 2:
                             _maxHp = Hp = 10;
                             Att = 4;
                             Arm = 4;
                             Exp = 6;
                             Opis = "A ten tu czego szuka";
                             Nazwa = "Bandyta";
                             break;
                         case 3:
                             _maxHp = Hp = 7;
                             Att = 6;
                             Arm = 2;
                             Exp = 5;
                             Opis = "Wielki czarny kocur. Może mleko podziała";
                             Nazwa = "Czarna pantera";
                             break;
                         case 4:
                             _maxHp = Hp = 5;
                             Att = 1;
                             Arm = 1;
                             Exp = 1;
                             Opis = "Mój koszmar z dzieciństwa";
                             Nazwa = "Agresywna kaczka";
                             break;
                         default: Console.WriteLine("Błąd");break;
                    }
                    break;
                case 4:
                    szansa = rnd.Next(1, 5);
                    switch (szansa)
                    {
                         case 1:
                             _maxHp = Hp = 13;
                             Att = 8;
                             Arm = 5;
                             Exp = 8;
                             Opis = "Może byś coś ubrał";
                             Nazwa = "Szkielet";
                             break;
                         case 2:
                             _maxHp = Hp = 16;
                             Att = 8;
                             Arm = 4;
                             Exp = 7;
                             Opis = "Wielka zielona góra mięsa";
                             Nazwa = "Trol";
                             break;
                         case 3:
                             _maxHp = Hp = 15;
                             Att = 7;
                             Arm = 5;
                             Exp = 7;
                             Opis = "Ma tylko jedno oko, na pewno mnie nie trafi";
                             Nazwa = "Cyklop";
                             break;
                         case 4:
                             _maxHp = Hp = 10;
                             Att = 6;
                             Arm = 4;
                             Exp = 6;
                             Opis = "Jak ja mam to trafić";
                             Nazwa = "Duch";
                             break;
                        default: Console.WriteLine("Błąd");break;
                    }
                    break;
            }
        }

        // wyświetlanie informacji o przeciwniku
        public void Status()
        {
            Console.WriteLine(Nazwa);
            Console.WriteLine(Opis);
            Console.WriteLine("HP: " + Hp + "/" + _maxHp);
            Console.WriteLine("Att: " + Att);
            Console.WriteLine("Arm: " + Arm);
            Console.WriteLine("Exp: " + Exp + "\n");
        }

        // utrata zdrowia przeciwnika w zależności od siły ataku gracza 
        public void PlayerAttack(Postac gracz)
        {
            var dmg = gracz.Att - Arm;
            if (dmg < 0) dmg = 0;
            Hp -= dmg;
        }

        // określenie z jaką siłą uderzy nas przeciwnik
        public int OpponentDmg(Postac gracz)
        {
            var dmg = Att - gracz.Arm;
            if (dmg < 0) dmg = 0;
            return dmg;
        }
        
    }
}