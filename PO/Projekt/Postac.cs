using System;
using System.Collections.Generic;

namespace Projekt
{
    public class Postac
    {
        private readonly int[] _levels = {10, 20, 40, 60, 100, 160};
        private int _maxHp;
        private int _hp;
        public int Att;
        public int Arm;
        private int _exp;
        public int Lvl;
        private readonly List<Przedmioty> _wyposazenie;
        private int _eliksiry;
        public int Klucze;

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

        public void Status()
        {
            Console.WriteLine("HP: " + _hp + "/" + _maxHp);
            Console.WriteLine("Att: " + Att);
            Console.WriteLine("Arm: " + Arm);
            Console.WriteLine("Exp: " + _exp + "/" + _levels[Lvl]);
            Console.WriteLine("Lvl: " + Lvl + "\n");
        }

        public void MaxHpUpdate(int newMaxHp)
        {
            _maxHp += newMaxHp;
            HpUpdate(0);
        }

        public void HpUpdate(int newHp)
        {
            _hp += newHp;
            if (_hp > _maxHp)
                _hp = _maxHp;
        }

        public void AttUpdate(int newAtt)
        {
            Att += newAtt;
        }

        public void ArmUpdate(int newArm)
        {
            Arm += newArm;
        }

        public void ExpUpdate(int newExp)
        {
            _exp += newExp;
        }

        public void KeysUpdate(int x)
        {
            Klucze += x;
        }

        public void Leveling()
        {
            if (_exp < _levels[Lvl]) return;
            _exp -= _levels[Lvl];
            Lvl++;
            _maxHp += 10;
            Console.WriteLine("Zdobywasz " + Lvl + " poziom");
        }

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

        private void DropingItem(Przedmioty prz)
        {
            MaxHpUpdate(-prz.Hp);
            AttUpdate(-prz.Att);
            ArmUpdate(-prz.Arm);
        }

        private void TakingItem(Przedmioty prz)
        {
            MaxHpUpdate(prz.Hp);
            AttUpdate(prz.Att);
            ArmUpdate(prz.Arm);
        }

        public int PlayerDmg(Przeciwnicy prz)
        {
            var dmg = Att - prz.Arm;
            if (dmg < 0) dmg = 0;
            return dmg;
        }

        public void OpponentAttack(Przeciwnicy prz)
        {
            var dmg = prz.Att - Arm;
            if (dmg < 0) dmg = 0;
            _hp -= dmg;
        }
        
        public bool IsAlive()
        {
            return _hp > 0;
        }

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

        private void AddElixir()
        {
            _eliksiry++;
        }
    }
}