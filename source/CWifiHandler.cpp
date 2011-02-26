#include "CWifiHandler.h"

stringstream l_data;
LPLOBBY_USER l_from;
int l_length;

void customVBL(void) {
	IPC_RcvCompleteCheck();  // Wifi scan and receive all the data transmitted
                           // to this Nintendo DS
	LOBBY_Update();  // Updtate LibLobby
}

void reception(unsigned char *data, int length, LPLOBBY_USER from) {
  l_data.str("");
  string token((char*)data, length);
  l_data << token;
  l_length = length;
  l_from = from;
}

CWifiHandler::CWifiHandler(void) : m_state(WIFI_STATE_INACTIVE) {}

CWifiHandler::~CWifiHandler(void) {}

void CWifiHandler::initialize(void) {
  // Initialize LibLobby
  PA_WaitForVBL(); PA_WaitForVBL(); PA_WaitForVBL();
	PA_VBLFunctionInit(customVBL);
	IPC_Init();
	IPC_SetChannelCallback(0, &LWIFI_IPC_Callback);
	LOBBY_Init();
	// PA_WaitForVBL(); PA_WaitForVBL(); PA_WaitForVBL();
	LOBBY_SetStreamHandler(0x0001, &reception);
}

void CWifiHandler::goToState(const T_WIFI_STATE p_newState) {
  switch(p_newState) {
    case WIFI_STATE_INACTIVE:
      break;
    case WIFI_STATE_ACTIVE:
      break;
    default:
      break;
  }
  m_state = p_newState;
}

int CWifiHandler::getIntInfo() {
  int info;
  while(1) {
    istringstream tokenizer(l_data.str());
    l_data.str("");
    string token;
    getline(tokenizer, token, ',');
    if (strcmp ("int",token.c_str()) == 0) {
      token = "";
      getline(tokenizer, token, ',');
      std::istringstream iss(token);
      iss >> info;
      LOBBY_SendToUser(m_opponent,0x0001,(unsigned char *)"ok",2);
      return info;
    }
    PA_WaitForVBL();
  }
}

void CWifiHandler::sendIntInfo(int info) {
  ostringstream message;
  char *str;
  message.str("");
  message << "int," << (int)info;
  str = new char[message.str().length()];
  strncpy (str, message.str().c_str(), message.str().length());
  LOBBY_SendToUser(m_opponent,0x0001,
                  (unsigned char *)str,message.str().length());
  delete str;
  while(1) {
    if (strcmp ("ok",l_data.str().c_str()) == 0) {
      l_data.str("");
      return;
    }
    PA_WaitForVBL();
  }
}

bool CWifiHandler::getBoolInfo() {
  int info;
  while(1) {
    istringstream tokenizer(l_data.str());
    l_data.str("");
    string token;
    getline(tokenizer, token, ',');
    if (strcmp ("bool",token.c_str()) == 0) {
      token = "";
      getline(tokenizer, token, ',');
      std::istringstream iss(token);
      iss >> info;
      LOBBY_SendToUser(m_opponent,0x0001,(unsigned char *)"ok",2);
      return (info == 1) ? true : false;
    }
    PA_WaitForVBL();
  }
}

void CWifiHandler::sendBoolInfo(bool info) {
  int infoInteger = (info) ? 1 : 0;
  ostringstream message;
  char *str;
  message.str("");
  message << "bool," << (int)infoInteger;
  str = new char[message.str().length()];
  strncpy (str, message.str().c_str(), message.str().length());
  LOBBY_SendToUser(m_opponent,0x0001,
                  (unsigned char *)str,message.str().length());
  delete str;
  while(1) {
    if (strcmp ("ok",l_data.str().c_str()) == 0) {
      l_data.str("");
      return;
    }
    PA_WaitForVBL();
  }
}

u8 CWifiHandler::connection() {
  bool decision = false;
  int nbUser, max;
  u16 posX, posY;
  ostringstream message;
  u8 playerOrder;
  char str[256];
  //char str[]= "boule";
  while (!decision) {
	  PA_16cErase (0);
		max = LOBBY_GetNumberOfKnownUsers();
		//max = 6;
		for (nbUser = 0; nbUser < max; nbUser++) {
			LPLOBBY_USER user = LOBBY_GetUserByID(nbUser);
			message.str("");
      message << nbUser+1 << ". " << LOBBY_GetUserName(user);
      strncpy (str, message.str().c_str(), 256);
			//strncpy (str, LOBBY_GetUserName(user), strlen(LOBBY_GetUserName(user)));
			PA_16cText(0, 20, 20+28*nbUser, 255, 40, str, 1, 3, 100);
		}
  
    if (strcmp ("request",l_data.str().c_str()) == 0) {
      m_opponent = l_from;
      l_data.str("");
      playerOrder = 1;
      message.str("");
      message << "from " << LOBBY_GetUserName(m_opponent);
      strncpy (str, message.str().c_str(), 256);
      PA_16cErase (0);
      PA_16cText(0, 20, 40, 255, 60, "You have received a challenge", 1, 3,
                 100);
      PA_16cText(0, 20, 53, 255, 60, str, 1, 3, 100);
      PA_16cText(0, 40, 100, 255, 120, "Accept", 1, 3, 100);
      PA_16cText(0, 140, 100, 255, 200, "Decline", 1, 3, 100);
      while(1) {
        if (Stylus.Released) {
          posX = Stylus.X;
          posY = Stylus.Y;
          if ((posX > 37) && (posX < 91) && (posY > 96) && (posY < 113)) {
            decision = true;
            LOBBY_SendToUser(m_opponent,0x0001,(unsigned char *)"accept",7);
            break;
          }
          if ((posX > 138) && (posX < 196) && (posY > 96) && (posY < 113)) {
            decision = false;
            LOBBY_SendToUser(m_opponent,0x0001,(unsigned char *)"decline",7);
            break;
          }
        }
        PA_WaitForVBL();
      }
      PA_16cErase (0);
    } else {
  		playerOrder = 0;
      if (Stylus.Released) {
        posX = Stylus.X;
        posY = Stylus.Y;
        for (nbUser = 0; nbUser < max; nbUser++) {
          if ((posX > 20) && (posX < 256) && (posY > 20+28*nbUser) &&
              (posY < 20+28*(nbUser+1))) {
            LOBBY_SendToUser(LOBBY_GetUserByID(nbUser),0x0001,
                             (unsigned char *)"request",7);
            PA_16cErase (0);
            PA_16cText(0, 20, 40, 255, 60, "Waiting for response from", 1, 3,
                       100);
            PA_16cText(0, 20, 53, 255, 60, "your opponent...", 1, 3, 100);
            while(1) {
              if (strcmp ("accept",l_data.str().c_str()) == 0) {
                m_opponent = l_from;
                l_data.str("");
                decision = true;
                break;
              } else {
                if (strcmp ("decline",l_data.str().c_str()) == 0) {
                  l_data.str("");
                  decision = false;        
                  break;
                }
              }
              PA_WaitForVBL();
            }
            PA_16cErase (0);
            break;
          }
        }
  		}
    }
 		PA_WaitForVBL();
  }
  return playerOrder;
}
