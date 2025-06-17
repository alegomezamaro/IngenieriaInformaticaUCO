# CMake generated Testfile for 
# Source directory: /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths
# Build directory: /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestDijkstra "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths/build//test_dijkstra" "01_tests_dijkstra")
set_tests_properties(TestDijkstra PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths/CMakeLists.txt;39;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths/CMakeLists.txt;0;")
add_test(TestFloyd "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths/build//test_floyd" "02_tests_floyd")
set_tests_properties(TestFloyd PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths/CMakeLists.txt;40;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths/CMakeLists.txt;0;")
add_test(TestAStar "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths/build//test_astar" "03_tests_astar")
set_tests_properties(TestAStar PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths/CMakeLists.txt;41;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/repaso/P6wgraph_paths/CMakeLists.txt;0;")
subdirs("priority_queue")
subdirs("graph")
subdirs("matrix")
