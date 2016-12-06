#ifndef __TS_THREAD_H__
#define __TS_THREAD_H__

#include <ex.h>
#include <list>

#ifdef EX_OS_WIN32
#	include <process.h>
typedef HANDLE TS_THREAD_HANDLE;
#else
#	include <pthread.h>
typedef pthread_t TS_THREAD_HANDLE;
#endif

class TsThreadManager;

class TsThreadBase
{
public:
	TsThreadBase(TsThreadManager* tm, const char* thread_name);
	virtual ~TsThreadBase();

	bool is_running(void) { return m_is_running; }

	// �����������̣߳�ִ�б������˵�run()������
	bool start(void);
	// �����̣߳��ȴ�wait_timeout_ms���룬���wait_timeout_msΪ0�������޵ȴ���
	bool stop(void);
	// ֱ�ӽ����̣߳�ǿɱ��������ʹ�ã�
	bool terminate(void);

protected:
	// �߳�ѭ��
	virtual void _thread_loop(void) = 0;
	// ����ֹͣ��־�����߳��ܹ���������
	virtual void _set_stop_flag(void) = 0;

#ifdef EX_OS_WIN32
	static unsigned int WINAPI _thread_func(LPVOID lpParam);
#else
	static void* _thread_func(void * pParam);
#endif

protected:
	TsThreadManager* m_thread_manager;
	ex_astr m_thread_name;
	TS_THREAD_HANDLE m_handle;
	bool m_is_running;
	bool m_stop_by_request;
};


// �߳�����������ʹ�ã�
class TsThreadLock
{
public:
	TsThreadLock();
	virtual ~TsThreadLock();

	void lock(void);
	void unlock(void);

private:
#ifdef EX_OS_WIN32
	CRITICAL_SECTION m_locker;
#else
	pthread_mutex_t m_locker;
#endif
};

// �߳���������
class TsThreadSmartLock
{
public:
	TsThreadSmartLock(TsThreadLock& lock) : m_lock(lock)
	{
		m_lock.lock();
	}
	~TsThreadSmartLock()
	{
		m_lock.unlock();
	}

private:
	TsThreadLock& m_lock;
};

typedef std::list<TsThreadBase*> ts_threads;

class TsThreadManager
{
	friend class TsThreadBase;

public:
	TsThreadManager();
	virtual ~TsThreadManager();

	void stop_all(void);

private:
	void _add_thread(TsThreadBase* tb);
	void _remove_thread(TsThreadBase* tb);

private:
	TsThreadLock m_lock;
	ts_threads m_threads;
};


// ԭ�Ӳ���
int ts_atomic_add(volatile int* pt, int t);
int ts_atomic_inc(volatile int* pt);
int ts_atomic_dec(volatile int* pt);

#endif // __TS_THREAD_H__
