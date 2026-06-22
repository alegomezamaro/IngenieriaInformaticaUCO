

--!TRACE

start_section :
        mli : array (tasks_range) of integer;
	di  : array (tasks_range) of integer;
end section;


priority_section :
	di := tasks.start_time
                + ((tasks.activation_number-1)*tasks.period)
                + tasks.deadline; 
        mli :=(100*di)-(100*tasks.rest_of_capacity/2);
end section;


election_section :
        return min_to_index(mli);
end section;



