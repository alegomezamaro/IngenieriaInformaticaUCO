
start_section :
	my_activation_delay :   array (tasks_range) of integer;
	my_activation_delay:=5;
end section;


priority_section :
	-- Each time a task ends an activation,
	-- the activation delay has to be increased
	--
	if tasks.rest_of_capacity(previously_elected) = 1
		then
		my_activation_delay(previously_elected):=
               	my_activation_delay(previously_elected)+5;
	end if;
end section;
	

election_section :
        return max_to_index(tasks.priority);
end section;


task_activation_section :
        set activation_rule1 my_activation_delay;
end section;


