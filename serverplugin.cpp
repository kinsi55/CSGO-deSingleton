﻿#include "engine/iserverplugin.h"
#undef MAX_VALUE //bspfile.h will declare this which breaks shit

#ifdef WIN32
#include <atlstr.h>
#else
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#endif

//-----------------------------------------------------------------------------
// Colours
//-----------------------------------------------------------------------------
#define COLOUR_YELLOW	Color(255,255,0,255)
#define COLOUR_CYAN		Color(0,255,255,255)
#define COLOUR_GREEN	Color(0,255,0,255)
#define COLOUR_RED	Color(255,0,0,255)

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CServerPlugin : public IServerPluginCallbacks
{
public:
	CServerPlugin() {};
	~CServerPlugin() {};

	// IServerPluginCallbacks methods
public:
	virtual bool			Load( CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory );
	virtual void			Unload() {};
	virtual void			Pause() {};
	virtual void			UnPause() {};
	virtual const char		*GetPluginDescription( void );
	virtual void			LevelInit( const char *pMapName ) {};
	virtual void			ServerActivate( edict_t *pEdictList, int edictCount, int clientMax ) {};
	virtual void			GameFrame( bool simulating ) {};
	virtual void			LevelShutdown() {};
	virtual void			ClientActive( edict_t *pEntity ) {};
	virtual void			ClientFullyConnect( edict_t *pEntity ) {};
	virtual void			ClientDisconnect( edict_t *pEntity ) {};
	virtual void			ClientPutInServer( edict_t *pEntity, const char *playername ) {};
	virtual void			SetCommandClient( int index ) {};
	virtual void			ClientSettingsChanged( edict_t *pEdict ) {};
	virtual PLUGIN_RESULT	ClientConnect( bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen ) { return PLUGIN_CONTINUE; }
	virtual PLUGIN_RESULT	ClientCommand( edict_t *pEntity, const CCommand &args ) { return PLUGIN_CONTINUE; }
	virtual PLUGIN_RESULT	NetworkIDValidated( const char *pszUserName, const char *pszNetworkID ) { return PLUGIN_CONTINUE; }
	virtual void			OnQueryCvarValueFinished( QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue ) {};
	virtual void			OnEdictAllocated( edict_t *edict ) {};
	virtual void			OnEdictFreed( const edict_t *edict ) {};
	virtual bool			BNetworkCryptKeyCheckRequired(uint32 unFromIP, uint16 usFromPort, uint32 unAccountIdProvidedByClient,
		bool bClientWantsToUseCryptKey) { return false; };
	virtual bool			BNetworkCryptKeyValidate(uint32 unFromIP, uint16 usFromPort, uint32 unAccountIdProvidedByClient,
		int nEncryptionKeyIndexFromClient, int numEncryptedBytesFromClient, byte* pbEncryptedBufferFromClient,
		byte* pbPlainTextKeyForNetchan) { return false; }

	// Internal interface
public:
	int						GetCommandIndex() { return m_iClientCommandIndex; }

private:
	int m_iClientCommandIndex;
};

//-----------------------------------------------------------------------------
// Singleton accessor
//-----------------------------------------------------------------------------
CServerPlugin g_Plugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CServerPlugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_Plugin);

//-----------------------------------------------------------------------------
// Purpose: called when the plugin is loaded, load the interface we need from the engine
//-----------------------------------------------------------------------------
bool CServerPlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	// Add -insecure to the CommandLine so we can't connect to VAC servers.
	// Source should already disallow us from loading clientplugins without
	// -insecure on the commandline. This is a very cautious safeguard.
	if(!CommandLine()->FindParm("-insecure"))
	{
		ConColorMsg(COLOUR_YELLOW, "\n========================================================================\n");

		ConColorMsg(COLOUR_CYAN,
			"You forgot to add \"-insecure\" to your launch options!\n\n"
			"This is a safe-guard to ensure you launch the game without VAC, and therefore disallow you from connecting to secure servers.\n"
			);

		ConColorMsg(COLOUR_YELLOW, "========================================================================\n\n");

		// Open console on startup so we don't miss the error message
		CommandLine()->AppendParm("-console", "");
		return false;
	}

#ifdef WIN32
	HANDLE handle = OpenMutex(MUTEX_ALL_ACCESS, false, "hl2_singleton_mutex");

	if (handle != NULL && ReleaseMutex(handle)) {
		ConColorMsg(COLOUR_GREEN, "[deSingleton] Released Singleton Mutex! You can start another CS:GO instance\n");
		return true;
	}
	else if(handle == NULL)
	{
		ConColorMsg(COLOUR_YELLOW, "[deSingleton] Failed to obtain Singleton Mutex handle!\n");
	}
	else 
	{
		ConColorMsg(COLOUR_YELLOW, "[deSingleton] Failed to release Singleton Mutex handle! Errorcode: %i\n", GetLastError());
	}

	return false;
#else
	int fd = open("/tmp/source_engine_2849099857.lock", O_WRONLY);
	if (fd == -1)
	{
		ConColorMsg(COLOUR_YELLOW, "[deSingleton] Failed to open the lock file\n");
		return false;
	}

	struct flock fl;
	fl.l_type = F_UNLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 1;

	if (fcntl(fd, F_SETLK, &fl) == -1)
	{
		ConColorMsg(COLOUR_YELLOW, "[deSingleton] Failed to unlock\n");
		return false;
	}

	return true;
#endif
}

//-----------------------------------------------------------------------------
// Purpose: the name of this plugin, returned in "plugin_print" command
//-----------------------------------------------------------------------------
const char *CServerPlugin::GetPluginDescription()
{
	return "deSingleton, 1.0, Kinsi55";
}