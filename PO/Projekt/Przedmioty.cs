using System;

namespace Projekt
{
    public class Przedmioty : Komnata
    {
        public readonly int Hp;
        public readonly int Att;
        public readonly int Arm;
        public readonly int Rodzaj; // 1 - Ubiór , 2 - Broń , 3 - Amulet , 4 - Użytkowe, 5 - Klucze
        
        public Przedmioty(int max, Random rnd)
        {
            var szansa = rnd.Next(1, max + 1);
            switch (szansa)
            {
                case 1:
                    szansa = rnd.Next(1, 12);
                    switch (szansa)
                    {
                        case 1:
                            Hp = 3;
                            Att = 0;
                            Arm = 0;
                            Rodzaj = 1;
                            Opis = "Chociaż ładnie wygląda";
                            Nazwa = "Koszulka";
                            break;
                        case 2: 
                            Hp = 0;
                            Att = 1;
                            Arm = 0;
                            Rodzaj = 2;
                            Opis = "Chyba służył do obierania ziemniaków";
                            Nazwa = "Nóż";
                            break;
                        case 3:
                            Hp = 0;
                            Att = 0;
                            Arm = 0;
                            Rodzaj = 5;
                            Opis = "Służy do otwierania skrzyń";
                            Nazwa = "Klucz";
                            break;
                        case 4:
                            Hp = 5;
                            Att = 0;
                            Arm = 0;
                            Rodzaj = 4;
                            Opis = "Czerwona breja w butelce, ale ma nienajgorszy smak";
                            Nazwa = "Eliksir życia";
                            break;
                        case 5:
                            Hp = 1;
                            Att = 0;
                            Arm = 1;
                            Rodzaj = 1;
                            Opis = "Jakbym miał Colę to bym pozbył się tej rdzy";
                            Nazwa = "Zardzewiała zbroja";
                            break;
                        case 6:
                            Hp = 5;
                            Att = 0;
                            Arm = 0;
                            Rodzaj = 1;
                            Opis = "Wygodna to ona nie jest";
                            Nazwa = "Słomiana zbroja";
                            break;
                        case 7:
                            Hp = 0;
                            Att = 1;
                            Arm = 1;
                            Rodzaj = 2;
                            Opis = "Może zostanę czarodziejem";
                            Nazwa = "Laska";
                            break;
                        case 8:
                            Hp = 0;
                            Att = 1;
                            Arm = 1;
                            Rodzaj = 2;
                            Opis = "Amunicja nigdy mi się nie skończy";
                            Nazwa = "Kamienie do rzucania";
                            break;
                        case 9:
                            Hp = 2;
                            Att = 0;
                            Arm = 0;
                            Rodzaj = 3;
                            Opis = "Amulet z malutkim czerwonym kamieniem";
                            Nazwa = "Amulet życia";
                            break;
                        case 10:
                            Hp = 0;
                            Att = 1;
                            Arm = 0;
                            Rodzaj = 3;
                            Opis = "Amulet z malutkim zielonym kamieniem";
                            Nazwa = "Amulet siły";
                            break;
                        case 11:
                            Hp = 0;
                            Att = 0;
                            Arm = 1;
                            Rodzaj = 3;
                            Opis = "Amulet z malutkim niebieskim kamieniem";
                            Nazwa = "Amulet obrony";
                            break;
                        default: Console.WriteLine("Błąd");break;
                    }
                    break;
                case 2:
                    szansa = rnd.Next(1, 8);
                    switch (szansa)
                    {
                        case 1:
                            Hp = 2;
                            Att = 1;
                            Arm = 1;
                            Rodzaj = 1;
                            Opis = "Jeszcze siwa broda i będę prawdziwym magiem";
                            Nazwa = "Magiczna szata";
                            break;
                        case 2:
                            Hp = 3;
                            Att = 0;
                            Arm = 2;
                            Rodzaj = 1;
                            Opis = "Jakaś krowa przez to zginęła";
                            Nazwa = "Skórzana zbroja";
                            break;
                        case 3:
                            Hp = 1;
                            Att = 0;
                            Arm = 3;
                            Rodzaj = 1;
                            Opis = "Czuję się jak buk";
                            Nazwa = "Drewniana zbroja";
                            break;
                        case 4:
                            Hp = 0;
                            Att = 2;
                            Arm = 0;
                            Rodzaj = 2;
                            Opis = "Standarowa broń każdego wojownika";
                            Nazwa = "Krótki miecz";
                            break;
                        case 5:
                            Hp = -5;
                            Att = 3;
                            Arm = 2;
                            Rodzaj = 2;
                            Opis = "Broń, która rani nie tylko przeciwników";
                            Nazwa = "Miecz obusieczny";
                            break;
                        case 6:
                            Hp = 0;
                            Att = 2;
                            Arm = 0;
                            Rodzaj = 2;
                            Opis = "Zostanę ninją z Wioski Liścia";
                            Nazwa = "Kunai";
                            break;
                        case 7:
                            Hp = 4;
                            Att = 0;
                            Arm = 0;
                            Rodzaj = 3;
                            Opis = "Amulet z małym czerwonym kamieniem";
                            Nazwa = "Amulet życia";
                            break;
                        default: Console.WriteLine("Błąd");
                            break;
                    }
                    break;
                case 3:
                    szansa = rnd.Next(1, 10);
                    switch (szansa)
                    {
                        case 1:
                            Hp = 3;
                            Att = 1;
                            Arm = 1;
                            Rodzaj = 1;
                            Opis = "Czemu ta zbroja jest taka ciężka";
                            Nazwa = "Żelazna zbroja";
                            break;
                        case 2:
                            Hp = -5;
                            Att = 1;
                            Arm = 4;
                            Rodzaj = 1;
                            Opis = "Na Summoner's Rift była lepsza, ale ta jest za darmo";
                            Nazwa = "Kolczasta kolczuga";
                            break;
                        case 3:
                            Hp = 3;
                            Att = 3;
                            Arm = 1;
                            Rodzaj = 1;
                            Opis = "Czuję się jak Bóg Śmierci";
                            Nazwa = "Czarne kimono";
                            break;
                        case 4:
                            Hp = 0;
                            Att = 4;
                            Arm = 0;
                            Rodzaj = 2;
                            Opis = "Jestem Robin Hood";
                            Nazwa = "Łuk";
                            break;
                        case 5:
                            Hp = 0;
                            Att = 3;
                            Arm = 1;
                            Rodzaj = 2;
                            Opis = "Wilkołak mi nie straszny";
                            Nazwa = "Srebrny miecz";
                            break;
                        case 6:
                            Hp = 5;
                            Att = 3;
                            Arm = 0;
                            Rodzaj = 2;
                            Opis = "Muzyka daje mi siłę. Muzyka to moc";
                            Nazwa = "Gitara";
                            break;
                        case 7:
                            Hp = 6;
                            Att = 0;
                            Arm = 0;
                            Rodzaj = 3;
                            Opis = "Amulet z niewielkim czerwonym kamieniem";
                            Nazwa = "Amulet życia";
                            break;
                        case 8:
                            Hp = 0;
                            Att = 2;
                            Arm = 0;
                            Rodzaj = 3;
                            Opis = "Amulet z niewielkim zielonym kamieniem";
                            Nazwa = "Amulet siły";
                            break;
                        case 9:
                            Hp = 0;
                            Att = 0;
                            Arm = 2;
                            Rodzaj = 3;
                            Opis = "Amulet z niewielkim niebieskim kamieniem";
                            Nazwa = "Amulet obrony";
                            break;
                        default:
                            Console.WriteLine("Błąd");
                            break;
                    }
                    break;
                case 4:
                    szansa = rnd.Next(1, 8);
                    switch (szansa)
                    {
                        case 1 :
                            Hp = 5;
                            Att = 1;
                            Arm = 5;
                            Rodzaj = 1;
                            Opis = "Gdybym uważał na lekcjach historii to bym wiedział do kogo należała";
                            Nazwa = "Zbroja ze skrzydłami";
                            break;
                        case 2:
                            Hp = 3;
                            Att = 2;
                            Arm = 4;
                            Rodzaj = 1;
                            Opis = "W 1410 nie chciałbym jej nosić";
                            Nazwa = "Pancerz Krzyżowca";
                            break;
                        case 3:
                            Hp = 2;
                            Att = 0;
                            Arm = 6;
                            Rodzaj = 1;
                            Opis = "Skorupa Żółwia";
                            Nazwa = "Teraz ja tu zamieszkam";
                            break;
                        case 4:
                            Hp = 3;
                            Att = 4;
                            Arm = 2;
                            Rodzaj = 2;
                            Opis = "Czuję się jak prawdziwy wojownik";
                            Nazwa = "Długi miecz z tarczą";
                            break;
                        case 5:
                            Hp = 5;
                            Att = 8;
                            Arm = 0;
                            Rodzaj = 2;
                            Opis = "Należała do Pana V";
                            Nazwa = "Złamana Czarna Różdżka";
                            break;
                        case 6:
                            Hp = 0;
                            Att = 10;
                            Arm = 0;
                            Rodzaj = 2;
                            Opis = "Jeszcze kaptur i będzie synchronizacja";
                            Nazwa = "Ukryte ostrza Altair'a";
                            break;
                        case 7:
                            Hp = 8;
                            Att = 0;
                            Arm = 0;
                            Rodzaj = 3;
                            Opis = "Amulet z dużym czerwonym kamieniem";
                            Nazwa = "Ammulet życia";
                            break;
                        default:Console.WriteLine("Błąd");
                            break;
                    }
                    break;
                default:Console.WriteLine("Błąd");
                    break;
            }
        }
        
        public void Wyswietl()
        {
            Console.WriteLine("Widzisz przed sobą:");
            Console.WriteLine(Nazwa);
            Console.WriteLine(Opis);
            Console.WriteLine("MaxHp: " + Hp);
            Console.WriteLine("Att: " + Att);
            Console.WriteLine("Arm: " + Arm);
        }
    }
}