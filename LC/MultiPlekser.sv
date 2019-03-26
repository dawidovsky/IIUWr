module zad1(
  input a, b, c, d, x, y,
  output o
);
  assign o = (!x & !y) ? a : (!x & y) ? b : (x & !y) ? c : d;
  
endmodule