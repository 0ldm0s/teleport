#include "ts_env.h"
#include "../common/ts_const.h"

TsEnv g_env;

TsEnv::TsEnv()
{}

TsEnv::~TsEnv()
{}

bool TsEnv::init(void)
{
	EXLOG_LEVEL(EX_LOG_LEVEL_INFO);

	ex_exec_file(m_exec_file);

	m_exec_path = m_exec_file;
	ex_dirname(m_exec_path);


	// ��λ log, etc ·��
	// Ĭ������£���������Ŀ¼��λ�ڱ���ִ�г���� ../ ���λ�ã�
	// ��������ڣ�������ǿ�������ģʽ�����Դ�Դ����ֿ��Ŀ¼�µ�shareĿ¼�в��ҡ�
	ex_wstr base_path = m_exec_path;
	ex_path_join(base_path, true, L"..", NULL);

	m_etc_path = base_path;
	ex_path_join(m_etc_path, false, L"etc", NULL);

	ex_wstr conf_file = m_etc_path;
	ex_path_join(conf_file, false, L"core.ini", NULL);

	if (!ex_is_file_exists(conf_file.c_str()))
	{
		EXLOGW("[core] ===== DEVELOPMENT MODE =====\n");
		base_path = m_exec_path;
		ex_path_join(base_path, true, L"..", L"..", L"..", L"..", L"server", L"share", NULL);

		m_etc_path = base_path;
		ex_path_join(m_etc_path, false, L"etc", NULL);

		conf_file = m_etc_path;
		ex_path_join(conf_file, false, L"core.ini", NULL);
	}

	if (!ex_is_file_exists(conf_file.c_str()))
	{
		EXLOGE("[core] core.ini not found.\n");
		return false;
	}

	if (!m_ini.LoadFromFile(conf_file))
	{
		EXLOGE("[core] can not load core.ini.\n");
		return false;
	}

	ExIniSection* ps = m_ini.GetSection(L"common");

	if (!ps->GetStr(L"replay-path", m_replay_path))
	{
		m_replay_path = base_path;
		ex_path_join(m_replay_path, false, L"data", L"replay", NULL);
	}

	ex_wstr log_file;
	if (!ps->GetStr(L"log-file", log_file))
	{
		ex_wstr log_path = base_path;
		ex_path_join(log_path, false, L"log", NULL);
		EXLOG_FILE(L"tpcore.log", log_path.c_str());
	}
	else
	{
		ex_remove_white_space(log_file);

		ex_wstr log_path = log_file;
		ex_dirname(log_path);
		ex_wstr file_name;
		file_name.assign(log_file, log_path.length() + 1, log_file.length());

		EXLOG_FILE(file_name.c_str(), log_path.c_str());
	}

	int log_level = EX_LOG_LEVEL_INFO;
	if (ps->GetInt(L"log-level", log_level))
	{
		EXLOGV("log-level: %d\n", log_level);
		EXLOG_LEVEL(log_level);
	}

	ex_wstr tmp;
	ps = m_ini.GetSection(L"rpc");
	if (!ps->GetStr(L"bind-ip", tmp))
	{
		rpc_bind_ip = TS_HTTP_RPC_HOST;
	}
	else
	{
		ex_wstr2astr(tmp, rpc_bind_ip);
	}
	if (!ps->GetInt(L"bind-port", rpc_bind_port))
	{
		rpc_bind_port = TS_HTTP_RPC_PORT;
	}

	return true;
}
