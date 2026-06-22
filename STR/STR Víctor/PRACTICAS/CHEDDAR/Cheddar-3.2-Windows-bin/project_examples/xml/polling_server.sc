
start_section  start1 :

  -- variables required to compute task priorities
  --
  current_priority : integer;
  task_to_elect : integer;
  i : integer;  

  -- have we some aperiodic tasks to run ?
  has_aperiodic : boolean;
  
  -- capacity remaining to be comsumed by the server 
  server_capacity : clock :=0;  

  -- Find the id of the task aperiodic server
  server_id : integer;
  server_id:= get_task_index("aperiodic_server"); 
  
end section;
    


automaton_section  polling_scheduler :

  -- First set of states : scheduling of aperiodic task
  --
  Run_Aperiodic : state;
  Compute_Aperiodic_Priorities : state;
  
  -- Second set of states : scheduling of periodic task
  --
  Run_Periodic : state;
  Compute_Periodic_Priorities : initial_state;





  -- Transitions for periodic task scheduling
  --     
  transition Compute_Periodic_Priorities ==> [,, 
      periodic_priority!] ==> Run_Periodic;
  transition Run_Periodic ==> [ task_to_elect/=server_id
     ,, 
     elect!] ==> Compute_Periodic_Priorities;
  

  -- Transitions for aperiodic task scheduling
  --
  transition Compute_Aperiodic_Priorities ==> [,,
      aperiodic_priority!] ==> Run_Aperiodic;
  transition Run_Aperiodic ==> [ 
         (has_aperiodic) 
     and (server_capacity<tasks.capacity(server_id)) 
     ,, 
     elect!] ==> Compute_Aperiodic_Priorities;
  

  -- Transitions between the two set of states
  --
  transition Run_Aperiodic ==> [ 
         (not has_aperiodic)
     or (server_capacity=tasks.capacity(server_id)) 
     ,, ] ==> Compute_Periodic_Priorities;
  transition Run_Periodic ==> [          
     task_to_elect=server_id, 
     server_capacity:=0; ,
        ] ==> Compute_Aperiodic_Priorities;

end section;




priority_section periodic_priority :
  current_priority:=integer'last;
  for i in tasks_range loop
		if (tasks.ready(i)=true) and (tasks.type(i) = "PERIODIC_TYPE")
               then 
                   if tasks.period(i) < current_priority  
                      then task_to_elect:=i;
                           current_priority:=tasks.period(i);    
                   end if;              
		end if;
  end loop;
end section;


priority_section aperiodic_priority :
  has_aperiodic:=false;
  current_priority:=0;
  for i in tasks_range loop
		if (tasks.ready(i)=true) and (tasks.type(i) = "APERIODIC_TYPE")
               then 
                   if tasks.priority(i) < current_priority  
                      then task_to_elect:=i;
                           current_priority:=tasks.priority(i);
                           has_aperiodic:=true;    
                   end if;              
		end if;
  end loop;
end section;


election_section elect :
   return task_to_elect;
end section;



