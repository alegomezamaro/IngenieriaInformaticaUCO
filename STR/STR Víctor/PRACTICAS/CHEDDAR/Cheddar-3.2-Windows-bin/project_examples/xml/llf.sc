

--!TRACE

start_section :
      dynamic_deadline : array (tasks_range)  of integer;
      laxity           : array (tasks_range) of integer;
end section;

priority_section :
      dynamic_deadline := start_time
                + ((tasks.activation_number-1)*tasks.period)
                + tasks.deadline; 
      laxity:=dynamic_deadline-tasks.rest_of_capacity;
end section;


election_section :
      return min_to_index(laxity);
end section;




