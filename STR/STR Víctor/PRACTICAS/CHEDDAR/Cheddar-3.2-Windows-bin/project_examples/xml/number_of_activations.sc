

start_section :
	id : integer;
	number_of_activation : array (tasks_range) of integer;
	number_of_activation:=0;
end section;

gather_event_analyzer_section :
	if events.type = "task_activation"
		then	
		id := get_task_index(events.task_name);
		number_of_activation(id):=number_of_activation(id)+1;
	end if;
end section;


display_event_analyzer_section :
	put(tasks.name,0,2);		
	put(number_of_activation,0,2);		
end section;

