CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(Multithreading)

file(GLOB all_libs 
	../boost_1_70_0/_BUILD/lib/*.a
)

ADD_EXECUTABLE(${PROJECT_NAME}
	"src/Basics.cpp"
	"src/Boost_1.cpp"
	"src/Boost_2.cpp"
)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC
	../boost_1_70_0/_BUILD/include
)	

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
	${all_libs}
	-lpthread
)
