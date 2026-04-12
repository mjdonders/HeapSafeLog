
#include <HeapSafeLog.h>

void setup() {
	MDO::logger().begin(Serial, 115200);

	MDO::logger().println("Hello world!");							//just one parameter
	MDO::logger().println("Hello", " ", "world", "!", 42);			//several parameters, other data types
	
	//some formatting options:
	MDO::logger().println();
	MDO::logger().println("Formatting output, hex:");
	MDO::logger().println("  ", MDO::hex(42));						//print the number 42 as it's hex value
	MDO::logger().println("  ", MDO::hex(42, 2));					//print the number 42 as it's hex value, alligned to ensure at least two numbers
	MDO::logger().println("  ", MDO::hex(6, 2));					//print the number 6 as it's hex value, alligned to ensure at least two numbers
	uint16_t uiTest = 1234;
	MDO::logger().println("  Variable value: ", MDO::hex(uiTest));	//expected typical usage
	
	MDO::logger().print("  Variable value: ");						//or using print and println, with same result
	MDO::logger().println(MDO::hex(uiTest));
	
	uint64_t uiBigTest1	=  18274613875;	//        4 4140 7A73
	uint64_t iBigTest2	= -18274613875;	//FFFF FFFB BEBF 858D
	MDO::logger().println("  ", MDO::hex(uiBigTest1, 16));
	MDO::logger().println("  ", MDO::hex(iBigTest2,  16));
	
	
	MDO::logger().println();
	MDO::logger().println("Formatting output, decimal:");	
	MDO::logger().println("  ", MDO::dec(  6, 2));
	MDO::logger().println("  ", MDO::dec( 42, 2));
	MDO::logger().println("  ", MDO::dec(123, 2));					//to show it does not always align: the '2' is a minimum amount of characters

	MDO::logger().println();
	MDO::logger().println("Formatting output, floating point:");
	double dTest = 3.14159265;
	MDO::logger().println("  ", dTest);								//without formatter, defaulting to standard Arduino output
	MDO::logger().println("  ", MDO::f(dTest, 1));					//with formatter, the '1' is the amount of numbers after the '.' (so 3.1 in this case)
	MDO::logger().println("  ", MDO::f(dTest, 4));					//with formatter (giving 3.1416)
}

void loop() {
}