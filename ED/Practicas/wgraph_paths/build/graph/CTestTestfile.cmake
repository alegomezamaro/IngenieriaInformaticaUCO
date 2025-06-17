# CMake generated Testfile for 
# Source directory: /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph
# Build directory: /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/build/graph
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestVertex "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/build/graph//test_vertex" "00_tests_vertex")
set_tests_properties(TestVertex PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph/CMakeLists.txt;26;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph/CMakeLists.txt;0;")
add_test(TestEdge "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/build/graph//test_edge" "01_tests_edge")
set_tests_properties(TestEdge PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph/CMakeLists.txt;27;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph/CMakeLists.txt;0;")
add_test(TestGraph "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/build/graph//test_graph" "02_tests_graph")
set_tests_properties(TestGraph PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph/CMakeLists.txt;28;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph/CMakeLists.txt;0;")
add_test(TestGraphFoldUnfold "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/build/graph//test_graph" "03_tests_graph_fold_unfold")
set_tests_properties(TestGraphFoldUnfold PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph/CMakeLists.txt;29;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_paths/graph/CMakeLists.txt;0;")
