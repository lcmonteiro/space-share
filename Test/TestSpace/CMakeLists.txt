cmake_minimum_required (VERSION 3.10)
#
# add
# 
set(sources
    "TestKernel/TestVariable.cpp"
)
set(targets 
    SpaceKernel
)
add_gtests(TestKernel "TestKernel/TestVariable.cpp" SpaceKernel)