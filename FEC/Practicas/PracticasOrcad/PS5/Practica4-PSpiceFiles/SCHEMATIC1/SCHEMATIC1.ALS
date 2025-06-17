.ALIASES
_    SumaCom(CIN=M S0=A0 S1=N01110 Suma=S0 COUT=N00964 ) CN @PRACTICA4.SCHEMATIC1(sch_1):SumaCom@PRACTICA4.SumaCom(sch_1)
_    SumaCom.Semisum(SUM0=A0 SUM1=N01110 SUM=SumaCom_N00170 CARRY=SumaCom_N00250 ) CN 
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1)
X_SumaCom_Semisum_U2A          SumaCom.Semisum.U2A(A=A0 B=N01110 Y=SumaCom_N00170 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1):INS208@74LS.74LS86A.Normal(chips)
X_SumaCom_Semisum_U1A          SumaCom.Semisum.U1A(A=N01110 B=A0 Y=SumaCom_N00250 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1):INS80@74LS.74LS08.Normal(chips)
_    _(SumaCom.Semisum.CARRY=SumaCom_N00250)
_    _(SumaCom.Semisum.SUM=SumaCom_N00170)
_    _(SumaCom.Semisum.SUM0=A0)
_    _(SumaCom.Semisum.SUM1=N01110)
_    SumaCom.Semisum1(SUM0=SumaCom_N00170 SUM1=M SUM=S0 CARRY=SumaCom_N00337 ) CN 
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1)
X_SumaCom_Semisum1_U2A          SumaCom.Semisum1.U2A(A=SumaCom_N00170 B=M Y=S0 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1):INS208@74LS.74LS86A.Normal(chips)
X_SumaCom_Semisum1_U1A          SumaCom.Semisum1.U1A(A=M B=SumaCom_N00170 Y=SumaCom_N00337 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1):INS80@74LS.74LS08.Normal(chips)
_    _(SumaCom.Semisum1.CARRY=SumaCom_N00337)
_    _(SumaCom.Semisum1.SUM=S0)
_    _(SumaCom.Semisum1.SUM0=SumaCom_N00170)
_    _(SumaCom.Semisum1.SUM1=M)
X_SumaCom_U1A          SumaCom.U1A(A=SumaCom_N00337 B=SumaCom_N00250 Y=N00964 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom@PRACTICA4.SumaCom(sch_1):INS292@74LS.74LS32.Normal(chips)
_    _(SumaCom.CIN=M)
_    _(SumaCom.COUT=N00964)
_    _(SumaCom.S0=A0)
_    _(SumaCom.S1=N01110)
_    _(SumaCom.Suma=S0)
_    SumaCom1(CIN=N00964 S0=A1 S1=N01230 Suma=S1 COUT=N00939 ) CN @PRACTICA4.SCHEMATIC1(sch_1):SumaCom1@PRACTICA4.SumaCom(sch_1)
X_SumaCom1_U1A          SumaCom1.U1A(A=SumaCom1_N00337 B=SumaCom1_N00250 Y=N00939 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom1@PRACTICA4.SumaCom(sch_1):INS292@74LS.74LS32.Normal(chips)
_    SumaCom1.Semisum1(SUM0=SumaCom1_N00170 SUM1=N00964 SUM=S1 CARRY=SumaCom1_N00337 ) CN 
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom1@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1)
X_SumaCom1_Semisum1_U2A          SumaCom1.Semisum1.U2A(A=SumaCom1_N00170 B=N00964 Y=S1 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom1@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1):INS208@74LS.74LS86A.Normal(chips)
X_SumaCom1_Semisum1_U1A          SumaCom1.Semisum1.U1A(A=N00964 B=SumaCom1_N00170 Y=SumaCom1_N00337 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom1@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1):INS80@74LS.74LS08.Normal(chips)
_    _(SumaCom1.Semisum1.CARRY=SumaCom1_N00337)
_    _(SumaCom1.Semisum1.SUM=S1)
_    _(SumaCom1.Semisum1.SUM0=SumaCom1_N00170)
_    _(SumaCom1.Semisum1.SUM1=N00964)
_    SumaCom1.Semisum(SUM0=A1 SUM1=N01230 SUM=SumaCom1_N00170 CARRY=SumaCom1_N00250 ) CN 
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom1@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1)
X_SumaCom1_Semisum_U2A          SumaCom1.Semisum.U2A(A=A1 B=N01230 Y=SumaCom1_N00170 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom1@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1):INS208@74LS.74LS86A.Normal(chips)
X_SumaCom1_Semisum_U1A          SumaCom1.Semisum.U1A(A=N01230 B=A1 Y=SumaCom1_N00250 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom1@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1):INS80@74LS.74LS08.Normal(chips)
_    _(SumaCom1.Semisum.CARRY=SumaCom1_N00250)
_    _(SumaCom1.Semisum.SUM=SumaCom1_N00170)
_    _(SumaCom1.Semisum.SUM0=A1)
_    _(SumaCom1.Semisum.SUM1=N01230)
_    _(SumaCom1.CIN=N00964)
_    _(SumaCom1.COUT=N00939)
_    _(SumaCom1.S0=A1)
_    _(SumaCom1.S1=N01230)
_    _(SumaCom1.Suma=S1)
_    SumaCom2(CIN=N00939 S0=A2 S1=N01472 Suma=S2 COUT=N00908 ) CN @PRACTICA4.SCHEMATIC1(sch_1):SumaCom2@PRACTICA4.SumaCom(sch_1)
X_SumaCom2_U1A          SumaCom2.U1A(A=SumaCom2_N00337 B=SumaCom2_N00250 Y=N00908 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom2@PRACTICA4.SumaCom(sch_1):INS292@74LS.74LS32.Normal(chips)
_    SumaCom2.Semisum1(SUM0=SumaCom2_N00170 SUM1=N00939 SUM=S2 CARRY=SumaCom2_N00337 ) CN 
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom2@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1)
X_SumaCom2_Semisum1_U2A          SumaCom2.Semisum1.U2A(A=SumaCom2_N00170 B=N00939 Y=S2 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom2@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1):INS208@74LS.74LS86A.Normal(chips)
X_SumaCom2_Semisum1_U1A          SumaCom2.Semisum1.U1A(A=N00939 B=SumaCom2_N00170 Y=SumaCom2_N00337 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom2@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1):INS80@74LS.74LS08.Normal(chips)
_    _(SumaCom2.Semisum1.CARRY=SumaCom2_N00337)
_    _(SumaCom2.Semisum1.SUM=S2)
_    _(SumaCom2.Semisum1.SUM0=SumaCom2_N00170)
_    _(SumaCom2.Semisum1.SUM1=N00939)
_    SumaCom2.Semisum(SUM0=A2 SUM1=N01472 SUM=SumaCom2_N00170 CARRY=SumaCom2_N00250 ) CN 
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom2@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1)
X_SumaCom2_Semisum_U2A          SumaCom2.Semisum.U2A(A=A2 B=N01472 Y=SumaCom2_N00170 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom2@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1):INS208@74LS.74LS86A.Normal(chips)
X_SumaCom2_Semisum_U1A          SumaCom2.Semisum.U1A(A=N01472 B=A2 Y=SumaCom2_N00250 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom2@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1):INS80@74LS.74LS08.Normal(chips)
_    _(SumaCom2.Semisum.CARRY=SumaCom2_N00250)
_    _(SumaCom2.Semisum.SUM=SumaCom2_N00170)
_    _(SumaCom2.Semisum.SUM0=A2)
_    _(SumaCom2.Semisum.SUM1=N01472)
_    _(SumaCom2.CIN=N00939)
_    _(SumaCom2.COUT=N00908)
_    _(SumaCom2.S0=A2)
_    _(SumaCom2.S1=N01472)
_    _(SumaCom2.Suma=S2)
_    SumaCom3(CIN=N00908 S0=A3 S1=N00555 Suma=S3 COUT=C4 ) CN @PRACTICA4.SCHEMATIC1(sch_1):SumaCom3@PRACTICA4.SumaCom(sch_1)
X_SumaCom3_U1A          SumaCom3.U1A(A=SumaCom3_N00337 B=SumaCom3_N00250 Y=C4 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom3@PRACTICA4.SumaCom(sch_1):INS292@74LS.74LS32.Normal(chips)
_    SumaCom3.Semisum1(SUM0=SumaCom3_N00170 SUM1=N00908 SUM=S3 CARRY=SumaCom3_N00337 ) CN 
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom3@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1)
X_SumaCom3_Semisum1_U2A          SumaCom3.Semisum1.U2A(A=SumaCom3_N00170 B=N00908 Y=S3 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom3@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1):INS208@74LS.74LS86A.Normal(chips)
X_SumaCom3_Semisum1_U1A          SumaCom3.Semisum1.U1A(A=N00908 B=SumaCom3_N00170 Y=SumaCom3_N00337 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom3@PRACTICA4.SumaCom(sch_1):Semisum1@PRACTICA4.SemiSum(sch_1):INS80@74LS.74LS08.Normal(chips)
_    _(SumaCom3.Semisum1.CARRY=SumaCom3_N00337)
_    _(SumaCom3.Semisum1.SUM=S3)
_    _(SumaCom3.Semisum1.SUM0=SumaCom3_N00170)
_    _(SumaCom3.Semisum1.SUM1=N00908)
_    SumaCom3.Semisum(SUM0=A3 SUM1=N00555 SUM=SumaCom3_N00170 CARRY=SumaCom3_N00250 ) CN 
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom3@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1)
X_SumaCom3_Semisum_U2A          SumaCom3.Semisum.U2A(A=A3 B=N00555 Y=SumaCom3_N00170 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom3@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1):INS208@74LS.74LS86A.Normal(chips)
X_SumaCom3_Semisum_U1A          SumaCom3.Semisum.U1A(A=N00555 B=A3 Y=SumaCom3_N00250 VCC=$G_DPWR GND=$G_DGND ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):SumaCom3@PRACTICA4.SumaCom(sch_1):Semisum@PRACTICA4.SemiSum(sch_1):INS80@74LS.74LS08.Normal(chips)
_    _(SumaCom3.Semisum.CARRY=SumaCom3_N00250)
_    _(SumaCom3.Semisum.SUM=SumaCom3_N00170)
_    _(SumaCom3.Semisum.SUM0=A3)
_    _(SumaCom3.Semisum.SUM1=N00555)
_    _(SumaCom3.CIN=N00908)
_    _(SumaCom3.COUT=C4)
_    _(SumaCom3.S0=A3)
_    _(SumaCom3.S1=N00555)
_    _(SumaCom3.Suma=S3)
U_DSTM1          DSTM1(VCC=$G_DPWR GND=$G_DGND OUT0=A3 OUT1=A2 OUT2=A1 OUT3=A0 ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):INS200@SOURCSTM.DigStim4.Normal(chips)
U_DSTM2          DSTM2(VCC=$G_DPWR GND=$G_DGND OUT0=B3 OUT1=B2 OUT2=B1 OUT3=B0 ) CN
+@PRACTICA4.SCHEMATIC1(sch_1):INS222@SOURCSTM.DigStim4.Normal(chips)
U_DSTM3          DSTM3(VCC=$G_DPWR GND=$G_DGND OUT=M ) CN @PRACTICA4.SCHEMATIC1(sch_1):INS457@SOURCSTM.DigStim1.Normal(chips)
X_U1A           U1A(A=B3 B=M Y=N00555 VCC=$G_DPWR GND=$G_DGND ) CN @PRACTICA4.SCHEMATIC1(sch_1):INS510@74LS.74LS86A.Normal(chips)
X_U1B           U1B(A=B0 B=M Y=N01110 VCC=$G_DPWR GND=$G_DGND ) CN @PRACTICA4.SCHEMATIC1(sch_1):INS1008@74LS.74LS86A.Normal(chips)
X_U1C           U1C(A=B1 B=M Y=N01230 VCC=$G_DPWR GND=$G_DGND ) CN @PRACTICA4.SCHEMATIC1(sch_1):INS1249@74LS.74LS86A.Normal(chips)
X_U1D           U1D(A=B2 B=M Y=N01472 VCC=$G_DPWR GND=$G_DGND ) CN @PRACTICA4.SCHEMATIC1(sch_1):INS1387@74LS.74LS86A.Normal(chips)
_    _(A0=A0)
_    _(A1=A1)
_    _(A2=A2)
_    _(A3=A3)
_    _(B0=B0)
_    _(B1=B1)
_    _(B2=B2)
_    _(B3=B3)
_    _(C4=C4)
_    _(M=M)
_    _(S0=S0)
_    _(S1=S1)
_    _(S2=S2)
_    _(S3=S3)
.ENDALIASES
