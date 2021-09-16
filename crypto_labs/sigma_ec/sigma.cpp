#include <iostream>

#include "client.h"

#define SIGNATURE_EXCHANGE(receiver, sender) \
    receiver.SetSignatureFriendKey(sender.GetName(), sender.GetSignaturePublicKey())
#define SHARED_EXCHANGE(receiver, sender) \
    receiver.SetFriendDataForSharedSecret(sender.GetName(), sender.GetDataForSharedSecret(receiver))
#define CONNECT(receiver, sender) \
    receiver.Connect(sender.GetSignatureAndData(receiver.GetName()))

int main()
{
    Client alice("Alice");
    Client bob("Bob");

    // step 0
    SIGNATURE_EXCHANGE(bob, alice);
    SIGNATURE_EXCHANGE(alice, bob);

    // step 1
    SHARED_EXCHANGE(bob, alice);
    SHARED_EXCHANGE(alice, bob);

    //step 2
    CONNECT(alice, bob);
    CONNECT(bob, alice);

    //step 3
    std::string test = "TEST! IT IS MESSAGE FOR ALICE!";
    CryptoPP::SecByteBlock cipher = bob.SendMessage(test);
    std::cout << alice.ReceiveMessage(cipher) << std::endl;

    return 0;
}

