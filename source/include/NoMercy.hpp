#pragma once
#include <cstdint>

#ifdef NOMERCY_EXPORTS
	#define NOMERCY_API __declspec(dllexport) 
#else
	#define NOMERCY_API __declspec(dllimport) 
#endif

extern "C" NOMERCY_API bool NM_Initialize(uint8_t u8NmVersion, const void* c_lpData);
extern "C" NOMERCY_API bool NM_InitializeLauncher(void* hInstance, const char* c_szLicenseCode);
extern "C" NOMERCY_API bool NM_InitializeService();
extern "C" NOMERCY_API bool NM_InitializeShadow(void* hwnd, void* hinst, char* lpszCmdLine, int nCmdShow);
extern "C" NOMERCY_API bool NM_InitializeHelper();
extern "C" NOMERCY_API bool NM_Finalize();
extern "C" NOMERCY_API void NM_ServiceMessage(int iMessageID);
extern "C" NOMERCY_API bool NM_MsgHelper(int32_t nCode, const void* c_lpMessage);
extern "C" NOMERCY_API void NM_OnTick();
extern "C" NOMERCY_API uint32_t NM_GetVersion();

namespace NoMercy
{
	typedef void(__stdcall* TNMCallback)(int Code, const char* c_szMessage, const void* lpParam);

	struct SNMTestMsgCtx
	{
		char szMessage[255];
	};
	struct SNMRedirectPtrMsgCtx
	{
		uint8_t pFuncIdx;
		void* lpFuncPointer;
	};
	struct SNMSignalMsgCtx
	{
		int32_t iSignalCode;
	};

	enum ENMSignalIDs
	{
		NM_SIG_ID_NULL = 0,
		NM_SIG_SCR_PROT_ON,
		NM_SIG_SCR_PROT_OFF,
		NM_SIG_HB_V1_SETUP,
		NM_SIG_HB_V2_SETUP,
		NM_SIG_FRM_TICK,
		NM_SIG_PTR_RDT_OK
	};

	enum NM_MESSAGE_CODES
	{
		NM_MSG_NULL = 0,
		NM_GAME_LAUNCH_ERROR,
		NM_SERVICE_LAUNCH_ERROR,
		NM_DRIVER_LAUNCH_ERROR,
		NM_NETWORK_ERROR,
		NM_GAME_STARTED,
		NM_PROTECTION_COMPLETE
	};

	enum NM_DATA_CODES
	{
		NM_DATA_NULL,

		// Test
		NM_DATA_SEND_TEST_MESSAGE = 13371337,
		NM_DATA_RECV_TEST_MESSAGE = NM_DATA_SEND_TEST_MESSAGE,

		// Pointer redirections
		NM_DATA_SEND_TRACEERROR = 1000,
		NM_DATA_SEND_NET_SEND_PROXY,
		NM_DATA_SEND_MAPPED_FILE_EXIST,
		NM_DATA_SEND_VID,
		NM_DATA_SEND_PHASE,
		NM_DATA_SEND_PLAYER_NAME,
		NM_DATA_SEND_MAPPED_FILE_HASH,
		NM_DATA_SEND_NET_SEND_SEQ,

		// Signals
		NM_DATA_SEND_SCREEN_PROTECTION_ON_SIGNAL = 2000,
		NM_DATA_SEND_SCREEN_PROTECTION_OFF_SIGNAL,

		NM_DATA_SEND_HEARTBEAT_V1_SETUP_SIGNAL,
		NM_DATA_SEND_HEARTBEAT_V2_SETUP_SIGNAL,

		NM_DATA_SEND_TICK_SIGNAL,

		NM_DATA_SEND_POINTER_REDIRECTION_COMPLETED_SIGNAL,

		// Utils
		NM_DATA_SEND_GAME_CODE = 3000,
		NM_DATA_SEND_PARENT_PROC_INFO,
		NM_DATA_SEND_USER_ID,
		NM_DATA_CHECK_FILE_SUM,
		NM_DATA_CHECK_API_HOOK,
		NM_DATA_PROTECT_FUNCTION,
		NM_DATA_PROTECT_MODULE,
		NM_DATA_SEED_PACKET_CRYPT_KEY,
		NM_DATA_ENCRYPT_CLIENT_PACKET,
		NM_DATA_DECRYPT_SERVER_PACKET,
		NM_DATA_PRINT_NOMERCY_MESSAGE,
		NM_DATA_SEND_GAME_NETWORK_INFORMATIONS,
		NM_DATA_ON_CLIENT_PACKET_RECEIVED,
		NM_DATA_SEND_CLIENT_PACKET,

		// Recv
		NM_DATA_RECV_VERSION = 4000,
		NM_DATA_RECV_IS_INITIALIZED,
		NM_DATA_RECV_SUSPECIOUS_EVENT
	};

	struct NoMercyData_V1
	{
		char szLicenseCode[255];
		uint32_t unGameVersion;
		TNMCallback lpMessageHandler;
	};
}
