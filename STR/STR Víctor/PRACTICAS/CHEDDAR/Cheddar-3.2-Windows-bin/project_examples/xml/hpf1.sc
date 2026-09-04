

start_section :
          to_run : integer;
          current_priority : integer;
          i : integer;
end section;


priority_section :
          current_priority:=0;

          for i in tasks_range loop
		if tasks.ready(i)=true then
                   if tasks.priority(i)>current_priority
                          then to_run:=i;
                               current_priority:=tasks.priority(i);
		   end if;
                  end if;
	  end loop;
end section;


election_section :
          return to_run;
end section;

