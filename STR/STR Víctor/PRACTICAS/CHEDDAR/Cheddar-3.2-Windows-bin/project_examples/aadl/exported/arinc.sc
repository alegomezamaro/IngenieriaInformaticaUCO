--!TRACE

start_section :

	partition_duration :  array (tasks_range) of integer;
	dynamic_priority :  array (tasks_range) of integer;
	number_of_partition : integer :=2;
	current_partition : integer :=0;
	time_partition : integer :=0;
	i : integer;

	partition_duration(0):=2;
	partition_duration(1):=4;
	time_partition:=partition_duration(current_partition);
	dynamic_priority:=0;

end section;

priority_section :

	if time_partition=0
		then  current_partition:=(current_partition+1) mod number_of_partition;
		      time_partition:=partition_duration(current_partition);
	end if;
	

	for i in  tasks_range loop
		if tasks.task_partition(i)=current_partition
                  then dynamic_priority(i):=tasks.priority(i);  
                  else dynamic_priority(i):=0;
                       tasks.ready(i):=false;              
		end if;
     end loop;
	time_partition:=time_partition-1;

end section;

election_section :

     return max_to_index(dynamic_priority);

end section;


