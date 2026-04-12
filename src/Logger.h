#ifndef _MDO_HeapSafeLog_Logger_H
#define _MDO_HeapSafeLog_Logger_H

#include <Arduino.h>
#include <type_traits>

#define MDO_LOG_LEVEL_DEBUG 0
#define MDO_LOG_LEVEL_INFO  1
#define MDO_LOG_LEVEL_WARN  2
#define MDO_LOG_LEVEL_ERROR 3
#define MDO_LOG_LEVEL_NONE  4

#ifndef MDO_LOG_LEVEL
#warning "MDO_LOG_LEVEL not defined, defaulting to DEBUG"
#define MDO_LOG_LEVEL MDO_LOG_LEVEL_DEBUG
#endif

#if MDO_LOG_LEVEL <= MDO_LOG_LEVEL_DEBUG
  #define MDO_DEBUG(...) MDO::logger().debug(__VA_ARGS__)
#else
  #define MDO_DEBUG(...)
#endif

#if MDO_LOG_LEVEL <= MDO_LOG_LEVEL_INFO
  #define MDO_INFO(...) MDO::logger().info(__VA_ARGS__)
#else
  #define MDO_INFO(...)
#endif

#if MDO_LOG_LEVEL <= MDO_LOG_LEVEL_WARN
  #define MDO_WARN(...) MDO::logger().warn(__VA_ARGS__)
#else
  #define MDO_WARN(...)
#endif

#if MDO_LOG_LEVEL <= MDO_LOG_LEVEL_ERROR
  #define MDO_ERROR(...) MDO::logger().error(__VA_ARGS__)
#else
  #define MDO_ERROR(...)
#endif

namespace MDO {
	
	
// Wrappers
template<typename T>
struct Hex {
    T value;
    int width;
};

template<typename T>
struct Dec {
    T value;
    int width;
};

template<typename T>
Hex<T> hex(T v, int w = 0) { return {v, w}; }

template<typename T>
Dec<T> dec(T v, int w = 0) { return {v, w}; }

template<typename T>
using is_integer = std::is_integral<typename std::decay<T>::type>;

struct Float {
    double value;	//keep double since this is used internally in Arduino framework anyhow
    int precision;
};

inline Float f(double v, int prec = 2) { return {v, prec}; }

class Logger;

/**
 * Interface class used to be able to print 'all' (which obeys this interface)
 */
class Printable {
	public:
		virtual void printTo(Logger& oLogSink) const = 0;
};

/**
 * Logger class.
 * Does not rely on String and also has some variadic options
 */ 
class Logger {

	public: // types
		enum class LogLevel : uint8_t {
			Debug	= MDO_LOG_LEVEL_DEBUG,
			Info	= MDO_LOG_LEVEL_INFO,
			Warn	= MDO_LOG_LEVEL_WARN,
			Error	= MDO_LOG_LEVEL_ERROR,
			None	= MDO_LOG_LEVEL_NONE
		};

	private:
		Print*   m_pLog;
		LogLevel m_eMinLogLevel;

	private:
		void printWithPadding(uint64_t uiVal, int iWidth, int iBase);

		bool shouldLog(LogLevel eLevel) const;

		//overload for Printable
		void writeOne(const MDO::Printable& value) {
			print(value);
		}
		
		//hexadecimal integer types
		template<typename T>
		typename std::enable_if<is_integer<T>::value, void>::type
		writeOne(Hex<T> h) {
			using U = typename std::make_unsigned<typename std::decay<T>::type>::type;
			printWithPadding(static_cast<U>(h.value), h.width, 16);
		}
		
		//decimal integer types
		template<typename T>
		typename std::enable_if<is_integer<T>::value, void>::type
		writeOne(Dec<T> d) {
			if (d.value < 0) {
				m_pLog->print('-');
				printWithPadding(static_cast<uint64_t>(-d.value), d.width, 10);
			} else {
				printWithPadding(static_cast<uint64_t>(d.value), d.width, 10);
			}
		}
		
		//floating point
		void writeOne(Float fval) {
			m_pLog->print(fval.value, fval.precision);
		}		

		//overload for everything else
		template<typename T>
		typename std::enable_if<
			!std::is_base_of<MDO::Printable, typename std::decay<T>::type>::value,
			void
		>::type
		writeOne(T&& value) {
			m_pLog->print(std::forward<T>(value));
		}

		//variadic expansion
		template<typename First, typename... Rest>
		void writeAll(First&& first, Rest&&... rest) {
			writeOne(std::forward<First>(first));
			writeAll(std::forward<Rest>(rest)...);
		}

		void writeAll() {} // base case

	public:

		//log level APIs
		template<typename... Args>
		void debug(Args&&... args) {
			if (shouldLog(LogLevel::Debug)) {
				writeAll(std::forward<Args>(args)...);
				m_pLog->println();
			}
		}

		template<typename... Args>
		void info(Args&&... args) {
			if (shouldLog(LogLevel::Info)) {
				writeAll(std::forward<Args>(args)...);
				m_pLog->println();
			}
		}

		template<typename... Args>
		void warn(Args&&... args) {
			if (shouldLog(LogLevel::Warn)) {
				writeAll(std::forward<Args>(args)...);
				m_pLog->println();
			}
		}

		template<typename... Args>
		void error(Args&&... args) {
			if (shouldLog(LogLevel::Error)) {
				writeAll(std::forward<Args>(args)...);
				m_pLog->println();
			}
		}

		//Printable support
		void print(const MDO::Printable& oToPrint) {
			oToPrint.printTo(*this);
		}

		void println(const MDO::Printable& oToPrint) {
			if ((m_pLog) && (m_eMinLogLevel != LogLevel::None)) {
				print(oToPrint);
				m_pLog->println();
			}
		}

		//generic print
		template<typename... Args>
		void print(Args&&... args) {
			if ((m_pLog) && (m_eMinLogLevel != LogLevel::None)) {
				writeAll(std::forward<Args>(args)...);
			}
		}

		template<typename... Args>
		void println(Args&&... args) {
			if ((m_pLog) && (m_eMinLogLevel != LogLevel::None)) {
				writeAll(std::forward<Args>(args)...);
				m_pLog->println();
			}
		}

		void			setMinLogLevel(LogLevel eLevel);
		void			begin(HardwareSerial& oSerialPort, uint32_t uiBaud);
		void			attach(Print& output);
		static Logger&	instance(); 
	
	private:
		Logger();
	public:
		virtual ~Logger();
};

	//for convenience
	inline Logger& logger() {
		return Logger::instance();
	}

	//can ease debugging: wait for a serial command to start/continue with our program
	inline void debugWaitForStart(HardwareSerial& oSerialPort, unsigned long ulMaxTimeout = 10000, char cStartCharacter = 's') {
		bool bDone = false;
		const unsigned long ulStart = millis();
		while (!bDone) {
			if (oSerialPort.available() > 0) {
				char cIncoming = oSerialPort.read();
				bDone = cIncoming == cStartCharacter;
			} else {
				delay(1);
			}
			
			if (!bDone) {
				//since this is typically used after a boot, no need to check for overflow..
				bDone = (millis() - ulStart) > ulMaxTimeout;
			}
		}
	}
	
}	//namespace end

#endif