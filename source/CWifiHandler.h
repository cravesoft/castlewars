#ifndef CWIFIHANDLER_H_
#define CWIFIHANDLER_H_

#include <PA9.h>
#include <sstream>
#include "MessageQueue.h"
#include "802.11.h"
#include "lobby.h"
#include "Singleton.h"
using namespace std;

// Wifi states
typedef enum {
  WIFI_STATE_INACTIVE = 0,
  WIFI_STATE_ACTIVE,
  WIFI_STATE_PLAYING,
  WIFI_STATE_WAITING
} T_WIFI_STATE;

class CWifiHandler : public Singleton<CWifiHandler> {
  friend class Singleton<CWifiHandler>;
 public:
  // Go to another state
  void goToState(const T_WIFI_STATE p_newState);
  void initialize(void);
  // Set the connection
  u8 connection();
  // Get an integer
  int getIntInfo();
  // Send an integer
  void sendIntInfo(int info);
  // Get a boolean
  bool getBoolInfo();
  // Send a boolean
  void sendBoolInfo(bool info);
 private:
  // Constructor
  CWifiHandler(void);
  // Destructor
  virtual ~CWifiHandler(void);
  // Wifi current state
  T_WIFI_STATE m_state;
  // Opponent name
  LPLOBBY_USER m_opponent;
  // Copy constructor and operator '=' forbidden
  CWifiHandler(const CWifiHandler &p_source);
  const CWifiHandler &operator=(const CWifiHandler &p_right);
};

#endif
