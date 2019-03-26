module Zad2(
  input [3:0] i,
  output o
);
  // res2 problem z bitem '0'
  // Scie¿ka krótsza od
  // wszystkich innnych ? Prosty fix ( wydluzam sciezke o 1)
  logic fix0 = i[0] && 1;
  // Rysujemy mape Karnaugh
  // Prosta odpowiedŸ z glitchami
  logic res1, res2, res3, res4, res5, res6;
  assign res1 = i[0] && i[1] && !i[2];
  assign res2 = fix0 && !i[1] && i[2];
  assign res3 = i[0] && !i[1] && i[3];
  assign res4 = i[1] && i[2] && !i[3];
  assign res5 = !i[0] && i[1] && i[3];
  assign res6 = !i[0] && i[2] && i[3];
  // Tam gdzie s¹ "dziury" na mapie
  // to dorabiamy "mosty"
  logic fix1, fix2, fix3, fix4;
  assign fix1 = i[0] && i[2] && !i[3];
  assign fix2 = i[1] && !i[2] && i[3];
  assign fix3 = i[0] && !i[2] && i[3];
  assign fix4 = !i[0] && i[1] && i[2];
  //or answer(o, res1, res2, res3, res4, res5,
  //          res6, fix1, fix2, fix3, fix4);
  // huge 'or' problem fix
  logic x1, x2, x3, x4, x5;
  assign x1 = res1 || res2;
  assign x2 = res3 || res4;
  assign x3 = res5 || res6;
  assign x4 = fix1 || fix2;
  assign x5 = fix3 || fix4;
  logic y1, y2, y3;
  assign y1 = x1 || x2;
  assign y2 = x2 || x3;
  assign y3 = x4 || x5;
  logic z1, z2;
  assign z1 = y1 || y2;
  assign z2 = y2 || y3;
  or answer(o, z1, z2);
endmodule
