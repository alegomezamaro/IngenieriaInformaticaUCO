

start_section :
        arrived_at : array (tasks_range) of integer;
end section;

priority_section :
        arrived_at := tasks.start_time
                + ((tasks.activation_number-1)*tasks.period;
end section;
               

election_section :
        return min_to_index(arrived_at);
end section;



