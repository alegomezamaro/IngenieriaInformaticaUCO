.ALIASES
X_U1A           U1A(A=N01368 B=N01368 Y=N01390 VCC=$G_DPWR GND=$G_DGND ) CN
+@S2.SCHEMATIC1(sch_1):INS1062@74ALS.74ALS00A.Normal(chips)
X_U1C           U1C(A=N00888 B=N00894 Y=N01368 VCC=$G_DPWR GND=$G_DGND ) CN
+@S2.SCHEMATIC1(sch_1):INS1150@74ALS.74ALS00A.Normal(chips)
X_U1D           U1D(A=N01390 B=N00914 Y=SALIDA VCC=$G_DPWR GND=$G_DGND ) CN
+@S2.SCHEMATIC1(sch_1):INS1198@74ALS.74ALS00A.Normal(chips)
U_A             A(VCC=$G_DPWR GND=$G_DGND OUT=N00888 ) CN @S2.SCHEMATIC1(sch_1):INS1478@SOURCSTM.DigStim1.Normal(chips)
U_B             B(VCC=$G_DPWR GND=$G_DGND OUT=N00894 ) CN @S2.SCHEMATIC1(sch_1):INS1510@SOURCSTM.DigStim1.Normal(chips)
U_C             C(VCC=$G_DPWR GND=$G_DGND OUT=N00914 ) CN @S2.SCHEMATIC1(sch_1):INS1542@SOURCSTM.DigStim1.Normal(chips)
_    _(SALIDA=SALIDA)
.ENDALIASES
