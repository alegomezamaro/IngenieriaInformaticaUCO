
start_section :

	gen1 : random;
	gen2 : random;
	exponential(gen1, 200);
	uniform(gen2, 0, 100);

end section;


election_section :

     return max_to_index(tasks.priority);

end section;

task_activation_section :

        set activation_rule1 10;
        set activation_rule2 2*tasks.capacity;
        set activation_rule3 gen1*20;
        set activation_rule4 gen2;

end section;


