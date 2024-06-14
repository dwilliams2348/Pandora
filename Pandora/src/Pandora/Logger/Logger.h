#pragma once

#include <cstdio>
#include <mutex>
#include <ctime>
#include <stdarg.h>

class Logger {
public:
	Logger()
		: mPriority(Logger::Priority::TracePriority), mInitialString(""), mFilepath(nullptr), mFile(nullptr), mTimeBuffer(), mTimestampFormat("%c") {}

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	~Logger() { FreeFile(); }

	/*
	* @brief Priority of the logger, if info is selected then priority of info and above will be displayed
	*/
	enum Priority {
		TracePriority = 0,
		DebugPriority = 1,
		InfoPriority = 2,
		WarnPriority = 3,
		ErrorPriority = 4,
		FatalPriority = 5
	};

	/*
	* @brief Set the priority to the given value.
	* @param priority: new priority
	*/
	void SetPriority(Priority priority) { mPriority = priority; }

	/*
	* @brief Returns the current priority
	*/
	const Priority GetPriority() const { return mPriority; }

	/*
	* @brief Setting this will print out the given string everyline after the timestamp and message priority
	*/
	void SetInitialString(const char* string) { mInitialString = string; }

	/*
	* @brief Returns the current initial string
	*/
	const char* GetInitialString() const { return mInitialString; }

	/*
	* Enables file output
	* Logs will be written to /log.txt
	* If the file doesn't exist, it will be created
	* File will be closed when program stops
	* Returns true if a file was successfully opened, false otherwise
	* 
	* @brief If called and successful, then the logs are written to /log.txt
	* @return Returns true if file was successfully opened
	*/
	bool OutputToFile() {
		mFilepath = "log.txt";
		return EnableFileOutput();
	}

	/*
	* Enables file output
	* Logs will be written to /log.txt
	* If the file doesn't exist, it will be created
	* File will be closed when program stops
	* Returns true if a file was successfully opened, false otherwise
	*/
	bool OutputToFile(const char* filepath) {
		mFilepath = filepath;
		return EnableFileOutput();
	}

	//If output to file was called and no filename was specified, then it will return "log.txt" which is in the working directory.
	const char* GetFilepath() const { return mFilepath; }

	//Format follows <ctime> strftime format specification
	void SetTimestampFormat(const char* timestampFormat) { mTimestampFormat = timestampFormat; }

	//Format follows <ctime> strftime format specification
	const char* GetTimestampFormat() const { return mTimestampFormat; }

	//Log a message (format + optional args, follow printf specification)
	//with a log priority of Trace
	template<typename...Args>
	void Trace(const char* msg, Args&&...args) {
		Log(TracePriority, msg, args...);
	}

	//Log a message (format + optional args, follow printf specification)
	//with a log priority of Debug
	template<typename...Args>
	void Debug(const char* msg, Args&&...args) {
		Log(DebugPriority, msg, args...);
	}

	//Log a message (format + optional args, follow printf specification)
	//with a log priority of Info
	template<typename...Args>
	void Info(const char* msg, Args&&...args) {
		Log(InfoPriority, msg, args...);
	}

	//Log a message (format + optional args, follow printf specification)
	//with a log priority of Warn
	template<typename...Args>
	void Warn(const char* msg, Args&&...args) {
		Log(WarnPriority, msg, args...);
	}

	//Log a message (format + optional args, follow printf specification)
	//with a log priority of Error
	template<typename...Args>
	void Error(const char* msg, Args&&...args) {
		Log(ErrorPriority, msg, args...);
	}

	//Log a message (format + optional args, follow printf specification)
	//with a log priority of Fatal
	template<typename...Args>
	void Fatal(const char* msg, Args&&...args) {
		Log(FatalPriority, msg, args...);
	}

private:
	void FreeFile() {
		if (mFile) {
			std::fclose(mFile);
			mFile = 0;
		}
	}

	bool EnableFileOutput() {
		FreeFile();
		mFile = std::fopen(mFilepath, "a");
		return (bool)mFile;
	}

	const char* MessagePriorityToString(Priority msgPriority) {
		const char* str;

		switch (msgPriority) {
		case Logger::TracePriority: str = "[Trace] "; break;
		case Logger::DebugPriority: str = "[Debug] "; break;
		case Logger::InfoPriority:	str = "[Info]  "; break;
		case Logger::WarnPriority:	str = "[Warn]  "; break;
		case Logger::ErrorPriority: str = "[Error] "; break;
		case Logger::FatalPriority: str = "[Fatal] "; break;
		default: str = "[none]  "; break;
		}

		return str;
	}

	void SetColor(Priority msgPriority) {
		const char* color;

		switch (msgPriority) {
		case Logger::TracePriority: color = mTraceColor; break;
		case Logger::DebugPriority: color = mDebugColor; break;
		case Logger::InfoPriority:	color = mInfoColor;  break;
		case Logger::WarnPriority:	color = mWarnColor;  break;
		case Logger::ErrorPriority: color = mErrorColor; break;
		case Logger::FatalPriority: color = mFatalColor; break;
		default: color = mNormalColor; break;
		}

		std::printf("%s", color);
	}

	void Log(Priority msgPriority, const char* msg, ...) {
		if (mPriority <= msgPriority) {
			std::time_t currentTime = std::time(0);
			std::tm* timestamp = std::localtime(&currentTime);

			std::scoped_lock lock(mLogMutex);

			SetColor(msgPriority);
			std::strftime(mTimeBuffer, 80, mTimestampFormat, timestamp);
			std::printf("%s ", mTimeBuffer);

			const char* msgPriorityStr = MessagePriorityToString(msgPriority);
			std::printf(msgPriorityStr, "%s");
			std::printf(mInitialString, "%s");
			va_list arglist;
			va_start(arglist, msg);
			std::vprintf(msg, arglist);
			va_end(arglist);
			std::printf("\n");

			std::printf("%s", mNormalColor);

			if (mFile) {
				std::fprintf(mFile, "%s ", mTimeBuffer);
				std::fprintf(mFile, "%s", msgPriorityStr);
				std::fprintf(mFile, "%s", mInitialString);
				va_start(arglist, msg);
				std::vfprintf(mFile, msg, arglist);
				va_end(arglist);
				std::fprintf(mFile, "\n");
			}
		}
	}
	
private:
	Priority mPriority;
	std::mutex mLogMutex;
	const char* mInitialString;
	char mTimeBuffer[80];
	const char* mTimestampFormat;
	const char* mFilepath;
	FILE* mFile;


	const char* mNormalColor = "\x1B[0m";
	const char* mTraceColor = "\x1b[38;5;249m";
	const char* mDebugColor = "\x1B[32m";
	const char* mInfoColor = "\x1b[34m";
	const char* mWarnColor = "\x1b[33m";
	const char* mErrorColor = "\x1B[31m";
	const char* mFatalColor = "\x1b[30;41m";
};