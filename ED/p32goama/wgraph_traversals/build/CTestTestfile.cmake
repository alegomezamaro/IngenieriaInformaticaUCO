# CMake generated Testfile for 
# Source directory: /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals
# Build directory: /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestDeepFirst "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/build//test_traversals" "01_tests_df")
set_tests_properties(TestDeepFirst PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/CMakeLists.txt;27;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/CMakeLists.txt;0;")
add_test(TestBreathFirst "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/build//test_traversals" "02_tests_bf")
set_tests_properties(TestBreathFirst PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/CMakeLists.txt;28;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/CMakeLists.txt;0;")
add_test(TestTopologicalSorting "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/build//test_traversals" "03_tests_ts")
set_tests_properties(TestTopologicalSorting PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/CMakeLists.txt;29;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/CMakeLists.txt;0;")
add_test(TestPrim "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/build//test_traversals" "04_tests_prim")
set_tests_properties(TestPrim PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/CMakeLists.txt;30;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/CMakeLists.txt;0;")
add_test(TestKruskal "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/build//test_traversals" "05_tests_kruskal")
set_tests_properties(TestKruskal PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/CMakeLists.txt;31;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/wgraph_traversals/CMakeLists.txt;0;")
subdirs("graph")
