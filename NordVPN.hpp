#include <string>

const std::string kNordVPNBinary = "nordvpn";

class NordVPN {
    enum class NordVPNAction { Disconnect, Connect };

   public:
    NordVPN(void);
    ~NordVPN(void);
    bool IsConnected(void);
    void Toggle(void);

   private:
    void SetAction(NordVPNAction action);
    bool connected_;
};
