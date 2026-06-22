
start_section :
        T1_id : integer := get_task_index("cyclic.impl.ea.t1");
        T2_id : integer := get_task_index("cyclic.impl.ea.t2");

	to_run : integer;
	i : integer;
	size : integer;
	schedule : array (time_units_range) of integer;

	dynamic_priority : array (tasks_range) of integer;
	
	schedule(0):=T1_id;
	schedule(1):=T2_id;
	schedule(2):=T1_id;
	size:=3;
	i:=0;
end section;


election_section :
        return max_to_index(dynamic_priority);
end section;


priority_section :

	dynamic_priority:=0; 

	dynamic_priority(schedule(i)):=1;
        put(dynamic_priority,0,10);

	i:=i+1;
	if (i = size-1)
	   then i:=0;
	end if;
end section;



