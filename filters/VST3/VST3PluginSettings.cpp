/***
 *     ▄████▄  ▒██   ██▒ ██▒   █▓ █    ██   ██████ ▓█████  ██▀███
 *    ▒██▀ ▀█  ▒▒ █ █ ▒░▓██░   █▒ ██  ▓██▒▒██    ▒ ▓█   ▀ ▓██ ▒ ██▒
 *    ▒▓█    ▄ ░░  █   ░ ▓██  █▒░▓██  ▒██░░ ▓██▄   ▒███   ▓██ ░▄█ ▒
 *    ▒▓▓▄ ▄██▒ ░ █ █ ▒   ▒██ █░░▓▓█  ░██░  ▒   ██▒▒▓█  ▄ ▒██▀▀█▄
 *    ▒ ▓███▀ ░▒██▒ ▒██▒   ▒▀█░  ▒▒█████▓ ▒██████▒▒░▒████▒░██▓ ▒██▒
 *    ░ ░▒ ▒  ░▒▒ ░ ░▓ ░   ░ ▐░  ░▒▓▒ ▒ ▒ ▒ ▒▓▒ ▒ ░░░ ▒░ ░░ ▒▓ ░▒▓░
 *      ░  ▒   ░░   ░▒ ░   ░ ░░  ░░▒░ ░ ░ ░ ░▒  ░ ░ ░ ░  ░  ░▒ ░ ▒░
 *    ░         ░    ░       ░░   ░░░ ░ ░ ░  ░  ░     ░     ░░   ░
 *    ░ ░       ░    ░        ░     ░           ░     ░  ░   ░
 *    ░                      ░
 *
 *
 *	 VST3 pkugin wrapper
 *	 15 fev 2020
 */

#include "stdafx.h"
#include "VST3PluginSettings.h"

tresult PLUGIN_API VST3PluginSettings::read(void* buffer, int32 numBytes, int32* numBytesRead)
{
	if (buffer == NULL && numBytes == NULL)
		goto LEAVE_;
	if (!m_buf)
		goto LEAVE_;
	if (m_sk > numBytes)
		goto LEAVE_;
	if (numBytes > m_s)
		numBytes -= (numBytes - m_s);

	__try {
		memcpy(buffer, &m_buf[m_sk], numBytes);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		goto LEAVE_;
	}
	m_sk += numBytes;

	__try {
		if (numBytesRead)
			*numBytesRead = numBytes;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		goto LEAVE_;
	}

	return kResultTrue;

LEAVE_:
	return kResultFalse;
}

tresult PLUGIN_API VST3PluginSettings::write(void* buffer, int32 numBytes, int32* numBytesWritten) {
	if (buffer == NULL && numBytes == NULL)
		goto LEAVE_;

	m_buf = (char*)realloc(m_buf, numBytes + m_s);
	if (m_buf == NULL)
		goto LEAVE_;
	__try {
		memcpy(m_buf + m_sk, buffer, numBytes);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		goto LEAVE_;
	}

	m_s += numBytes;
	m_sk += numBytes;
	__try {
		if (numBytesWritten)
			*numBytesWritten = numBytes;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		goto LEAVE_;
	}
	return kResultTrue;

LEAVE_:
	return kResultFalse;
}

tresult PLUGIN_API VST3PluginSettings::seek(int64 pos, int32 mode, int64* result) {
	if (mode == kIBSeekSet)
		m_sk = pos;
	else if (mode == kIBSeekCur)
		m_sk += pos;
	else if (mode == kIBSeekEnd)
		m_sk = m_s;

	__try {
		if (result != 0)
			*result = m_sk;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return kResultFalse;
	}
	return kResultTrue;
}

tresult PLUGIN_API VST3PluginSettings::tell(int64* pos) {
	if (pos != 0) {
		__try {
			*pos = m_sk;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			goto LEAVE_;
		}
		return kResultTrue;
	}
LEAVE_:
	return kResultFalse;
}

tresult PLUGIN_API VST3PluginSettings::getStreamSize(int64& size) {
	if (&size != 0) {
		__try {
			size = m_s;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			goto LEAVE_;
		}
		return kResultTrue;
	}
LEAVE_:
	return kResultFalse;
}

tresult PLUGIN_API VST3PluginSettings::setStreamSize(int64 size) {
	m_s = size;
	return kResultTrue;
};