
start_section  start_processor :
      partition_clock : clock:=0;
end section;
   

automaton_section  processor_scheduler :
   Schedule_Partition2 : initial_state;
   Schedule_Partition1 : state;
   Restart : state;
      
  transition Schedule_Partition2 ==> [ ,  , wakeup2?] 
             ==> Schedule_Partition1;
  transition Schedule_Partition1 ==> [partition_clock = 6 , , wakeup1?] 
             ==> Restart ;
  transition Restart ==> [partition_clock = 10 ,  partition_clock:=0; ,] ==> Schedule_Partition2;
end section;
   