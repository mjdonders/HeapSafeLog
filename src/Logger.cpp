#include "Logger.h"

namespace MDO {

void Logger::printWithPadding(uint64_t uiVal, int iWidth, int iBase) {
	if (m_pLog == nullptr) {
		return;
	}
	
	char buf[65]; //should be sufficient for a 64 bit number
	char* p = buf + sizeof(buf) - 1;
	*p = '\0';

	do {
		int iDigit = uiVal % iBase;
		*(--p) = (iDigit < 10) ? ('0' + iDigit) : ('A' + iDigit - 10);
		uiVal /= iBase;
	} while (uiVal > 0);

	int len = (buf + sizeof(buf) - 1) - p;
	while (len < iWidth) {
		m_pLog->print('0');
		iWidth--;
	}

	m_pLog->print(p);	
}

bool Logger::shouldLog(LogLevel eLevel) const {

	if ((m_pLog == nullptr) || (m_eMinLogLevel == LogLevel::None)) {
		return false;
	}
    return static_cast<uint8_t>(eLevel) >= static_cast<uint8_t>(m_eMinLogLevel);
}

void Logger::setMinLogLevel(LogLevel eLevel) {
	m_eMinLogLevel = eLevel;
}

void Logger::begin(HardwareSerial& oSerialPort, uint32_t uiBaud) {
	oSerialPort.begin(uiBaud);
	begin(oSerialPort);	
}

//so this can also be used like:
//   WiFiClient client;
//   logger().begin(client);
// or
//   File file = SD.open("log.txt");
//   logger().begin(file);
//
//use this method when the above begin provides the following: error: cannot convert 'HWCDC' to 'HardwareSerial&'
//in this case, do Serial.begin(115200) first, and call this begin after.
void Logger::begin(Print& output) {
    m_pLog = &output;
}

/*static*/ Logger& Logger::instance() {
	static Logger log;
	return log;
}

Logger::Logger() {
	m_pLog = nullptr;
	m_eMinLogLevel = static_cast<LogLevel>(MDO_LOG_LEVEL);
}

Logger::~Logger() {
}

}	//namespace end