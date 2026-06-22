
    #include "kernel.h"
    #include "kernel_id.h"
    #include "ecrobot_interface.h"
    #define velocidadInicialB 50 //M30
    #define velocidadInicialC 50 //M2

    /*--------------------------------------------------------------------------*/
    /* OSEK declarations                                                        */
    /*--------------------------------------------------------------------------*/
    DeclareTask(Avance);
    DeclareTask(Final);
    DeclareTask(Calibrar);
    DeclareCounter(contador);
    DeclareAlarm(alarma);

    /*--------------------------------------------------------------------------*/
    /* Definitions                                                              */
    /*--------------------------------------------------------------------------*/
    //int velocidadB = 100;
    //int velocidadC = 100;

    int velocidadB = velocidadInicialB;
    int velocidadC = velocidadInicialC;
    /*--------------------------------------------------------------------------*/
    /* Function to be invoked from a category 2 interrupt                       */
    /*--------------------------------------------------------------------------*/
    void user_1ms_isr_type2(){
        SignalCounter(contador);
    }

    /*--------------------------------------------------------------------------*/
    /* Task information:                                                        */
    /* -----------------                                                        */
    /* Name    : Avance                                                         */
    /* Priority: 1                                                              */
    /* Typ     : EXTENDED TASK                                                  */
    /* Schedule: FULL                                                           */
    /* Objective: Hacer que el robot avance, activa motores                     */
    /*--------------------------------------------------------------------------*/
    TASK(Avance)
    {
        systick_wait_ms(3000);

        // Activa motores para comprobar si existe desvio en la navegacion
        nxt_motor_set_speed(NXT_PORT_B, velocidadB, 1);
        nxt_motor_set_speed(NXT_PORT_C, velocidadC, 1);

        // Espera hasta que se agote el time_out
        systick_wait_ms(9000);


        // Despierta la tarea de parada de motores
        ChainTask(Final);

        // Termina la tarea actual
        TerminateTask();
    }
    
    
    /*--------------------------------------------------------------------------*/
    /* Task information:                                                        */
    /* -----------------                                                        */
    /* Name    : Calibrar                                                       */
    /* Priority: 2                                                              */
    /* Typ     : EXTENDED TASK                                                  */
    /* Schedule: FULL                                                           */
    /* Objective: Función que calibra los motores para corregir desvío          */
    /*--------------------------------------------------------------------------*/
    TASK(Calibrar)
    {
        int rpmB = nxt_motor_get_count(NXT_PORT_B);
        int rpmC = nxt_motor_get_count(NXT_PORT_C);

        int margen = 5;

        if(rpmB < rpmC) {
            if(velocidadB < velocidadInicialB + margen)
                velocidadB++;
            else
                velocidadC--;
            nxt_motor_set_speed(NXT_PORT_B, velocidadB, 1);
            nxt_motor_set_speed(NXT_PORT_C, velocidadC, 1);
        }

        if(rpmC < rpmB) {
            if(velocidadC < velocidadInicialC + margen)
                //velocidadC=velocidadC+2;
                velocidadC++;
            else
                //velocidadB=velocidadB-2;
                velocidadB--;
            nxt_motor_set_speed(NXT_PORT_B, velocidadB, 1);
            nxt_motor_set_speed(NXT_PORT_C, velocidadC, 1);
        }

        nxt_motor_set_count(NXT_PORT_B, 0);
        nxt_motor_set_count(NXT_PORT_C, 0);


        TerminateTask();
    }

    /*--------------------------------------------------------------------------*/
    /* Task information:                                                        */
    /* -----------------                                                        */
    /* Name    : Final                                                          */
    /* Priority: 3                                                              */
    /* Typ     : EXTENDED TASK                                                  */
    /* Schedule: FULL                                                           */
    /* Objective: Para los motores y cancela todas las alarmas                  */
    /*--------------------------------------------------------------------------*/
    TASK(Final)
    {

      int rpmB = nxt_motor_get_count(NXT_PORT_B);
      int rpmC = nxt_motor_get_count(NXT_PORT_C);

      display_goto_xy(0,0);
      display_unsigned(rpmB, 6);
      display_unsigned(rpmC, 6);
      display_goto_xy(0,5);
      display_unsigned(velocidadB, 3);
      display_unsigned(velocidadC, 3);
      display_update();

      // Para los motores
      nxt_motor_set_speed(NXT_PORT_B, 0, 1);
      nxt_motor_set_speed(NXT_PORT_C, 0, 1);

      CancelAlarm(alarma);

      // Termina la tarea actual
      TerminateTask();

    }
