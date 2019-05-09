module d_latch(
  input d, e,
  output q, nq
);

  logic s, r;

  nor g1(q, r, nq);
  nor g2(nq, s, q);
  and g3(r, e, nd);
  and g4(s, e, d);
  not g5(nd, d);

endmodule

module dff_master_slave(
  input d, c,
  output o
);

  logic q, nq1, nq2, nclk;

  d_latch dl1(d, nclk, q, nq1);
  d_latch dl2(q, c, o, nq2);
  not g(nclk, c);

endmodule

module mux(
  input l, r, i0, i1, i2, i3,
  output o
);
  assign o = l & r ? i3 : r ? i1 : l ? i2 : i0;
endmodule

module main(
  output [7:0] q,
  input [7:0]d,
  input i, c, l, r
);
  logic m1;
  mux mm0(l, r, q[0], i, q[1], d[0], m1);
  dff_master_slave dd0(m1, c, q[0]);
  logic m2;
  mux mm1(l, r, q[1], q[0], q[2], d[1], m2);
  dff_master_slave dd1(m2, c, q[1]);
  logic m3;
  mux mm2(l, r, q[2], q[1], q[3], d[2], m3);
  dff_master_slave dd2(m3, c, q[2]);
  logic m4;
  mux mm3(l, r, q[3], q[2], q[4], d[3], m4);
  dff_master_slave dd3(m4, c, q[3]);
  logic m5;
  mux mm4(l, r, q[4], q[3], q[5], d[4], m5);
  dff_master_slave dd4(m5, c, q[4]);
  logic m6;
  mux mm5(l, r, q[5], q[4], q[6], d[5], m6);
  dff_master_slave dd5(m6, c, q[5]);
  logic m7;
  mux mm6(l, r, q[6], q[5], q[7], d[6], m7);
  dff_master_slave dd6(m7, c, q[6]);
  logic m8;
  mux mm7(l, r, q[7], q[6], i, d[7], m8);
  dff_master_slave dd7(m8, c, q[7]);
  
  
endmodule