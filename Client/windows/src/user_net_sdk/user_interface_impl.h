#ifndef user_interface_impl_h__
#define user_interface_impl_h__


#include "user_interface.h"


class CNetDataLayer;
class CNetInterLayer;
class CImplTimer;
class  CUserInterfaceImpl:public IUserInterface
{
public:

	CUserInterfaceImpl();

	~CUserInterfaceImpl();

	bool InitSDK();

	int EstablishPersistentChannel();

	void RegisterPushFunc(IPushMessageOpt* pPushMessageOpt);
	void PushMessageOpt(const std::string& push_message);

	int GetResponseByRequestPersistentConnection(const std::string& request, std::string& response);

	int GetResponseByRequestShortConnection(const std::string& request, std::string& response);

	int SendAsynRequest(const int asyn_request_id, const std::string& request);

private:

	/**
	* @brief ��������������������״̬�Ƿ��������Է�������̨�𵽷�ֹ�뿪���ӵ����ã�
	* @param [in] ����״̬�ص�����
	* @return
	*/
	int HeartBeatDetect();
	/**
	* @brief ��ȡ�������������״̬�Ƿ�����
	* @return
	*/
	int GetLiveStatus();
	void StopHeartBeat();
	static void OnTimeGetLiveStatus(void* param);

private:

	CImplTimer*  implTimer_;
	LiveStatusCB liveStatusCb_;

	CNetDataLayer*	pNetDataOpt_;
	CNetInterLayer* pInterLayer_;

	IPushMessageOpt* pPushMessageOpt_;

	bool b_callback_register_;


};


#endif
