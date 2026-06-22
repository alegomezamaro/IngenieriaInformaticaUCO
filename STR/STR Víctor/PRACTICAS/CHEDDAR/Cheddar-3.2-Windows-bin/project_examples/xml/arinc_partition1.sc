
start_section  start1 :
  partition1_capacity : integer := 4;
  partition1_duration : clock := 0;
  quantum : integer :=2;  
  my_prio : array (tasks_range) of integer;
  my_prio:=0;
end section;
 

priority_section partition1_priority :   
   quantum:=quantum-1;
   if quantum = 0
      then quantum:=2;
           my_prio(previously_elected):=my_prio(previously_elected)+1;
   end if; 
end section;
   

election_section partition1_election :
   return min_to_index(my_prio);
end section;



automaton_section  partition1_scheduler  :
  Pended : initial_state;
  Ready : state;
  Wait_Priority : state;
     
  transition Pended ==> [ , partition1_duration:=0;,wakeup1!] ==> Wait_Priority;
  transition Wait_Priority ==> [partition1_duration<partition1_capacity, , partition1_priority!] ==> Ready;
  transition Ready ==> [ ,  , partition1_election!] ==> Wait_Priority;
  transition Wait_Priority ==> [partition1_duration=partition1_capacity,  , ] ==> Pended;
end section;
