


start_section :
	p : array (tasks_range) of integer;
	i : integer;
end section;


priority_section :
	for i in tasks_range loop
		p(i):= tasks.rest_of_capacity(i)/tasks.v(i);
	end loop;
end section;


election_section :
	return min_to_index(p);
end section;

