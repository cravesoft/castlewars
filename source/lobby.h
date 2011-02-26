#ifndef lobby_included
#define lobby_included

#ifdef __cplusplus
  extern "C" {
#endif

/* reasons for userinfo callback */
#define				USERINFO_REASON_REGOGNIZE			0
#define				USERINFO_REASON_TIMEOUT				1
#define				USERINFO_REASON_RETURN				2
#define				USERINFO_REASON_ROOMCREATED			3
#define				USERINFO_REASON_ROOMCHANGE			4

#define				USERID_MYSELF						0xFFFF
#define				ROOMID_MYROOM						0xFFFF

#define				ROOMFLAG_INVISIBLE					BIT(0)

/* an user */
typedef struct		LOBBY_USER LOBBY_USER, *LPLOBBY_USER ;
/* an room */
typedef struct		LOBBY_ROOM LOBBY_ROOM, *LPLOBBY_ROOM ;

/* callbacks for streamdata and userinfo */
typedef void (*		LOBBY_STREAMHANDLER_PROC		)(unsigned char *data, int length, LPLOBBY_USER from) ;
typedef void (*		LOBBY_USERINFOHANDLER_PROC		)(LPLOBBY_USER user, unsigned long reason) ;

/* start up LOBBY (needs working wifi setup) */
int					LOBBY_Init(void) ;
/* when running, the lobby needs to be updated regulary. Best to be done on VBlank */
void				LOBBY_Update(void) ;

/* functions for managing users */
/// Change the username of the local DS
/*
		At the start of the lobby, the local name is set from the firmware.
		This function can be used to change the name. 
		Maximum length is 32 chars, including the terminating zero.

*/
void				LOBBY_SetOwnName(char *name) ;


/// Retrieve a user by the ID it was recognized by
/*
		The ID represents the order of user recognizes beginning at 0\n
		The local user can be retrieved with ID=USERID_MYSELF
		/sa LOBBY_GetUserByMAC
		/return 0 if failed, valid LPLOBBY_USER otherwise
*/
LPLOBBY_USER		LOBBY_GetUserByID(unsigned short id) ;


/// Retrieve a user by the mac-address it is operating on
/*
		The mac-address is the 6-byte HW-address of the users DS\n
		The local user can not be retrieved
		/sa LOBBY_GetUserByID
		/return 0 if failed, valid LPLOBBY_USER otherwise
*/
LPLOBBY_USER		LOBBY_GetUserByMAC(unsigned char *mac) ;


/// Retrieve the number of known users
/*
		This number will never decrease. If a user gets "lost" it will\n
		be flagged as timedout, but not removed. On returning, the old ID\n
		The local user is not counted.
		will be reused.
		/sa LOBBY_GetUserByID, LOBBY_IsTimedOut
*/
unsigned short		LOBBY_GetNumberOfKnownUsers(void) ;


/// Get the user's timeout-status
/*
		If no message from a user is received within a fix timespan,\n
		the user will timeout. The ID of the user remains valid.\n
		The user might return from the timeout\n
		/return 0 - user is still active\n 1 - user was not active for some time now
*/
int					LOBBY_IsTimedOut(LPLOBBY_USER user) ;


/// Internal use only
void				LOBBY_UserResetTimeout(LPLOBBY_USER user) ;


/// Gets the name of the LPLOBBY_USER
/*
		Retrieves the name of the user. It defaults to the name\n
		specified in the DS firmware settings.\n
*/
const char *		LOBBY_GetUserName(LPLOBBY_USER user) ;


/// Gets the send status to LPLOBBY_USER for all streams
/*
		/sa LOBBY_UserIsStreamSent
		/return 0 - if there is a send pending\n 1 - if there is at least one packet sent, but not yet acknowledged as received
*/
int					LOBBY_UserIsAllSent(LPLOBBY_USER user) ;


/// Gets the send status to LPLOBBY_USER for the streamID
/*
		/sa LOBBY_UserIsAllSent
		/return 0 - if there is a send pending\n 1 - if there is at least one packet sent, but not yet acknowledged as received
*/
int					LOBBY_UserIsStreamSent(LPLOBBY_USER user,unsigned short streamID) ;


/// Create a room, with the local user as room leader
/*
		/param name: not yet used
		/param maxUsers: the allowed number of users, including the leader
		/param gameCode: an ID representing the game/author It can be assumed that all software using the same gameCode follows the same stream formats (except for version differences)
		/param gameVersion: for the author's free use
*/
void				LOBBY_CreateRoom(char *name, int maxUsers, unsigned short gameCode, unsigned short gameVersion) ;


/// Join a room as additional user
/*
		There is no direct feedback on the join.\n
		If the join succeeds, a userinfo callback is issued\n
		and LOBBY_GetRoomByID(ROOMID_MYROOM) returns a non-0\n
		If a join failed, GetRoomByID keeps returning a 0, and\n
		the room's max and current user# are equal\n
		(A Join & Wait function with return values will be supplied later)
		/param room: the room to be joined
*/
void				LOBBY_JoinRoom(LPLOBBY_ROOM room) ;


/// Leave the room the local user joined
/*
		This functionality is WIP
*/
void				LOBBY_LeaveRoom(void) ;

/// Set room visibility. Can be called only by the room leader.
/*
//		/param room: the room where to set the visibility
		/param visible: flag stating if the room is visible, 0 = not visible, 1 = visible
*/
//void				LOBBY_SetRoomVisibility(LPLOBBY_ROOM room, int visible);
void				LOBBY_SetRoomVisibility(int visible);

/// Retrieve the number of all known rooms
/*
		This functionality is WIP\n
*/
unsigned short		LOBBY_GetNumberOfKnownRooms(void) ;


/// Get a room by the recognized order
/*
		This functionality is WIP\n
*/
LPLOBBY_ROOM		LOBBY_GetRoomByID(unsigned long id) ;


/// Get a room by the mac-address it is hosted on
/*
*/
LPLOBBY_ROOM		LOBBY_GetRoomByMAC(unsigned char *mac) ;


/// Get a room by the user hosting the room
/*
*/
LPLOBBY_ROOM		LOBBY_GetRoomByUser(LPLOBBY_USER user) ;


/// Get a room by a given gamecode
/*
		/param gameCode: ID of the game/author
		/param anchor: 0 - Search for the first known room with the gameCode, or subsequently a LPLOBBY_ROOM to find the next room 
*/
LPLOBBY_ROOM		LOBBY_GetRoomByGame(LPLOBBY_ROOM anchor, unsigned short gameCode) ;


/// Retrieve the number of users currently in the room
/*
*/
unsigned short		LOBBY_GetUsercountInRoom(LPLOBBY_ROOM room) ;


/// Retrieve the number of users allowed in the room
/*
*/
unsigned short		LOBBY_GetMaxUsercountInRoom(LPLOBBY_ROOM room) ;


/// Retrieve the user within the room from 0 to maxUsers-1
/*
			The users are at the same slot for every user
*/
LPLOBBY_USER		LOBBY_GetRoomUserBySlot(LPLOBBY_ROOM room, unsigned char slot) ;


/// Retrieve the room name
/*
*/
char*		LOBBY_GetRoomName(LPLOBBY_ROOM room) ;


/// Retrieve the gameCode from the room
/*
*/
unsigned short		LOBBY_GetRoomGameCode(LPLOBBY_ROOM room) ;


/// Retrieve the gameVersion from the room
/*
*/
unsigned short		LOBBY_GetRoomGameVersion(LPLOBBY_ROOM room) ;


/* sending & receiving streams */
/// Set the routine which is receiving data of the streamID
/*
			Following streamIDs are preserved: 0xFFFF, 0x7FFF
			/param streamID: below 0x8000: All messages are sent in-order and will be delivered, except of one side timing out. other messages are "fire and forget"
			/param callback: the function to be called with the received data
*/
void				LOBBY_SetStreamHandler(unsigned short streamID, LOBBY_STREAMHANDLER_PROC callback) ;


/// Send data of a stream to a user
/*
			Note: 
				You can not send to yourself
				You can not send to timed out users
*/
void				LOBBY_SendToUser(LPLOBBY_USER user,unsigned short stream, unsigned char *data, int length) ;


/// Send data to a room
/*
			Sends to all members of the room the local user is within
			Sends to the roomleader of a room the local user is not within
*/
void				LOBBY_SendToRoom(LPLOBBY_ROOM room, unsigned short stream, unsigned char *data, int length) ;


/// Send data to all known users
/*
*/
void				LOBBY_SendToAll(unsigned short stream, unsigned char *data, int length) ;


/// Send a broadcast 
/*
			Unlike LOBBY_SendToAll, there is only one message triggered to the broadcast MAC-Address
			Only non-acked streams can be used.
*/
void				LOBBY_Broadcast(unsigned short stream, unsigned char *data, int length) ;


/* set userinfo callbacks */
void				LOBBY_SetUserInfoCallback(LOBBY_USERINFOHANDLER_PROC callback) ;

#ifdef __cplusplus
  }
#endif

#endif
