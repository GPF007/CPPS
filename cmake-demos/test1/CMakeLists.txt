cmake_minimum_required(VERSION 3.10) 

# set the project name 
project(Hello) 

#这条命令设置输出的目录
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#src
aux_source_directory(./src source)


# add the executable 
add_executable(hello ${source}) 

#链接库
target_link_libraries(hello -lpthread)