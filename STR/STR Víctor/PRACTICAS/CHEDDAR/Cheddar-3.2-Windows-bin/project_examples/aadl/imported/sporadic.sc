
start_section :
	
	gen1 : random;
	exponential(gen1, 10);

end section;

election_section :

        return max_to_index(tasks.priority);

end section;

task_activation_section :

        set sporadic_activation max(tasks.period, gen1);
        set random_activation gen1;

end section;
