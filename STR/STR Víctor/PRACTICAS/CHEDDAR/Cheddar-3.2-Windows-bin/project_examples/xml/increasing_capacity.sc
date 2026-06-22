
start_section :
	i : integer;
end section;

priority_section :
     for i in tasks_range loop
		if (tasks.rest_of_capacity(i) = 1)
			and (tasks.name(i) = "T1")
			then tasks.capacity(i):=tasks.capacity(i)+1;
		end if;
     end loop;
     put(tasks.capacity,0,2);
end section;

election_section :
        return min_to_index(tasks.period);
end section;



