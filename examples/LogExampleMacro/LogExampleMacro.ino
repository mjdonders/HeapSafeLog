
//This is the macro-based example
//it has as main benefit that it can easily be disabled with the above MDO_LOG_LEVEL
//any call to a non-relevant-level will also *not* be compiled, providing "zero-overhead logging"

//It's advised to put the following two statements in a dedicated header file in your sketch (example: log.h)
//If this is put in each C++ (or .ino) file it will be 'ambigious' what log level is used (since this is a singleton, there can only be one)
#define MDO_LOG_LEVEL MDO_LOG_LEVEL_WARN	
#include <HeapSafeLog.h>					

void setup() {
	MDO::logger().begin(Serial, 115200);
	
	MDO_WARN("Starting program");	//is printed
	MDO_INFO("Starting program2");	//is not printed (nor part of the final binary)
	
	//proving that it's not compiled, 'note' is undefined after all
	MDO_DEBUG("If the above stays at WARN, this will not be visible nor compiled", 6, note);
	
	//and a more typical call, with several parameters
	MDO_ERROR("This is a fake error, with value: ", 6, " and also multiple parameters, like: ", 2.0f);

	//and a new line, only affected by the MDO_LOG_LEVEL when that is not LogLevel::None
	MDO::logger().println("New line");
	
	MDO::logger().setMinLogLevel(MDO::Logger::LogLevel::None);
	MDO::logger().println("This will *not* be printed");			//unlike the above on line 15, this will be compiled though
	
	
	MDO::logger().setMinLogLevel(MDO::Logger::LogLevel::Info);		//revert to loglevel 'info'
	MDO_WARN("done..");												//and show that that creates output
}


void loop() {
}