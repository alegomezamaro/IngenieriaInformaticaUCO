


start_section :

        i           : integer;
        nb_T2       : integer;
        nb_T1           : integer;
        bound_on_jitter : integer;
        max_delay       : integer;
        min_delay       : integer;
        tmp             : integer;
        T1_end_time     : array (time_units_range) of integer;
        T2_end_time     : array (time_units_range) of integer;

        min_delay:=integer'last;
        max_delay:=integer'first;
        i:=0;
        nb_T1:=0; nb_T2:=0;

end section;


gather_event_analyzer_section :

        if (events.type = "end_of_task_capacity")
		then
			if (events.task_name = "T1")
				then	
                                T1_end_time(nb_T1):=events.time;
				nb_T1:=nb_T1+1;
			end if;
			if (events.task_name = "T2")
				then	
                                T2_end_time(nb_T2):=events.time;
				nb_T2:=nb_T2+1;
			end if;
	    end if;

end section;


display_event_analyzer_section :
              
      while (i<nb_T1) and (i<nb_T2) loop
            tmp:=abs(T1_end_time(i)-T2_end_time(i));
            min_delay:=min(tmp, min_delay);
            max_delay:=max(tmp, max_delay);  
	    i:=i+1;
      end loop;
      bound_on_jitter:=abs(max_delay-min_delay);        

      put(min_delay);
      put(max_delay);
      put(bound_on_jitter);     


end section;
