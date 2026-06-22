
start_section :
	dynamic_priority : array (tasks_range) of integer;
end section;
		

priority_section :
	dynamic_priority := tasks.start_time
		+ ((tasks.activation_number-1)*tasks.period)
		+ tasks.deadline; 
	put(dynamic_priority);
end section;

election_section :
	return min_to_index(dynamic_priority);
end section;


