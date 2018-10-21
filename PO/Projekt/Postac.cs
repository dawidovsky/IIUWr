using System;
using System.Collections.Generic;

namespace Projekt
{
    public class Postac
    {
        private readonly int[] _levels = {10, 20, 40, 60, 100, 160}; // ilość doświadczenia na poziom
        private int _maxHp; // maksymalne życie 
        private int _hp; // aktualne życie 
        public int Att; // siła ataku 
        public int Arm; // moc obrony 
        private int _exp; // doświadczenie 
        public int Lvl; // poziom 
        private readonly List<Przedmioty> _wyposazenie; // wyposażenie
        private int _eliksiry; // ilość eliksirów 
        public int Klucze; // ilość kluczy 

        public Postac()
        {
            _maxHp = 20;
            _hp = 20;
            Att = 1;
            Arm = 0;
            _exp = 0;
            Lvl = 1;
            _wyposazenie = new List<Przedmioty>();
            Klucze = 0;
        }

        // wyświetlanie stanu gracza 
        public void Status()
        {
            Console.WriteLine("HP: " + _hp + "/" + _maxHp);
            Console.WriteLine("Att: " + Att);
            Console.WriteLine("Arm: " + Arm);
            Console.WriteLine("Exp: " + _exp + "/" + _levels[Lvl]);
            Console.WriteLine("Lvl: " + Lvl + "\n");
        }

        // zmiana maksymalnego życia gracza 
        public void MaxHpUpdate(int newMaxHp)
        {
            _maxHp += newMaxHp;
            HpUpdate(0);
        }

        // zmiana punktów życia gracza
        public void HpUpdate(int newHp)
        {
            _hp += newHp;
            if (_hp > _maxHp)
                _hp = _maxHp;
        }

        // zmiana siły ataku gracza
        public void AttUpdate(int newAtt)
        {
            Att += newAtt;
        }

        // zmiana mocy obrony gracza
        public void ArmUpdate(int newArm)
        {
            Arm += newArm;
        }

        // zmiana punktów doświadczenia gracza 
        public void ExpUpdate(int newExp)
        {
            _exp += newExp;
        }

        // zmiana ilości kluczy 
        public void KeysUpdate(int x)
        {
            Klucze += x;
        }

        // obsługa zdobywania poziomu
        public void Leveling()
        {
            if (_exp < _levels[Lvl]) return;
            _exp -= _levels[Lvl];
            Lvl++;
            _maxHp += 10;
            Console.WriteLine("Zdobywasz " + Lvl + " poziom");
        }

        // sprawdzanie posiadanych przedmiotów
        public void CheckInventory()
        {
            foreach (var eq in _wyposazenie)
            {
                eq.Wyswietl();
                Console.WriteLine();
            }
            Console.WriteLine("Ilosc kluczy: " + Klucze);
            Console.WriteLine("Ilość eliksirów: " + _eliksiry + "\n");
        }

        // dodawanie i usuwanie przedmiotów z ekwipunku 
        public void ChangeInv(Przedmioty prz)
        {
            var isThere = false;
            if (prz.Rodzaj == 5)
            {
                KeysUpdate(1);
                return;
            }

            if (prz.Rodzaj == 4)
            {
                AddElixir();
                return;
            }
            foreach (var eq in _wyposazenie)
            {
                if (eq.Rodzaj != prz.Rodzaj) continue;
                _wyposazenie.Remove(eq);
                _wyposazenie.Add(prz);
                DropingItem(eq);
                TakingItem(prz);
                isThere = true;
                break;
            }
            if (isThere) return;
            _wyposazenie.Add(prz);
            TakingItem(prz);
        }

        // zmiana statystyk gracza po wyrzuceniu przedmiotu
        private void DropingItem(Przedmioty prz)
        {
            MaxHpUpdate(-prz.Hp);
            AttUpdate(-prz.Att);
            ArmUpdate(-prz.Arm);
        }

        // zmiana statystyk gracza po podniesieniu przedmiotu
        private void TakingItem(Przedmioty prz)
        {
            MaxHpUpdate(prz.Hp);
            AttUpdate(prz.Att);
            ArmUpdate(prz.Arm);
        }

        // określa jak mocno uderzymy przeciwnika
        public int PlayerDmg(Przeciwnicy prz)
        {
            var dmg = Att - prz.Arm;
            if (dmg < 0) dmg = 0;
            return dmg;
        }

        // utrata zdrowia gracza zależna od siły przeciwnika
        public void OpponentAttack(Przeciwnicy prz)
        {
            var dmg = prz.Att - Arm;
            if (dmg < 0) dmg = 0;
            _hp -= dmg;
        }
        
        // sprawdzenie czy gracz żyje
        public bool IsAlive()
        {
            return _hp > 0;
        }

        // używanie eliksiru
        public void ElixirUsage()
        {
            if (_eliksiry > 0)
            {
                HpUpdate(5);
                _eliksiry--; 
                Console.WriteLine("Eliksir przywrócił 5 punktów zdrowia");
                return;
            }
            Console.WriteLine("Nie posiadasz eliksirów zdrowia");
        }

        // dodawanie eliksiru do inwentarza
        private void AddElixir()
        {
            _eliksiry++;
        }
    }
}