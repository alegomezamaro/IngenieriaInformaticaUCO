# CMake generated Testfile for 
# Source directory: /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree
# Build directory: /home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestCreateKDTree "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree/build//test_kdtree" "01_tests_create_kdtree")
set_tests_properties(TestCreateKDTree PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree/CMakeLists.txt;31;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree/CMakeLists.txt;0;")
add_test(TestKDTreeNearestL1 "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree/build//test_kdtree" "02_tests_find_nn_L1")
set_tests_properties(TestKDTreeNearestL1 PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree/CMakeLists.txt;32;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree/CMakeLists.txt;0;")
add_test(TestKDTreeNearestL2 "/usr/bin/python3" "run_tests.py" "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree/build//test_kdtree" "03_tests_find_nn_L2")
set_tests_properties(TestKDTreeNearestL2 PROPERTIES  WORKING_DIRECTORY "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree" _BACKTRACE_TRIPLES "/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree/CMakeLists.txt;33;add_test;/home/ale/Documents/GitHub/IngenieriaInformaticaUCO/ED/p32goama/kdtree/CMakeLists.txt;0;")
subdirs("pattern")
subdirs("binary_tree")
