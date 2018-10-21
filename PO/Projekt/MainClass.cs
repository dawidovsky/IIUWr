using System;

namespace Projekt
{
    // cała obsługa wyświetlanych komunikatów 
    // głównie jest to sam tekst, który wyświetla się graczowi
    public class MainClass
    {
        public static void Main()
        {
            var gracz = new Postac();
            var rnd = new Random();
            Console.WriteLine("Pojawiasz się w zapomnianym labiryncie.");
            Console.WriteLine("Wciśnij dowolny klawisz by przejść do pierwszej komnaty");
            Console.Read();
            while (gracz.IsAlive())  // gra działa dopóki gracz jest żywy
            {
                var stan = "0";
                var kom = new Komnata(rnd);
                if (kom.Typ == 1) // obsługa komnaty z przeciwnikiem 
                {
                    Console.WriteLine("Nowy Przeciwnik");
                    var opp = new Przeciwnicy(gracz.Lvl, rnd);
                    var flee = false;
                    while (opp.Hp > 0)
                    {
                        if (!gracz.IsAlive()) break;
                        opp.Status();
                        Console.WriteLine("Wybierz co chcesz dalej zrobić");
                        Console.WriteLine("1.Przejść do kolejnej tury walki");
                        Console.WriteLine("2.Sprawdzić swój stan");
                        Console.WriteLine("3.Sprawdzić swój ekwipunek");
                        Console.WriteLine("4.Użyj eliksiru zdrowia");
                        Console.WriteLine("5.Ucieknij z walki");
                        Console.WriteLine("6.Wyjdź z gry");
                        stan = Console.ReadLine();
                        Console.Clear();
                        if (stan == "1")
                        {
                            Console.WriteLine("Zadajesz przeciwnikowi " + gracz.PlayerDmg(opp) + " punktów obrażeń");
                            opp.PlayerAttack(gracz);
                            if (opp.Hp <= 0) break;
                            Console.WriteLine("Przeciwnik zadaje Ci " + opp.OpponentDmg(gracz) + " punktów obrażeń");
                            gracz.OpponentAttack(opp);
                        }
                        else if (stan == "2")
                            gracz.Status();
                        else if (stan == "3")
                            gracz.CheckInventory();
                        else if (stan == "4")
                            gracz.ElixirUsage();
                        else if (stan == "5")
                        {
                            var dmg = rnd.Next(opp.Att, opp.Att * 2 + 1);
                            gracz.HpUpdate(-dmg);
                            Console.WriteLine("Uciekając z pola walki straciłeś " + dmg + " punktów życia\n");
                            opp.Hp = 0;
                            flee = true;
                        }
                        else if (stan == "6")
                        {
                            Console.WriteLine("Czy na pewno chcesz wyjsć?");
                            Console.WriteLine("1.Tak");
                            Console.WriteLine("2.Nie");
                            var decyzja = Console.ReadLine();
                            if (decyzja == "1")
                            {
                                gracz.HpUpdate(-100000);
                            }
                            Console.Clear();
                        }
                    }
                    if (gracz.IsAlive() && !flee)
                    {
                        Console.WriteLine("Pokonałeś przeciwnika");
                        Console.WriteLine("Zdobyłeś " + opp.Exp + " punktów doświadczenia\n");
                        gracz.ExpUpdate(opp.Exp);
                        gracz.Leveling();
                    }
                    kom.Typ = 5;
                }

                else if (kom.Typ == 2) // obsługa komnaty z przedmiotem 
                {
                    Console.WriteLine("Coś leży na ziemi");
                    var prz = new Przedmioty(gracz.Lvl, rnd);
                    while (stan != "1" && stan != "5")
                    {
                        if (!gracz.IsAlive()) break;
                        prz.Wyswietl();
                        Console.WriteLine("\nWybierz co chcesz dalej zrobić");
                        Console.WriteLine("1.Iść do kolejnej komnaty");
                        Console.WriteLine("2.Sprawdzić swój stan");
                        Console.WriteLine("3.Sprawdzić swój ekwipunek");
                        Console.WriteLine("4.Podnieść i podmienić przedmioty");
                        Console.WriteLine("5.Wyjdź z gry");

                        stan = Console.ReadLine();
                        Console.Clear();
                        if (stan == "2")
                            gracz.Status();
                        else if (stan == "3")
                            gracz.CheckInventory();
                        else if (stan == "4")
                        {
                            gracz.ChangeInv(prz);
                            kom.Typ = 5;
                            break;
                        }
                        else if (stan == "5")
                        {
                            Console.WriteLine("Czy na pewno chcesz wyjsć?");
                            Console.WriteLine("1.Tak");
                            Console.WriteLine("2.Nie");
                            var decyzja = Console.ReadLine();
                            if (decyzja == "1")
                            {
                                gracz.HpUpdate(-100000);
                                Console.Clear();
                            }
                            else
                            {
                                stan = "0";
                                Console.Clear();
                            }
                        }
                    }
                }

                else if (kom.Typ == 3) // obsługa komnaty z wydarzeniem
                {
                    Console.WriteLine("Coś się dzieje");
                    var wd = new Wydarzenie(rnd);
                    wd.Wyswietl();
                    switch (wd.Co)
                    {
                        case "Hp":
                            gracz.HpUpdate(wd.Wplyw);
                            break;
                        case "Att":
                            gracz.AttUpdate(wd.Wplyw);
                            break;
                        case "Arm":
                            gracz.ArmUpdate(wd.Wplyw);
                            break;
                        case "Exp":
                            gracz.ExpUpdate(wd.Wplyw);
                            break;
                        case "MaxHp":
                            gracz.MaxHpUpdate(wd.Wplyw);
                            break;
                        default: Console.WriteLine("Bład");
                            break;
                    }
                    while (stan != "1" && stan != "4")
                    {
                        if (!gracz.IsAlive()) break;
                        Console.WriteLine("\nWybierz co chcesz dalej zrobić");
                        Console.WriteLine("1.Iść do kolejnej komnaty");
                        Console.WriteLine("2.Sprawdzić swój stan");
                        Console.WriteLine("3.Sprawdzić swój ekwipunek");
                        Console.WriteLine("4.Wyjdź z gry");

                        stan = Console.ReadLine();
                        Console.Clear();
                        if (stan == "2")
                            gracz.Status();
                        else if (stan == "3")
                            gracz.CheckInventory();
                        else if (stan == "4")
                        {
                            Console.WriteLine("Czy na pewno chcesz wyjsć?");
                            Console.WriteLine("1.Tak");
                            Console.WriteLine("2.Nie");
                            var decyzja = Console.ReadLine();
                            if (decyzja == "1")
                            {
                                gracz.HpUpdate(-100000);
                                Console.Clear();
                            }
                            else
                            {
                                stan = "0";
                                Console.Clear();
                            } 
                        }
                    }
                }

                else if (kom.Typ == 4) // obsługa komnaty ze skrzynią 
                {
                    Console.Write("Na środku pomieszczenia stoi piękna skrzynia");
                    var skr = new Skrzynia(gracz.Lvl, rnd);
                    while (stan != "1" && stan != "6")
                    {
                        if (!gracz.IsAlive()) break;
                        if (skr.Zam)
                        {
                            Console.WriteLine("\nSkrzynia jest zamknięta");
                            Console.WriteLine("\nWybierz co chcesz dalej zrobić");
                            Console.WriteLine("1.Iść do kolejnej komnaty");
                            Console.WriteLine("2.Sprawdzić swój stan");
                            Console.WriteLine("3.Sprawdzić swój ekwipunek");
                            Console.WriteLine("4.Otworzyć skrzynię");
                            Console.WriteLine("5.Uderzyć skrzynię");
                            Console.WriteLine("6.Wyjdź z gry");

                            stan = Console.ReadLine();
                            Console.Clear();
                            if (stan == "2")
                                gracz.Status();
                            else if (stan == "3")
                                gracz.CheckInventory();
                            else if (stan == "4")
                            {
                                if (gracz.Klucze > 0)
                                {
                                    skr.Open();
                                    gracz.KeysUpdate(-1);
                                }
                                else
                                    Console.WriteLine("Nie posiadasz kluczy");
                            }
                            else if (stan == "5")
                            {
                                if (gracz.Att > 6)
                                {
                                    Console.WriteLine("Zniszczyłeś skrzynię");
                                    skr.Open();
                                }
                                else
                                {
                                    Console.WriteLine("Była to bardzo bolesne");
                                    gracz.HpUpdate(-1);
                                    Console.WriteLine("Straciłeś 1 Hp");
                                }

                            }
                            else if (stan == "6")
                            {
                                Console.WriteLine("Czy na pewno chcesz wyjsć?");
                                Console.WriteLine("1.Tak");
                                Console.WriteLine("2.Nie");
                                var decyzja = Console.ReadLine();
                                if (decyzja == "1")
                                {
                                    gracz.HpUpdate(-100000);
                                    Console.Clear();
                                }
                                else
                                {
                                    stan = "0";
                                    Console.Clear();
                                }
                            }
                        }
                        else
                        {
                            Console.WriteLine("\nSkrzynia jest otwarta, w środku znajduje się: ");
                            skr.Wnetrze.Wyswietl();
                            Console.WriteLine("\nWybierz co chcesz dalej zrobić");
                            Console.WriteLine("1.Iść do kolejnej komnaty");
                            Console.WriteLine("2.Sprawdzić swój stan");
                            Console.WriteLine("3.Sprawdzić swój ekwipunek");
                            Console.WriteLine("4.Sprawdzic opis przedmiotu");
                            Console.WriteLine("5.Podnieść i podmienić przedmioty");
                            Console.WriteLine("6.Wyjśc z gry");

                            stan = Console.ReadLine();
                            Console.Clear();
                            if (stan == "2")
                                gracz.Status();
                            else if (stan == "3")
                                gracz.CheckInventory();
                            else if (stan == "4")
                                skr.Wnetrze.Wyswietl();
                            else if (stan == "5")
                            {
                                gracz.ChangeInv(skr.Wnetrze);
                                break;
                            }
                            else if (stan == "6")
                            {
                                Console.WriteLine("Czy na pewno chcesz wyjsć?");
                                Console.WriteLine("1.Tak");
                                Console.WriteLine("2.Nie");
                                var decyzja = Console.ReadLine();
                                if (decyzja == "1")
                                {
                                    gracz.HpUpdate(-100000);
                                    Console.Clear();
                                }
                                else
                                {
                                    stan = "0";
                                    Console.Clear();
                                }
                            }
                        }
                    }
                    if (!skr.Zam)
                        kom.Typ = 5;
                }

                if (kom.Typ == 5) // obsługa pustej komnaty
                {
                    stan = "0";
                    while (stan != "1" && stan != "5")
                    {
                        if (!gracz.IsAlive()) break;
                        Console.WriteLine("Wybierz co chcesz dalej zrobić");
                        Console.WriteLine("1.Iść do kolejnej komnaty");
                        Console.WriteLine("2.Sprawdzić swój stan");
                        Console.WriteLine("3.Sprawdzić swój ekwipunek");
                        Console.WriteLine("4.Użyć eliksiru");
                        Console.WriteLine("5.Wyjdź z gry");

                        stan = Console.ReadLine();
                        Console.Clear();
                        if (stan == "2")
                            gracz.Status();
                        else if (stan == "3")
                            gracz.CheckInventory();
                        else if (stan == "4")
                            gracz.ElixirUsage();
                        else if (stan == "5")
                        {
                            Console.WriteLine("Czy na pewno chcesz wyjsć?");
                            Console.WriteLine("1.Tak");
                            Console.WriteLine("2.Nie");
                            var decyzja = Console.ReadLine();
                            if (decyzja == "1")
                            {
                                gracz.HpUpdate(-100000);
                                Console.Clear();
                            }
                            else
                            {
                                stan = "0";
                                Console.Clear();
                            }
                        }
                    }
                }
            }
            Console.WriteLine("Nie żyjesz"); // śmierć gracza - komunikat 
            Console.Read();
        }
    }
}

