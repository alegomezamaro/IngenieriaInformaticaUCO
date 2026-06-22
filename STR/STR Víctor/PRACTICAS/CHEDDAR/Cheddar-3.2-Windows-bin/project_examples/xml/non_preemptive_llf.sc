
--!TRACE

start_section :
	dynamic_deadline : array (tasks_range) of integer;
	laxity           : array (tasks_range) of integer;
	to_run	     : integer;
	i		     : integer;
	min_laxity 	     : integer;
end section;

priority_section :
	dynamic_deadline := tasks.start_time
		+ ((tasks.activation_number-1)*tasks.period)
		+ tasks.deadline; 
	laxity:=dynamic_deadline-tasks.rest_of_capacity;


	min_laxity:=integer'last;
	for i in tasks_range loop
		if min_laxity > laxity(i)
			then if tasks.ready(i)=true
					then to_run:=i;
			             min_laxity:=laxity(i);
				  end if;	
		end if;
	end loop;


	if laxity(previously_elected)=min_laxity
		then to_run:=previously_elected;
	end if;
end section;

election_section :
        return to_run;
end section;




