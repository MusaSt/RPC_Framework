#ifndef user_interface_h__
#define user_interface_h__

#include "user_interface_defines.h"

#ifndef UNIT_TEST

#ifdef _DLL_MODE
#define DLL_MODE_API __declspec(dllexport)
#else
#define DLL_MODE_API __declspec(dllimport)
#endif

#endif


/*ע������ͽӿڣ�ʹ���߿����Լ�ʵ���ڲ��߼� */
class IPushMessageOpt
{
public:
	virtual ~IPushMessageOpt() {};

	/**
	 * @brief sdk�ڲ����ͳ�������Ϣ(����sdk����ĳ�����Ϣ���������쳣��Ϣ��
	 * @param ��Ϣ����
	 * @param ��Ϣ����
	 */
	virtual void LocalPushMessageOpt(const int message_type, const PUSH_INFO& pushInfo) = 0;

	/**
	 * @brief ά������
	 * @param ����״̬ SUCCESSΪ���������������ӣ�
	 */
	virtual void LiveStatusCB(const int ret) = 0;

	/**
	 * @brief �첽�������Ϣ��Ӧ
	 * @param �첽���̱�ʶ
	 * @param ��Ϣ����
	 */
	virtual void AsynServerResponseOpt(const int asyn_id, const PUSH_INFO& pushInfo) = 0;

	/**
	 * @brief ������������͵���Ϣ
	 * @param ��Ϣ����
	 * @param ��Ϣ����
	 */
	virtual void ServerPushMessageOpt(const int message_type, const PUSH_INFO& pushInfo) = 0;
};


#ifndef UNIT_TEST
class  DLL_MODE_API IUserInterface
#else
class  IUserInterface
#endif
{
public:
	virtual ~IUserInterface() {}

	static IUserInterface* GetInstance();

	static void DestroyImplInstance(const IUserInterface* pImpl);

	/**
	 * @brief ��ʼ��SDK���ڴ˽ӿ�����У�������ò���ȫ��ͨ�������ļ����أ�
	 */
	virtual bool InitSDK() = 0;

	virtual void UninitSDK() = 0;


	/**
	 * @brief ע�������߼�����Init�ɹ��������ã�
	 * @param [in] ����IPushMessageOpt
	 */
	virtual void RegisterPushFunc(IPushMessageOpt* pPushMessageOpt) = 0;

	/**
	* @brief �ͷ���˽���������
	*/
	virtual int EstablishPersistentChannel() = 0;

	/**
	 * @brief Զ�̹��̵��ýӿ�ʵ��(�����ӣ������ӿڣ�
	 * @param [in]	������������ֻҪ������Э���Ӧ���ɣ�
	 * @param [out] ��Ӧ
	 */
	virtual int GetResponseByRequestPersistentConnection(const std::string& request, std::string& response) = 0;

	/**
	 * @brief Զ�̹��̵��ýӿ�ʵ��(�����ӣ������ӿڣ�
	 * @param [in]	������������ֻҪ������Э���Ӧ���ɣ�
	 * @param [out] ��Ӧ
	 */
	virtual int GetResponseByRequestShortConnection(const std::string& request, std::string& response) = 0;


	/**
	 * @brief �����첽����(���ͺ������أ��������ӿڣ���IPushMessageOpt:AsynServerResponseOpt�и����첽���̱�ʶ�����Ӧ��
	 * @param [in]	�첽���̱�ʶ(���뱣֤Ψһ��
	 * @param [in]  ����
	 */
	virtual int SendAsynRequest(const int asyn_request_id, const std::string& request) = 0;


private:

	static IUserInterface* instance_;

};

#endif // user_interface_h__