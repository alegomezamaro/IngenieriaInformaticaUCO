

election_section  elect1 :
      return min_to_index(tasks.priority);
end section;

priority_section prio1 :
    put(tasks.period,0,4);
end section;

automaton_section automaton1 : 
  Compute_Priority : state;
  Choose_Task : initial_state;
      
  transition Compute_Priority ==> [ ,  , prio1!] ==> Choose_Task;
  transition Choose_Task ==> [ , , elect1!] ==> Compute_Priority;
end section;
