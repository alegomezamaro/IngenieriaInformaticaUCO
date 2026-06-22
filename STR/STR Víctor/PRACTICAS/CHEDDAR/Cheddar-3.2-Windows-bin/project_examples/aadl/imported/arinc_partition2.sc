
start_section  start2 :
   partition2_capacity : integer := 6;
   partition2_duration : clock := 0; 
end section;
 

election_section  partition2_election :
   return min_to_index(tasks.priority);
end section;


automaton_section  partition2_scheduler  :
  Ready : state;
  Pended : initial_state;
    
  transition Pended ==> [ , partition2_duration:=0; ,wakeup2!] ==> Ready;
  transition Ready ==> [ partition2_duration < partition2_capacity, , partition2_election!] ==> Ready;
  transition Ready ==> [partition2_duration=partition2_capacity,  , ] ==> Pended;
end section;
   
