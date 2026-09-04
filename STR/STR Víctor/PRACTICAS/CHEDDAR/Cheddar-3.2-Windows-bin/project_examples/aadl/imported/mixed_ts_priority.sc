--!TRACE

start_section :
	
      i : integer;
      gen1 : random;
      current_activation : integer;
      
      exponential(gen1, 10);
      current_activation:=integer'last;
      dynamic_priority : array (tasks_range) of integer;
      
end section;
      
priority_section :

      for i in tasks_range loop
		if tasks.activation_number(i) < current_activation 
                  then current_activation:=tasks.activation_number(i);          
		end if;
      end loop;
	

      dynamic_priority:=0;
      for i in tasks_range loop
            if tasks.activation_number(i)=current_activation
               then dynamic_priority(i):=tasks.priority(i);
            end if;
      end loop;

end section;


election_section :

      return max_to_index(dynamic_priority);

end section;



task_activation_section :

        set sporadic_activation max(tasks.period, gen1);
        set random_activation gen1;

end section;



